#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <utility>
#include <string>
#include "Block.h"
#include "CircularArray.h"
#include "BTree.h"
#include "ChainHash.h"
#include "Trie.h"

class Blockchain {
private:
    CircularArray<Block*> blockchain;

    ChainHash<std::string, Record*> hash_index_sender;

    ChainHash<std::string, Record*> hash_index_receiver;

    BTree<Datetime, Record*> btree_index_date;

    BTree<double, Record*> btree_index_amount;

    Trie<Record*> trie_index_sender_id;

    Trie<Record*> trie_index_receiver_id;

public:

    // HASH INDEX SENDER
    std::vector<Record*> i_hash_sender_equal_to(const std::string& key) {
        return hash_index_sender.get(key);
    }

    void i_hash_sender_delete_key(const std::string& key) {
        hash_index_sender.remove(key);
    }

    // HASH INDEX RECEIVER
    std::vector<Record*> i_hash_receiver_equal_to(const std::string& key) {
        return hash_index_receiver.get(key);
    }

    void i_hash_receiver_delete_key(const std::string& key) {
        hash_index_receiver.remove(key);
    }

    // BTREE INDEX DATE
    std::vector<Record*> i_btree_sorted_records_by_date() {
        return btree_index_date.get_sorted_elements();
    }

    std::vector<Record*> i_btree_records_in_date_range(Datetime begin, Datetime end) {
        return btree_index_date.range_search(begin, end);
    }

    std::vector<Record*> i_btree_records_in_date(Datetime date) {
        return btree_index_date.search(date);
    }

    void i_btree_date_delete_key(Datetime key) {
        auto attempts = btree_index_date.search(key).size();

        for (int i = 0; i < attempts; ++i) {
            btree_index_date.remove(key);
        }
    }

    Record* i_btree_last_record() {
        return btree_index_date.maxVal();
    }

    Record* i_btree_first_record() {
        return btree_index_date.minVal();
    }

    // BTREE INDEX AMOUNT

    std::vector<Record*> i_btree_records_in_amount_range(double begin, double end) {
        return btree_index_amount.range_search(begin, end);
    }

    void i_btree_amount_delete_key(double key) {
        auto attempts = btree_index_amount.search(key).size();

        for (int i = 0; i < attempts; ++i) {
            btree_index_amount.remove(key);
        }
    }

    Record* i_btree_max_record() {
        return btree_index_amount.maxVal();
    }

    Record* i_btree_min_record() {
        return btree_index_amount.minVal();
    }

    // TRIE INDEX SENDER
    std::vector<Record*> i_trie_sender_contains(std::string key) {
        return trie_index_sender_id.search(std::move(key));
    }

    // TRIE INDEX RECEIVER
    std::vector<Record*> i_trie_receiver_contains(std::string key) {
        return trie_index_receiver_id.search(std::move(key));
    }

    // CALCULATIONS
    double calc_total_amount_sent_by_user(const std::string& key) {
        double res = 0;

        for (auto i: hash_index_sender.get(key)) {
            res += dynamic_cast<RecordBank*>(i)->amount;
        }

        return res;
    }

    double calc_total_amount_sent() {
        double res = 0;

        for (auto i: btree_index_date.range_search(Datetime("0000-00-00 00:00:00"), Datetime("9999-99-99 99:99:99"))) {
            res += dynamic_cast<RecordBank*>(i)->amount;
        }

        return res;
    }

    double calc_total_amount_received_by_user(const std::string& key) {
        double res = 0;

        for (auto i: hash_index_receiver.get(key)) {
            res += dynamic_cast<RecordBank*>(i)->amount;
        }

        return res;
    }

    Blockchain() {
        auto genesis_block = new Block;
        genesis_block->mineBlock("GENESIS");
        blockchain.push_back(genesis_block);
    }

    void addBlock(Block* block) {
        block->mineBlock(blockchain[blockchain.size() - 1]->curr_hash);
        blockchain.push_back(block);

        for (int i = 0; i < block->maxBlockSize; ++i) {
            if (block->block_records[i] != nullptr) {
                hash_index_sender.insert(dynamic_cast<RecordBank*>(block->block_records[i])->sender_id, block->block_records[i]);
                hash_index_receiver.insert(dynamic_cast<RecordBank*>(block->block_records[i])->receiver_id, block->block_records[i]);
                btree_index_date.insert(dynamic_cast<RecordBank*>(block->block_records[i])->date, block->block_records[i]);
                trie_index_sender_id.insert(dynamic_cast<RecordBank*>(block->block_records[i])->sender_id, block->block_records[i]);
                trie_index_receiver_id.insert(dynamic_cast<RecordBank*>(block->block_records[i])->receiver_id, block->block_records[i]);
                btree_index_amount.insert(dynamic_cast<RecordBank*>(block->block_records[i])->amount, block->block_records[i]);
            }
        }
    }

    // Cambia el Record de un Block ya insertado.
    bool EXPLOIT_changeRecord(int block_index, int record_index, Record* record) {
        if (block_index >= blockchain.size() || block_index < 1 ||
            record_index >= blockchain[0]->maxBlockSize || record_index < 0) {
            return false;
        }

        delete blockchain[block_index]->block_records[record_index];
        blockchain[block_index]->block_records[record_index] = nullptr;

        blockchain[block_index]->block_records[record_index] = record;

        for (int i = block_index; i < blockchain.size(); ++i) {
            blockchain[i]->prev_hash = blockchain[i - 1]->curr_hash;
            blockchain[i]->recalculateHash();
        }

        return true;
    }

    // Elimina el Record de un Block ya insertado.
    bool EXPLOIT_deleteRecord(int block_index, int record_index) {
        if (block_index >= blockchain.size() || block_index < 1 ||
            record_index >= blockchain[0]->maxBlockSize || record_index < 0) {
            return false;
        }

        delete blockchain[block_index]->block_records[record_index];
        blockchain[block_index]->block_records[record_index] = nullptr;

        for (int i = block_index; i < blockchain.size(); ++i) {
            blockchain[i]->prev_hash = blockchain[i - 1]->curr_hash;
            blockchain[i]->recalculateHash();
        }

        return true;
    }

    // Mina todos los Blocks de la Blockchain.
    void EXPLOIT_mineAllBlockchain() {
        for (int i = 1; i < blockchain.size(); ++i) {
            if (!blockchain[i]->validateHash()) {
                blockchain[i]->mineBlock(blockchain[i - 1]->curr_hash);
            }
        }
    }

    // Comprueba que la estructura de la Blockchain no haya sido corrompida.
    bool isBlockchainExploited() {
        for (int i = 1; i < blockchain.size(); ++i) {
            if (!blockchain[i]->validateHash()) {
                return true;
            }
        }
        return false;
    }

    // Imprime todos los Blocks del Blockchain.
    friend std::ostream& operator<<(std::ostream& os, Blockchain& bc) {
        for (int i = 0; i < bc.blockchain.size(); ++i) {
            os << "------------------------------------------------------------------------------------------------\n";
            os << "BLOCK ID: " << i << "\n";
            os << *bc.blockchain[i];
        }
        os << "------------------------------------------------------------------------------------------------\n";
        return os;
    }

    std::string to_string() {
        std::string res;

        for (int i = 0; i < blockchain.size(); ++i) {
            res += "------------------------------------------------------------------------------------------------\n";
            res += "BLOCK ID: ";
            res += std::to_string(i);
            res += "\n";
            res += blockchain[i]->to_string();
        }
        res += "------------------------------------------------------------------------------------------------\n";
        return res;
    }

    ~Blockchain() {
        for (int i = 0; i < blockchain.size(); ++i) {
            delete blockchain[i];
        }
    }
};

#endif

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include "CircularArray.h"

class Blockchain {
private:
    // Los Blocks se guardarán en un CircularArray.
    CircularArray<Block*> blockchain;

public:
    // Agrega un nuevo Block al Blockchain.
    void addBlock(Block* block) {
        // Si el Block es el primero en colocarse, su hash previo será GENESIS.
        // Caso contrario, su hash previo será el hash del bloque anterior.
        if (blockchain.size() == 0) {
            block->mineBlock("GENESIS");
        } else {
            block->mineBlock(blockchain[blockchain.size() - 1]->curr_hash);
        }
        blockchain.push_back(block);
    }

    // EDUCATIVE PURPOSES
    // Cambia el Record de un Block ya insertado.
    bool EXPLOIT_changeRecord(int block_index, int record_index, Record* record) {
        if (block_index >= blockchain.size() || block_index < 0 ||
            record_index >= blockchain[0]->maxBlockSize || record_index < 0) {
            return false;
        }

        blockchain[block_index]->block_records[record_index] = record;

        for (int i = block_index; i < blockchain.size(); ++i) {
            if (i != 0) {
                blockchain[i]->prev_hash = blockchain[i - 1]->curr_hash;
            }
            blockchain[i]->recalculateHash();
        }

        return true;
    }

    // EDUCATIVE PURPOSES
    // Elimina el Record de un Block ya insertado.
    bool EXPLOIT_deleteRecord(int block_index, int record_index) {
        if (block_index >= blockchain.size() || block_index < 0 ||
            record_index >= blockchain[0]->maxBlockSize || record_index < 0) {
            return false;
        }

        delete blockchain[block_index]->block_records[record_index];
        blockchain[block_index]->block_records[record_index] = nullptr;

        for (int i = block_index; i < blockchain.size(); ++i) {
            if (i != 0) {
                blockchain[i]->prev_hash = blockchain[i - 1]->curr_hash;
            }
            blockchain[i]->recalculateHash();
        }

        return true;
    }

    // EDUCATIVE PURPOSES
    // Mina todos los Blocks de la Blockchain.
    void EXPLOIT_mineAllBlockchain() {
        for (int i = 0; i < blockchain.size(); ++i) {
            if (!blockchain[i]->validateHash()) {
                if (i == 0) {
                    blockchain[i]->mineBlock("GENESIS");
                } else {
                    blockchain[i]->mineBlock(blockchain[i - 1]->curr_hash);
                }
            }
        }
    }

    // Comprueba que la estructura de la Blockchain no haya sido corrompida.
    bool isBlockchainExploited() {
        for (int i = 0; i < blockchain.size(); ++i) {
            if (!blockchain[i]->validateHash()) {
                return true;
            }
        }
        return false;
    }

    // EDUCATIVE PURPOSES
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

    ~Blockchain() {
        for (int i = 0; i < blockchain.size(); ++i) {
            delete blockchain[i];
        }
    }
};


#endif

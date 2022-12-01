//
// Created by HP on 1/12/2022.
//
#include "Blockchain.h"

Blockchain::Blockchain() {
    auto genesis_block = new Block;
    genesis_block->mineBlock("GENESIS");
    blockchain.push_back(genesis_block);
}

// Agrega un nuevo Block al Blockchain.
void Blockchain::addBlock(Block* block) {
    block->mineBlock(blockchain[blockchain.size() - 1]->curr_hash);
    blockchain.push_back(block);
}

// EDUCATIVE PURPOSES
// Cambia el Record de un Block ya insertado.
bool Blockchain::EXPLOIT_changeRecord(int block_index, int record_index, Record* record) {
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

// EDUCATIVE PURPOSES
// Elimina el Record de un Block ya insertado.
bool Blockchain::EXPLOIT_deleteRecord(int block_index, int record_index) {
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

// EDUCATIVE PURPOSES
// Mina todos los Blocks de la Blockchain.
void Blockchain::EXPLOIT_mineAllBlockchain() {
    for (int i = 1; i < blockchain.size(); ++i) {
        if (!blockchain[i]->validateHash()) {
            blockchain[i]->mineBlock(blockchain[i - 1]->curr_hash);
        }
    }
}

// Comprueba que la estructura de la Blockchain no haya sido corrompida.
bool Blockchain::isBlockchainExploited() {
    for (int i = 1; i < blockchain.size(); ++i) {
        if (!blockchain[i]->validateHash()) {
            return true;
        }
    }
    return false;
}
Blockchain::~Blockchain() {
    for (int i = 0; i < blockchain.size(); ++i) {
        delete blockchain[i];
    }
}
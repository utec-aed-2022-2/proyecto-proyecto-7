//
// Created by HP on 1/12/2022.
//
#include "Block.h"


Block::Block() {
        proof_of_work = std::to_string(generate_random_int());
}

std::string Block::serializeBlockRecords() {
    std::string serialized_block_records;

    for (int i = 0; i < MAX_BLOCK_SIZE; ++i) {
        if (block_records[i] == nullptr) {
            serialized_block_records += "  " + std::to_string(i) + ". EMPTY RECORD" + "\n";
        } else {
            serialized_block_records += "  " + std::to_string(i) + ". " + block_records[i]->serialize() + "\n";
        }
    }
    return serialized_block_records;
}

bool Block::insertRecord(Record *record) {
    // Si el Block ya está lleno, retorna false.
    if (block_records_size == MAX_BLOCK_SIZE) {
        return false;
    }
    block_records[block_records_size] = record;
    ++block_records_size;
    recalculateHash();
    return true;
}

void Block::recalculateHash() {
    curr_hash = SHA256_string(prev_hash + serializeBlockRecords());
}

Block::~Block() {
    for (auto& block_record: block_records) {
        delete block_record;
    }
}
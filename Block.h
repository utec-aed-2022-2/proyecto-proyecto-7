#ifndef BLOCK_H
#define BLOCK_H

#include "Record.h"
#include <random>
#include "SHA256.h"
#include <utility>

SHA256 sha;

// Cantidad máxima de Records que podrá guardar un Block.
const int MAX_BLOCK_SIZE = 5;

// Rango del entero usado para el Proof Of Work.
const int MIN_POW = 11;
const int MAX_POW = 11;

// Función que genera un entero aleatorio entre cierto rango.
int generate_random_int() {
    std::random_device srd;
    std::mt19937 smt(srd());
    std::uniform_int_distribution<int> dist(MIN_POW, MAX_POW);
    return dist(smt);
}

// Permite obtener un hash de un string cualquiera.
std::string SHA256_string(const std::string& input) {
    sha.update(input);
    return SHA256::toString(sha.digest());
}

class Blockchain;

class Block {
private:
    friend class Blockchain;

    // Número con el que tendrá que empezar el hash de nuestro Block para que sea válido.
    std::string proof_of_work;

    // Creará un hash usando los datos del Block hasta que sea válido.
    void mineBlock(std::string _prev_hash) {
        prev_hash = std::move(_prev_hash);
        // Se usa un nonce para encontrar un hash válido.
        int nonce = 0;
        do {
            curr_hash = SHA256_string(prev_hash + serializeBlockRecords() + std::to_string(nonce));
            ++nonce;
        } while (!validateHash());
    }

    // Retorna si el hash del Block es válido.
    [[nodiscard]] bool validateHash() const {
        // Compara si los primeros dígitos del hash son iguales al Proof of Work.
        if (curr_hash.substr(0, proof_of_work.length()) == proof_of_work) {
            return true;
        }
        return false;
    }

public:
    const int maxBlockSize = MAX_BLOCK_SIZE;

    // Cada Block tiene un array de punteros a Records.
    Record* block_records[MAX_BLOCK_SIZE] = {nullptr};

    // Cantidad de Records no vacíos que almacena un Block en cierto momento.
    int block_records_size = 0;

    // El hash tanto del Block actual como del previo.
    std::string curr_hash;
    std::string prev_hash;

    Block();

    // Convierte y retorna en un solo string los Records de un Block.
    std::string serializeBlockRecords();

    // Insertará un Record en el Block.
    bool insertRecord(Record* record);

    // Recalcula el hash del bloque cada vez que sus datos cambian.
    void recalculateHash();

    // EDUCATIVE PURPOSES
    // Sobrecarga que permite mostrar toda sobre un Block.
    friend std::ostream& operator<<(std::ostream& os, Block& block) {
        os << "CURRENT HASH: " << block.curr_hash << "\n";
        os << "PREVIOUS HASH: " << block.prev_hash << "\n";
        os << "PROOF OF WORK: " << block.proof_of_work << "\n";
        os << "RECORDS:\n";
        os << block.serializeBlockRecords();

        return os;
    }

    // Destructor que realiza un delete por cada Record que tenga el Block.
    ~Block();
};


#endif

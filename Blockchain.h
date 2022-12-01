#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include "CircularArray.h"

class Blockchain {
private:
    // Los Blocks se guardarán en un CircularArray.
    CircularArray<Block*> blockchain;

public:
    // Creamos al bloque génesis junto al Blockchain
    Blockchain();

    // Agrega un nuevo Block al Blockchain.
    void addBlock(Block* block);

    // EDUCATIVE PURPOSES
    // Cambia el Record de un Block ya insertado.
    bool EXPLOIT_changeRecord(int block_index, int record_index, Record* record);

    // EDUCATIVE PURPOSES
    // Elimina el Record de un Block ya insertado.
    bool EXPLOIT_deleteRecord(int block_index, int record_index);

    // EDUCATIVE PURPOSES
    // Mina todos los Blocks de la Blockchain.
    void EXPLOIT_mineAllBlockchain();

    // Comprueba que la estructura de la Blockchain no haya sido corrompida.
    bool isBlockchainExploited();

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

    ~Blockchain();
};


#endif

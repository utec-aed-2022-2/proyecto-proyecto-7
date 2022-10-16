#include "pseudoapp.h"


void test_block() {
    // Se crea un nuevo bloque.
    Block b;

    // Se muestra el bloque vació.
    std::cout << "\n"
              << b << std::endl;

    // Se agregan 5 distintos registros al bloque.
    // Para este ejemplo cada bloque podrá guardar 5 registros como máximo.
    b.insertRecord(new RecordPerson("Nicolas", "Arroyo", 18));
    b.insertRecord(new RecordPerson("Ronaldo", "Flores", 18));
    b.insertRecord(new RecordPerson("Jose", "Chachi", 18));
    b.insertRecord(new RecordBank("Marcos", "Paolo", 15, "2004-12-05"));
    b.insertRecord(new RecordBank("Josue", "Renato", 500, "2012-06-27"));

    // Se muestra el bloque en cuestión.
    std::cout << "\n"
              << b << std::endl;

    // Se intenta agregar un nuevo registro cuando el bloque ya está lleno.
    // El intento debe retornar false.
    std::cout << std::boolalpha << b.insertRecord(new RecordBank("Heider", "Manuel", 865, "2013-09-02")) << std::endl;

    // Volvemos  a imprimir el bloque para comprobar que no se colocó el último registro.
    std::cout << "\n"
              << b << std::endl;
}

void test_blockchain() {
    // Creamos un objeto blockchain.
    Blockchain blockchain;

    // Se crea un bloque y se le añade distintos datos.
    auto block_1 = new Block;
    block_1->insertRecord(new RecordBank("Nicolas", "Josue", 150, "2020-12-23"));

    // Se crea un bloque y se le añade distintos datos.
    auto block_2 = new Block;
    block_2->insertRecord(new RecordBank("Nicolas", "Josue", 150, "2020-12-23"));
    block_2->insertRecord(new RecordBank("Nicolas", "Josue", 150, "2020-12-23"));

    // Se crea un bloque y se le añade distintos datos.
    auto block_3 = new Block;
    block_3->insertRecord(new RecordBank("Nicolas", "Josue", 150, "2020-12-23"));
    block_3->insertRecord(new RecordBank("Nicolas", "Josue", 150, "2020-12-23"));
    block_3->insertRecord(new RecordBank("Nicolas", "Josue", 150, "2020-12-23"));

    // Agregamos los bloques al blockchain.
    blockchain.addBlock(block_1);
    blockchain.addBlock(block_2);
    blockchain.addBlock(block_3);

    // Imprimimos la blockchain.
    std::cout << blockchain;

    // Comprobamos la integridad de nuestra blockchain.
    std::cout << "Is blockchain exploited ?: " << std::boolalpha << blockchain.isBlockchainExploited() << std::endl;

    // EXPLOIT Cambiamos registros de nuestra blockchain.
    blockchain.EXPLOIT_changeRecord(0, 0, new RecordBank("Nicolas", "Hacker", 1000000, "2020-12-23"));
    blockchain.EXPLOIT_changeRecord(0, 4, new RecordBank("Nicolas", "Hacker", 1000000, "2020-12-23"));

    // EXPLOIT Cambiamos registros de nuestra blockchain.
    blockchain.EXPLOIT_deleteRecord(1, 1);

    // Imprimimos la blockchain y comprobamos su integridad.
    std::cout << blockchain;
    std::cout << "Is blockchain exploited ?: " << std::boolalpha << blockchain.isBlockchainExploited() << std::endl;

    // EXPLOIT Minamos toda la blockchain maliciosamente para no dejar evidencia de los cambios realizados.
    blockchain.EXPLOIT_mineAllBlockchain();
    // Imprimimos la blockchain y comprobamos su integridad.
    std::cout << blockchain;
    std::cout << "Is blockchain exploited ?: " << std::boolalpha << blockchain.isBlockchainExploited() << std::endl;
}

void test_blockchain_v2() {
    // Creamos un objeto blockchain.
    Blockchain blockchain;

    for (int i = 0; i < 50; ++i) {
        auto block = new Block;
        block->insertRecord(
                new RecordBank("Sender" + std::to_string(i), "Receiver" + std::to_string(i), i, "2000-01-01"));
        block->insertRecord(new RecordPerson("Person" + std::to_string(i), "Person" + std::to_string(i), 18));
        blockchain.addBlock(block);
    }

    // Mostramos la blockchain y verificamos su integridad.
    std::cout << blockchain;
    std::cout << "Is blockchain exploited ?: " << std::boolalpha << blockchain.isBlockchainExploited() << std::endl;
}

int main() {
    //    test_block();
    //    test_blockchain();
    //    test_blockchain_v2();
    //    mainMenu(); // Leer parte final del README
}

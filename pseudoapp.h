#ifndef PSEUDOAPP_H
#define PSEUDOAPP_H

#include "Blockchain.h"
#include <iostream>
#include <vector>

Blockchain my_bc;

void mainMenu();

void blockCreationMenu() {
    int selection;
    auto my_b = new Block;

    do {
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1. Add Bank Record" << std::endl;
        std::cout << "2. Add Block to Blockchain" << std::endl;
        std::cout << "3. Back" << std::endl;
        std::cout << "Select option: ";
        std::cin >> selection;
        std::cout << "---------------------------------------------------" << std::endl;

        if (selection == 1) {
            std::string sender;
            std::string receiver;
            double amount;
            std::string date;

            std::cout << "---------------------------------------------------" << std::endl;
            std::cout << "Sender: ";
            std::cin >> sender;
            std::cout << "Receiver: ";
            std::cin >> receiver;
            std::cout << "Amount: ";
            std::cin >> amount;
            std::cout << "Date: ";
            std::cin >> date;
            std::cout << "---------------------------------------------------" << std::endl;

            my_b->insertRecord(new RecordBank(sender, receiver, amount, date));
        }
    } while (selection == 1);

    if (selection == 2) {
        my_bc.addBlock(my_b);
        mainMenu();
    }
    if (selection == 3) {
        mainMenu();
    }
}

void mainMenu() {
    int selection;

    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "1. Create Block" << std::endl;
    std::cout << "2. Show Blockchain" << std::endl;
    std::cout << "3. Exit App" << std::endl;
    std::cout << "Select option: ";
    std::cin >> selection;
    std::cout << "---------------------------------------------------" << std::endl;

    if (selection == 1) {
        blockCreationMenu();
    }
    else if (selection == 2) {
        std::cout << my_bc;
        mainMenu();
    }
    else if (selection == 3) {
        return;
    }
}

#endif
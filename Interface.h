#ifndef V2_INTERFACE_H
#define V2_INTERFACE_H

#include <iostream>
#include "Blockchain.h"

void main_menu(Blockchain& bc);

double to_number(const std::string& str) {
    std::istringstream iss(str);
    double num = 0;
    iss >> num;
    return num;
}

void get_data(Blockchain& bc) {
    std::vector<std::string> senders_vector, receivers_vector, dates_vector;
    std::vector<double> amounts_vector;
    std::ifstream file("C:/Users/Lenovo/Desktop/UTEC/CuartoCiclo/AED/proyecto-final/v1/data.csv");

    std::string tmp_sender;
    std::string tmp_receiver;
    std::string tmp_amount;
    std::string tmp_date;
    std::string line;
    double tmp_amount_d;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::getline(iss, tmp_sender, ',');
        std::getline(iss, tmp_receiver, ',');
        std::getline(iss, tmp_amount, ',');
        std::getline(iss, tmp_date, ',');
        tmp_amount_d = to_number(tmp_amount);
        senders_vector.push_back(tmp_sender);
        receivers_vector.push_back(tmp_receiver);
        amounts_vector.push_back(tmp_amount_d);
        dates_vector.push_back(tmp_date);
    }

    file.close();

    int ctr = 0;
    for (int j = 0; j < 10; ++j) {
        auto b = new Block;
        for (int k = 0; k < 5; ++k) {
            b->insertRecord(new RecordBank(senders_vector[ctr], receivers_vector[ctr], amounts_vector[ctr], dates_vector[ctr]));
            ++ctr;
        }
        bc.addBlock(b);
    }
}

void main_menu(Blockchain& bc) {
    while (true) {
        int option;
        std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
        std::cout << std::endl;
        std::cout << "MENU PRINCIPAL" << std::endl;
        std::cout << std::endl;
        std::cout << "0.  Salir" << std::endl;
        std::cout << "1.  Mostrar blockchain" << std::endl;
        std::cout << "2.  Cargar mock data" << std::endl;
        std::cout << std::endl;
        std::cout << "3.  Calcular monto total enviado" << std::endl;
        std::cout << "4.  Calcular monto total enviado por usuario en especifico" << std::endl;
        std::cout << "5.  Calcular monto total recibido por usuario en especifico" << std::endl;
        std::cout << std::endl;
        std::cout << "6.  Mostrar registros en orden cronologico" << std::endl;
        std::cout << "7.  Mostrar registros en fecha especifica" << std::endl;
        std::cout << "8.  Mostrar registros en rango de fechas" << std::endl;
        std::cout << "9.  Mostrar registros hechos por un usuario en especifico" << std::endl;
        std::cout << "10. Mostrar registros recibidos por un usuario en especifico" << std::endl;
        std::cout << "11. Mostrar registros en rango de montos" << std::endl;
        std::cout << "12. Mostrar registros enviados por un usuario cuyo nombre incluye a" << std::endl;
        std::cout << "13. Mostrar registros recibidos por un usuario cuyo nombre incluye a" << std::endl;
        std::cout << std::endl;
        std::cout << "14. Borrar nombre del indice Hash sender" << std::endl;
        std::cout << "15. Borrar nombre del indice Hash receiver" << std::endl;
        std::cout << "16. Borrar fecha del indice BTree de fechas" << std::endl;
        std::cout << "17. Borrar monto del indice BTree de montos" << std::endl;
        std::cout << std::endl;
        std::cout << "18. Exploit - Minar blockchain" << std::endl;
        std::cout << "19. Exploit - Modificar registro" << std::endl;
        std::cout << std::endl;
        std::cout << "20. Agregar bloque" << std::endl;
        std::cout << std::endl;
        std::cout << "Opcion elegida: ";
        std::cin >> option;
        std::cout << std::endl;
        std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;

        if (option == 0) {
            return;
        }
        else if (option == 1) {
            std::cout << bc;
        }
        else if (option == 2) {
            get_data(bc);
        }
        else if (option == 3) {
            std::cout << "Monto total: " << bc.calc_total_amount_sent() << std::endl;
        }
        else if (option == 4) {
            std::string user;
            std::cout << "Usuario: ";
            std::cin >> user;
            std::cout << "Monto total enviado por " << user << ": " << bc.calc_total_amount_sent_by_user(user) << std::endl;
        }
        else if (option == 5) {
            std::string user;
            std::cout << "Usuario: ";
            std::cin >> user;
            std::cout << "Monto total recibido por " << user << ": " << bc.calc_total_amount_received_by_user(user) << std::endl;
        }
        else if (option == 6) {
            std::cout << "Sender, Receiver, Amount, Date" << std::endl;
            for (const auto& i: bc.i_btree_sorted_records_by_date()) {
                std::cout << i->serialize() << std::endl;
            }
        }
        else if (option == 7) {
            std::string date;
            std::cout << "Fecha especifica (YYYY-MM-DD HH-MM-SS): ";
            std::cin.ignore();
            std::getline(std::cin, date);
            for (auto i: bc.i_btree_records_in_date(Datetime(date))) {
                std::cout << i->serialize() << std::endl;
            }
        }
        else if (option == 8) {
            std::string date_range;
            std::cout << "Rango de fechas (YYYY-MM-DD HH-MM-SS YYYY-MM-DD HH-MM-SS): ";
            std::cin.ignore();
            std::getline(std::cin, date_range);

            for (const auto& i: bc.i_btree_records_in_date_range(Datetime(date_range.substr(0, 19)), Datetime(date_range.substr(20, 39)))) {
                std::cout << i->serialize() << std::endl;
            }
        }
        else if (option == 9) {
            std::string user;
            std::cout << "Usuario: ";
            std::cin >> user;
            for (const auto& i: bc.i_hash_sender_equal_to(user)) {
                std::cout << i->serialize() << std::endl;
            }
        }
        else if (option == 10) {
            std::string user;
            std::cout << "Usuario: ";
            std::cin >> user;
            for (const auto& i: bc.i_hash_receiver_equal_to(user)) {
                std::cout << i->serialize() << std::endl;
            }
        }
        else if (option == 11) {
            double amount_range_1;
            double amount_range_2;

            std::cout << "Monto base: ";
            std::cin >> amount_range_1;
            std::cout << "Monto limite: ";
            std::cin >> amount_range_2;

            for (const auto& i: bc.i_btree_records_in_amount_range(amount_range_1, amount_range_2)) {
                std::cout << i->serialize() << std::endl;
            }
        }
        else if (option == 12) {
            std::string user;
            std::cout << "Usuario: ";
            std::cin >> user;
            for (const auto& i: bc.i_trie_sender_contains(user)) {
                std::cout << i->serialize() << std::endl;
            }
        }
        else if (option == 13) {
            std::string user;
            std::cout << "Usuario: ";
            std::cin >> user;
            for (const auto& i: bc.i_trie_receiver_contains(user)) {
                std::cout << i->serialize() << std::endl;
            }
        }
        else if (option == 14) {
            std::string user;
            std::cout << "Usuario: ";
            std::cin >> user;
            bc.i_hash_sender_delete_key(user);
        }
        else if (option == 15) {
            std::string user;
            std::cout << "Usuario: ";
            std::cin >> user;
            bc.i_hash_receiver_delete_key(user);
        }
        else if (option == 16) {
            std::string date;
            std::cout << "Fecha especifica (YYYY-MM-DD HH-MM-SS): ";
            std::cin.ignore();
            std::getline(std::cin, date);
            bc.i_btree_date_delete_key(Datetime(date));
        }
        else if (option == 17) {
            double amount;
            std::cout << "Monto especifico: ";
            std::cin >> amount;
            bc.i_btree_amount_delete_key(amount);
        }
        else if (option == 18) {
            bc.EXPLOIT_mineAllBlockchain();
        }
        else if (option == 19) {
            int block_id;
            int record_id;
            std::string sender;
            std::string receiver;
            double amount;
            std::string date;

            std::cout << "Block id: ";
            std::cin >> block_id;
            std::cout << "Record id: ";
            std::cin >> record_id;
            std::cout << "Sender id: ";
            std::cin >> sender;
            std::cout << "Receiver id: ";
            std::cin >> receiver;
            std::cout << "Amount: ";
            std::cin >> amount;
            std::cout << "Date: ";
            std::cin.ignore();
            std::getline(std::cin, date);

            bc.EXPLOIT_changeRecord(block_id, record_id, new RecordBank(sender, receiver, amount, date));
        }
        else if (option == 20) {
            int n_records;
            std::cout << "Number of records (0-5): ";
            std::cin >> n_records;
            auto b = new Block;

            for (int i = 0; i < n_records; ++i) {
                std::string sender;
                std::string receiver;
                double amount;
                std::string date;

                std::cout << "Sender id: ";
                std::cin >> sender;
                std::cout << "Receiver id: ";
                std::cin >> receiver;
                std::cout << "Amount: ";
                std::cin >> amount;
                std::cout << "Date: ";
                std::cin.ignore();
                std::getline(std::cin, date);

                b->insertRecord(new RecordBank(sender, receiver, amount, date));
            }

            bc.addBlock(b);
        }
    }

}

#endif

#include "gui.h"
#include <QApplication>
#include "Blockchain.h"
#include <functional>
#include <utility>
#include <sstream>
#include "BTree.h"
#include <cmath>
#include <fstream>

double to_number(const std::string& str) {
    std::istringstream iss(str);
    double num = 0;
    iss >> num;
    return num;
}

void get_data(Blockchain& bc) {
    std::vector<std::string> senders_vector, receivers_vector, dates_vector;
    std::vector<double> amounts_vector;
    std::ifstream file("C:/Users/juand/Google Drive/UTEC/2022-2/AED/PF/PF_Frontend_ADS/gui/data.csv");

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



int main(int argc, char *argv[])
{
    Blockchain blockchain;
    get_data(blockchain);
    QApplication a(argc, argv);
    gui w;
    w.show();
    return a.exec();
//    std::cout<<blockchain.to_string();
//    return 0;
}





//int main() {
//    Blockchain blockchain;
//    get_data(blockchain);

    // SHOW BLOCKCHAIN IN CONSOLE
//    std::cout << blockchain;

    // CALC: SHOW TOTAL AMOUNT SENT BY AN SPECIFIC USER
//    std::cout << blockchain.calc_total_amount_sent_by_user("Heider") << std::endl;

    // CALC: SHOW TOTAL AMOUNT RECEIVED BY AN SPECIFIC USER
//    std::cout << blockchain.calc_total_amount_received_by_user("Heider") << std::endl;

    // INDEX: SHOW RECORDS THAT SENDER ID CONTAINS SUBSTRING
//    for (const auto& i: blockchain.i_trie_sender_contains("He")) {
//        std::cout << i->serialize() << std::endl;
//    }

    // INDEX: SHOW RECORDS THAT RECEIVER ID CONTAINS SUBSTRING
//    for (const auto& i: blockchain.i_trie_receiver_contains("He")) {
//        std::cout << i->serialize() << std::endl;
//    }

    // INDEX: SHOW RECORDS SORTED BY DATE
//    for (const auto& i: blockchain.i_btree_sorted_records_by_date()) {
//        std::cout << i->serialize() << std::endl;
//    }

    // INDEX: SHOW RECORDS IN GIVEN DATE RANGE
//    for (const auto& i: blockchain.i_btree_records_in_date_range(Datetime("2018-01-01 00:00:00"), Datetime("2019-01-01 00:00:00"))) {
//        std::cout << i->serialize() << std::endl;
//    }

    // INDEX: SHOW RECORDS IN GIVEN DATE
//    for (const auto& i: blockchain.i_btree_records_in_date(Datetime("2020-12-01 12:46:00"))) {
//        std::cout << i->serialize() << std::endl;
//    }

    // INDEX: SHOW RECORDS MADE BY GIVEN NAME
//    for (const auto& i: blockchain.i_hash_sender_equal_to("Heider")) {
//        std::cout << i->serialize() << std::endl;
//    }

//    blockchain.i_hash_sender_delete_key("Heider");
//    std::cout << "-------------------------------------------------" << std::endl;

//    for (const auto& i: blockchain.i_hash_sender_equal_to("Heider")) {
//        std::cout << i->serialize() << std::endl;
//    }

    // INDEX: SHOW RECORDS RECEIVED BY GIVEN NAME
//    for (const auto& i: blockchain.i_hash_receiver_equal_to("Heider")) {
//        std::cout << i->serialize() << std::endl;
//    }

//    blockchain.i_hash_receiver_delete_key("Heider");
//    std::cout << "-------------------------------------------------" << std::endl;

//    for (const auto& i: blockchain.i_hash_receiver_equal_to("Heider")) {
//        std::cout << i->serialize() << std::endl;
//    }
//}


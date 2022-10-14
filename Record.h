#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>
#include <utility>

struct Record {
    virtual std::string serialize() = 0;
};

struct RecordBank : public Record {
    std::string sender_id;
    std::string receiver_id;
    double amount;
    std::string date;

    RecordBank(std::string sender_id, std::string receiver_id, double amount, std::string date) : sender_id(std::move(sender_id)),
                                                                                                  receiver_id(std::move(receiver_id)),
                                                                                                  amount(amount),
                                                                                                  date(std::move(date)) {}

    std::string serialize() override {
        std::string formatted;

        formatted += sender_id + ", ";
        formatted += receiver_id + ", ";
        formatted += std::to_string(amount) + ", ";
        formatted += date;

        return formatted;
    }
};

#endif
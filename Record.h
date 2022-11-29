#ifndef V1_RECORD_H
#define V1_RECORD_H

#include <iostream>
#include <string>
#include "tuple"

struct Datetime {
    int year;

    int month;

    int day;

    int hour;

    int minute;

    int second;

    Datetime() = default;

    explicit Datetime(const std::string& date) {
        year = std::stoi(date.substr(0, 4));
        month = std::stoi(date.substr(5, 7));
        day = std::stoi(date.substr(8, 10));
        hour = std::stoi(date.substr(11, 13));
        minute = std::stoi(date.substr(14, 16));
        second = std::stoi(date.substr(17, 19));
    }

    bool operator<(Datetime const& other) {
        return std::tie(year, month, day, hour, minute, second) <
               std::tie(other.year, other.month, other.day, other.hour, other.minute, other.second);
    }

    bool operator<=(Datetime const& other) {
        return std::tie(year, month, day, hour, minute, second) <=
               std::tie(other.year, other.month, other.day, other.hour, other.minute, other.second);
    }

    bool operator>(Datetime const& other) {
        return std::tie(year, month, day, hour, minute, second) >
               std::tie(other.year, other.month, other.day, other.hour, other.minute, other.second);
    }

    bool operator>=(Datetime const& other) {
        return std::tie(year, month, day, hour, minute, second) >=
               std::tie(other.year, other.month, other.day, other.hour, other.minute, other.second);
    }

    bool operator==(Datetime const& other) {
        return std::tie(year, month, day, hour, minute, second) ==
               std::tie(other.year, other.month, other.day, other.hour, other.minute, other.second);
    }

    friend std::ostream& operator<<(std::ostream& os, const Datetime& dt);
};

std::ostream& operator<<(std::ostream& os, const Datetime& dt) {
    os << dt.year << "-" << dt.month << "-" << dt.day << " " << dt.hour << ":" << dt.minute << ":" << dt.second;
    return os;
}

struct Record {
    virtual std::string serialize() = 0;

    virtual ~Record() = default;
};

struct RecordBank : public Record {
    std::string sender_id; // Hash

    std::string receiver_id; // Hash

    double amount; // BTree

    Datetime date; // Btree

    RecordBank(std::string sender_id, std::string receiver_id, double amount, const std::string& date) :
            sender_id(std::move(sender_id)),
            receiver_id(std::move(receiver_id)),
            amount(amount),
            date(date) {}

    std::string serialize() override {
        std::string formatted;

        formatted += sender_id + ", ";
        formatted += receiver_id + ", ";
        formatted += std::to_string(amount) + ", ";
        formatted += std::to_string(date.year) + "-";
        formatted += std::to_string(date.month) + "-";
        formatted += std::to_string(date.day) + " ";
        formatted += std::to_string(date.hour) + ":";
        formatted += std::to_string(date.minute) + ":";
        formatted += std::to_string(date.second);

        return formatted;
    }

    friend std::ostream& operator<<(std::ostream& os, const RecordBank& dt);
};

std::ostream& operator<<(std::ostream& os, const RecordBank& dt) {
    os << dt.sender_id << " | " << dt.receiver_id << " | " << dt.amount << " | " << dt.date;
    return os;
}

#endif

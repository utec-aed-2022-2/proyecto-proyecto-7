#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>
#include <utility>

// Estructura virtual que representa a un registro.
struct Record {
    // Sus datos podrán ser serializados.
    virtual std::string serialize() = 0;
    virtual ~Record() = default;
};

// Estructura hija que representa el registro de un banco.
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

// Estructura hija que representa el registro de una persona.
struct RecordPerson : public Record {
    std::string nombres;
    std::string apellidos;
    int edad;

    RecordPerson(std::string nombres, std::string apellidos, int edad) : nombres(std::move(nombres)),
                                                                         apellidos(std::move(apellidos)),
                                                                         edad(edad){};

    std::string serialize() override {
        std::string formatted;

        formatted += nombres + ", ";
        formatted += apellidos + ", ";
        formatted += std::to_string(edad);

        return formatted;
    }
};

#endif
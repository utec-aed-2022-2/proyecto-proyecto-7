#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>
#include <utility>

struct Record {
    virtual std::string serialize() = 0;
};

#endif
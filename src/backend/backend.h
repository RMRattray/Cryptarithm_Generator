#ifndef BACKEND_H
#define BACKEND_H

#include <vector>
#include <string>

enum Operation {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION
};

struct request_data
{
    Operation op;
    std::vector<std::string> factors;
};

std::vector<std::string> find_cryptarithms(request_data req);
void do_arithmetic();


#endif
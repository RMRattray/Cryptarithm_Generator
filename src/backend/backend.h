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
    int factor_count;
    int blank;
    std::vector<std::string> factors;
};


#endif
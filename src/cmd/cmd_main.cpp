#include "backend.h"
#include <vector>
#include <string>

int main(int argc, char ** argv) {
    if (argc < 4) return EXIT_FAILURE;

    request_data main_req;
    switch (argv[1][0])
    {
    case '+':
        main_req.op = Operation::ADDITION;
        break;
    case '-':
        main_req.op = Operation::SUBTRACTION;
        break;
    case '*':
        main_req.op = Operation::MULTIPLICATION;
        break;
    default:
        return EXIT_FAILURE;
    }

    int a = 2;
    while (a < argc) {
        std::string factor = std::string(argv[a]);
        main_req.factors.push_back(factor);
        ++a;
    }

    find_cryptarithms(main_req);
}
#include <iostream>
#include <string>
#include <vector>
#include "backend.h"
#include "finder.h"

int main(int argc, char ** argv) {
    if (argc < 4) {
        std::cout << "Correct usage:\ncryptarithm_cmd.exe op word1 word2...\nExample\ncryptarithm_cmd.exe + send more";
        return EXIT_FAILURE;
    }

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
        std::cout << "Operation must be +, -, or *\n";
        return EXIT_FAILURE;
    }

    int a = 2;
    while (a < argc) {
        std::string factor = std::string(argv[a]);
        main_req.factors.push_back(factor);
        ++a;
    }

    cryptarithm::Finder f;
    auto w = f.find_cryptarithms(main_req);
    for (std::string search_string : w) {
        std::cout << search_string << std::endl;
    }
}
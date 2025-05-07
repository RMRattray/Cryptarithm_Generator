#include <iostream>
#include <string>
#include <vector>
#include "../backend/backend.h"
#include "../backend/finder.h"

int main(int argc, char ** argv) {
    if (argc < 5) {
        std::cout << "Correct usage:\ncryptarithm_cmd.exe ex op word1 word2...\nExample\ncryptarithm_cmd.exe ! + send more";
        return EXIT_FAILURE;
    }

    request_data main_req;
    switch (argv[2][0])
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

    int a = 3;
    while (a < argc) {
        std::string factor = std::string(argv[a]);
        main_req.factors.push_back(factor);
        ++a;
    }

    cryptarithm::Finder f;
    auto w = f.find_cryptarithms(main_req, (argv[1][0] == '!'));
    for (std::string search_string : w) {
        std::cout << search_string << std::endl;
    }
    f.read_words("words.txt");
}
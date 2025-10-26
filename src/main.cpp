#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <optional>

#include "tokeniser.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Incorrect usage! Correct usage is cynda <input.cy>\n";
        return 1; 
    }

    // read file contents into string
    std::ifstream input(argv[1]);
    std::stringstream buffer;
    buffer << input.rdbuf();
    std::string code_str = buffer.str();
    input.close();

    Tokeniser t(std::move(code_str));
    std::vector<Token> tokens = t.tokenise();

    std::cout << "Finished" << std::endl;

    return 0;
}

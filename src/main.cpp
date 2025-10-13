#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <optional>
#include <cctype>
#include <cstdlib>

enum class TokenType {
    _return,
    int_lit,
    semi
};

struct Token {
    TokenType type;
    std::optional<std::string> value;
};

std::vector<Token> tokenise(const std::string& code) {
    std::vector<Token> tokens{};
    std::string buf{};

    for (int i = 0; i < code.length(); i++) {
        char start = code.at(i);
        // check for identifier
        // make sure the first character is an alphabet
        if (std::isalpha(start)) {
            // rest of identifier can be alphanumeric
            while (i < code.length() && std::isalnum(code.at(i))) {
                buf += code.at(i);
                i++;
            }
            // bring back 1 to account for for loop incrementation
            i--;
            
            if (buf == "return") {
                Token tok{.type = TokenType::_return};
                tokens.push_back(tok);
            } else {
                std::cerr << "INVALID TOKEN!" << std::endl;
                // exits with error code 1
                exit(1);
            }
            
        } else if(std::isdigit(start)) {
            // if number, get all digits
            while (std::isdigit(code.at(i))) {
                buf.push_back(code.at(i));
                i++;
            }
            // bring back 1 to account for for loop incrementation
            i--;

            Token tok{.type = TokenType::int_lit, .value = buf};
            tokens.push_back(tok);
        } else if (ispunct(start)) {

            if (code.at(i) == ';') {
                tokens.push_back({.type = TokenType::semi});
            } else {
                std::cerr << "INVALID TOKEN!" << std::endl;
                // exits with error code 1
                exit(1);
            }

        } else if(std::isspace(start)) {
            // handle spaces etc.
        } else {
            std::cerr << "INVALID CHARACTER!" << std::endl;
            // exits with error code 1
            exit(1);
        }
        // clear buffer for next token
        buf.clear();
    }

    return tokens;
    
}

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

    tokenise(code_str);

    std::cout << "Finished" << std::endl;

    return 0;
}

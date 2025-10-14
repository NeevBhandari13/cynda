#include <vector>
#include <iostream>

#include "tokeniser.hpp"

Tokeniser::Tokeniser(const std::string& src)
    : m_src(src) // member initialiser list, has to be used for const variable
    {}

std::vector<Token> Tokeniser::tokenise() {
    std::vector<Token> tokens{};
    std::string buf{};

    for (int i = 0; i < m_src.length(); i++) {
        char start = m_src.at(i);
        // check for identifier
        // make sure the first character is an alphabet
        if (std::isalpha(start)) {
            // rest of identifier can be alphanumeric
            while (i < m_src.length() && std::isalnum(m_src.at(i))) {
                buf += m_src.at(i);
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
            while (std::isdigit(m_src.at(i))) {
                buf.push_back(m_src.at(i));
                i++;
            }
            // bring back 1 to account for for loop incrementation
            i--;

            Token tok{.type = TokenType::int_lit, .value = buf};
            tokens.push_back(tok);
        } else if (ispunct(start)) {

            if (m_src.at(i) == ';') {
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


#include <vector>
#include <iostream>

#include "tokeniser.hpp"

Tokeniser::Tokeniser(const std::string& src)
    : m_src(src) // member initialiser list, has to be used for const variable
    {
        
    }

std::vector<Token> Tokeniser::tokenise() {
    std::vector<Token> tokens{};
    std::string buf{};

    while (peek().has_value()) {
        // keyword case
        if (std::isalpha(peek().value())) {
            buf.push_back(consume());
            while (peek().has_value() && std::isalnum(peek().value())) {
                buf.push_back(consume());
            }
            if (buf == "return") {
                Token tok{.type = TokenType::_return};
                tokens.push_back(tok);
            } else {
                std::cerr << "INVALID TOKEN! " << buf << std::endl;
                // exits with error code 1
                exit(1);
            }
        // integer literal case
        } else if (std::isdigit(peek().value())) {
            buf.push_back(consume());
            while (peek().has_value() && std::isdigit(peek().value())) {
                buf.push_back(consume());
            }
            Token tok{.type = TokenType::int_lit, .value = buf};
            tokens.push_back(tok);
        } else if (std::ispunct(peek().value())) {
            buf.push_back(consume());

            if (buf == ";") {
                tokens.push_back({.type = TokenType::semi});
            } else {
                std::cerr << "INVALID TOKEN! " << buf << std::endl;
                // exits with error code 1
                exit(1);
            }

        } else if(std::isspace(peek().value())) {
            // handle spaces etc.
            consume();
        } else {
            std::cerr << "INVALID CHARACTER! " << peek().value() << std::endl;
            // exits with error code 1
            exit(1);
        }
        // clear buffer for next token
        buf.clear();
    }

    return tokens;
    
}

std::optional<char> Tokeniser::peek(int ahead) const {
        if (m_index + ahead >= m_src.length()) {
            return {};
        } else {
            return m_src.at(m_index + ahead);
        }
    }

char Tokeniser::consume() {
        char cur = m_src.at(m_index);
        m_index++;
        return cur;
    }


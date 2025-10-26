#pragma once

#include <string>
#include <optional>
#include <vector>

enum class TokenType {
    _return,
    int_lit,
    semi
};

struct Token {
    TokenType type;
    std::optional<std::string> value;
};

class Tokeniser {
public:
    Tokeniser(const std::string& src);

    std::vector<Token> tokenise();


private:
    const std::string m_src;
    int m_index = 0;

    std::optional<char> peek(int ahead = 0) const;

    char consume();


};

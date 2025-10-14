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
};

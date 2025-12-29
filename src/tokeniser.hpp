#pragma once

#include <string>
#include <optional>
#include <vector>

enum class TokenType {
    _return,
    int_lit,
    semi,
    open_curly_brace,
    close_curly_brace
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

    std::optional<char> peek(int offset = 0) const;

    char consume();


};

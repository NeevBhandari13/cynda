# pragma once

#include "tokeniser.hpp"

enum class NodeType {
    Return,
    IntLit,
    Main,
    Expr
};

struct ExprNode {
    Token m_expression;
};

struct ReturnNode {
    ExprNode m_retVal;
};

class Parser {
    public:
        Parser(std::vector<Token> tokens);

    private: 
        const std::vector<Token> m_tokens;
        int m_index;

        std::optional<ExprNode> parseExpr();

        std::optional<ReturnNode> parseReturn();

        bool parseSemi();

        std::optional<Token> peek(int offset = 0);

        Token consume();

};

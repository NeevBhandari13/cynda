#include <iostream>

#include "parser.hpp"

Parser::Parser(std::vector<Token> tokens)
        : m_tokens(std::move(tokens))
        {};

std::optional<ExprNode> Parser::parseExpr() {
    if (peek().value().type == TokenType::int_lit) {
        return ExprNode{.m_expression = consume()};
    } else {
        return {};
    }
}

bool Parser::parseSemi() {
    if (peek().value().type == TokenType::semi) {
        consume();
        return true;
    } else {
        return false;
    }
}

std::optional<ReturnNode> Parser::parseReturn() {
    if (peek().value().type == TokenType::_return) {
        // advance the index and create a return node
        consume();
        auto retExpr = parseExpr();
        parseSemi();
        if (retExpr) {
            ReturnNode retNode = ReturnNode{.m_retVal = retExpr.value()};
            return retNode;
        } else {
            ReturnNode retNode = ReturnNode{};
        }
    } else {
        return {};
    }
};

std::optional<Token> Parser::peek(int offset) {
    if (m_index + offset >= m_tokens.size()) {
        return {};
    } else {
        return m_tokens[m_index + offset];
    }
};

Token Parser::consume() {
    Token tok = m_tokens[m_index];
    m_index++;
    return tok;
};


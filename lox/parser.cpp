// Reference: http://www.craftinginterpreters.com/

#include <string>
#include <vector>
#include <iostream>

#include "expr.hpp"
#include "lox.hpp"
#include "parser.hpp"
#include "token.hpp"
#include "token_type.hpp"

namespace lox {

    class Parser::ParseError {}; 

    Expr* Parser::expression() {
        return equality();
    }

    Expr* Parser::equality() {
        Expr* expr = comparison();
        std::vector<TokenType> types = {TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL};

        while(match(types)) {
            Token oper = previous();
            Expr* right = comparison();
            expr = new Expr::Binary(expr, oper, right);
        }

        return expr;
    }

    Expr* Parser::comparison() {
        Expr* expr = addition();
        std::vector<TokenType> types = {TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL};

        while(match(types)) {
            Token oper = previous();
            Expr* right = addition();
            expr = new Expr::Binary(expr, oper, right);
        }

        return expr;
    }

    Expr* Parser::addition() {
        Expr* expr = multiplication();
        std::vector<TokenType> types = {TokenType::MINUS, TokenType::PLUS};

        while(match(types)) {
            Token oper = previous();
            Expr* right = multiplication();
            expr = new Expr::Binary(expr, oper, right);
        }

        return expr;
    }

    Expr* Parser::multiplication() {
        Expr* expr = unary();
        std::vector<TokenType> types = {TokenType::SLASH, TokenType::STAR};

        while(match(types)) {
            Token oper = previous();
            Expr* right = unary();
            expr = new Expr::Binary(expr, oper, right);
        }

        return expr;
    }

    Expr* Parser::unary() {
        std::vector<TokenType> types = {TokenType::BANG, TokenType::MINUS};

        if(match(types)) {
            Token oper = previous();
            Expr* right = unary();
            return new Expr::Unary(oper, right);
        }

        return primary();
    }

    Expr* Parser::primary() {
        std::vector<TokenType> types = {TokenType::FALSE};

        types[0] = TokenType::FALSE;
        if(match(types)) return new Expr::Literal("false", types[0]);

        types[0] = TokenType::TRUE;
        if(match(types)) return new Expr::Literal("true", types[0]);

        types[0] = TokenType::NIL;
        if(match(types)) return new Expr::Literal("nil", types[0]);

        types.clear();
        types.push_back(TokenType::NUMBER);
        types.push_back(TokenType::STRING);
        if(match(types)) {
            return new Expr::Literal(previous().literal, previous().type);
        }

        types.clear();
        types.push_back(TokenType::LEFT_PAREN);
        if(match(types)) {
            Expr* expr = expression();
            consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
            return new Expr::Grouping(expr);
        }
        
        throw error(peek(), "Expect expression.");
    }

    bool Parser::match(std::vector<TokenType> &types) {
        for(auto type: types) {
            if(check(type)) {
                advance();
                return true;
            }
        }
        return false;
    }

    Token Parser::consume(TokenType type, std::string message) {
        if(check(type)) return advance();
        throw *(error(peek(), message));
    }

    bool Parser::check(TokenType type) {
        if(is_at_end()) return false;
        return peek().type == type;
    }

    Token Parser::advance() {
        if(!is_at_end()) current++;
        return previous();
    }

    bool Parser::is_at_end() {
        return peek().type == TokenType::END_OF_FILE;
    }

    Token Parser::peek() {
        return tokens[current];
    }

    Token Parser::previous() {
        return tokens[current-1];
    }

    Parser::ParseError* Parser::error(Token token, std::string message) {
        Lox::error(token.line, message);
        return new Parser::ParseError();
    }

    void Parser::synchronize() {
        advance();

        while(!is_at_end()) {
            if(previous().type == TokenType::SEMICOLON) return;

            switch(peek().type) {
                case TokenType::CLASS:
                case TokenType::FUN:
                case TokenType::VAR:
                case TokenType::FOR:
                case TokenType::IF:
                case TokenType::WHILE:
                case TokenType::PRINT:
                case TokenType::RETURN:
                    return;
            }

            advance();
        }
    }

    Parser::Parser(std::vector<Token> tokens) :
        tokens(tokens),
        current(0)
    {}

    Expr* Parser::parse(){
        try {
            return expression();
        } catch(const ParseError* e) {
            return nullptr;
        }
        
    }

} // namespace lox

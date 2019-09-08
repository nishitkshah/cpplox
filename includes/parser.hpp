// Reference: http://www.craftinginterpreters.com/

#include <string>
#include <vector>

#include "expr.hpp"
#include "lox.hpp"
#include "token.hpp"
#include "token_type.hpp"

#ifndef PARSER_H
#define PARSER_H

namespace lox {

    class Parser {
        private:
            class ParseError;

            std::vector<Token> tokens;
            int current;

            Expr* expression();

            Expr* equality();

            Expr* comparison();

            Expr* addition();

            Expr* multiplication();

            Expr* unary();

            Expr* primary();

            bool match(std::vector<TokenType> &types);

            Token consume(TokenType type, std::string message);

            bool check(TokenType type);

            Token advance();

            bool is_at_end();

            Token peek();

            Token previous();

            ParseError* error(Token token, std::string message);

            void synchronize();

        public:
            Parser(std::vector<Token> tokens);

            Expr* parse();
    };

} // namespace lox

#endif

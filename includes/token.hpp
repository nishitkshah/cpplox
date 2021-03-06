// Reference: http://www.craftinginterpreters.com/

#include <string>

#include "token_type.hpp"

#ifndef TOKEN_H
#define TOKEN_H

namespace lox {

    class Token {
        public:
            TokenType type;
            std::string lexeme;
            std::string literal;
            int line;
        
        public:
            Token(TokenType type, std::string lexeme,
                std::string literal, int line);
            Token(const lox::Token &token);

            std::string str() const;
    };

} // namespace lox

#endif

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

            std::string str() const;
    };

} // namespace lox

#endif

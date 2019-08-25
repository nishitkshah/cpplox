// Reference: http://www.craftinginterpreters.com/

#include <string>

#include "token.hpp"
#include "token_type.hpp"

namespace lox {

    Token::Token(TokenType type, std::string lexeme,
        std::string literal, int line) :
        type(type),
        lexeme(lexeme),
        literal(literal),
        line(line)
    {}

    Token::Token(const lox::Token &token) :
        type(token.type),
        lexeme(token.lexeme),
        literal(token.literal),
        line(token.line)
    {}

    std::string Token::str() const {
        return lexeme + " " + literal;
    }

} // namespace lox

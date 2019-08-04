#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include "token.hpp"

namespace lox {
    
    class Scanner{
    private:
        std::string source;
        std::vector<Token> tokens;
        int start;
        int current;
        int line;

    public:
        Scanner(std::string source);
        std::vector<Token> scan_tokens();
    private:
        bool is_at_end();
        void scan_token();
        char advance();
        void add_token(TokenType type);
        void add_token(TokenType type, std::string literal);
        bool match(char expected);
        char peek();
    };
    
} // namespace lox

#endif

#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <unordered_map>
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
        std::unordered_map<std::string, TokenType> keywords;

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
        void string();
        // Returns true if c is underscore or isalpha returns true.
        bool is_alpha(char c);
        // Wrapper around C++ isdigit. Added for sake of completeness.
        bool is_digit(char c);
        // Returns true if is_digit or is_alpha returns true.
        bool is_alpha_numeric(char c);
        void number();
        char peek_next();
        void identifier();
    };
    
} // namespace lox

#endif

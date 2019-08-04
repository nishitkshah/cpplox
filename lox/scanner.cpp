#include <string>
#include <vector>

#include "lox.hpp"
#include "scanner.hpp"
#include "token.hpp"

namespace lox {
        
    Scanner::Scanner(std::string source) :
        source(source),
        start(0),
        current(0),
        line(1)
    {}
    
    std::vector<Token> Scanner::scan_tokens() {
        while(!is_at_end()){
            start = current;
            scan_token();
        }
        tokens.push_back(Token(TokenType::END_OF_FILE, "", "", line));
        return tokens;
    }

    bool Scanner::is_at_end(){
        return current >= source.size();
    }

    void Scanner::scan_token(){
        char c = advance();
        switch (c) {
            // Single characters tokens that can be uniquely identified
            case '(':
                add_token(TokenType::LEFT_PAREN); break;
            case ')':
                add_token(TokenType::RIGHT_PAREN); break;
            case '{':
                add_token(TokenType::LEFT_BRACE); break;
            case '}':
                add_token(TokenType::RIGHT_BRACE); break;
            case ',':
                add_token(TokenType::COMMA); break;
            case '.':
                add_token(TokenType::DOT); break;
            case '-':
                add_token(TokenType::MINUS); break;
            case '+':
                add_token(TokenType::PLUS); break;
            case ';':
                add_token(TokenType::SEMICOLON); break;
            case '*':
                add_token(TokenType::STAR); break;

            // Single characters tokens that are also prefix of two character tokens
            case '!':
                add_token(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
            case '=':
                add_token(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
            case '<':
                add_token(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
            case '>':
                add_token(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;

            // Scan division operator and single line comment
            case '/':
                if (match('/')) {
                    while (peek() != '\n' && !is_at_end())
                        advance();
                        // No need to create tokens for comments
                } else {
                    add_token(TokenType::SLASH);
                }
                break;

            // Scan whitepace
            case ' ':
            case '\r':
            case '\t':
                // Ignore Whitespace
                break;
            case '\n':
                line++;
                break;

            // Unexpected character
            default:
                Lox::error(line, "Unexpected character."); break;
        }
    }

    char Scanner::advance() {
        current++;
        return source[current-1];
    }

    void Scanner::add_token(TokenType type) {
        add_token(type, "");
    }

    void Scanner::add_token(TokenType type, std::string literal) {
        std::string text = source.substr(start, current-start);
        tokens.push_back(Token(type, text, literal, line));
    }

    bool Scanner::match(char expected) {
        if (is_at_end()) return false;
        if (source[current] != expected) return false;
        current++;
        return true;
    }

    char Scanner::peek() {
        if (is_at_end()) return '\0';
        return source[current];
    }

} // namespace lox

#include <cctype>
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
    {
        keywords.clear();
        keywords["and"] = TokenType::AND;
        keywords["class"] = TokenType::CLASS;
        keywords["else"] = TokenType::ELSE;
        keywords["false"] = TokenType::FALSE;
        keywords["for"] = TokenType::FOR;
        keywords["fun"] = TokenType::FUN;
        keywords["if"] = TokenType::IF;
        keywords["nil"] = TokenType::NIL;
        keywords["or"] = TokenType::OR;
        keywords["print"] = TokenType::PRINT;
        keywords["return"] = TokenType::RETURN;
        keywords["super"] = TokenType::SUPER;
        keywords["this"] = TokenType::THIS;
        keywords["true"] = TokenType::TRUE;
        keywords["var"] = TokenType::VAR;
        keywords["while"] = TokenType::WHILE;
    }
    
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

            // Consume String Literals
            case '"':
                string(); break;

            // Consume Number literals, keywords, identifiers
            // and unexpected characters
            default:
                if (is_digit(c)) {
                    number();
                } else if (is_alpha(c)) {
                    identifier();
                } else {
                    Lox::error(line, "Unexpected character.");
                }
                break;
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

    void Scanner::string() {
        while (peek() != '"' && !is_at_end()) {
            // Allow double quote escaping and backslash escaping within the string
            if (peek() == '\\') {
                if (peek_next() == '"' || peek_next() == '\\') {
                    // TODO: When escaped, remove the escaping backslash
                    // and put the resultant special character.
                    // This way we can handle '\n', '\r' etc.
                    advance();
                }
            }
            if (peek() == '\n') line++; // Multi-line string
            advance();
        }

        // Unterminated string.
        if (is_at_end()) {
            Lox::error(line, "Unterminated string.");
            return;
        }

        // The closing ".
        advance();

        // Trim the surrounding quotes.
        std::string value = source.substr(start+1, current-start-2);
        add_token(TokenType::STRING, value);
    }

    bool Scanner::is_alpha(char c) {
        return isalpha(c) || (c == '_');
    }

    bool Scanner::is_digit(char c) {
        return isdigit(c);
    }

    bool Scanner::is_alpha_numeric(char c) {
        return is_alpha(c) || is_digit(c);
    }

    void Scanner::number() {
        while (is_digit(peek())) advance();

        // Look for a fractional part.
        if (peek() == '.' && is_digit(peek_next())) {
            // Consume the "."
            advance();

            while (is_digit(peek())) advance();
        }

        // TODO: Need a way to handle string and double literals. Use union?
        add_token(TokenType::NUMBER, source.substr(start, current-start));
    }

    char Scanner::peek_next() {
        if ((current+1) >= source.size()) return '\0';
        return source[current+1];
    }

    void Scanner::identifier() {
        while (is_alpha_numeric(peek()))
            advance();
        std::string text = source.substr(start, current-start);
        TokenType type = TokenType::IDENTIFIER;
        if (keywords.count(text))
            type = keywords[text];
        add_token(TokenType::IDENTIFIER);
    }

} // namespace lox

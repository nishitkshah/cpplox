// Reference: http://www.craftinginterpreters.com/

#ifndef LOX_H
#define LOX_H

#include <string>

#include "token.hpp"

namespace lox {

    class Lox {
        private:
            static bool had_error;

        public:
            static void run_file(std::string path);
            static void run_prompt();
            static void run(std::string s);
            static void error(int line, std::string message);
            static void error(Token token, std::string message);
        private:
            static void report(int line, std::string where, std::string message);
    };

} // namespace lox

#endif

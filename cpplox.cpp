// Reference: http://www.craftinginterpreters.com/

#include <iostream>
#include <cstdlib>
#include "lox.hpp"

int main(int argc, char *argv[]){
    if (argc>2) {
        std::cout << "Usage: jlox [script]\n";
        exit(64);
    } else if (argc==2) {
        lox::Lox interpretter;       // NOTE: Lox interpretter(); fails as it treats it as a function declaration
        interpretter.run_file(argv[1]);
    } else {
        lox::Lox interpretter;
        interpretter.run_prompt();
    }
    return 0;
}

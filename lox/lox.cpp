#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "lox.hpp"

namespace lox {

    bool Lox::had_error = false;

    void Lox::run_file(std::string path) {
        std::stringstream sstr;
        std::ifstream ifs(path);
        if (!ifs) {
            throw "File " + path + " could not be opened for reading";  // TODO: Handle this with try catch or replace it with cerr and exit()
        }
        sstr << ifs.rdbuf();
        run(sstr.str());    // TODO: Not a good way. Takes the entire file in memory.
        if(had_error) std::exit(65);
    }

    void Lox::run_prompt() {
        while (1) {
            std::cout << "> ";
            std::string s;
            std::getline(std::cin, s);
            run(s);
            had_error = false;
        }
    }

    void Lox::run(std::string s) {
        /*
        Scanner scanner(s);
        std::vector<Token> tokens = scanner.scanTokens();
        for(Token token: tokens){
            std::cout << token.str() << std::endl;
        } */
        std::cout << s <<std::endl;
    }

    void Lox::error(int line, std::string message) {
        report(line, "", message);
    }

    void Lox::report(int line, std::string where, std::string message) {
        std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
        had_error = true;
    }

}

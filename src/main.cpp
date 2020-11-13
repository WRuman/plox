#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <sysexits.h>
#include <string.h>


#include "Scanner.h"

bool hadError = false;

void report(int line, const std::string& where, const std::string& msg) {
    constexpr auto prefix = "[line " ;
    constexpr auto mid = "] Error" ;
    std::cerr << prefix << line << mid << where << ": " << msg << std::endl;
    exit(EXIT_FAILURE);
}


void run(std::istream& source) {
    auto scanner = pl::Scanner(source);
    for (auto token : scanner.scanTokens()) {
        std::cout << token << std::endl;
    }
}


void runfile(char *scriptName) {
    std::cout << "Script runner mode: " << scriptName << std::endl;
    std::ifstream ifs(scriptName);
    if (ifs.is_open()) {
        run(ifs);
    }
    if (hadError) {
        exit(EX_DATAERR);
    }
}

void runPrompt() {
    std::cout << "Prompt mode" << std::endl;
    while(true) {
        std::string in; 
        std::getline(std::cin, in);
        if (std::cin.eof()) {
            break;
        }
        if (in.empty()) {
            continue;
        }
        std::istringstream iss(in);
        run(iss);
        hadError = false;
    }
}

int main(int argc, char **argv) {
    if (argc > 2) {
        std::cout << "Usage: plox [script]" << std::endl;
        return EX_USAGE;
    } else if (argc == 2) {
        runfile(argv[1]);
    } else {
        runPrompt();
    }
    return 0;
}
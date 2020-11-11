#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <sysexits.h>
#include <string.h>


void report(const std::string& msg) {
    std::cerr << msg << std::endl;
    exit(EXIT_FAILURE);
}


void run(std::istream& source) {
    std::string firstLine;
    std::getline(source, firstLine);
    std::cout << firstLine << std::endl;
}


void runfile(char *scriptName) {
    std::cout << "Script runner mode: " << scriptName << std::endl;
    std::ifstream ifs(scriptName);
    if (ifs.is_open()) {
        run(ifs);
    } else {
        report("Could not open script file " + std::string(scriptName));
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
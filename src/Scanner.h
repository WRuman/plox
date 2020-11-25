#ifndef PL_SCANNER_H
#define PL_SCANNER_H
#include <sstream>
#include <vector>

#include "Token.h"

namespace pl {
class Scanner
{
private:
    int start = 0;
    int current = 0;
    int line = 1;
    std::vector<Token> tokens{};
    std::string lexeme{""};
    std::istream& source;
    static TokenType typeFor(char c);
    char advance();
    void addToken(TokenType t);
    void addToken(TokenType t, std::string literal);
    bool match(char expected);
    void killLine();
    void scanToken();
public:
    Scanner(std::istream& source): source(source) {};
    std::vector<Token> scanTokens();
};
}
#endif
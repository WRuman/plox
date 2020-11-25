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
    /**
     * Returns true if the next extracted character matches the provided one
     */
    bool match(char expected);
    /**
     * Returns true if the character is an ASCII digit [0-9]
     */
    bool isDigit(char c);
    /**
     * Looks ahead two positions
     */
    char peekNext();
    /**
     * Consumes the rest of the characters in the current line until EOF or newline
     * is found. No tokens are emitted.
     */
    void killLine();
    void scanToken();
    // Lexeme specific
    void string();
    void number();
public:
    Scanner(std::istream& source): source(source) {};
    std::vector<Token> scanTokens();
};
}
#endif
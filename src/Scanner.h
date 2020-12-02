#ifndef PL_SCANNER_H
#define PL_SCANNER_H
#include <sstream>
#include <vector>
#include <unordered_map>

#include "Token.h"

namespace pl {
class Scanner
{
private:
    std::unordered_map<std::string, TokenType> identifierByName = {
        {"and", TokenType::AND},
        {"class", TokenType::CLASS},
        {"else", TokenType::ELSE},
        {"false", TokenType::FALSE},
        {"for", TokenType::FOR},
        {"fun", TokenType::FUN},
        {"if", TokenType::IF},
        {"nil", TokenType::NIL},
        {"or", TokenType::OR},
        {"print", TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"super", TokenType::SUPER},
        {"this", TokenType::THIS},
        {"true", TokenType::TRUE},
        {"var", TokenType::VAR},
        {"while", TokenType::WHILE}
    };
    int start = 0;
    int current = 0;
    int line = 1;
    int blockComment = 0;
    std::vector<Token> tokens{};
    std::string lexeme{""};
    std::istream& source;
    static TokenType typeFor(char c);
    char advance();
    void addToken(TokenType t);
    void addToken(TokenType t, std::string literal);
    /**
     * Returns true if the next value that will be retrieved from the source stream is an EOF
     */
    bool atEnd();
    /**
     * Returns true if the next extracted character matches the provided one
     */
    bool match(char expected);
    /**
     * Returns true if the character is an ASCII digit [0-9]
     */
    bool isDigit(char c);
    /**
     * Returns true if the character is an ASCII alphabetical character [a-Z]
     */
    bool isAlpha(char c);
    /**
     * Returns true if the character is either a digit or alphabetical character
     */
    bool isAlphaNumeric(char c);
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
    void identifier();
public:
    Scanner(std::istream& source): source(source) {};
    std::vector<Token> scanTokens();
};
}
#endif
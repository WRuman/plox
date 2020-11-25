#include "Scanner.h"
#include <iostream>

namespace pl {
std::vector<Token> Scanner::scanTokens() {
    while (!source.eof()) {
        start = current;
        scanToken();
    }
    tokens.push_back(Token(TokenType::EOF, "", nullptr, line));
    return tokens;
}

char Scanner::advance() {
    current++;
    char c = source.get();
    lexeme.push_back(c);
    return c;
}

void Scanner::addToken(TokenType t) {
    addToken(t, nullptr);
}

void Scanner::addToken(TokenType t, std::string literal) {
    tokens.push_back(Token(t, lexeme, literal, line));
    lexeme = "";
}

void Scanner::scanToken() {
    char c = advance();
    switch (c)
    {
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;
        default:
            std::cerr << line << "Unexpected character '" << c <<  "'" << std::endl;
            break;
    }
}
}
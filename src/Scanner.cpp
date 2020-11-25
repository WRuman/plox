#include "Scanner.h"
#include <iostream>

namespace pl {
std::vector<Token> Scanner::scanTokens() {
    while (!source.eof()) {
        start = current;
        lexeme = "";
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

bool Scanner::match(char expected) {
    if (source.eof()) {
        return false;
    }
    char next = static_cast<char>(source.peek());
    if (next != expected) {
        return false;
    }
    current++;
    return true;
}

void Scanner::addToken(TokenType t) {
    addToken(t, nullptr);
}

void Scanner::addToken(TokenType t, std::string literal) {
    tokens.push_back(Token(t, lexeme, literal, line));
}

void Scanner::killLine() {
    while (!source.eof() && source.peek() != '\n') {
        advance();
    }
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
        case '!': addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
        case '=': addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
        case '<': addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
        case '>': addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
        case '/':
            // Double slash indicates a comment, so discard the rest of the line.
            if (match('/')) {
                killLine();
            } else {
                addToken(TokenType::SLASH);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace
            break;
        case '\n':
            line++;
            break;
        default:
            std::cerr << line << "Unexpected character '" << c <<  "'" << std::endl;
            break;
    }
}
}
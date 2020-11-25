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

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

char Scanner::peekNext() {
    char firstOut = source.get();
    char peeked = source.peek();
    source.putback(firstOut);
    return peeked;
}

void Scanner::addToken(TokenType t) {
    addToken(t, nullptr);
}

void Scanner::addToken(TokenType t, std::string literal) {
    tokens.push_back(Token(t, lexeme, literal, line));
}

void Scanner::killLine() {
    // Continue until newline or EOF is found, but do not consume the newline
    while (!source.eof() && source.peek() != '\n') {
        advance();
    }
}

void Scanner::string() {
    // Continue until the other quote or EOF is found, but do not consume the quote
    while (!source.eof() && source.peek() != '"') {
        if (source.peek() == '\n') {
            line++;
        }
        advance();
    }
    if (source.eof()) {
        std::cerr << line << "Unterminated string" << std::endl;
        return;
    }

    // Capture the terminating quote
    advance();

    // Omit the quotes
    std::string literal = lexeme.substr(1, lexeme.length() - 2);
    addToken(TokenType::STRING, literal);
}

void Scanner::number() {
    while (isDigit(source.peek())) {
        advance();
    }

    // There may be a fractional part to look for
    if (source.peek() == '.' && isDigit(peekNext())) {
        // Consumes .
        advance();
        while (isDigit(source.peek())) {
            advance();
        }
    }

    //TODO Add handling for multiple types of literals
    //addToken(TokenType::NUMBER, )
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
        case '"': string(); break;
        default:
            if (isDigit(c)) {
                number();
            } else {
                std::cerr << line << "Unexpected character '" << c <<  "'" << std::endl;
            }
            break;
    }
}
}
#ifndef PL_TOKEN_H
#define PL_TOKEN_H
#include <sstream>


#include "TokenType.h"

namespace pl {
    class Token
    {
    private:
        const TokenType type;
        const std::string lexeme;
        const std::string literal;
        const int line;
    public:
        Token(TokenType t, std::string le, std::string li, int ln): type(t), lexeme(le), literal(li), line(ln) {};
        friend std::ostream& operator<<(std::ostream& os, const Token& tok);
    };
}
#endif
#include "Token.h"
#include <iomanip>

namespace pl {
std::ostream& operator<<(std::ostream& os, const Token& tok) {
    auto v = static_cast<typename std::underlying_type<TokenType>::type>(tok.type);
    os << std::setw(20) << std::left << "Token: " << std::right << v << std::endl
       << std::setw(20) << std::left << "Line:" << std::right << tok.line << std::endl
       << std::setw(20) << std::left << "Lex:" << std::right << tok.lexeme << std::endl
       << std::setw(20) << std::left << "Lit:" << std::right << tok.literal << std::endl;
    return os;
}
}
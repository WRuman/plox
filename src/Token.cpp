#include "Token.h"

namespace pl {
std::ostream& operator<<(std::ostream& os, const Token& tok) {
    auto v = static_cast<typename std::underlying_type<TokenType>::type>(tok.type);
    os << v << " " << tok.lexeme << " " << tok.literal;
    return os;
}
}
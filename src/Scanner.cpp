#include "Scanner.h"

namespace pl {
std::vector<pl::Token> pl::Scanner::scanTokens() {
    auto list = std::vector<pl::Token>();
    while (!source.eof()) {
        source.get();
        //list.push_back(Token(source.get()));
    }
    return list;
}
}
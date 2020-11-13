#ifndef PL_SCANNER_H
#define PL_SCANNER_H
#include <sstream>
#include <vector>

#include "Token.h"

namespace pl {
class Scanner
{
private:
    std::istream& source;
public:
    Scanner(std::istream& source): source(source) {};
    std::vector<Token> scanTokens();
};
}
#endif
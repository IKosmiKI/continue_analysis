#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <regex>
#include "tokeninfo.h"
using namespace std;


class Lexer {
public:
    Lexer(const string& input);

    TokenInfo nextToken();

private:
    string input;
    size_t pos;
};



#endif //LEXER_H

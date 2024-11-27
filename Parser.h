#ifndef PARSER_H
#define PARSER_H
#include "tokeninfo.h"
#include <string>
#include <cctype>
#include <iostream>
#include <vector>
#include <stack>
#include <regex>
using namespace std;


class Parser {
    Parser(Lexer& lexer);

    void parse();

private:
    Lexer& lexer;
    void continue_analysis(stack<TokenInfo> stack);
};



#endif //PARSER_H

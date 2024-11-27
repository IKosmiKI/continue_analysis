#ifndef PARSER_H
#define PARSER_H
#include <stack>
#include "Lexer.h"

using namespace std;


class Parser {
public:
    Parser(Lexer& lexer);

    void parse();

private:
    Lexer& lexer;
    void continue_analysis(stack<TokenInfo> stack);
};



#endif //PARSER_H

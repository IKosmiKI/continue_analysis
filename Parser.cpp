#include "Parser.h"
#include <iostream>
Parser::Parser(Lexer& lexer) : lexer(lexer) {}
void Parser::parse() {
    TokenInfo token;
    stack<TokenInfo> loopStack;

    do {
        token = lexer.nextToken();
        switch (token.type) {
            case Token::Semicolon:
                if (loopStack.top().type == Token::Continue) {
                    loopStack.push(token);
                    continue_analysis(loopStack);
                }
            break;
            case Token::While:
            case Token::For:
            case Token::Do:
            case Token::Continue:
                loopStack.push(token);
            break;
            case Token::EndOfFile:
            case Token::Identifier:
                // Обработка идентификаторов
                break;
            case Token::Unknown:
                cerr << "Error: Unknown token '" << token.value << "'." << endl;
            break;
            case Token::Whitespace:
                // Игнорируем пробелы
                    break;
        }
    } while (token.type != Token::EndOfFile);
}
void Parser::continue_analysis(stack<TokenInfo> stack) {
    string str;
    // const regex invalidPattern(R"((^|\s)continue\s*=|=\s*continue(\s|;|$))");
    const regex validPattern(R"((;)(^|\s)continue\s*;|\)\s*continue(\s*;)|\)\s*\{\s*.*(;)\s*continue(\s*;))");
    while (!stack.empty()) {
        str = stack.top().value + str;
        stack.pop();
    };
    if (regex_match(str, validPattern)) cout << "Valid Continue Using" << endl;
    else cerr << "Error: Invalid Continue Using" << endl;
}
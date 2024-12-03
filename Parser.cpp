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
                // if (loopStack.top().type == Token::Continue) {
                //     loopStack.push(token);
                //     continue_analysis(loopStack);
                // }
                // else loopStack.push(token);
                loopStack.push(token);
            break;
            case Token::Continue:
                loopStack.push(token);
                token = lexer.nextToken();
                if (token.type!=Token::Unknown) loopStack.push(token);
                if (token.type == Token::Semicolon) {
                    continue_analysis(loopStack);
                }
                else cerr << "Error: Invalid Continue Using" << endl;
                break;
            case Token::While:
            case Token::For:
            case Token::Do:
            case Token::LParen:
            case Token::RParen:
            case Token::LBracer:
            case Token::RBracer:
            case Token::Equal:
            // case Token::Continue:
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
    const regex validPattern(R"((while\s*\(.*|for\s*\(.*|do\s*\(.*)(\).*(;)(^|\s)continue\s*;|\)\s*continue(\s*;)|\)\s*\{*\s*.*(;)\s*continue(\s*;)|\)\s*\{*\s*continue(\s*;)))");
    while (!stack.empty()) {
        str = stack.top().value + str;
        stack.pop();
    };
    if (regex_search(str, validPattern)) cout << "Valid Continue Using" << endl;
    else cerr << "Error: Invalid Continue Using" << endl;
}
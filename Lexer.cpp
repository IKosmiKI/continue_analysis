#include "Lexer.h"
Lexer::Lexer(const string& input) : input(input), pos(0) {}
TokenInfo Lexer::nextToken() {
    // Пропускаем пробелы
    while (pos < input.size() && isspace(input[pos])) {
        pos++;
    }

    // Проверяем конец строки
    if (pos >= input.size()) {
        return {Token::EndOfFile, ""};
    }

    if (input.substr(pos, 8) == "continue") {
        pos += 8;
        return {Token::Continue, "continue"};
    }

    if (input.substr(pos, 1) == ";") {
        pos += 1;
        return {Token::Semicolon, ";"};
    }

    if (input.substr(pos, 1) == "(") {
        pos += 1;
        return {Token::LParen, "("};
    }

    if (input.substr(pos, 1) == ")") {
        pos += 1;
        return {Token::RParen, ")"};
    }

    if (input.substr(pos, 1) == "{") {
        pos += 1;
        return {Token::LBracer, "{"};
    }

    if (input.substr(pos, 1) == "}") {
        pos += 1;
        return {Token::RBracer, "}"};
    }

    if (input.substr(pos, 1) == "=") {
        pos += 1;
        return {Token::Equal, "="};
    }

    if (input.substr(pos, 2) == "do") {
        pos += 2;
        return {Token::Do, "do"};
    }

    if (input.substr(pos, 5) == "while") {
        pos += 5;
        return {Token::While, "while"};
    }

    if (input.substr(pos, 3) == "for") {
        pos += 3;
        return {Token::For, "for"};
    }

    if (isalpha(input[pos])) {
        size_t start = pos;
        while (pos < input.size() && (isalnum(input[pos]) || input[pos] == '_')) {
            pos++;
        }
        return {Token::Identifier, input.substr(start, pos - start)};
    }

    return {Token::Unknown, string(1, input[pos++])};
}
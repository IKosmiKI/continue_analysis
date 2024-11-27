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

    // Проверяем на ключевое слово "continue"
    if (input.substr(pos, 8) == "continue") {
        pos += 8; // увеличиваем позицию на длину слова "continue"
        return {Token::Continue, "continue"};
    }

    if (input.substr(pos, 1) == ";") {
        pos += 8; // увеличиваем позицию на длину слова "continue"
        return {Token::Semicolon, ";"};
    }

    if (input.substr(pos, 2) == "do") {
        pos += 8; // увеличиваем позицию на длину слова "continue"
        return {Token::Do, "do"};
    }

    // Проверяем на ключевое слово "while"
    if (input.substr(pos, 5) == "while") {
        pos += 5;
        return {Token::While, "while"};
    }

    // Проверяем на ключевое слово "for"
    if (input.substr(pos, 3) == "for") {
        pos += 3;
        return {Token::For, "for"};
    }

    // Проверяем на идентификаторы (буквы и цифры)
    if (isalpha(input[pos])) {
        size_t start = pos;
        while (pos < input.size() && (isalnum(input[pos]) || input[pos] == '_')) {
            pos++;
        }
        return {Token::Identifier, input.substr(start, pos - start)};
    }

    // Если токен не распознан
    return {Token::Unknown, string(1, input[pos++])};
}
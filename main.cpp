#include <string>
#include <cctype>
#include <iostream>
#include <vector>
#include <stack>
#include <regex>
using namespace std;

enum class Token {
    Continue,
    While,
    For,
    Identifier,
    EndOfFile,
    Unknown,
    Whitespace,
    Semicolon,
    Do
};

struct TokenInfo {
    Token type;
    string value;
};

void continue_analysis(stack<TokenInfo> stack) {
    string str;
    const regex invalidPattern(R"((^|\s)continue\s*=|=\s*continue(\s|;|$))");
    const regex validPattern(R"((;)(^|\s)continue\s*;|\)\s*continue(\s*;)|\)\s*\{\s*.*(;)\s*continue(\s*;))");
    while (stack.top().type != Token::While || stack.top().type != Token::For) {
        str = stack.top().value + str;
        if (regex_match(str, invalidPattern)) cerr << "Error: Invalid Continue Using" << endl;
        else if (regex_match(str, validPattern)) cout << "Valid Continue Using" << endl;
    };
}


class Lexer {
public:
    Lexer(const string& input) : input(input), pos(0) {}

    TokenInfo nextToken() {
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

private:
    string input;
    size_t pos;
};

class Parser {
public:
    Parser(Lexer& lexer) : lexer(lexer) {}

    void parse() {
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

private:
    Lexer& lexer;
};

int main() {
    string input = "while (true) { continue; }"; // Пример корректного использования
    // string input = "int main() { continue; }"; // Пример некорректного использования
    Lexer lexer(input);
    Parser parser(lexer);
    parser.parse();

    return 0;
}
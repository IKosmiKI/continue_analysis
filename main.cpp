#include <string>
#include <cctype>
#include <iostream>
#include <vector>
#include <stack>

enum class Token {
    Continue,
    While,
    For,
    Identifier,
    EndOfFile,
    Unknown,
    Whitespace
};

struct TokenInfo {
    Token type;
    std::string value;
};

class Lexer {
public:
    Lexer(const std::string& input) : input(input), pos(0) {}

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
        return {Token::Unknown, std::string(1, input[pos++])};
    }

private:
    std::string input;
    size_t pos;
};

class Parser {
public:
    Parser(Lexer& lexer) : lexer(lexer) {}

    void parse() {
        TokenInfo token;
        std::stack<Token> loopStack;

        do {
            token = lexer.nextToken();
            switch (token.type) {
                case Token::While:
                case Token::For:
                    loopStack.push(token.type);
                    break;
                case Token::Continue:
                    if (loopStack.empty()) {
                        std::cerr << "Error: 'continue' used outside of a loop." << std::endl;
                    } else {
                        std::cout << "Valid 'continue' found." << std::endl;
                    }
                    break;
                case Token::EndOfFile:
                    break;
                case Token::Identifier:
                    // Обработка идентификаторов
                    break;
                case Token::Unknown:
                    std::cerr << "Error: Unknown token '" << token.value << "'." << std::endl;
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
    std::string input = "while (true) { continue; }"; // Пример корректного использования
    // std::string input = "int main() { continue; }"; // Пример некорректного использования
    Lexer lexer(input);
    Parser parser(lexer);
    parser.parse();

    return 0;
}
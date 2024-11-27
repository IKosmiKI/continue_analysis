#include <string>
#include <regex>
#include "Lexer.h"
#include "Parser.h"
using namespace std;

int main() {
    string input = "while (true) { continue; }"; // Пример корректного использования
    // string input = "while (true) { } continue;"
    // string input = "while (true) { } {continue;}"
    // string input = "int main() { continue; }"; // Пример некорректного использования
    Lexer lexer(input);
    Parser parser(lexer);
    parser.parse();

    return 0;
}
#include <string>
#include <cctype>
#include <iostream>
#include <vector>
#include <stack>
#include <regex>
#include "Lexer.cpp"
#include "Parser.cpp"
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
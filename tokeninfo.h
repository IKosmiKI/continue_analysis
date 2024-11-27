#include <string>
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
    Do,
    LBracer,
    RBracer,

};
struct TokenInfo {
    Token type;
    string value;
};
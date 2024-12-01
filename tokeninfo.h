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
    LParen,
    RParen,
    LBracer,
    RBracer,
    Equal,

};
struct TokenInfo {
    Token type;
    string value;
};
#pragma once
#include "../common/Token.hpp"
#include <string>
#include <vector>
#include <unordered_map>

namespace maz {

class Lexer {
public:
    Lexer(std::string source, std::string filename = "");
    std::vector<Token> tokenize();

private:
    std::string source;
    std::string filename;
    size_t start{0};
    size_t current{0};
    size_t line{1};
    size_t column{1};
    size_t startColumn{1};

    std::vector<Token> tokens;
    static const std::unordered_map<std::string, TokenType> keywords;

    bool isAtEnd() const;
    char advance();
    char peek() const;
    char peekNext() const;
    bool match(char expected);

    void scanToken();
    void identifier();
    void number();
    void stringLiteral();
    void multilineComment();

    void addToken(TokenType type);
    void addToken(TokenType type, std::string lexeme);

    bool canEndStatement(TokenType type) const;
};

} // namespace maz


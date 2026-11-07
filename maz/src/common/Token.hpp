#pragma once
#include "TokenType.hpp"
#include <string>

namespace maz {

struct SourceLocation {
    std::string file;
    size_t line{1};
    size_t column{1};

    SourceLocation() = default;
    SourceLocation(std::string f, size_t l, size_t c)
        : file(std::move(f)), line(l), column(c) {}
};

struct Token {
    TokenType type;
    std::string lexeme;
    SourceLocation location;

    Token() : type(TokenType::TOKEN_EOF) {}
    Token(TokenType t, std::string lex, SourceLocation loc)
        : type(t), lexeme(std::move(lex)), location(std::move(loc)) {}
};

} // namespace maz


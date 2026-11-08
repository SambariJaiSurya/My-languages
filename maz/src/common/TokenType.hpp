#pragma once
#include <string>

namespace maz {

enum class TokenType {
    // End of file / line
    TOKEN_EOF,
    TOKEN_NEWLINE,

    // Literals
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_STRING,
    TOKEN_BOOL,
    TOKEN_NULL,
    TOKEN_IDENTIFIER,

    // Keywords
    TOKEN_DEF,
    TOKEN_RETURN,
    TOKEN_CONST,
    TOKEN_DYN,
    TOKEN_FORCE,
    TOKEN_NEW,
    TOKEN_GLOBAL,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_FOR,
    TOKEN_WHILE,
    TOKEN_TRY,
    TOKEN_CATCH,
    TOKEN_CLASS,
    TOKEN_STRUCT,
    TOKEN_CONSTRUCTOR,
    TOKEN_EXTENDS,
    TOKEN_INCLUDE,
    TOKEN_IMPLEMENT,
    TOKEN_PUBLIC,
    TOKEN_PRIVATE,
    TOKEN_PROTECTED,
    TOKEN_INTERNAL,
    TOKEN_ASYNC,
    TOKEN_AWAIT,
    TOKEN_USE,

    // Type keywords
    TOKEN_TYPE_INT,
    TOKEN_TYPE_FLOAT,
    TOKEN_TYPE_DOUBLE,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_CHAR,
    TOKEN_TYPE_BOOL,

    // Operators
    TOKEN_PLUS,          // +
    TOKEN_MINUS,         // -
    TOKEN_STAR,          // *
    TOKEN_SLASH,         // /
    TOKEN_PERCENT,       // %
    TOKEN_PLUS_PLUS,     // ++
    TOKEN_MINUS_MINUS,   // --
    TOKEN_ASSIGN,        // =
    TOKEN_PLUS_ASSIGN,   // +=
    TOKEN_MINUS_ASSIGN,  // -=
    TOKEN_STAR_ASSIGN,   // *=
    TOKEN_SLASH_ASSIGN,  // /=

    // Comparison & Logic
    TOKEN_EQUAL_EQUAL,   // ==
    TOKEN_BANG_EQUAL,    // !=
    TOKEN_LESS,          // <
    TOKEN_LESS_EQUAL,    // <=
    TOKEN_GREATER,       // >
    TOKEN_GREATER_EQUAL, // >=
    TOKEN_BANG,          // !
    TOKEN_AND_AND,       // &&
    TOKEN_OR_OR,         // ||

    // Delimiters
    TOKEN_LPAREN,        // (
    TOKEN_RPAREN,        // )
    TOKEN_LBRACE,        // {
    TOKEN_RBRACE,        // }
    TOKEN_LBRACKET,      // [
    TOKEN_RBRACKET,      // ]
    TOKEN_COMMA,         // ,
    TOKEN_COLON,         // :
    TOKEN_DOT,           // .
    TOKEN_QUESTION,      // ?
    TOKEN_SEMICOLON      // ; (optional statement separator)
};

inline std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::TOKEN_EOF: return "EOF";
        case TokenType::TOKEN_NEWLINE: return "NEWLINE";
        case TokenType::TOKEN_INT: return "INT";
        case TokenType::TOKEN_FLOAT: return "FLOAT";
        case TokenType::TOKEN_STRING: return "STRING";
        case TokenType::TOKEN_BOOL: return "BOOL";
        case TokenType::TOKEN_NULL: return "NULL";
        case TokenType::TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TokenType::TOKEN_DEF: return "def";
        case TokenType::TOKEN_RETURN: return "return";
        case TokenType::TOKEN_CONST: return "const";
        case TokenType::TOKEN_DYN: return "dyn";
        case TokenType::TOKEN_FORCE: return "force";
        case TokenType::TOKEN_NEW: return "new";
        case TokenType::TOKEN_IF: return "if";
        case TokenType::TOKEN_ELSE: return "else";
        case TokenType::TOKEN_FOR: return "for";
        case TokenType::TOKEN_WHILE: return "while";
        case TokenType::TOKEN_TRY: return "try";
        case TokenType::TOKEN_CATCH: return "catch";
        case TokenType::TOKEN_CLASS: return "class";
        case TokenType::TOKEN_STRUCT: return "struct";
        case TokenType::TOKEN_CONSTRUCTOR: return "constructor";
        case TokenType::TOKEN_EXTENDS: return "extends";
        case TokenType::TOKEN_INCLUDE: return "include";
        case TokenType::TOKEN_IMPLEMENT: return "implement";
        case TokenType::TOKEN_PUBLIC: return "public";
        case TokenType::TOKEN_PRIVATE: return "private";
        case TokenType::TOKEN_PROTECTED: return "protected";
        case TokenType::TOKEN_INTERNAL: return "internal";
        case TokenType::TOKEN_ASYNC: return "async";
        case TokenType::TOKEN_AWAIT: return "await";
        case TokenType::TOKEN_USE: return "use";
        case TokenType::TOKEN_PLUS: return "+";
        case TokenType::TOKEN_MINUS: return "-";
        case TokenType::TOKEN_STAR: return "*";
        case TokenType::TOKEN_SLASH: return "/";
        case TokenType::TOKEN_PERCENT: return "%";
        case TokenType::TOKEN_PLUS_PLUS: return "++";
        case TokenType::TOKEN_MINUS_MINUS: return "--";
        case TokenType::TOKEN_ASSIGN: return "=";
        case TokenType::TOKEN_PLUS_ASSIGN: return "+=";
        case TokenType::TOKEN_MINUS_ASSIGN: return "-=";
        case TokenType::TOKEN_STAR_ASSIGN: return "*=";
        case TokenType::TOKEN_SLASH_ASSIGN: return "/=";
        case TokenType::TOKEN_EQUAL_EQUAL: return "==";
        case TokenType::TOKEN_BANG_EQUAL: return "!=";
        case TokenType::TOKEN_LESS: return "<";
        case TokenType::TOKEN_LESS_EQUAL: return "<=";
        case TokenType::TOKEN_GREATER: return ">";
        case TokenType::TOKEN_GREATER_EQUAL: return ">=";
        case TokenType::TOKEN_BANG: return "!";
        case TokenType::TOKEN_AND_AND: return "&&";
        case TokenType::TOKEN_OR_OR: return "||";
        case TokenType::TOKEN_LPAREN: return "(";
        case TokenType::TOKEN_RPAREN: return ")";
        case TokenType::TOKEN_LBRACE: return "{";
        case TokenType::TOKEN_RBRACE: return "}";
        case TokenType::TOKEN_LBRACKET: return "[";
        case TokenType::TOKEN_RBRACKET: return "]";
        case TokenType::TOKEN_COMMA: return ",";
        case TokenType::TOKEN_COLON: return ":";
        case TokenType::TOKEN_DOT: return ".";
        case TokenType::TOKEN_QUESTION: return "?";
        case TokenType::TOKEN_SEMICOLON: return ";";
        default: return "UNKNOWN";
    }
}

} // namespace maz


#include "Lexer.hpp"
#include "../common/Error.hpp"
#include <cctype>

namespace maz {

const std::unordered_map<std::string, TokenType> Lexer::keywords = {
    {"def", TokenType::TOKEN_DEF},
    {"return", TokenType::TOKEN_RETURN},
    {"const", TokenType::TOKEN_CONST},
    {"dyn", TokenType::TOKEN_DYN},
    {"force", TokenType::TOKEN_FORCE},
    {"new", TokenType::TOKEN_NEW},
    {"if", TokenType::TOKEN_IF},
    {"else", TokenType::TOKEN_ELSE},
    {"for", TokenType::TOKEN_FOR},
    {"while", TokenType::TOKEN_WHILE},
    {"try", TokenType::TOKEN_TRY},
    {"catch", TokenType::TOKEN_CATCH},
    {"class", TokenType::TOKEN_CLASS},
    {"struct", TokenType::TOKEN_STRUCT},
    {"constructor", TokenType::TOKEN_CONSTRUCTOR},
    {"extends", TokenType::TOKEN_EXTENDS},
    {"include", TokenType::TOKEN_INCLUDE},
    {"implement", TokenType::TOKEN_IMPLEMENT},
    {"public", TokenType::TOKEN_PUBLIC},
    {"private", TokenType::TOKEN_PRIVATE},
    {"protected", TokenType::TOKEN_PROTECTED},
    {"internal", TokenType::TOKEN_INTERNAL},
    {"async", TokenType::TOKEN_ASYNC},
    {"await", TokenType::TOKEN_AWAIT},
    {"use", TokenType::TOKEN_USE},
    {"true", TokenType::TOKEN_BOOL},
    {"false", TokenType::TOKEN_BOOL},
    {"null", TokenType::TOKEN_NULL}
};

Lexer::Lexer(std::string src, std::string fname)
    : source(std::move(src)), filename(std::move(fname)) {}

std::vector<Token> Lexer::tokenize() {
    while (!isAtEnd()) {
        start = current;
        startColumn = column;
        scanToken();
    }

    // If last token was not a newline/EOF, add a trailing newline if appropriate
    if (!tokens.empty() && canEndStatement(tokens.back().type)) {
        tokens.emplace_back(TokenType::TOKEN_NEWLINE, "\n", SourceLocation(filename, line, column));
    }

    tokens.emplace_back(TokenType::TOKEN_EOF, "", SourceLocation(filename, line, column));
    return tokens;
}

bool Lexer::isAtEnd() const {
    return current >= source.length();
}

char Lexer::advance() {
    char c = source[current++];
    column++;
    return c;
}

char Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return source[current];
}

char Lexer::peekNext() const {
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
}

bool Lexer::match(char expected) {
    if (isAtEnd() || source[current] != expected) return false;
    current++;
    column++;
    return true;
}

bool Lexer::canEndStatement(TokenType type) const {
    switch (type) {
        case TokenType::TOKEN_IDENTIFIER:
        case TokenType::TOKEN_INT:
        case TokenType::TOKEN_FLOAT:
        case TokenType::TOKEN_STRING:
        case TokenType::TOKEN_BOOL:
        case TokenType::TOKEN_NULL:
        case TokenType::TOKEN_RPAREN:
        case TokenType::TOKEN_RBRACKET:
        case TokenType::TOKEN_RBRACE:
        case TokenType::TOKEN_PLUS_PLUS:
        case TokenType::TOKEN_MINUS_MINUS:
        case TokenType::TOKEN_RETURN:
            return true;
        default:
            return false;
    }
}

void Lexer::scanToken() {
    char c = advance();
    switch (c) {
        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace
            break;

        case '\n': {
            if (!tokens.empty() && canEndStatement(tokens.back().type)) {
                tokens.emplace_back(TokenType::TOKEN_NEWLINE, "\n", SourceLocation(filename, line, startColumn));
            }
            line++;
            column = 1;
            break;
        }

        case '(': addToken(TokenType::TOKEN_LPAREN); break;
        case ')': addToken(TokenType::TOKEN_RPAREN); break;
        case '{': addToken(TokenType::TOKEN_LBRACE); break;
        case '}': addToken(TokenType::TOKEN_RBRACE); break;
        case '[': addToken(TokenType::TOKEN_LBRACKET); break;
        case ']': addToken(TokenType::TOKEN_RBRACKET); break;
        case ',': addToken(TokenType::TOKEN_COMMA); break;
        case ':': addToken(TokenType::TOKEN_COLON); break;
        case '.': addToken(TokenType::TOKEN_DOT); break;
        case '?': addToken(TokenType::TOKEN_QUESTION); break;
        case ';': addToken(TokenType::TOKEN_SEMICOLON); break;

        case '+':
            if (match('+')) addToken(TokenType::TOKEN_PLUS_PLUS);
            else if (match('=')) addToken(TokenType::TOKEN_PLUS_ASSIGN);
            else addToken(TokenType::TOKEN_PLUS);
            break;

        case '-':
            if (match('-')) addToken(TokenType::TOKEN_MINUS_MINUS);
            else if (match('=')) addToken(TokenType::TOKEN_MINUS_ASSIGN);
            else addToken(TokenType::TOKEN_MINUS);
            break;

        case '*':
            if (match('=')) addToken(TokenType::TOKEN_STAR_ASSIGN);
            else addToken(TokenType::TOKEN_STAR);
            break;

        case '%':
            addToken(TokenType::TOKEN_PERCENT);
            break;

        case '!':
            if (match('=')) addToken(TokenType::TOKEN_BANG_EQUAL);
            else addToken(TokenType::TOKEN_BANG);
            break;

        case '=':
            if (match('=')) addToken(TokenType::TOKEN_EQUAL_EQUAL);
            else addToken(TokenType::TOKEN_ASSIGN);
            break;

        case '<':
            if (match('=')) addToken(TokenType::TOKEN_LESS_EQUAL);
            else addToken(TokenType::TOKEN_LESS);
            break;

        case '>':
            if (match('=')) addToken(TokenType::TOKEN_GREATER_EQUAL);
            else addToken(TokenType::TOKEN_GREATER);
            break;

        case '&':
            if (match('&')) addToken(TokenType::TOKEN_AND_AND);
            else throw MazException(SourceLocation(filename, line, startColumn), "Unexpected character '&', did you mean '&&'?");
            break;

        case '|':
            if (match('|')) addToken(TokenType::TOKEN_OR_OR);
            else throw MazException(SourceLocation(filename, line, startColumn), "Unexpected character '|', did you mean '||'?");
            break;

        case '/':
            if (match('/')) {
                // Single line comment
                while (peek() != '\n' && !isAtEnd()) advance();
            } else if (match('*')) {
                multilineComment();
            } else if (match('=')) {
                addToken(TokenType::TOKEN_SLASH_ASSIGN);
            } else {
                addToken(TokenType::TOKEN_SLASH);
            }
            break;

        case '"':
            stringLiteral();
            break;

        default:
            if (std::isdigit(c)) {
                number();
            } else if (std::isalpha(c) || c == '_') {
                identifier();
            } else {
                throw MazException(SourceLocation(filename, line, startColumn),
                    std::string("Unexpected character: '") + c + "'");
            }
            break;
    }
}

void Lexer::stringLiteral() {
    std::string val;
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') {
            line++;
            column = 1;
        }
        if (peek() == '\\') {
            advance(); // Consume escape '\'
            if (isAtEnd()) break;
            char esc = advance();
            switch (esc) {
                case 'n': val.push_back('\n'); break;
                case 't': val.push_back('\t'); break;
                case 'r': val.push_back('\r'); break;
                case '\\': val.push_back('\\'); break;
                case '"': val.push_back('"'); break;
                default: val.push_back(esc); break;
            }
        } else {
            val.push_back(advance());
        }
    }

    if (isAtEnd()) {
        throw MazException(SourceLocation(filename, line, startColumn), "Unterminated string literal.");
    }

    // Consume the closing quote
    advance();
    addToken(TokenType::TOKEN_STRING, val);
}

void Lexer::number() {
    while (std::isdigit(peek())) advance();

    // Look for fractional part
    if (peek() == '.' && std::isdigit(peekNext())) {
        advance(); // consume '.'
        while (std::isdigit(peek())) advance();
        addToken(TokenType::TOKEN_FLOAT);
    } else {
        addToken(TokenType::TOKEN_INT);
    }
}

void Lexer::identifier() {
    while (std::isalnum(peek()) || peek() == '_') advance();

    std::string text = source.substr(start, current - start);
    auto it = keywords.find(text);
    if (it != keywords.end()) {
        addToken(it->second, text);
    } else {
        addToken(TokenType::TOKEN_IDENTIFIER, text);
    }
}

void Lexer::multilineComment() {
    while (!isAtEnd()) {
        if (peek() == '*' && peekNext() == '/') {
            advance(); // consume '*'
            advance(); // consume '/'
            return;
        }
        if (peek() == '\n') {
            line++;
            column = 1;
        }
        advance();
    }
    throw MazException(SourceLocation(filename, line, startColumn), "Unterminated multi-line comment.");
}

void Lexer::addToken(TokenType type) {
    std::string text = source.substr(start, current - start);
    addToken(type, text);
}

void Lexer::addToken(TokenType type, std::string lexeme) {
    tokens.emplace_back(type, std::move(lexeme), SourceLocation(filename, line, startColumn));
}

} // namespace maz


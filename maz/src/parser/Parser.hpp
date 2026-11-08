#pragma once
#include "../common/Token.hpp"
#include "../common/Error.hpp"
#include "../ast/AST.hpp"
#include <vector>
#include <memory>

namespace maz {

class Parser {
public:
    explicit Parser(std::vector<Token> tokens);
    std::shared_ptr<Program> parse();

private:
    std::vector<Token> tokens;
    size_t current{0};

    // Helper navigators
    bool isAtEnd() const;
    const Token& peek() const;
    const Token& previous() const;
    Token advance();
    bool check(TokenType type) const;
    bool match(std::initializer_list<TokenType> types);
    Token consume(TokenType type, const std::string& message);
    void skipNewlines();

    // Statements
    StmtPtr declaration();
    StmtPtr constDeclaration();
    StmtPtr dynDeclaration();
    StmtPtr newDeclaration();
    StmtPtr globalDeclaration();
    StmtPtr typedDeclaration(ValueType type);
    StmtPtr functionDeclaration();
    StmtPtr statement();
    StmtPtr ifStatement();
    StmtPtr whileStatement();
    StmtPtr forStatement();
    StmtPtr returnStatement();
    std::shared_ptr<BlockStmt> blockStatement();
    StmtPtr expressionStatement();

    // Expressions
    ExprPtr expression();
    ExprPtr assignment();
    ExprPtr logicalOr();
    ExprPtr logicalAnd();
    ExprPtr equality();
    ExprPtr comparison();
    ExprPtr term();
    ExprPtr factor();
    ExprPtr unary();
    ExprPtr postfix();
    ExprPtr call(ExprPtr expr);
    ExprPtr primary();

    // Error recovery
    void synchronize();
};

} // namespace maz


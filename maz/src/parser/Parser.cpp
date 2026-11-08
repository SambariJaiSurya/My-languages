#include "Parser.hpp"

namespace maz {

Parser::Parser(std::vector<Token> t) : tokens(std::move(t)) {}

std::shared_ptr<Program> Parser::parse() {
    std::vector<StmtPtr> statements;
    skipNewlines();
    while (!isAtEnd()) {
        try {
            StmtPtr stmt = declaration();
            if (stmt) {
                statements.push_back(stmt);
            }
        } catch (const MazException& e) {
            synchronize();
            throw; // Re-throw to be captured by error reporter
        }
        skipNewlines();
    }
    return std::make_shared<Program>(std::move(statements));
}

bool Parser::isAtEnd() const {
    return peek().type == TokenType::TOKEN_EOF;
}

const Token& Parser::peek() const {
    return tokens[current];
}

const Token& Parser::previous() const {
    return tokens[current - 1];
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

bool Parser::match(std::initializer_list<TokenType> types) {
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) return advance();
    throw MazException(peek().location, message + " (got '" + peek().lexeme + "')");
}

void Parser::skipNewlines() {
    while (check(TokenType::TOKEN_NEWLINE) || check(TokenType::TOKEN_SEMICOLON)) {
        advance();
    }
}

StmtPtr Parser::declaration() {
    skipNewlines();
    if (match({TokenType::TOKEN_DEF})) {
        return functionDeclaration();
    }
    if (match({TokenType::TOKEN_CONST})) {
        return constDeclaration();
    }
    if (match({TokenType::TOKEN_DYN})) {
        return dynDeclaration();
    }
    if (match({TokenType::TOKEN_NEW})) {
        return newDeclaration();
    }
    if (match({TokenType::TOKEN_GLOBAL})) {
        return globalDeclaration();
    }
    if (match({TokenType::TOKEN_TYPE_INT})) {
        return typedDeclaration(ValueType::Int);
    }
    if (match({TokenType::TOKEN_TYPE_FLOAT})) {
        return typedDeclaration(ValueType::Float);
    }
    if (match({TokenType::TOKEN_TYPE_DOUBLE})) {
        return typedDeclaration(ValueType::Float);
    }
    if (match({TokenType::TOKEN_TYPE_STRING})) {
        return typedDeclaration(ValueType::String);
    }
    if (match({TokenType::TOKEN_TYPE_BOOL})) {
        return typedDeclaration(ValueType::Bool);
    }
    if (match({TokenType::TOKEN_TYPE_CHAR})) {
        return typedDeclaration(ValueType::String);
    }
    return statement();
}

StmtPtr Parser::constDeclaration() {
    ValueType expType = ValueType::Null;
    if (match({TokenType::TOKEN_TYPE_INT})) expType = ValueType::Int;
    else if (match({TokenType::TOKEN_TYPE_FLOAT})) expType = ValueType::Float;
    else if (match({TokenType::TOKEN_TYPE_DOUBLE})) expType = ValueType::Float;
    else if (match({TokenType::TOKEN_TYPE_STRING})) expType = ValueType::String;
    else if (match({TokenType::TOKEN_TYPE_BOOL})) expType = ValueType::Bool;
    else if (match({TokenType::TOKEN_TYPE_CHAR})) expType = ValueType::String;

    std::vector<std::shared_ptr<VarDeclStmt>> decls;
    do {
        Token name = consume(TokenType::TOKEN_IDENTIFIER, "Expected constant name.");
        consume(TokenType::TOKEN_ASSIGN, "Expected '=' in constant initialization.");
        ExprPtr initializer = expression();
        decls.push_back(std::make_shared<VarDeclStmt>(name, initializer, true, false, false, expType));
    } while (match({TokenType::TOKEN_COMMA}));

    if (decls.size() == 1) {
        return decls[0];
    }
    return std::make_shared<MultiVarDeclStmt>(std::move(decls));
}

StmtPtr Parser::dynDeclaration() {
    std::vector<std::shared_ptr<VarDeclStmt>> decls;
    do {
        Token name = consume(TokenType::TOKEN_IDENTIFIER, "Expected variable name after 'dyn'.");
        ExprPtr initializer = nullptr;
        if (match({TokenType::TOKEN_ASSIGN})) {
            initializer = expression();
        } else {
            initializer = std::make_shared<LiteralExpr>(Value::makeNull(), name.location);
        }
        decls.push_back(std::make_shared<VarDeclStmt>(name, initializer, false, true, false, ValueType::Null));
    } while (match({TokenType::TOKEN_COMMA}));

    if (decls.size() == 1) {
        return decls[0];
    }
    return std::make_shared<MultiVarDeclStmt>(std::move(decls));
}

StmtPtr Parser::newDeclaration() {
    ValueType expType = ValueType::Null;
    if (match({TokenType::TOKEN_TYPE_INT})) expType = ValueType::Int;
    else if (match({TokenType::TOKEN_TYPE_FLOAT})) expType = ValueType::Float;
    else if (match({TokenType::TOKEN_TYPE_DOUBLE})) expType = ValueType::Float;
    else if (match({TokenType::TOKEN_TYPE_STRING})) expType = ValueType::String;
    else if (match({TokenType::TOKEN_TYPE_BOOL})) expType = ValueType::Bool;
    else if (match({TokenType::TOKEN_TYPE_CHAR})) expType = ValueType::String;

    Token name = consume(TokenType::TOKEN_IDENTIFIER, "Expected variable name after 'new'.");
    ExprPtr initializer = nullptr;
    if (match({TokenType::TOKEN_ASSIGN})) {
        initializer = expression();
    }
    return std::make_shared<VarDeclStmt>(name, initializer, false, false, true, expType);
}

StmtPtr Parser::globalDeclaration() {
    Token name = consume(TokenType::TOKEN_IDENTIFIER, "Expected variable name after 'global'.");
    return std::make_shared<GlobalStmt>(name);
}

StmtPtr Parser::typedDeclaration(ValueType type) {
    std::vector<std::shared_ptr<VarDeclStmt>> decls;
    do {
        Token name = consume(TokenType::TOKEN_IDENTIFIER, "Expected variable name in declaration.");
        ExprPtr initializer = nullptr;
        if (match({TokenType::TOKEN_ASSIGN})) {
            initializer = expression();
        }
        decls.push_back(std::make_shared<VarDeclStmt>(name, initializer, false, false, false, type));
    } while (match({TokenType::TOKEN_COMMA}));

    if (decls.size() == 1) {
        return decls[0];
    }
    return std::make_shared<MultiVarDeclStmt>(std::move(decls));
}

StmtPtr Parser::functionDeclaration() {
    Token name = consume(TokenType::TOKEN_IDENTIFIER, "Expected function name.");
    consume(TokenType::TOKEN_LPAREN, "Expected '(' after function name.");

    std::vector<std::pair<Token, ExprPtr>> parameters;
    if (!check(TokenType::TOKEN_RPAREN)) {
        do {
            Token paramName = consume(TokenType::TOKEN_IDENTIFIER, "Expected parameter name.");
            ExprPtr defaultVal = nullptr;
            if (match({TokenType::TOKEN_ASSIGN})) {
                defaultVal = expression();
            }
            parameters.emplace_back(paramName, defaultVal);
        } while (match({TokenType::TOKEN_COMMA}));
    }
    consume(TokenType::TOKEN_RPAREN, "Expected ')' after parameters.");
    skipNewlines();

    consume(TokenType::TOKEN_LBRACE, "Expected '{' before function body.");
    std::shared_ptr<BlockStmt> body = blockStatement();

    return std::make_shared<FunctionStmt>(name, std::move(parameters), body);
}

StmtPtr Parser::statement() {
    skipNewlines();
    if (match({TokenType::TOKEN_IF})) {
        return ifStatement();
    }
    if (match({TokenType::TOKEN_WHILE})) {
        return whileStatement();
    }
    if (match({TokenType::TOKEN_FOR})) {
        return forStatement();
    }
    if (match({TokenType::TOKEN_RETURN})) {
        return returnStatement();
    }
    if (match({TokenType::TOKEN_LBRACE})) {
        return blockStatement();
    }
    return expressionStatement();
}

StmtPtr Parser::ifStatement() {
    consume(TokenType::TOKEN_LPAREN, "Expected '(' after 'if'.");
    ExprPtr condition = expression();
    consume(TokenType::TOKEN_RPAREN, "Expected ')' after condition.");
    skipNewlines();

    StmtPtr thenBranch = statement();
    StmtPtr elseBranch = nullptr;

    skipNewlines();
    if (match({TokenType::TOKEN_ELSE})) {
        skipNewlines();
        elseBranch = statement();
    }

    return std::make_shared<IfStmt>(condition, thenBranch, elseBranch);
}

StmtPtr Parser::whileStatement() {
    consume(TokenType::TOKEN_LPAREN, "Expected '(' after 'while'.");
    ExprPtr condition = expression();
    consume(TokenType::TOKEN_RPAREN, "Expected ')' after while condition.");
    skipNewlines();

    StmtPtr body = statement();
    return std::make_shared<WhileStmt>(condition, body);
}

// Rule 7: Three-part loop with comma separation and 'new' scoping
StmtPtr Parser::forStatement() {
    consume(TokenType::TOKEN_LPAREN, "Expected '(' after 'for'.");

    bool hasNew = false;
    StmtPtr initializer = nullptr;

    if (match({TokenType::TOKEN_NEW})) {
        hasNew = true;
        Token name = consume(TokenType::TOKEN_IDENTIFIER, "Expected loop variable name after 'new'.");
        consume(TokenType::TOKEN_ASSIGN, "Expected '=' in loop variable initialization.");
        ExprPtr initVal = expression();
        initializer = std::make_shared<VarDeclStmt>(name, initVal, false, false);
    } else if (!check(TokenType::TOKEN_COMMA)) {
        ExprPtr expr = expression();
        initializer = std::make_shared<ExpressionStmt>(expr);
    }

    // Rule 7: clauses separated by commas!
    consume(TokenType::TOKEN_COMMA, "Expected ',' after for loop initialization clause.");

    ExprPtr condition = nullptr;
    if (!check(TokenType::TOKEN_COMMA)) {
        condition = expression();
    }
    consume(TokenType::TOKEN_COMMA, "Expected ',' after for loop condition clause.");

    ExprPtr update = nullptr;
    if (!check(TokenType::TOKEN_RPAREN)) {
        update = expression();
    }
    consume(TokenType::TOKEN_RPAREN, "Expected ')' after for clauses.");
    skipNewlines();

    StmtPtr body = statement();
    return std::make_shared<ForStmt>(hasNew, initializer, condition, update, body);
}

StmtPtr Parser::returnStatement() {
    Token keyword = previous();
    ExprPtr value = nullptr;
    if (!check(TokenType::TOKEN_NEWLINE) && !check(TokenType::TOKEN_SEMICOLON) && !check(TokenType::TOKEN_RBRACE) && !isAtEnd()) {
        value = expression();
    }
    return std::make_shared<ReturnStmt>(keyword, value);
}

std::shared_ptr<BlockStmt> Parser::blockStatement() {
    std::vector<StmtPtr> statements;
    skipNewlines();
    while (!check(TokenType::TOKEN_RBRACE) && !isAtEnd()) {
        statements.push_back(declaration());
        skipNewlines();
    }
    consume(TokenType::TOKEN_RBRACE, "Expected '}' after block.");
    return std::make_shared<BlockStmt>(std::move(statements));
}

StmtPtr Parser::expressionStatement() {
    ExprPtr expr = expression();
    return std::make_shared<ExpressionStmt>(expr);
}

ExprPtr Parser::expression() {
    return assignment();
}

ExprPtr Parser::assignment() {
    bool isForce = match({TokenType::TOKEN_FORCE});

    ExprPtr expr = logicalOr();

    if (match({TokenType::TOKEN_ASSIGN})) {
        Token equals = previous();
        ExprPtr value = assignment();

        if (auto varExpr = std::dynamic_pointer_cast<VariableExpr>(expr)) {
            return std::make_shared<AssignExpr>(varExpr->name, value, isForce);
        }
        throw MazException(equals.location, "Invalid assignment target.");
    }

    // Compound assignments: +=, -=, *=, /=
    if (match({TokenType::TOKEN_PLUS_ASSIGN, TokenType::TOKEN_MINUS_ASSIGN,
               TokenType::TOKEN_STAR_ASSIGN, TokenType::TOKEN_SLASH_ASSIGN})) {
        Token opToken = previous();
        ExprPtr value = assignment();

        if (auto varExpr = std::dynamic_pointer_cast<VariableExpr>(expr)) {
            TokenType binaryOpType;
            if (opToken.type == TokenType::TOKEN_PLUS_ASSIGN) binaryOpType = TokenType::TOKEN_PLUS;
            else if (opToken.type == TokenType::TOKEN_MINUS_ASSIGN) binaryOpType = TokenType::TOKEN_MINUS;
            else if (opToken.type == TokenType::TOKEN_STAR_ASSIGN) binaryOpType = TokenType::TOKEN_STAR;
            else binaryOpType = TokenType::TOKEN_SLASH;

            Token binaryToken(binaryOpType, opToken.lexeme.substr(0, 1), opToken.location);
            ExprPtr binaryExpr = std::make_shared<BinaryExpr>(expr, binaryToken, value);
            return std::make_shared<AssignExpr>(varExpr->name, binaryExpr, false);
        }
        throw MazException(opToken.location, "Invalid compound assignment target.");
    }

    if (isForce) {
        throw MazException(previous().location, "'force' must be used with an assignment (e.g. force x = value).");
    }

    return expr;
}

ExprPtr Parser::logicalOr() {
    ExprPtr expr = logicalAnd();
    while (match({TokenType::TOKEN_OR_OR})) {
        Token op = previous();
        ExprPtr right = logicalAnd();
        expr = std::make_shared<BinaryExpr>(expr, op, right);
    }
    return expr;
}

ExprPtr Parser::logicalAnd() {
    ExprPtr expr = equality();
    while (match({TokenType::TOKEN_AND_AND})) {
        Token op = previous();
        ExprPtr right = equality();
        expr = std::make_shared<BinaryExpr>(expr, op, right);
    }
    return expr;
}

ExprPtr Parser::equality() {
    ExprPtr expr = comparison();
    while (match({TokenType::TOKEN_BANG_EQUAL, TokenType::TOKEN_EQUAL_EQUAL})) {
        Token op = previous();
        ExprPtr right = comparison();
        expr = std::make_shared<BinaryExpr>(expr, op, right);
    }
    return expr;
}

ExprPtr Parser::comparison() {
    ExprPtr expr = term();
    while (match({TokenType::TOKEN_GREATER, TokenType::TOKEN_GREATER_EQUAL,
                  TokenType::TOKEN_LESS, TokenType::TOKEN_LESS_EQUAL})) {
        Token op = previous();
        ExprPtr right = term();
        expr = std::make_shared<BinaryExpr>(expr, op, right);
    }
    return expr;
}

ExprPtr Parser::term() {
    ExprPtr expr = factor();
    while (match({TokenType::TOKEN_PLUS, TokenType::TOKEN_MINUS})) {
        Token op = previous();
        ExprPtr right = factor();
        expr = std::make_shared<BinaryExpr>(expr, op, right);
    }
    return expr;
}

ExprPtr Parser::factor() {
    ExprPtr expr = unary();
    while (match({TokenType::TOKEN_STAR, TokenType::TOKEN_SLASH, TokenType::TOKEN_PERCENT})) {
        Token op = previous();
        ExprPtr right = unary();
        expr = std::make_shared<BinaryExpr>(expr, op, right);
    }
    return expr;
}

ExprPtr Parser::unary() {
    if (match({TokenType::TOKEN_BANG, TokenType::TOKEN_MINUS})) {
        Token op = previous();
        ExprPtr right = unary();
        return std::make_shared<UnaryExpr>(op, right, true);
    }
    if (match({TokenType::TOKEN_PLUS_PLUS, TokenType::TOKEN_MINUS_MINUS})) {
        Token op = previous();
        ExprPtr right = unary();
        if (auto varExpr = std::dynamic_pointer_cast<VariableExpr>(right)) {
            return std::make_shared<UpdateExpr>(varExpr->name, op, true);
        }
        throw MazException(op.location, "Prefix increment/decrement target must be a variable.");
    }
    return postfix();
}

ExprPtr Parser::postfix() {
    ExprPtr expr = primary();

    while (true) {
        if (match({TokenType::TOKEN_LPAREN})) {
            expr = call(expr);
        } else if (match({TokenType::TOKEN_PLUS_PLUS, TokenType::TOKEN_MINUS_MINUS})) {
            Token op = previous();
            if (auto varExpr = std::dynamic_pointer_cast<VariableExpr>(expr)) {
                expr = std::make_shared<UpdateExpr>(varExpr->name, op, false);
            } else {
                throw MazException(op.location, "Postfix increment/decrement target must be a variable.");
            }
        } else {
            break;
        }
    }
    return expr;
}

ExprPtr Parser::call(ExprPtr callee) {
    Token paren = previous();
    std::vector<ExprPtr> arguments;
    if (!check(TokenType::TOKEN_RPAREN)) {
        do {
            arguments.push_back(expression());
        } while (match({TokenType::TOKEN_COMMA}));
    }
    consume(TokenType::TOKEN_RPAREN, "Expected ')' after arguments.");
    return std::make_shared<CallExpr>(callee, paren, std::move(arguments));
}

ExprPtr Parser::primary() {
    if (match({TokenType::TOKEN_BOOL})) {
        bool val = (previous().lexeme == "true");
        return std::make_shared<LiteralExpr>(Value(val), previous().location);
    }
    if (match({TokenType::TOKEN_NULL})) {
        return std::make_shared<LiteralExpr>(Value::makeNull(), previous().location);
    }
    if (match({TokenType::TOKEN_INT})) {
        int64_t val = std::stoll(previous().lexeme);
        return std::make_shared<LiteralExpr>(Value(val), previous().location);
    }
    if (match({TokenType::TOKEN_FLOAT})) {
        double val = std::stod(previous().lexeme);
        return std::make_shared<LiteralExpr>(Value(val), previous().location);
    }
    if (match({TokenType::TOKEN_STRING})) {
        return std::make_shared<LiteralExpr>(Value(previous().lexeme), previous().location);
    }
    if (match({TokenType::TOKEN_IDENTIFIER})) {
        return std::make_shared<VariableExpr>(previous());
    }
    if (match({TokenType::TOKEN_LPAREN})) {
        ExprPtr expr = expression();
        consume(TokenType::TOKEN_RPAREN, "Expected ')' after expression.");
        return expr;
    }

    throw MazException(peek().location, "Unexpected token in expression: '" + peek().lexeme + "'");
}

void Parser::synchronize() {
    advance();
    while (!isAtEnd()) {
        if (previous().type == TokenType::TOKEN_NEWLINE || previous().type == TokenType::TOKEN_SEMICOLON) return;

        switch (peek().type) {
            case TokenType::TOKEN_CLASS:
            case TokenType::TOKEN_DEF:
            case TokenType::TOKEN_FOR:
            case TokenType::TOKEN_IF:
            case TokenType::TOKEN_WHILE:
            case TokenType::TOKEN_RETURN:
            case TokenType::TOKEN_CONST:
            case TokenType::TOKEN_DYN:
                return;
            default:
                break;
        }
        advance();
    }
}

} // namespace maz


#pragma once
#include "../common/Token.hpp"
#include "../common/Value.hpp"
#include <memory>
#include <vector>

namespace maz {

class ASTVisitor;

// Base Expression
class Expr {
public:
    virtual ~Expr() = default;
    virtual void accept(ASTVisitor& visitor) = 0;
};

using ExprPtr = std::shared_ptr<Expr>;

// Base Statement
class Stmt {
public:
    virtual ~Stmt() = default;
    virtual void accept(ASTVisitor& visitor) = 0;
};

using StmtPtr = std::shared_ptr<Stmt>;

// Forward declarations of AST nodes
class LiteralExpr;
class VariableExpr;
class BinaryExpr;
class UnaryExpr;
class AssignExpr;
class UpdateExpr;
class CallExpr;

class ExpressionStmt;
class VarDeclStmt;
class MultiVarDeclStmt;
class BlockStmt;
class IfStmt;
class WhileStmt;
class ForStmt;
class FunctionStmt;
class ReturnStmt;
class BreakStmt;
class ContinueStmt;
class Program;

class GlobalStmt;

// Visitor Interface
class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;

    virtual void visitLiteralExpr(LiteralExpr& expr) = 0;
    virtual void visitVariableExpr(VariableExpr& expr) = 0;
    virtual void visitBinaryExpr(BinaryExpr& expr) = 0;
    virtual void visitUnaryExpr(UnaryExpr& expr) = 0;
    virtual void visitAssignExpr(AssignExpr& expr) = 0;
    virtual void visitUpdateExpr(UpdateExpr& expr) = 0;
    virtual void visitCallExpr(CallExpr& expr) = 0;

    virtual void visitExpressionStmt(ExpressionStmt& stmt) = 0;
    virtual void visitVarDeclStmt(VarDeclStmt& stmt) = 0;
    virtual void visitMultiVarDeclStmt(MultiVarDeclStmt& stmt) = 0;
    virtual void visitGlobalStmt(GlobalStmt& stmt) = 0;
    virtual void visitBlockStmt(BlockStmt& stmt) = 0;
    virtual void visitIfStmt(IfStmt& stmt) = 0;
    virtual void visitWhileStmt(WhileStmt& stmt) = 0;
    virtual void visitForStmt(ForStmt& stmt) = 0;
    virtual void visitFunctionStmt(FunctionStmt& stmt) = 0;
    virtual void visitReturnStmt(ReturnStmt& stmt) = 0;
    virtual void visitBreakStmt(BreakStmt& stmt) = 0;
    virtual void visitContinueStmt(ContinueStmt& stmt) = 0;
    virtual void visitProgram(Program& program) = 0;
};

// Expression Implementations
class LiteralExpr : public Expr {
public:
    Value value;
    SourceLocation location;

    LiteralExpr(Value val, SourceLocation loc)
        : value(std::move(val)), location(std::move(loc)) {}

    void accept(ASTVisitor& visitor) override { visitor.visitLiteralExpr(*this); }
};

class VariableExpr : public Expr {
public:
    Token name;

    explicit VariableExpr(Token n) : name(std::move(n)) {}

    void accept(ASTVisitor& visitor) override { visitor.visitVariableExpr(*this); }
};

class BinaryExpr : public Expr {
public:
    ExprPtr left;
    Token op;
    ExprPtr right;

    BinaryExpr(ExprPtr l, Token o, ExprPtr r)
        : left(std::move(l)), op(std::move(o)), right(std::move(r)) {}

    void accept(ASTVisitor& visitor) override { visitor.visitBinaryExpr(*this); }
};

class UnaryExpr : public Expr {
public:
    Token op;
    ExprPtr right;
    bool isPrefix;

    UnaryExpr(Token o, ExprPtr r, bool prefix = true)
        : op(std::move(o)), right(std::move(r)), isPrefix(prefix) {}

    void accept(ASTVisitor& visitor) override { visitor.visitUnaryExpr(*this); }
};

class AssignExpr : public Expr {
public:
    Token name;
    ExprPtr value;
    bool isForce{false};

    AssignExpr(Token n, ExprPtr val, bool force = false)
        : name(std::move(n)), value(std::move(val)), isForce(force) {}

    void accept(ASTVisitor& visitor) override { visitor.visitAssignExpr(*this); }
};

class UpdateExpr : public Expr {
public:
    Token name;
    Token op; // ++ or --
    bool isPrefix;

    UpdateExpr(Token n, Token o, bool prefix)
        : name(std::move(n)), op(std::move(o)), isPrefix(prefix) {}

    void accept(ASTVisitor& visitor) override { visitor.visitUpdateExpr(*this); }
};

class CallExpr : public Expr {
public:
    ExprPtr callee;
    Token paren;
    std::vector<ExprPtr> arguments;

    CallExpr(ExprPtr c, Token p, std::vector<ExprPtr> args)
        : callee(std::move(c)), paren(std::move(p)), arguments(std::move(args)) {}

    void accept(ASTVisitor& visitor) override { visitor.visitCallExpr(*this); }
};

// Statement Implementations
class ExpressionStmt : public Stmt {
public:
    ExprPtr expression;

    explicit ExpressionStmt(ExprPtr expr) : expression(std::move(expr)) {}

    void accept(ASTVisitor& visitor) override { visitor.visitExpressionStmt(*this); }
};

class VarDeclStmt : public Stmt {
public:
    Token name;
    ExprPtr initializer;
    bool isConst{false};
    bool isDyn{false};
    bool isNew{false};
    ValueType explicitType{ValueType::Null};
    bool isTimer{false};

    VarDeclStmt(Token n, ExprPtr init, bool c = false, bool d = false, bool nw = false, ValueType expType = ValueType::Null, bool timer = false)
        : name(std::move(n)), initializer(std::move(init)), isConst(c), isDyn(d), isNew(nw), explicitType(expType), isTimer(timer) {}

    void accept(ASTVisitor& visitor) override { visitor.visitVarDeclStmt(*this); }
};

class MultiVarDeclStmt : public Stmt {
public:
    std::vector<std::shared_ptr<VarDeclStmt>> declarations;

    explicit MultiVarDeclStmt(std::vector<std::shared_ptr<VarDeclStmt>> decls)
        : declarations(std::move(decls)) {}

    void accept(ASTVisitor& visitor) override { visitor.visitMultiVarDeclStmt(*this); }
};

class GlobalStmt : public Stmt {
public:
    Token name;

    explicit GlobalStmt(Token n) : name(std::move(n)) {}

    void accept(ASTVisitor& visitor) override { visitor.visitGlobalStmt(*this); }
};

class BlockStmt : public Stmt {
public:
    std::vector<StmtPtr> statements;

    explicit BlockStmt(std::vector<StmtPtr> stmts) : statements(std::move(stmts)) {}

    void accept(ASTVisitor& visitor) override { visitor.visitBlockStmt(*this); }
};

class IfStmt : public Stmt {
public:
    ExprPtr condition;
    StmtPtr thenBranch;
    StmtPtr elseBranch; // can be null

    IfStmt(ExprPtr cond, StmtPtr thenBr, StmtPtr elseBr = nullptr)
        : condition(std::move(cond)), thenBranch(std::move(thenBr)), elseBranch(std::move(elseBr)) {}

    void accept(ASTVisitor& visitor) override { visitor.visitIfStmt(*this); }
};

class WhileStmt : public Stmt {
public:
    std::string label;
    ExprPtr condition;
    StmtPtr body;

    WhileStmt(ExprPtr cond, StmtPtr b, std::string lbl = "")
        : label(std::move(lbl)), condition(std::move(cond)), body(std::move(b)) {}

    void accept(ASTVisitor& visitor) override { visitor.visitWhileStmt(*this); }
};

class ForStmt : public Stmt {
public:
    std::string label;
    bool hasNew{false};
    StmtPtr initializer; // e.g. VarDeclStmt or ExpressionStmt (can be null)
    ExprPtr condition;   // can be null
    ExprPtr update;      // can be null
    StmtPtr body;

    ForStmt(bool isNew, StmtPtr init, ExprPtr cond, ExprPtr upd, StmtPtr b, std::string lbl = "")
        : label(std::move(lbl)), hasNew(isNew), initializer(std::move(init)), condition(std::move(cond)),
          update(std::move(upd)), body(std::move(b)) {}

    void accept(ASTVisitor& visitor) override { visitor.visitForStmt(*this); }
};

class FunctionStmt : public Stmt {
public:
    Token name;
    std::vector<std::pair<Token, ExprPtr>> parameters; // token name and optional default expr
    std::shared_ptr<BlockStmt> body;

    FunctionStmt(Token n, std::vector<std::pair<Token, ExprPtr>> params, std::shared_ptr<BlockStmt> b)
        : name(std::move(n)), parameters(std::move(params)), body(std::move(b)) {}

    void accept(ASTVisitor& visitor) override { visitor.visitFunctionStmt(*this); }
};

class ReturnStmt : public Stmt {
public:
    Token keyword;
    ExprPtr value; // can be null

    ReturnStmt(Token kw, ExprPtr val)
        : keyword(std::move(kw)), value(std::move(val)) {}

    void accept(ASTVisitor& visitor) override { visitor.visitReturnStmt(*this); }
};

class BreakStmt : public Stmt {
public:
    Token keyword;
    int depth{1}; // 1-based loop depth (or 0 if label-based)
    std::string label; // target label if specified

    BreakStmt(Token kw, int d = 1, std::string lbl = "")
        : keyword(std::move(kw)), depth(d), label(std::move(lbl)) {}

    void accept(ASTVisitor& visitor) override { visitor.visitBreakStmt(*this); }
};

class ContinueStmt : public Stmt {
public:
    Token keyword;
    int depth{1}; // 1-based loop depth (or 0 if label-based)
    std::string label; // target label if specified

    ContinueStmt(Token kw, int d = 1, std::string lbl = "")
        : keyword(std::move(kw)), depth(d), label(std::move(lbl)) {}

    void accept(ASTVisitor& visitor) override { visitor.visitContinueStmt(*this); }
};

class Program : public Stmt {
public:
    std::vector<StmtPtr> statements;

    explicit Program(std::vector<StmtPtr> stmts) : statements(std::move(stmts)) {}

    void accept(ASTVisitor& visitor) override { visitor.visitProgram(*this); }
};

} // namespace maz


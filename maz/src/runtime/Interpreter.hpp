#pragma once
#include "../ast/AST.hpp"
#include "Environment.hpp"
#include "../common/Value.hpp"
#include <memory>
#include <vector>

namespace maz {

class Interpreter : public ASTVisitor {
public:
    Interpreter();

    void interpret(const std::shared_ptr<Program>& program);
    Value evaluate(Expr& expr);
    void execute(Stmt& stmt);
    void executeBlock(const std::vector<StmtPtr>& statements, std::shared_ptr<Environment> env);

    // Visitor methods for expressions
    void visitLiteralExpr(LiteralExpr& expr) override;
    void visitVariableExpr(VariableExpr& expr) override;
    void visitBinaryExpr(BinaryExpr& expr) override;
    void visitUnaryExpr(UnaryExpr& expr) override;
    void visitAssignExpr(AssignExpr& expr) override;
    void visitUpdateExpr(UpdateExpr& expr) override;
    void visitCallExpr(CallExpr& expr) override;

    // Visitor methods for statements
    void visitExpressionStmt(ExpressionStmt& stmt) override;
    void visitVarDeclStmt(VarDeclStmt& stmt) override;
    void visitMultiVarDeclStmt(MultiVarDeclStmt& stmt) override;
    void visitGlobalStmt(GlobalStmt& stmt) override;
    void visitBlockStmt(BlockStmt& stmt) override;
    void visitIfStmt(IfStmt& stmt) override;
    void visitWhileStmt(WhileStmt& stmt) override;
    void visitForStmt(ForStmt& stmt) override;
    void visitFunctionStmt(FunctionStmt& stmt) override;
    void visitReturnStmt(ReturnStmt& stmt) override;
    void visitBreakStmt(BreakStmt& stmt) override;
    void visitContinueStmt(ContinueStmt& stmt) override;
    void visitProgram(Program& program) override;

    std::shared_ptr<Environment> getGlobals() { return globals; }

private:
    std::shared_ptr<Environment> globals;
    std::shared_ptr<Environment> currentEnv;
    Value lastEvaluatedValue;

    void registerBuiltins();
};

} // namespace maz


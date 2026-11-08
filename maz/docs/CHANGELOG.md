# Changelog

All notable changes to the MAZ programming language will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [0.2.0-alpha] - 2026-11-08

### Added
- **Rule 75 Enhanced Loop Control System:**
  - Basic `break` and `continue` statements for both `for` and `while` loops.
  - Multi-level loop control: `break N` and `continue N` for unwinding/continuing N enclosing loop levels.
  - Labelled loops: `label: for (...)` and `label: while (...)` with `break label` and `continue label`.
  - Strict compile-time validation: ensures loop depths are positive compile-time integer constants <= active loop count, labels exist and identify enclosing loops without duplicates, and forbids loop control outside loop contexts.
  - Correct execution of `for` update expressions after `continue`.
- **Live Timer Variables:**
  - `timer <name> [= init]` creates a live float timer variable tracking elapsed execution time. Defaults to 0.0 if uninitialized (`timer t`).
  - `int timer <name> [= init]` creates an integer timer tracking whole elapsed seconds.
  - Strictly numeric; assigning a number updates the offset and resumes tracking.
- **Word Logical Operators & Compound Assignment:**
  - `and`, `or`, and `not` supported as first-class language keywords with short-circuit evaluation.
  - `+=`, `-=`, `*=`, `/=`, `%=` compound assignment operators.

## [0.1.0-alpha] - 2026-11-07

### Added
- **Initial Foundation Architecture:** Complete project layout and modular C++20 engine.
- **Specification Documentation:**
  - `docs/LANGUAGE_SPEC.md`: Complete initial specification incorporating all 72 foundation rules.
  - `docs/DECISIONS.md`: Design rationale, resolved ambiguities, and formal grammar proposals.
  - `docs/ARCHITECTURE.md`: Multi-stage compilation and runtime pipeline.
  - `docs/FEATURES.md`: Implementation status tracker.
  - `docs/ROADMAP.md`: Multi-version milestone roadmap (v0.1 to v0.6+).
  - `docs/LIBRARIES.md`: Specification of the modular library ecosystem.
- **Lexer:**
  - Tokenization of identifiers, keywords (`def`, `const`, `dyn`, `force`, `new`, `if`, `else`, `for`, `while`, `return`, `true`, `false`, `null`).
  - Operators: arithmetic (`+`, `-`, `*`, `/`, `%`), relational (`==`, `!=`, `<`, `<=`, `>`, `>=`), logical (`&&`, `||`, `!`), mutation (`++`, `--`).
  - Comments: single-line `//` and multi-line `/* ... */`.
  - Semicolon-free statement termination via newlines and braces.
  - Source position tracking (line and column) for precise diagnostics.
- **Parser & AST:**
  - Full recursive descent parser for expressions, statements, blocks, control flow, and functions.
  - Distinct support for C++-style conditions (`if (cond) { ... } else if ...`).
  - Three-part loops with comma clause separators: `for (new i = 0, i < 10, i++)`.
  - Functions with inferred returns and default parameters: `def add(a, b = 10)`.
- **Runtime & Evaluator:**
  - Dynamic & inferred type system with static type lock on reassignment.
  - Explicit re-typing using `force`.
  - Fully dynamic variables using `dyn`.
  - Immutable bindings with `const`.
  - Built-in standard output: `display(...)` (no newline) and `displayl(...)` (with newline), plus `endl` constant.
  - Built-in input system (Rule 73): `input()`, `inputint()`, `inputfloat()`, `inputbool()`, `inputstring()`.
  - Arithmetic, logical, and string concatenation operations.
  - Lexical scoping and closure execution.
- **Tooling:**
  - MAZ CLI with file runner (`maz run <file>`) and interactive REPL (`maz repl`).
  - Formatted error messages with code snippet indicators.


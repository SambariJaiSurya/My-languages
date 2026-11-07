# Contributing to MAZ

Welcome to the **MAZ** programming language project!

MAZ is designed as an **evolving, learning language**. We welcome contributions from developers of all skill levels. Whether you are learning C++, writing standard libraries, or working on the compiler backend, this guide outlines our development principles and workflow.

---

## 1. Guiding Principles

1. **Evolutionary Growth:** MAZ is built to evolve. Never discard a new language concept simply because it wasn't in an early draft. Document how it interacts with existing features in `docs/DECISIONS.md`.
2. **Pedagogical Clarity:** The MAZ codebase serves as a learning tool. Prefer clean, well-commented, modular C++ code over cryptic micro-optimizations in the early frontend.
3. **Rock-Solid Diagnostics:** Never emit a cryptic or unhelpful error message. Always include file path, line number, column number, and clear guidance on why an error occurred and how to resolve it.
4. **Specification First:** Whenever modifying grammar or runtime semantics, update `docs/LANGUAGE_SPEC.md` and `docs/FEATURES.md` alongside the implementation.

---

## 2. Project Directory Layout

```
maz/
├── docs/               # Specifications, Architecture, Roadmap, Decisions
├── src/                # C++ Compiler & Runtime Source Code
│   ├── common/         # Token definitions, Position, Values, Error reporting
│   ├── lexer/          # Scanner / Tokenizer
│   ├── ast/            # AST Node hierarchy
│   ├── parser/         # Recursive descent parser
│   ├── runtime/        # Environment, Scope, Evaluator, Builtins
│   └── main.cpp        # CLI Entrypoint & REPL
├── examples/           # Sample .maz programs showcasing features
├── tests/              # Test suites and validation scripts
└── Makefile / build.ps1# Build scripts
```

---

## 3. Building MAZ

MAZ requires a modern C++ compiler supporting C++20 (GCC 11+, Clang 13+, or MSVC 2019+).

### Using GCC (MinGW / Linux / macOS):
```bash
g++ -std=c++20 -O2 -I src src/common/*.cpp src/lexer/*.cpp src/parser/*.cpp src/runtime/*.cpp src/main.cpp -o maz
```

### Running a MAZ Program:
```bash
./maz run examples/hello.maz
```

### Starting the Interactive REPL:
```bash
./maz repl
```

---

## 4. Submitting Proposals

When proposing a new language rule or library namespace:
1. Formulate the proposal in terms of syntactic benefit and runtime cost.
2. Check for conflicts against the 72 initial foundational rules in `docs/DECISIONS.md`.
3. Provide sample `.maz` snippets demonstrating idiomatic usage.


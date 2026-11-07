# MAZ Programming Language
**A modern, extensible, general-purpose programming language designed to grow.**

MAZ combines the rapid readability of Python and JavaScript with the low-level capability, control, and performance of C++. It is engineered as an evolving language project to support applications, web development, AI/ML, game development, robotics, and embedded microcontrollers (such as Arduino and ESP32).

---

## Quick Start

### 1. Build the MAZ Compiler & Runtime
MAZ is implemented in clean C++20 with zero external dependencies.

```bash
# Using Windows CMD:
build.bat

# Using PowerShell:
.\build.ps1

# Using GCC directly:
g++ -std=c++20 -O2 -I src src/lexer/Lexer.cpp src/parser/Parser.cpp src/runtime/Environment.cpp src/runtime/Interpreter.cpp src/main.cpp -o maz.exe
```

### 2. Run Example Programs
```bash
.\maz.exe run examples/01_hello.maz
.\maz.exe run examples/02_hybrid_types.maz
.\maz.exe run examples/03_conditions_and_math.maz
.\maz.exe run examples/04_loops.maz
.\maz.exe run examples/05_functions.maz
```

### 3. Interactive REPL
```bash
.\maz.exe repl
```

---

## Language Highlights (MAZ 0.1)

```maz
// Variables & Type Inference
count = 10
const PI = 3.14159

// Dynamic Types & Force
dyn dynamicVal = "flexible"
dynamicVal = 42

force count = "now a string" // Explicit re-typing

// Standard Output
display("Hello from MAZ!")

// Loops: Three-part loop separated by commas (Rule 7)
for (new i = 0, i < 5, i++) {
    display("Loop index: " + i)
}

// Functions with default parameters
def greet(name = "World") {
    display("Hello, " + name + "!")
}

greet()
greet("Developer")
```

---

## Project Documentation
Detailed specifications and architectural guides are maintained in the `docs/` directory:

- [Language Specification](file:///e:/coding stuff/my languages/maz/docs/LANGUAGE_SPEC.md) — Complete rules of the MAZ language.
- [Compiler Architecture](file:///e:/coding stuff/my languages/maz/docs/ARCHITECTURE.md) — Multi-stage compiler and execution pipeline.
- [Development Decisions & Contradictions](file:///e:/coding stuff/my languages/maz/docs/DECISIONS.md) — Rationale, identified ambiguities, and resolutions.
- [Development Roadmap](file:///e:/coding stuff/my languages/maz/docs/ROADMAP.md) — Version milestones from v0.1 to v0.6+.
- [Feature Tracker](file:///e:/coding stuff/my languages/maz/docs/FEATURES.md) — Implemented, planned, and experimental features.
- [Library Ecosystem](file:///e:/coding stuff/my languages/maz/docs/LIBRARIES.md) — Modular namespaces (`maz.web`, `maz.ai`, `maz.arduino`, `maz.game`, etc.).
- [Changelog](file:///e:/coding stuff/my languages/maz/docs/CHANGELOG.md) — Release notes and historical changes.
- [Contributing Guide](file:///e:/coding stuff/my languages/maz/docs/CONTRIBUTING.md) — Guidelines for extending MAZ.


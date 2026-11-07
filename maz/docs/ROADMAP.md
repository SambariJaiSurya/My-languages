# MAZ Development Roadmap
**Project Vision:** Building an evolving, general-purpose programming language for applications, systems, web, AI, games, and embedded hardware.

---

## Milestone 1: MAZ 0.1 — Foundation (Current Milestone)
**Goal:** Deliver a fully functional, self-contained MAZ compiler frontend and execution engine capable of running core algorithmic programs.

- [x] Dedicated project folder structure and architecture documentation.
- [x] Complete language specification based on all 72 foundation rules.
- [x] Comprehensive architectural decisions record (`DECISIONS.md`).
- [x] Semicolon-free Lexer with line and column tracking.
- [x] Recursive Descent Parser supporting expressions, statements, blocks, conditions, loops, and functions.
- [x] Three-part loop with comma separation and `new` variable scoping semantics.
- [x] Hybrid type inference with static type checking, `dyn`, and `force`.
- [x] Built-in standard output: `display()`.
- [x] Arithmetic, logical, relational, and string concatenation operators.
- [x] User-defined functions with default parameters and inferred returns.
- [x] Interactive REPL and file execution CLI (`maz run <file>`).
- [x] Initial suite of automated test programs and examples.

---

## Milestone 2: MAZ 0.2 — Core Language & OOP
**Goal:** Introduce object-oriented programming, user-defined data structures, collection types, and modular imports.

- [ ] Array literals and core array methods (`pushback()`, `length()`, `pop()`).
- [ ] Homogeneous array enforcement and dynamic heterogeneous arrays (`dyn[]`).
- [ ] Class definitions with `public`, `private`, `protected`, and `internal` access modifiers.
- [ ] Explicit constructors via `constructor` keyword.
- [ ] Structures (`struct`) for value-type data encapsulation.
- [ ] Single inheritance via `extends` and mixin composition via `include`.
- [ ] Explicit interfaces via `interface` and `implement`.
- [ ] Exception handling with `try` and `catch` blocks.
- [ ] Module import system (`use maz.math`, relative file imports).
- [ ] Explicit nullable types (`type?` and non-nullable verification).

---

## Milestone 3: MAZ 0.3 — Advanced Systems & Concurrency
**Goal:** Expand MAZ into low-level systems programming and high-performance asynchronous execution.

- [ ] Simplified generic types and functions.
- [ ] Pointer operations (`*p`, `&var`) and memory address inspection.
- [ ] Hybrid memory model: automatic GC memory vs explicit manual allocation (`alloc` / `free`).
- [ ] Object ownership semantics and reference borrowing.
- [ ] Asynchronous programming with `async` and `await`.
- [ ] Native operating system threads and thread synchronization primitives.
- [ ] Standard file I/O operations (file reading, writing, seeking).
- [ ] C and C++ Foreign Function Interface (FFI).

---

## Milestone 4: MAZ 0.4 — Bytecode Runtime & Ecosystem Tools
**Goal:** Transition to a high-throughput virtual machine and establish developer tooling.

- [ ] MAZ Intermediate Representation (IR).
- [ ] Bytecode generator and instruction encoder.
- [ ] High-performance stack-based Virtual Machine (VM).
- [ ] Interactive terminal debugger (breakpoints, stepping, stack trace, variable inspect).
- [ ] Code formatter tool (`maz format`).
- [ ] Documentation generator from doc-comments (`maz doc`).
- [ ] Initial MAZ Package Manager (`maz install`, `maz publish`, `maz create`).

---

## Milestone 5: MAZ 0.5 — Native Compilation & JIT
**Goal:** Bring compile-to-native capabilities and runtime JIT optimizations.

- [ ] LLVM code generator backend for standalone executable binary compilation.
- [ ] Profile-guided Just-in-Time (JIT) compiler inside the MAZ VM.
- [ ] Cross-compilation for Windows, Linux, and macOS.
- [ ] Ahead-of-time dead code elimination and constant propagation optimizations.

---

## Milestone 6: MAZ 0.6+ — Specialized Domain Expansion
**Goal:** Expand MAZ standard libraries and targets across all promised domains.

### 6.1 Embedded & Microcontroller Target
- Direct compilation target for Arduino (ATmega328P / AVR) and ESP32.
- Built-in hardware APIs: `pinMode()`, `digitalWrite()`, `digitalRead()`, `analogRead()`, `delay()`.
- Zero-external-dependency microcontroller flashing tool in MAZ CLI.

### 6.2 Web Development (`maz.web`)
- MAZ-native reactive frontend components compiling to WebAssembly.
- Built-in HTTP web server and REST/WebSocket routing (`maz.webserver`).

### 6.3 Artificial Intelligence & Data Science (`maz.ai`, `maz.ml`)
- Multidimensional tensor library with CPU and GPU acceleration (`maz.gpu`).
- Automatic differentiation and neural network layers.

### 6.4 Game & Graphics Development (`maz.game`)
- 2D and 3D rendering pipeline (OpenGL / Vulkan abstraction).
- Integrated 2D rigid-body physics engine.
- Game state persistence, save/load checkpoints, and instant hot-reset.

### 6.5 GUI & Mobile Development (`maz.gui`, `maz.mobile`)
- Declarative cross-platform GUI framework for desktop and mobile.


# MAZ Development Roadmap
**Project Vision:** Building an evolving, general-purpose programming language for applications, systems, web, AI, games, and embedded hardware.

---

## Approved Implementation Milestones (Rules 1–87)

Following the complete 87-rule specification, language feature additions are now closed and organized into sequential development phases:

---

## Milestone 1: MAZ 0.1 — Foundation (Current Live Version 🟢)
**Goal:** Deliver a fully functional, self-contained MAZ compiler frontend and execution engine capable of running core algorithmic programs.

- [x] Dedicated project folder structure and architecture documentation.
- [x] Complete language specification based on all 87 rules.
- [x] Comprehensive architectural decisions record (`DECISIONS.md`).
- [x] Semicolon-free Lexer with line and column tracking.
- [x] Recursive Descent Parser supporting expressions, statements, blocks, conditions, loops, and functions.
- [x] Three-part loop with comma separation and `new` variable scoping semantics.
- [x] Hybrid type inference with static type checking, `dyn`, and `force`.
- [x] Built-in standard output: `display()`.
- [x] Built-in input system (Rule 73): `input()`, `inputInt()`, `inputFloat()`, `inputBool()`, `inputString()`.
- [x] Arithmetic, logical (`&&`, `||`, `!`), relational, and string concatenation operators.
- [x] User-defined functions with default parameters and inferred returns.
- [x] Interactive REPL and file execution CLI (`maz run <file>`).
- [x] Automated test runner suite (`tests/run_tests.ps1`).

---

## Milestone 2: MAZ 0.2 — Expressions, Control Flow & Collections
**Goal:** Complete intermediate operations, advanced control flow, collections, and lambdas.

- [ ] **Operators (Rule 74):**
  - Compound assignment: `+=`, `-=`, `*=`, `/=`, `%=`.
  - Word logical operators: `and`, `or`, `not` (identical to `&&`, `||`, `!`).
  - Bitwise operators: `&`, `|`, `^`, `~`, `<<`, `>>`.
  - Ternary conditional operator: `condition ? trueVal : falseVal`.
  - Type conversions: Standalone (`toInt(x)`, `toFloat(x)`, `toString(x)`, `toBool(x)`) and dot methods (`x.toInt()`).
  - Prefix/postfix increment & decrement in larger expressions: `y = ++x`, `y = x++`.
- [ ] **Control Flow (Rule 75):**
  - `break` and `continue` statements.
  - `switch` and `case` with auto-break by default and explicit `fallthrough`.
- [ ] **Scope (Rule 76):**
  - Strict block scoping in `{}` blocks.
  - Python-style explicit `global count` inside functions.
- [ ] **Functions (Rule 77):**
  - Lambdas and arrow functions: `(a, b) => a + b` and `(x) => { ... }`.
  - Named arguments: `fn(name: "Alice", prefix: "Hello")`.
  - Variadic parameters: `def sum(...numbers)`.
- [ ] **Strings & Chars (Rule 78):**
  - String interpolation: `"Hello, ${name}!"`.
  - Dedicated `char` type with single quotes `'A'`.
  - String methods: `.length()`, `.substring()`, `.toUpper()`, `.toLower()`, `.contains()`, `.split()`, `.trim()`.
- [ ] **Collections (Rule 79):**
  - Array bracket literals: `[1, 2, 3]`.
  - Array methods: `.push()`, `.pop()`, `.insert()`, `.remove()`, `.length()`, `.contains()`, `.sort()`, `.reverse()`.
  - Map / Dictionary literals: `{"key": "value"}`.

---

## Milestone 3: MAZ 0.3 — Object-Oriented Programming & Error Handling
**Goal:** Full object-oriented capabilities, resource management, and enterprise-grade exception handling.

- [ ] **OOP (Rules 80, 11, 18, 69):**
  - Classes (`class`) and structs (`struct`).
  - Explicit constructors: `constructor(...) { ... }`.
  - Named destructors: `destructor() { ... }`.
  - Access modifiers: `public`, `private`, `protected`, `internal`.
  - Properties: `get prop() { ... }` and `set prop(val) { ... }`.
  - Single inheritance via `extends` and mixins via `include`.
  - Interfaces via `implement`.
  - Object identity and equality.
- [ ] **Error Handling (Rules 81, 8):**
  - Structured `try`, `catch`, `finally` blocks.
  - Typed exceptions: `catch (err: TypeError)`.
  - `throw Error(...)` statement.

---

## Milestone 4: MAZ 0.4 — Bytecode Virtual Machine & Modules
**Goal:** High-performance bytecode VM, modular package management, and system operations.

- [ ] **Modules & Packages (Rule 82):**
  - `export` keyword on functions, classes, and constants.
  - Selective `use math { add, subtract }` and aliasing `use math as m`.
- [ ] **System & Filesystem (Rule 85):**
  - Built-in `sys` module: `sys.args`, `sys.env()`, `sys.stdin`, `sys.stdout`, `sys.stderr`, `displayErr()`.
  - Object-oriented I/O: `File`, `Directory`, `Path`.
- [ ] **Bytecode Engine:**
  - Intermediate representation, bytecode generator, stack VM.
- [ ] **Developer Tooling (Rule 86):**
  - Unified CLI: `maz check`, `maz fmt`, `maz test`.

---

## Milestone 5: MAZ 0.5 — Advanced Systems & Concurrency
**Goal:** Low-level memory management and native concurrency.

- [ ] **Systems Memory (Rule 83):**
  - Low-level `alloc()` and `free()`.
  - Typed allocation: `alloc<int>(10)`.
  - Raw pointers (`*`, `&`) with safe GC interaction / memory pinning.
- [ ] **Concurrency (Rule 84):**
  - `spawn(() => task())` and task handles with `.join()`.
  - Communication channels: `Channel()`, `send()`, `receive()`.
  - Mutexes, thread pools, and cancellation tokens.

---

## Milestone 6: MAZ 0.6+ — Native Compilation & Domain Targets
**Goal:** Hardware and multi-platform compilation.

- [ ] Standalone native binary compilation (`maz build --release`).
- [ ] Embedded & Microcontroller backend (Arduino / ESP32).
- [ ] WebAssembly / frontend integration (`maz.web`).
- [ ] Native GUI, 2D/3D Game engine, AI & ML tensor libraries.


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


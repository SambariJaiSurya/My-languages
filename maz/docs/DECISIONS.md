# MAZ Design Decisions & Architectural Analysis
**Document Version:** 1.0.0  
**Status:** Canonical Reference  

---

## 1. Overview

This document records the foundational design decisions of the MAZ programming language, tracks unresolved ambiguities and potential contradictions discovered across the 72 initial design rules, and outlines formal proposals to resolve them while strictly preserving the creator's intent.

---

## 2. Foundational Design Decisions (The 72 Rules)

| ID | Category | Summary of Decision | Architectural Rationale |
|---|---|---|---|
| ADR-01 | Syntax | Python-inspired assignment, inferred types, `const` keyword | Reduces boilerplate for newcomers while maintaining type safety. |
| ADR-02 | Syntax | Curly braces `{}` for code blocks | Unambiguous block demarcation, familiar to C++/JS developers. |
| ADR-03 | Functions | `def` keyword for functions with inferred return types | Concise function declaration without redundant type headers. |
| ADR-04 | Types | Hybrid type system (static + inferred + dynamic) | Balances compile-time optimization with dynamic prototyping. |
| ADR-05 | Output | Built-in `display()` function | Clear, universal standard output without heavy I/O imports. |
| ADR-06 | Control Flow | C++ style conditions `if (...) {} else if (...) {} else {}` | Explicit boolean condition parentheses prevent grammar ambiguities. |
| ADR-07 | Loops | 3-part loop separated by commas; `new` loop-local variable | Unique MAZ loop syntax avoiding semicolons; explicit shadowing semantics. |
| ADR-08 | Errors | `try` and `catch` blocks with rich diagnostic traces | Robust exception handling with high-level readability. |
| ADR-09 | Types | `dyn` for dynamic types, `force` for type mutations | Disallows accidental type mutation while giving explicit override control. |
| ADR-10 | Arrays | Homogeneous array literals by default, `pushback()` method | Type-safe contiguous vector representations with intuitive expansion. |
| ADR-11 | OOP | Classes with `private`, `public`, `protected`, `internal` | Full encapsulation model for enterprise and system architecture. |
| ADR-12 | Modules | `use` keyword for importing packages and modules | Clean and consistent import syntax across all namespaces. |
| ADR-13 | Math | Operators `+`, `-`, `*`, `/`, `%` | Standard mathematical arithmetic notation. |
| ADR-14 | Literals | Lowercase `true`, `false`, `null` | Consistent with modern programming standards (C++, JS). |
| ADR-15 | Strings | Double quotes `"..."` and `+` concatenation | Natural string syntax familiar to beginners and seasoned programmers. |
| ADR-16 | Comments | `//` single-line and `/* ... */` multi-line | C/C++ style comments, universally recognized. |
| ADR-17 | OOP | Typed and inferred object declarations | Flexible instantiation patterns matching hybrid type design. |
| ADR-18 | OOP | Support both `include` and `extends` | Distinct mechanisms for class inheritance vs component/mixin inclusion. |
| ADR-19 | Async | `async` and `await` keywords | Non-blocking asynchronous I/O with synchronous syntax readability. |
| ADR-20 | OOP | Access modifiers (`public`, `private`, `protected`, `internal`) | Granular access control at class and module boundaries. |
| ADR-21 | Functions | Inferred return types by default | Reduces cognitive load while allowing compiler optimization. |
| ADR-22 | Functions | Default parameters supported; missing arguments error | Improves API ergonomics without requiring function overloading. |
| ADR-23 | Arrays | Homogeneous by default; `dyn` arrays for heterogeneous elements | Balances vector memory efficiency with flexible data collections. |
| ADR-24 | Loops | Collection iteration `for (item : collection)` | Clean C++-style range iteration syntax without iterator boilerplate. |
| ADR-25 | Systems | Pointers (`*`) and address-of (`&`) operations | Low-level direct memory manipulation for systems and microcontroller code. |
| ADR-26 | Strings | Single-line and multiline string literals | Convenient representation of multiline documents, SQL, HTML, and shaders. |
| ADR-27 | Extensibility | Reusable custom functions without new keyword requirements | Clean language extensibility through first-class functions. |
| ADR-28 | Modules | Hierarchical modules and custom package distribution | Scalable namespace organization for enterprise and open-source packages. |
| ADR-29 | Generics | Simplified generic syntax compared to C++ templates | High-performance parametric polymorphism without template madness. |
| ADR-30 | Concurrency | Both threads (native OS) and async/await (event loop) | Supports CPU-bound parallel workloads and I/O-bound concurrency. |
| ADR-31 | I/O | Standard file handling APIs in core runtime | File reading and writing available out-of-the-box. |
| ADR-32 | Vision | Safe high-level and low-level systems access | Unified language spanning microcontrollers to web applications. |
| ADR-33 | Web | MAZ-native frontend and HTML integration | Unified full-stack development experience. |
| ADR-34 | Web | Web server and HTTP route handling | Built-in HTTP services for backend APIs. |
| ADR-35 | Data | Embedded database engine and external driver support | Frictionless data persistence. |
| ADR-36 | Web | Browser interaction and JavaScript interop | Seamless compilation/interop with browser runtimes (Wasm / JS). |
| ADR-37 | Compiler | Both Bytecode/VM and Native compilation targets | Fast development cycle via VM, maximum performance via native codegen. |
| ADR-38 | Compiler | Just-in-Time (JIT) compilation in VM runtime | Adaptive profiling and hot-path machine code generation. |
| ADR-39 | Tooling | Built-in package manager in MAZ CLI | Dependency resolution, publishing, and registry integration. |
| ADR-40 | Tooling | Interactive debugger with step, inspection, breakpoints | First-class developer debugging experience with rich error context. |
| ADR-41 | GPU | GPU compute and graphics libraries (`maz.gpu`) | Direct access to compute shaders, Vulkan, DirectX, and CUDA. |
| ADR-42 | Games | 2D/3D game engines, states, physics, and resets | Rapid game prototyping and production-grade rendering. |
| ADR-43 | AI/ML | Native AI & machine learning libraries (`maz.ai`, `maz.ml`) | Tensors, auto-diff, neural network training and inference. |
| ADR-44 | Embedded | Native Arduino and ESP32 programming without external libs | Direct GPIO, ADC, PWM, serial, and delay operations in core. |
| ADR-45 | Types | Dual support for explicit types and type inference | Developer choice between explicit documentation and swift prototyping. |
| ADR-46 | Types | Enumerations (`enum`) | Strongly-typed named constants. |
| ADR-47 | Memory | Hybrid automatic and manual memory allocation | Garbage collection for application code; alloc/free for systems/embedded. |
| ADR-48 | Runtime | Reflection and runtime type inspection | Dynamic serialization, dependency injection, and debugging. |
| ADR-49 | OOP | Distinct `struct` (value type) and `class` (reference type) | Memory locality optimization for high-performance data structures. |
| ADR-50 | OOP | Interfaces and explicit `implement` keyword | Clean polymorphism and contract-driven API design. |
| ADR-51 | Syntax | Increment (`++`) and decrement (`--`) operators | Familiar concise mutation operators. |
| ADR-52 | Tooling | Unified MAZ CLI for project management, run, build, test | Consistent developer interface across all supported platforms. |
| ADR-53 | Tooling | Built-in testing runner command | Uniform test discovery and automated reporting. |
| ADR-54 | Tooling | Automated documentation generator from doc comments | High-quality API documentation directly from source code. |
| ADR-55 | UI | Native GUI framework and external toolkit bindings | Desktop and mobile cross-platform graphical application creation. |
| ADR-56 | Platform | Multiplatform targets (Windows, Linux, macOS, Android, iOS) | Broad ecosystem reach. |
| ADR-57 | Structure | Support for single-file scripts and modular projects | Seamless scaling from quick automation scripts to multi-million line codebases. |
| ADR-58 | Metaprog | Hygienic compile-time code generation macros | Expressive metaprogramming and zero-cost abstractions. |
| ADR-59 | Extensibility | Controlled custom syntax extensions | Domain-specific language (DSL) creation without breaking tools. |
| ADR-60 | Errors | Comprehensive diagnostic error formatting | Beginner-friendly error messages with clear suggested remedies. |
| ADR-61 | Tooling | Interactive REPL (Read-Eval-Print Loop) | Instant experimentation and interactive learning. |
| ADR-62 | Types | Non-nullable by default; explicit `?` for nullable types | Eliminates null pointer exceptions ("billion-dollar mistake"). |
| ADR-63 | Functions | No traditional function overloading in v1 | Avoids ambiguity in type inference and keeps compiler resolution predictable. |
| ADR-64 | Interop | Foreign Function Interface (FFI) for C and C++ | Direct reuse of massive existing C/C++ libraries. |
| ADR-65 | Memory | Tracing/ref-counting GC by default | Safe memory management without manual bookkeeping for general apps. |
| ADR-66 | Compiler | Compile-time constant execution (`comptime`) | Zero-cost initialization and compile-time validation. |
| ADR-67 | Security | Memory safety and sandboxing defaults | Secure application execution with opt-in low-level privileges. |
| ADR-68 | Packaging | Standalone native binary and portable bytecode bundle distribution | Choice between zero-dependency native binaries or portable VM packages. |
| ADR-69 | OOP | Explicit `constructor` keyword for constructors | Unambiguous object initialization method distinct from class name. |
| ADR-70 | OOP | Formalized semantic separation: `extends` vs `include` | Clear architectural division between subtyping and behavioral mixins. |
| ADR-71 | Types | Syntax modifier `?` designates nullable types | Consistent, compact nullable type syntax. |
| ADR-72 | Memory | Coherent ownership model bridging GC and manual pointers | Prevents memory safety bugs when pointers interact with garbage collector. |
| ADR-73 | I/O | Built-in typed & universal input system (`input`, `inputInt`, etc.) | Direct standard console input without external libraries, avoiding C++ `cin >>`. |
| ADR-74 | Operators | Comprehensive operators, compounds, bitwise, ternary, conversion | Complete expression evaluation and type casting pipeline. |
| ADR-75 | Control | Advanced control flow: `break`, `continue`, `switch/case`, loop-else | Flexible looping and multi-branch decision structures. |
| ADR-76 | Scope | Lexical scoping, variable lifetimes, block isolation, explicit global | Clean modular variable management avoiding silent leaks. |
| ADR-77 | Functions | Lambdas, closures, recursion protection, named & variadic args | Modern functional capabilities alongside procedural paradigms. |
| ADR-78 | Strings | Comprehensive string manipulation, UTF-8 unicode, escapes, formatting | Complete text processing suite. |
| ADR-79 | Collections | Arrays (homogeneous, dynamic, multi-dim), maps, sets, map/filter/reduce | Comprehensive high-performance collection abstractions. |
| ADR-80 | OOP | Destructors, `static`, `this`, `abstract`, `final`, properties, equality | Full-scale object model for complex software architectures. |
| ADR-81 | Errors | Typed exceptions, multiple catch blocks, `finally`, assertions | Enterprise-grade diagnostic resilience and safe resource cleanup. |
| ADR-82 | Modules | Granular exports/imports, package registry, dependency locking | Scalable multi-package ecosystem. |
| ADR-83 | Memory | Stack/heap allocation, ownership transfer, move semantics, pinning | High-performance safe systems programming without GC interference. |
| ADR-84 | Concurrency | Thread safety, mutexes, channels, cancellation, deadlock detection | Robust parallel execution models. |
| ADR-85 | OS / Sys | Process management, directory/filesystem APIs, env variables | Full operating system interaction. |
| ADR-86 | Tooling | Formatter, linter, profiler, source maps, language server protocol | Professional-grade developer tooling suite. |
| ADR-87 | Security | Sandboxed execution, permissions, cryptographic primitives, cross-target | Production safety and architecture portability. |

---

## 3. Analysis of Contradictions & Ambiguities

### Ambiguity 1: Comma Separation in `for` Loops vs Comma Operator / Arguments
- **The Conflict:** Rule 7 specifies that three-part loops use commas instead of semicolons:
  `for (new i = 0, i < 10, i++)`
  In C and JavaScript, the comma `,` is also an expression operator (e.g. `a, b`) or an argument separator in function calls.
- **Problem:** If an expression inside one of the three clauses contains a comma (such as calling a function with multiple arguments `for (new i = getStart(1, 2), i < limit, i++)`), the parser could mistakenly interpret the comma inside the call as the clause separator.
- **Proposed Resolution:**
  The parser enforces grammar nesting levels. Commas that appear inside parentheses `()`, brackets `[]`, or braces `{}` belong to the inner expression. Only top-level un-nested commas inside the outer `for (...)` header act as clause separators. This completely resolves the ambiguity while fully preserving Rule 7.

---

### Ambiguity 2: Loop Variable Scoping Without `new` (Rule 7)
- **The Rule:** "The `new` keyword creates a loop-local variable that shadows an outside variable and is unavailable after. Without `new`, an existing variable is reused. If no variable exists, the loop variable is created in the global scope."
- **The Conflict:** Implicitly leaking a loop counter into global scope when a programmer simply writes `for (i = 0, i < 10, i++)` is known to cause accidental global variable pollution and bugs in languages like early JavaScript or Python.
- **Proposed Resolution:**
  1. For initial compliance with Rule 7, if an identifier is not marked with `new` and does not exist in any enclosing scope, it will be placed in the module/global scope.
  2. The compiler/analyzer will emit a helpful warning:
     `"Notice: Variable 'i' was not declared with 'new' and did not exist in an outer scope; creating global variable. Use 'for (new i = ...)' for loop-local scoping."`
  3. In MAZ 0.2+, the community will be asked if strict lexical block scoping by default should be adopted or if `new` remains the required keyword for local variables.

---

### Ambiguity 3: Interaction Between Type Inference, `dyn`, and `force` (Rules 1, 9, 45)
- **The Question:** How does variable initialization and reassignment behave in each scenario?
- **Clarified Semantics:**
  - Case 1: `x = 10`  
    `x` is inferred as `int`. Reassignment `x = 20` is valid. Reassignment `x = "hello"` produces a compile/runtime type error (`Cannot assign string to int variable 'x'`).
  - Case 2: `force x = "hello"`  
    The type constraint on `x` is explicitly replaced. `x` is now inferred as `string`.
  - Case 3: `dyn y = 10`  
    `y` is declared as a dynamic variable. `y = "hello"` is completely valid without `force` because `y` has dynamic type identity.
  - Case 4: `const z = 3.14`  
    `z` is immutable. Neither `z = 4.0` nor `force z = "pi"` is permitted.

---

### Ambiguity 4: Inheritance Semantics: `extends` vs `include` (Rules 18, 70)
- **The Question:** Both `extends` and `include` are supported. What are their precise differences?
- **Formal Definition:**
  - **`extends` (Single Class Inheritance):**
    Establishes an `is-a` relationship with class subtyping and virtual dispatch. A class may only `extends` one parent class (single inheritance), preserving clean object memory layouts and avoiding the "diamond problem".
  - **`include` (Mixin / Trait Composition):**
    Establishes a `has-behavior-of` relationship. A class may `include` multiple mixins/traits. The methods and fields of the included mixin are copied or flattened into the target class. Conflicts are resolved explicitly at compile-time.

---

### Ambiguity 5: Coexistence of Garbage Collection and Pointers (Rules 25, 47, 65, 72)
- **The Question:** If MAZ has automatic garbage collection (GC) and also raw pointers (`*`, `&`), what happens if GC moves or collects an object while a raw pointer is pointing to it?
- **Formal Proposal (Tiered Memory Architecture):**
  - **Tier 1 (Managed Space - Default):** References to classes, dynamic arrays, and strings are managed by the GC. Safe, high-level code cannot produce dangling pointer crashes.
  - **Tier 2 (Unsafe / Systems Space):** Pointers (`*`, `&`) operate on stack variables, value `struct`s, or manually allocated memory blocks (`alloc()` / `free()`).
  - When taking a raw pointer to a GC-managed object, the object must be explicitly pinned or placed in a designated unmanaged region, ensuring total safety without sacrificing microcontroller/embedded control.

---

### Ambiguity 6: Semicolonless Grammar and Newline Sensitivity
- **The Challenge:** Without semicolons, the lexer/parser needs clear rules to distinguish whether a newline terminates a statement or if the statement continues on the next line.
- **Resolution (Automatic Semicolon / Statement Insertion Rules):**
  A newline is treated as a statement terminator *only* if the preceding token could legally end a statement (e.g., identifier, literal, `)`, `]`, `}`, `++`, `--`, `return`) and the subsequent token cannot legally continue the expression. If a binary operator like `+`, `-`, `*`, `,` appears at the end of the line, the statement continues across the newline.

---

## 4. Detailed Specification of Rules 74–82 (Approved Final Design)

### Summary of Decisions
| Question / Feature | Approved Choice | Syntax & Semantics |
|---|---|---|
| **Ternary Operator (Rule 74.7)** | C-style `? :` | `condition ? trueExpr : falseExpr` |
| **Switch & Case (Rule 75.3)** | Auto-break by default | Explicit `fallthrough` keyword required for continuation |
| **Logical Operators (Rule 74.3)** | Symbols & Words | Both `&&`, `\|\|`, `!` and `and`, `or`, `not` with identical precedence & short-circuiting |
| **Type Conversions (Rule 74.10)** | Dual invocations | Standalone functions (`toInt(x)`) and dot methods (`x.toInt()`) |
| **Inc/Dec in Expressions (Rule 74.5)** | C/JS traditional | Prefix (`++x`) modifies then yields; Postfix (`x++`) yields then modifies |
| **Operator Precedence (Rule 74.8)** | Standard C-family | Conventional precedence order (Parens > Unary > Multiplicative > Additive > Shift > Relational > Equality > Bitwise > Logical > Ternary > Assignment) |
| **Loop-else (Rule 75.6)** | Rejected | No `else` on `for`/`while`; use standard flags and conditional blocks |
| **Block Scoping (Rule 76.3)** | Strict Block Scope | Variables in `{}` never leak out; `new` shadows outer variables |
| **Immutability (Rule 76.7)** | `const` keyword only | Sole immutable binding keyword |
| **Global Access (Rule 76.8)** | `global x` | Explicit statement inside functions to rebind/assign globals |
| **Lambdas (Rules 77.2, 77.3)** | Arrow syntax | `(a, b) => a + b` and `(x) => { ... }` |
| **Named Arguments (Rule 77.4)** | Colon syntax | `fn(name: "Alice", prefix: "Hello")` |
| **Variadic Parameters (Rule 77.5)** | Prefix ellipsis | `def sum(...numbers)` collected into MAZ array |
| **String Interpolation (Rule 78)** | Dollar-curly `${}` | `"Hello, ${name}! In 5 years: ${age + 5}"` |
| **Character Type (Rule 78)** | Distinct `char` | Single quotes `'A'` for UTF-8 scalar values |
| **Array Operations (Rule 79)** | Bracket literals & dot methods | `[1, 2, 3]` with `.push()`, `.pop()`, `.length()`, etc. (`pushback()` retained as alias) |
| **Map / Dictionary (Rule 79)** | Brace key-value literals | `{"name": "Alice", "age": 20}` |
| **Destructors (Rule 80.1)** | `destructor() { ... }` | Named destructor for object lifecycle cleanup |
| **Properties (Rule 80.7)** | `get` and `set` | `get width() { ... }` and `set width(val) { ... }` |
| **Structured Errors (Rule 81)** | Multi-catch & `finally` | `try { ... } catch (err: TypeError) { ... } finally { ... }` and `throw` |
| **Modules (Rule 82)** | `export` & selective `use` | `export def add()`, `use math { add, subtract }`, `use math as m` |
| **Memory Allocation (Rule 83)** | `alloc()` / `free()` | Low-level systems allocation: `ptr = alloc(size)`, `ptr = alloc<Type>(count)`, `free(ptr)` |
| **Concurrency (Rule 84)** | `spawn()` & Channels | Task handles: `handle = spawn(() => fn())`, `ch = Channel()`, `ch.send()`, `ch.receive()` |
| **System Streams (Rule 85)** | `sys` module & `displayErr()` | `use sys`, `sys.args`, `sys.env()`, `sys.stdin`, `sys.stdout`, `sys.stderr`, `displayErr()` |
| **File System API (Rule 85)** | OOP `File`, `Directory`, `Path` | `file = File("data.txt")`, `file.readAllText()`, `directory = Directory("dir")`, `path = Path(...)` |
| **Compiler CLI (Rules 86 & 87)** | Unified `maz` CLI | `maz run`, `maz build [--debug / --release]`, `maz test`, `maz fmt`, `maz install`, `maz check`, `maz repl` |




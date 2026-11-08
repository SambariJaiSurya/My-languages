# MAZ Feature Implementation Tracker
**Last Updated:** MAZ v0.1.0-alpha  

---

## 1. Feature Status Legend
- 🟢 **Implemented:** Fully functional and tested in the current version.
- 🟡 **In Progress / Planned:** Under active design or slated for an imminent milestone.
- ⚪ **Future Roadmap:** Planned for later versions according to the roadmap.
- 🧪 **Experimental:** Under active investigation and prototyping.

---

## 2. Core Language Features

| Feature | Status | Version | Category | Description |
|---|---|---|---|---|
| Automatic Type Inference | 🟢 Implemented | v0.1 | Types | Variables infer type on initial assignment (`x = 42`) |
| Dynamic Variables (`dyn`) | 🟢 Implemented | v0.1 | Types | Dynamic type mutation without type errors (`dyn v = 1`) |
| Forced Re-typing (`force`) | 🟢 Implemented | v0.1 | Types | Explicit type change on existing static variable (`force x = "str"`) |
| Constants (`const`) | 🟢 Implemented | v0.1 | Variables | Immutable variable bindings (`const PI = 3.14`) |
| Primitive Types (`int`, `float`, `string`, `bool`, `null`) | 🟢 Implemented | v0.1 | Types | Fundamental value representations |
| Arithmetic Operators (`+`, `-`, `*`, `/`, `%`) | 🟢 Implemented | v0.1 | Operators | Standard arithmetic computations |
| Comparison Operators (`==`, `!=`, `<`, `<=`, `>`, `>=`) | 🟢 Implemented | v0.1 | Operators | Relational equality and ordering |
| Logical Operators (`&&`, `||`, `!`, `and`, `or`, `not`) | 🟢 Implemented | v0.1 | Operators | Boolean conjunction, disjunction, and negation (symbols & words) |
| Compound Assignments (`+=`, `-=`, `*=`, `/=`, `%=`) | 🟢 Implemented | v0.1 | Operators | In-place variable assignment and computation |
| Increment / Decrement (`++`, `--`) | 🟢 Implemented | v0.1 | Operators | Fast pre/post variable mutation |
| String Concatenation (`+`) | 🟢 Implemented | v0.1 | Strings | Combining strings and values using `+` |
| Output Functions (`display`, `displayl`) | 🟢 Implemented | v0.1 | I/O | `display()` prints without newline, `displayl()` prints with newline |
| Input Functions (`input`, `inputint`, `inputfloat`, `inputbool`, `inputstring`) | 🟢 Implemented | v0.1 | I/O | Rule 73: Built-in typed & universal input system |
| Conditions (`if`, `else if`, `else`) | 🟢 Implemented | v0.1 | Control Flow | C++ style branch evaluation |
| Three-Part Loop with Commas (`for`) | 🟢 Implemented | v0.1 | Control Flow | `for (new i = 0, i < 10, i++)` with `new` scoping |
| While Loops (`while`) | 🟢 Implemented | v0.1 | Control Flow | Condition-driven iteration |
| Enhanced Loop Control (`break`, `continue`, `label:`, `break/continue N`) | 🟢 Implemented | v0.1 | Control Flow | Rule 75: Multi-level, labelled, and basic loop unwinding |
| Built-in Live Timer Variables (`timer`, `int timer`) | 🟢 Implemented | v0.1 | Variables | Elapsed execution time tracking with auto-initialization |
| Function Declarations (`def`) | 🟢 Implemented | v0.1 | Functions | Inferred return types and closures |
| Default Parameters | 🟢 Implemented | v0.1 | Functions | Functions with optional parameters having default values |
| Comments (`//` and `/* */`) | 🟢 Implemented | v0.1 | Lexer | Single-line and multi-line comments |
| Semicolonless Grammar | 🟢 Implemented | v0.1 | Lexer/Parser | Newline and brace statement termination |
| Rich Error Diagnostics | 🟢 Implemented | v0.1 | Tooling | File, line, column, and explanatory error messages |
| Interactive REPL | 🟢 Implemented | v0.1 | Tooling | Interactive read-eval-print loop |
| Array Literals & Methods (`pushback`) | ⚪ Planned | v0.2 | Collections | Homogeneous and dynamic arrays |
| Classes & Structures (`class`, `struct`) | ⚪ Planned | v0.2 | OOP | Reference and value type object definitions |
| Constructors (`constructor`) | ⚪ Planned | v0.2 | OOP | Explicit object constructors |
| Access Modifiers (`public`, `private`, etc.) | ⚪ Planned | v0.2 | OOP | Member encapsulation boundaries |
| Inheritance (`extends` vs `include`) | ⚪ Planned | v0.2 | OOP | Class inheritance and mixin composition |
| Interfaces (`interface`, `implement`) | ⚪ Planned | v0.2 | OOP | Polymorphic contracts |
| Exception Handling (`try` / `catch`) | ⚪ Planned | v0.2 | Errors | Structured exception catching |
| Module System (`use`) | ⚪ Planned | v0.2 | Modules | Module imports and exports |
| Nullable Types (`?`) | ⚪ Planned | v0.2 | Types | Safe non-nullable types and explicit nullability |
| Generics | ⚪ Planned | v0.3 | Types | Simplified generic types and algorithms |
| Pointers and References (`*`, `&`) | ⚪ Planned | v0.3 | Systems | Low-level pointer and address operations |
| Async / Await (`async`, `await`) | ⚪ Planned | v0.3 | Concurrency | Asynchronous event loop and promises |
| Native Multi-threading | ⚪ Planned | v0.3 | Concurrency | Thread creation and synchronization primitives |
| Bytecode Compiler & Virtual Machine | ⚪ Planned | v0.4 | VM | Fast stack/register virtual machine |
| Package Manager (`maz install`, etc.) | ⚪ Planned | v0.4 | Tooling | Ecosystem dependency manager |
| Interactive Step Debugger | ⚪ Planned | v0.4 | Tooling | Breakpoints, stepping, and inspection |
| Native Compilation Backend (LLVM) | ⚪ Planned | v0.5 | Compiler | Direct AOT compilation to machine code |
| JIT Compilation | ⚪ Planned | v0.5 | Compiler | Dynamic hot-path machine code compilation |
| Native Arduino & Microcontroller Target | ⚪ Planned | v0.6 | Hardware | Direct code generation for AVR/ESP32 |
| Web & Full-Stack Engine (`maz.web`) | ⚪ Planned | v0.6 | Web | Full-stack web applications and routing |
| Native AI / Machine Learning Engine | ⚪ Planned | v0.6 | AI | Tensors, autograd, and neural network training |
| Game Development Engine (`maz.game`) | ⚪ Planned | v0.6 | Games | 2D/3D graphics, physics, audio, and state resets |
| Metaprogramming & Macros | 🧪 Experimental | v0.7 | Metaprog | Compile-time macro expansion |
| Custom Syntax Extensions | 🧪 Experimental | v0.7 | Extensibility | Controlled DSL syntax grammar hooks |


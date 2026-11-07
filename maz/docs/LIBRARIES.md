# MAZ Library Ecosystem Specification
**Status:** Living Design Specification  

---

## 1. Ecosystem Philosophy

MAZ adheres to a **modular and expandable ecosystem** architecture. The core language executable remains lightweight and fast, while specialized domains are provided through structured official and community packages.

However, fundamental operations required for common workflows—including basic Arduino and microcontroller hardware operations—are built into the language so developers can get started without installing external packages.

---

## 2. Standard Namespace Hierarchy

### 2.1 Web & Networking
- `maz.web`: Unified frontend component model and DOM/Wasm bridge.
- `maz.webserver`: HTTP/HTTPS server engine, request routing, middlewares, and REST handlers.
- `maz.html`: HTML templating and JSX-style markup generation.
- `maz.browser`: High-level browser automation and JavaScript bridge.
- `maz.network`: Low-level TCP, UDP, TLS sockets, and WebSocket client/servers.

### 2.2 Artificial Intelligence & Machine Learning
- `maz.ai`: High-level AI workflows, LLM agents, and prompt pipelines.
- `maz.ml`: Classical machine learning algorithms (linear models, decision trees, clustering).
- `maz.neural`: Deep learning primitives (tensors, backpropagation, layers, optimizers).
- `maz.data`: Dataframes, CSV/JSON/Parquet parsers, feature normalization.
- `maz.gpu`: Low-level GPU compute shaders (CUDA/ROCm/Metal/Vulkan compute abstractions).

### 2.3 Hardware, Embedded & IoT
- `maz.arduino`: **Built-in core target support** for pin configuration, digital/analog I/O, PWM, and millisecond/microsecond delays.
- `maz.esp`: ESP32 and ESP8266 Wi-Fi, BLE, deep sleep, and dual-core task pinning.
- `maz.hardware`: Generic bus communication (I2C, SPI, UART, CAN bus).
- `maz.robotics`: Kinematics, PID controllers, motor and servo drivers.
- `maz.iot`: MQTT client, CoAP, IoT sensor telemetry.

### 2.4 Game & Graphics Development
- `maz.game`: Game loop lifecycle, scenes, input handling, and camera management.
- `maz.graphics`: 2D sprite rendering and 3D mesh rendering pipelines.
- `maz.physics`: 2D and 3D rigid body dynamics, collision detection, and raycasting.
- `maz.audio`: Spatial 3D audio, sound effects, and music playback.
- `maz.animation`: Skeletal animation, keyframe interpolation, and tweens.

### 2.5 Core Systems & Utilities
- `maz.math`: Trigonometry, matrix transformations, complex numbers, random generation.
- `maz.filesystem`: High-performance path manipulation, directory traversal, file streams.
- `maz.system`: Process management, environment variables, system signals.
- `maz.database`: Embedded SQLite engine, connection pooling, and ORM abstractions.
- `maz.crypto`: Cryptographic hashing (SHA-256, BLAKE3), encryption (AES-GCM), key exchange.
- `maz.security`: Sandboxed runtime policies and memory safety checks.
- `maz.gui`: Declarative desktop and mobile graphical user interfaces.
- `maz.mobile`: Android and iOS platform adapters and native device APIs.


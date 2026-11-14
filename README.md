# LLD & Machine Coding Mastery (C++ & Java)

A dedicated repository for mastering **Low-Level Design (LLD)** and **Machine Coding** within product-based companies.

Every design problem and architectural pattern is implemented symmetrically in both **Modern C++ (C++20)** and **Modern Java (Java 17/21)** to develop deep language fluency, clean code practices, and strong design fundamentals.

---

## Repository Structure

```text
lld_mastery/
├── cpp/
│   ├── review/               # Language fundamentals & syntactical warm-ups
│   │   └── exe_1.cpp
│   ├── week1_oop_patterns/   # Creational & Structural foundations
│   ├── week2_collections/    # In-memory stores & STL deep dive
│   ├── week3_behavioral/     # Behavioral patterns & state machines
│   └── week4_machine_coding/ # Full end-to-end design problems
└── java/
    ├── review/               # Core contracts, POJOs & language nuances
    ├── week1_oop_patterns/
    ├── week2_collections/
    ├── week3_behavioral/
    └── week4_machine_coding/
```

---

## Evaluation Rubric for Every Solution

- **S.O.L.I.D. Principles:** Single Responsibility, Open/Closed for extensions.
- **Separation of Concerns:** Distinct separation across Models, Repositories, Strategies, and Services.
- **Contracts First:** Design to interfaces (`pure virtual` in C++, `interface` in Java).
- **Memory & Resource Safety:** RAII (`std::unique_ptr` / `std::shared_ptr`) in C++; null-safe practices (`Optional`) in Java.
- **Thread-Safety (Where applicable):** Concurrency guards (`mutex`, atomic types, concurrent collections).
- **Deterministic Driver Code:** Executable `main()` with clean, verifiable test outputs.

---

## Build & Run Commands

### C++ (C++20 Standard)

```bash
# Compile
g++ -std=c++20 -Wall -Wextra path/to/file.cpp -o app

# Run
./app
```

### Java (Java 17+)

```bash
# Compile
javac path/to/File.java

# Run
java path.to.File
```

***

# Deadlock Cheat Base

Welcome to Deadlock Cheat Base, an advanced, modular cheat development framework for games on the Source 2 engine. Built with modern C++20 standards, Deadlock Cheat Base offers a highly optimized, extensible, and well-organized structure, designed for developers looking to create secure and efficient cheats with minimal runtime overhead.

# Key Features
- Modern C++ Implementation: Utilizing C++20 features, this project ensures high efficiency, readability, and memory safety.
- Doxygen Documentation: In-depth, clean, and organized documentation across all modules using Doxygen comments. This facilitates an easy understanding of the codebase for contributors.
- Hook Management System: A powerful hook manager that leverages compile-time validation and tokenized hook identifiers. Hooks can be easily created, managed, and removed with minimal code, providing an organized way to inject functionality into the game.
- Interactive ImGui Menu: Features a customizable and modern UI built with ImGui, allowing real-time configuration and control over cheat options.

# Project Structure
- ``core``: Contains essential components for initializing and configuring the project:
  - ``bootstrap``: Sets up and manages the foundational settings and system initialization.
  - ``ui``: Manages the ImGui-based user interface, providing customizable and responsive UI elements for in-game controls.
- ``systems``: Core systems that provide the cheat's primary functionalities:
    - ``render``: Handles graphics rendering for UI elements and overlays.
    - ``input``: Processes user inputs, allowing for customizable control bindings and cheat toggling.
    - ``hooker``: Manages the creation, registration, and removal of hooks, using the powerful hook management system.
    - ``module & pattern parser``: Implements memory scanning and pattern matching, enabling fast, compile-time optimized access to function addresses in the game's memory.
- ``utils``: Contains helper functions and utility classes.
- ``third_party``: Contains external libraries that the project depends on:
    - ``imgui``: A popular, lightweight library for creating graphical user interfaces, used here to build intuitive in-game menus.
    - ``minhook``: A versatile, minimalistic hooking library.
- ``valve``: Implements the Source 2 SDK to support Valve’s games and engine structures.

# Requirements
- C++20/23-compliant compiler
- Windows platform (DirectX 11 and Windows API integration)
- ImGui library

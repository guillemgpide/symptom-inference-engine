# Symptom Inference Engine

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](#)
[![Build](https://img.shields.io/badge/Build-Make-green.svg)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

> A lightweight command-line inference engine written in C that calculates disease probabilities based on user symptoms. Built from scratch with custom dynamic data structures and memory management.

## 🚀 Key Features

* **Heuristic Scoring Algorithm:** Calculates the most probable diseases by aggregating weighted relevance scores of matching symptoms.
* **Dynamic Memory Management:** Completely avoids hardcoded limits by implementing a custom dynamic Linked List ADT (Abstract Data Type) for symptom storage. Safe memory allocation verified against memory leaks and segmentation faults.
* **Multi-format Data Persistence:** Capable of loading initial baseline data from structured text files and applying live research updates parsed from binary files.
* **Robust CLI Interface:** Input validation and interactive terminal menu handling.

## 🛠️ Tech Stack

* **Language:** C (Standard Library)
* **Build System:** GNU Make
* **Architecture:** Custom ADTs (Disease & Symptom structs)

## ⚙️ Quick Start

    # Clone the repository
    git clone https://github.com/yourusername/symptom-inference-engine.git

    # Navigate to the project directory
    cd symptom-inference-engine

    # Build the executable using the provided Makefile
    make

    # Run the engine
    ./symptom_engine

*Note: The application requires a base disease text file to initialize. Sample data is provided in the `data/` folder.*

## 🧠 Technical Decisions & Architecture

- **Data Structures:** I chose to implement a custom `LinkedList` for symptom management rather than static arrays. This ensures the application footprint remains lightweight and scales dynamically regardless of the number of symptoms per disease.
- **Binary vs Text Parsing:** Implementing both parsing methods allowed for a clear separation of concerns: human-readable baseline configurations (`.txt`) vs. structured, fast-loading systemic updates (`.bin`).

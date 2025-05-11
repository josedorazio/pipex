# Pipex Project

**Pipex** is a 42 School project aimed at practicing and enhancing knowledge in systems programming. The project simulates a basic implementation of pipes in the shell environment, allowing communication between processes and management of standard input/output.

## Table of Contents

1. [Project Overview](#project-overview)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Project Structure](#project-structure)
6. [Technologies Used](#technologies-used)
7. [License](#license)

## Project Overview

**Pipex** is a C programming project that mimics the functionality of pipes in Unix-like systems. The goal is to simulate the process of piping commands together, handling input/output redirection, and managing multiple processes efficiently.

### Key objectives:

* Implement basic pipe functionality (`|`) and input/output redirection (`<`, `>`)
* Handle multiple commands and execute them sequentially
* Manage the creation of child processes, handle system calls, and work with standard streams

This project is part of my ongoing development as an engineer, focusing on systems-level programming, understanding process management, and improving problem-solving skills.

## Features

* **Simulates pipes**: Allows chaining multiple commands together, passing output from one command as input to another.
* **Input/Output Redirection**: Supports redirection of input and output to/from files.
* **Multi-command handling**: Executes multiple commands in sequence, handling the piping between them.
* **Error handling**: Includes proper error handling for various system calls and scenarios like invalid commands or bad input/output files.

## Installation

To install and run the project locally:

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/pipex.git
   ```

2. Navigate to the project directory:

   ```bash
   cd pipex
   ```

3. Compile the program:

   ```bash
   make
   ```

4. Run the program:

   ```bash
   ./pipex input_file command1 command2 ... output_file
   ```

## Usage

The program mimics the piping functionality found in shell environments. To use it:

```bash
./pipex input_file command1 command2 ... output_file
```

* `input_file`: The file that will be used as input for the first command.
* `command1, command2, ...`: The sequence of commands to be executed.
* `output_file`: The file where the final output will be stored.

Example:

```bash
./pipex input.txt "grep hello" "awk '{print $1}'" output.txt
```

This command reads from `input.txt`, pipes the output of `grep hello` to `awk '{print $1}'`, and writes the final output to `output.txt`.

## Project Structure

The project is organized as follows:

```
pipex/
│
├── src/
│   ├── pipex.c           # Main program file
│   ├── pipe_utils.c      # Utility functions for piping and redirection
│   └── ...
│
├── include/
│   ├── pipex.h           # Header file with function declarations and constants
│   └── ...
│
├── Makefile              # Makefile to compile the program
└── README.md             # Project documentation

```

## Technologies Used

* **C Programming**: The project is implemented using C for system-level programming.
* **Unix System Calls**: The project uses Unix system calls like `pipe()`, `fork()`, `execvp()`, `dup2()`, etc., to handle process creation and management.
* **Makefile**: Used for automation of the build process.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

# 🐚 Minishell

> As beautiful as a shell.

## 📝 About The Project

**Minishell** is a 42 school project where the objective is to recreate a minimalist version of `bash`. The goal is to dive deep into the Unix system, understanding process creation, file descriptors, abstract syntax trees (or similar parsing logic), pipes, redirections, and signals. 

This repository contains both the mandatory implementation and the bonus features.

## ✨ Features

### Mandatory
* **Prompt**: Displays a prompt while waiting for a new command.
* **History**: Keeps track of previously entered commands using the `readline` library.
* **Execution**: Searches and launches the correct executable using the `PATH` environment variable or via absolute/relative paths.
* **Quotes Handling**: 
  * Single quotes (`'`) prevent the shell from interpreting meta-characters.
  * Double quotes (`"`) prevent interpretation of meta-characters except for `$` (environment variables).
* **Redirections**:
  * `<` redirect input.
  * `>` redirect output.
  * `<<` here-document (reads input until a delimiter is seen).
  * `>>` redirect output in append mode.
* **Pipes (`|`)**: Connects the output of one command to the input of the next.
* **Environment Variables**: Expands `$VAR` to its value and `$?` to the exit status of the last executed command.
* **Signals**: Properly handles `ctrl-C`, `ctrl-D` (EOF), and `ctrl-\` just like in bash.
* **Built-in Commands**:
  * `echo` (with `-n` option)
  * `cd` (relative or absolute paths)
  * `pwd` (print working directory)
  * `export` (export environment variables)
  * `unset` (unset environment variables)
  * `env` (print environment)
  * `exit` (exit the shell)

### Bonus
* Logical operators `&&` and `||` with parenthesis for command priorities.
* Wildcard `*` matching for the current working directory.

## 📂 Project Structure

* `src/` - Mandatory source files.
* `inc/` - Mandatory header files.
* `srcbonus/` - Bonus source files.
* `incbonus/` - Bonus header files.
* `libft/` - Custom C library containing standard utility functions.
* `Makefile` - Compilation instructions and rules.

## 🚀 Getting Started

### Prerequisites
* A Unix-like operating system (Linux/macOS)
* `gcc` or `cc` compiler
* `make`
* `readline` library installed on your system

### Installation

1. Clone the repository:
   ```bash
   # Clone the repo using git
   git clone [https://github.com/iestero42/minishell.git](https://github.com/iestero42/minishell.git)
   cd minishell

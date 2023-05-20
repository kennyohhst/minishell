# Minishell

Minishell is the second project of the Unix branch at 42, a minimum viable version of a real shell. The main goal of this project is to have a good understanding of process creation and synchronization using the C programming language.

The shell provides a command-line interface that allows users to interact with the operating system. It takes input from the user and executes commands in the form of executable programs or shell built-in commands.

## Features

- The shell supports executing commands, as well as shell built-in commands such as `cd`, `echo`, `env`, `export`, `pwd`, and `unset`.
- The shell supports redirection of input and output streams using `<` and `>` symbols.
- The shell supports pipes (`|`) to connect the output of one command to the input of another.
- The shell supports signals such as `Ctrl-C` and `Ctrl-D` to terminate a running process or the entire shell.
- The shell supports line editing and history using the GNU readline library.

## Getting Started

### Prerequisites

- The Readline library `sudo apt-get install libreadline8 libreadline-dev`
- A Unix-like operating system such as Linux or macOS.
- GCC compiler installed.

### Installing and running

1. Clone this repository:
```
git clone https://github.com/kennyohhst/minishell minishell
```

2. cd into the right directory
```
cd minishell
```

3. Run Make to compile the program
```
make
```

4. Execute the program
```
./minishell
```

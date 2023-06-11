# HSH: The Holberton Shell

The **HSH** (Holberton Shell) is a project developed at Holberton School, designed to help students understand advanced concepts related to shell development. It covers various aspects such as processes, system calls, bit manipulation, file management, and error handling.

## Table of Contents

- [Getting HSH](#getting-hsh)
- [Features](#features)
- [Builtins](#builtins)
- [History](#history)

## Getting HSH

To try the **HSH** shell, follow these steps:

1. Clone the current project repository by executing the following command:

   ```
   git clone https://github.com/shehab910/simple_shell.git
   cd simple_shell
   ```

2. Once the repository is cloned, compile the shell by ensuring that it is tested and guarantees work based on **gcc-4.8** and the **C90 standard**. This ensures compatibility with the required compiler version and language standard.

   ```
   gcc -Wall -Wextra -pedantic -std=gnu89 *.c -o hsh
   ```

3. After successful compilation, you will be ready to use the **HSH** shell.

   ```
   ./hsh
   ```

## Features

The **HSH** shell provides the following features:

- [x] Interactive and non-interactive modes.
- [x] Displays a prompt and waits for the user to type a command. Each command line ends with a new line.
- [x] Handles errors gracefully and provides appropriate error messages if an executable cannot be found.
- [x] Handles the "end of file" condition (Ctrl+D) to indicate the end of user input.
- [x] Supports command lines with arguments.
- [x] Handles the `PATH` environment variable to locate and execute programs.
- [x] Supports the `exit` command to exit the shell with an optional status.
- [x] Handles the Ctrl-C signal to prevent termination of the shell.
- [ ] Handles command separators (`;`) to execute multiple commands on a single line.
- [ ] Handles logical operators (`&&` and `||`) for conditional command execution.
- [ ] Handles variable replacements using the `$?` and `$$` syntax.
- [ ] Handles comments using the `#` symbol.
- [ ] Supports the history feature to track previously executed commands.
- [ ] Supports file input to read and execute commands from a file.

## Builtins

The **HSH** shell provides the following built-in commands:

- [x] `exit [STATUS]`: Exits the shell with an optional exit status.
- [ ] `cd [DIRECTORY]` or `[OPTION]`: Changes the current working directory.
- [x] `env`: Displays the environment variables.
- [ ] `setenv [VARIABLE] [VALUE]`: Initializes a new environment variable or updates an existing one.
- [ ] `unsetenv [VARIABLE]`: Removes an environment variable.
- [ ] `alias [name [='value'] ...]`: Manages command aliases.
- [ ] `help [BUILTIN]`: Displays help information for a built-in command.
- [ ] `history`: Displays the command history.

## History

In the field of Unix operating systems, the original design and implementation were accomplished by **Ken Thompson**, a renowned computer scientist and co-creator of the Unix operating system. He made significant contributions to the development of Unix, which laid the foundation for modern operating systems.

The first version of the UNIX shell, a fundamental component of the Unix operating system, was written by **Ken Thompson** himself. The shell is an interactive command-line interface that enables users to interact with the underlying operating system.

The **B programming language** was invented by **Ken Thompson** as well. It served as a direct predecessor to the C programming language, which has become one of the most widely used and influential programming languages.

**Ken Thompson** is a highly influential computer scientist who played a crucial role in the development of Unix and various programming languages. His contributions have greatly impacted the fields of operating systems and programming language design.

A shell works as a command-line interpreter that facilitates communication between the user and the operating system. It reads commands from the user, interprets them, and executes the corresponding programs or actions. The shell manages processes, handles input and output, and provides various features to enhance user productivity.

In the context of processes, a **pid** (Process ID) refers to a unique numerical identifier assigned to each running process by the operating system. It is used to track and manage processes. The **ppid** (Parent Process ID) represents the ID of the parent process that spawned the current process.

To manipulate the environment of the current process, the shell provides various mechanisms. This includes managing environment variables, which are key-value pairs that store information such as configuration settings and system paths.

A **function** is a reusable block of code within a program that performs a specific task. It allows for modular and organized programming. On the other hand, a **system call** is a request made by a program to the operating system for performing privileged operations, such as file operations or process management.

Processes are created by using system calls, such as `fork()`, which creates a new process by duplicating the existing one. The new process, known as the child process, can execute different code from the parent process.

There are three valid prototypes for the `main` function in C:

```c
int main(void);
int main(int argc, char *argv[]);
int main(int argc, char *argv[], char *envp[]);
```

The `PATH` is an environment variable that specifies a list of directories where the shell searches for executable programs when a command is entered. The shell utilizes the `PATH` to locate and execute programs without requiring their full path to be specified.

To execute another program from the shell, the `execve` system call is used. It replaces the current process image with a new one specified by the given program path.

The shell can suspend the execution of a process until one of its children terminates by using system calls like `wait()` or `waitpid()`. These calls allow the parent process to wait for the completion of child processes.

**EOF** (End-of-File) is a condition that indicates the end of a file or the end of an input stream. In the context of shell input, pressing **Ctrl+D** signals an EOF condition, which is interpreted as the end of user input.

Feel free to explore the **HSH** shell and utilize its features for an enhanced command-line experience.

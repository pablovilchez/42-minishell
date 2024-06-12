# 42 - Minishell

![42 School](https://img.shields.io/badge/42%20School-Project-blue)
![Git](https://img.shields.io/badge/Git-F05032?logo=git&logoColor=white)
![C](https://img.shields.io/badge/C-A8B9CC?logo=c&logoColor=white)
![Bash](https://img.shields.io/badge/Bash-4EAA25?logo=gnubash&logoColor=white)
![Grade](https://img.shields.io/badge/Grade-101-brightgreen)



## Description

Minishell is a project from 42 School that involves creating a simple yet functional shell in C. The goal of this project is to gain a deeper understanding of how shells work and to develop advanced programming skills in C.

## Features

- Execution of basic commands (e.g., `ls`, `echo`, `cat`, etc.)
- Input and output redirection (`>`, `>>`, `<`)
- Pipes (`|`)
- Environment variables
- Signal handling and process management
- Support for built-in commands like `cd`, `export`, `unset`, `env`, `exit`

## Requirements

- Unix-based operating system (Linux or macOS)
- GCC compiler
- Readline library (optional for advanced functionality)

## Installation

1. Clone the repository:

    ```sh
    git clone https://github.com/pablovilchez/42-minishell.git
    ```

2. Navigate to the project directory:

    ```sh
    cd minishell
    ```

3. Compile the project:

    ```sh
    make
    ```

## Usage

Run the shell by executing the following command:

```sh
./minishell
```

## Built-in Commands

- `cd [directory]`: Change the current directory.
- `export [variable]=[value]`: Set an environment variable.
- `unset [variable]`: Remove an environment variable.
- `env`: Display the current environment variables.
- `exit [status]`: Exit the shell with a status code.

## Examples

```sh
$ ./minishell
minishell> ls -l
total 8
-rwxr-xr-x 1 user group 4096 Jun 12 12:00 minishell
minishell> echo "Hello, World!"
Hello, World!
minishell> cat < file.txt | grep "search" > output.txt
minishell> exit
$
```

## Authors

- **Pol** - [github.com/pablovilchez](https://github.com/pablovilchez)
- **Gabi** - [github.com/gkrusta](https://github.com/gkrusta)

## License

This project is licensed under the MIT License.

## Acknowledgments

- Thanks to 42 School for the project guidelines and support.

---

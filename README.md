# Simple Shell
A study project to create a shell capable of processing and executing bash commands

## Requirements
- A valid C installation
- A C compiler, such as gcc

## Installation and running
1. Download and extract this repository as a .zip or use `git clone` with this page's URL.
2. Open the terminal and navigate to the folder containing the downloaded files.
3. Use `gcc *.c` to compile all the C files together. Optionally, add `-o [FILENAME]` to name the resulting file whatever is put as `FILENAME` instead of "a.out".
4. Run the created file by using `./[FILENAME]`. If you didn't use the `-o` option above then the command would be `./a.out`.

## Use
The shell will behave similarly to those included in most operating systems, running given commands in the shell's environment.
- Running the file with arguments will cause the shell to process the arguments as shell commands (and their arguments) and execute them instantly and quit
- Running the file with no arguments will run the shell in interactive mode, allowing the user to type commands line by line.
In either mode, as either a set of run arguments or command, providing the name of a command from the bin PATH or current directory will execute it.

### Interactive mode
Interactive mode lets the user continually enter commands without having to re-run the shell. After processing a command, it will expect another input without delay in a new line.
This mode has two built-in commands:
- `env`: Print the current environment the shell is operating in, including PATH variables and other relevant data objects that can affect runtime.
- `exit`: Stop taking commands and terminate the program.

## Examples
The examples below assume the file was compiled with the name "simple_shell".
- `simple_shell`: Run the shell in interactive mode.
### Non-interactive
- `simple_shell ls -l`: Execute the "ls" command with the one-per-line argument via the shell, then exit.
- `simple_shell echo "Hello"`: Execute the "echo" command with the argument "Hello", then exit
### Interactive
- `ls -l`: Execute the ";s command with the one-per-line argument via the shell, then wait for another input.
- `echo "Hello"`: Execute the "echo" command with the argument "Hello", then wait for another input.
- `env`: Print the current environment variables, then wait for another input.
- `exit`: Quit the program.

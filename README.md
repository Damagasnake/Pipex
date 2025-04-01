# Pipex

A C program that simulates the Unix pipeline functionality, allowing command execution with redirected input/output.

---

## Overview

Pipex replicates the behavior of the shell pipe operator (`|`) by implementing a program that can take an input file, multiple commands, and output the result to an output file. This program is designed to work like the Unix command:

```bash
< infile cmd1 | cmd2 | cmd3 ... | cmdn > outfile
```

### Features:
- Handle multiple commands in a pipeline (not limited to just 2).
- Process command arguments correctly.
- Proper file descriptor management.
- Error handling for commands, files, and processes.
- Clean memory management.

---

## File Structure

```
├── main.c           # Entry point of the program
├── cmd_parse.c      # Command parsing and linked list creation
├── path_utils.c     # Functions for finding command paths
├── execute.c        # Core execution logic with pipes
├── execute_cmd.c    # Command execution functionality
└── pipex.h          # Header with declarations and data structures
```

---

## Data Structures

```c
typedef struct s_pipexcmd
{
    pid_t pid1;                  // Process ID for this command
    pid_t pid2;                  // Second process ID (if needed)
    int tube[2];                 // Pipe file descriptors [read, write]
    int infile;                  // Input file descriptor
    int outfile;                 // Output file descriptor
    char **cmds;                 // Command and its arguments
    int argc;                    // Number of arguments
    int status;                  // Execution status
    struct s_pipexcmd *nextnode; // Next command in pipeline
} t_pipexcmd;
```

---

## Command Flow

1. **Parsing**: The program parses the command line arguments to create a linked list of commands.
2. **Execution**: For each command in the linked list:
   - Create a pipe for passing data to the next command.
   - Fork a new process.
   - In the child process:
     - Set up input from the previous pipe or input file.
     - Set up output to the next pipe or output file.
     - Execute the command.
   - In the parent process:
     - Close unused file descriptors.
     - Save the read end of the pipe for the next command.
3. **Cleanup**: Wait for all child processes to finish and free allocated memory.

---

## Usage

```bash
./pipex infile cmd1 cmd2 ... cmdn outfile
```

Example:

```bash
./pipex input.txt "ls -l" "grep a" "wc -l" output.txt
```

This is equivalent to the shell command:

```bash
< input.txt ls -l | grep a | wc -l > output.txt
```

---

## Error Handling

The program handles various error cases:

- Invalid number of arguments.
- File access errors.
- Command not found.
- Fork errors.
- Pipe creation errors.

---

## Learning Outcomes

This project demonstrates:

- Understanding of Unix processes and IPC (Inter-Process Communication).
- Working with file descriptors and redirections.
- Using pipes to connect processes.
- Proper memory management in C.
- Handling environment variables.
- Implementation of command parsing.

---

## License

This project is part of the 42 School curriculum.

---

*Authored by Damaga*
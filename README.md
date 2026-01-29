*This project has been created as part of the 42 curriculum by dzhukov.*

## Description
This project involves programming a function that returns a line read from a file descriptor. The goal is to create a highly useful function for your collection while learning the important concept of static variables in C programming. Reading a line from a file descriptor can be tedious, and this function simplifies the process by returning one line at a time upon repeated calls.

## Instructions

### Compilation
The project must be compiled with the following flags: `-Wall -Wextra -Werror`. Additionally, you must define a buffer size for the `read()` function using the `-D BUFFER_SIZE=n` flag.

> [!IMPORTANT]
> You will have to write your own main.c to test the function, or uncomment my main() function (which reads the whole test.txt file) inside get_next_line.c file.

**Example:**
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

### Execution and Behavior
The function `get_next_line(int fd)` returns the line that was read, including the terminating `\n` character.

If the end of the file is reached and does not end with a `\n`, the line is returned without it.

The function returns `NULL` when there is nothing else to read or if an error occurred.

It is designed to work both with file reading and standard input.

## Resources

* **C Programming Documentation:** General documentation for `read`, `malloc`, and `free`.

* **Static Variables:** YouTube guides on how static variables and file descriptors work.

* **AI Usage:** AI *(Gemini)* was utilized as a tutoring tool for the following tasks:

  * Clarifying the logic behind `read`, and `open` functions and their parameters.

  * Explaining the theory behind file descriptors and *"everything is a file"* concept.

  * Structuring and formatting the technical documentation for this README.

## Algorithm Justification
The selected algorithm utilizes a static character pointer to maintain a *"stash"* of data between function calls. This approach was chosen over a Linked List implementation for several reasons:

1. **Memory Continuity:** Using a static string with `ft_strjoin` keeps the data in a contiguous block of memory, which is generally more cache-friendly than a linked list where nodes are scattered throughout the heap.

2. **Implementation Complexity:** A linked list approach requires a custom structure and more complex logic for *"cleaning"* or *"updating"* the nodes after a line is extracted. The static string approach simplifies the *"cleanup"* phase to a single `malloc` and `free` cycle.

3. **Efficiency with Buffer Sizes:** While linked lists can be efficient for very large buffer sizes to avoid massive realloc operations, a string-based approach is more straightforward for the typical `BUFFER_SIZE` ranges.


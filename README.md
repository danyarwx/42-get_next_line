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

---

### Detailed Explanation

We have a file with multiple lines:

```bash
Line One\n
Line Two\n
Line Three\n
```

And the BUFFER_SIZE set to 5 initially

How get_next_line works:

The main function reads the file with a given buffer and puts it
into a string buffer.
Buffer gets overwritten with each call.
Now we uppend each of the read outputs into another string called stash,
using ft_strjoin and freeing the previous stash all the time.
And with each iteration we check whether or not this stash contains '\n'

As soon as newline is inside the string, we stop the loop,
we free the buffer, and we return the stash containing either just our first string or a little more.

Next step is to extract the exact line we need.
With the extract_line function we allocate memory and make a copy of the string just till the newline symbol or till end of string is reached, this is stored in "line".

Next step is to update stash in case we have something left.
Here we basically make another stash and copy there from the newline

```c
if (stash[i] == '\0')
{
    free(stash);
    return (NULL);
}
```

What it does:
- Check if there's any content after the `\n`
- If the character right after `\n` is `\0`, we've extracted everything

Example 1**: `stash = "OneLine\n"`
```bash
Index: 0 1 2 3 4 5 6 7 8
Char:  O n e L i n e \n \0

After i++: i = 8
Check: stash[8] == '\0'? → YES

Action:
  1. free(stash) → release memory
  2. return NULL → nothing left
```

We either update stash by copying everything after the newline, or we check and if there is not anything after the newline or EOF is reached, we free stash and return NULL;

Finally we return the line that was read.
If we run get next line again, the leftovers are stored in the static variable stash and we are going to print them out next time.

*This project has been created as part of the 42 curriculum by raaribou.*

# get_next_line

## Description

`get_next_line` is a C function that returns **one line at a time** from a file descriptor. Calling it repeatedly in a loop reads a file (or standard input) line by line until there is nothing left to read.

```c
char *get_next_line(int fd);
```

**Goal.** Add a reusable function to my C toolbox and learn an important C concept: **static variables**, which keep a value alive between calls. Along the way the project covers file descriptors, the `read` system call, heap memory management (`malloc` / `free`, leak-free code) and careful handling of edge cases.

**Behavior**

- Returns the line that was read, **including the terminating `\n`**. The only exception is the last line of a file that does not end with `\n`.
- Returns `NULL` when there is nothing left to read, or when an error occurs (`read` fails, `malloc` fails, invalid file descriptor).
- Works on regular files and on standard input.
- Reads as little as possible on each call: it stops reading as soon as a newline has been found.
- Works for any `BUFFER_SIZE` (1, 42, 9999, 10000000...).

**Allowed functions:** `read`, `malloc`, `free`. Forbidden: `lseek`, global variables, `libft`.

### Files

| File | Part | Content |
|---|---|---|
| `get_next_line.c` | mandatory | `get_next_line` and its static helpers |
| `get_next_line_utils.c` | mandatory | string helpers (`ft_strlen`, `ft_strchr`, `ft_strdup`, `ft_strjoin`, `ft_substr`) |
| `get_next_line.h` | mandatory | prototypes and the `BUFFER_SIZE` default |
| `get_next_line_bonus.c` | bonus | same function, handling several file descriptors at once |
| `get_next_line_utils_bonus.c` | bonus | string helpers and the file descriptor list lookup |
| `get_next_line_bonus.h` | bonus | prototypes, the `t_fds` type and the `BUFFER_SIZE` default |

## Instructions

No Makefile is required for this project. The files are compiled together with your own `main.c`. `BUFFER_SIZE` is set with `-D BUFFER_SIZE=n`; if the flag is omitted, the headers define a default of `2048`.

**Example `main.c`** (works for both the mandatory and the bonus version, because both expose the same `get_next_line` prototype):

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	fd = 0;
	if (ac > 1)
		fd = open(av[1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

It reads the file given as the first argument, or standard input when no argument is given. The caller owns every returned line and must `free` it.

**Mandatory**

```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
./a.out file.txt
```

**Bonus**

```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line_bonus.c get_next_line_utils_bonus.c
./a.out file.txt
```

To test the bonus, call `get_next_line` on two different file descriptors in turn: each one keeps its own position.

## Algorithm

### The idea

A `read` call returns a fixed number of bytes (`BUFFER_SIZE`) that has nothing to do with where lines end. One `read` can contain half a line, exactly one line, or many lines. So the function needs somewhere to keep the **leftover** bytes between calls. This is the job of a **static variable**: `static char *cache`. It lives for the whole program, but is visible only inside `get_next_line`.

### Steps of one call

```
cache (from the previous call)
   |
   v
1. read_and_save   read BUFFER_SIZE bytes at a time and append them to the cache
                   until the cache contains a '\n' or read() returns 0 (EOF)
2. extract_line    copy the cache up to and including the first '\n'
                   (or up to the end of the string if there is no '\n')
3. trim            keep only what comes after that line; free the old cache
   |
   v
return the line   (the cache now holds only the leftover)
```


### Why this design

- **Static cache.** It is the simplest way to remember the leftover between calls without a global variable. A global is forbidden, and a static variable has the same lifetime with a much smaller scope.
- **Read until a newline, not the whole file.** The subject asks to read as little as possible per call. The loop stops as soon as the cache contains a `\n`, so a huge file is never loaded at once.
- **Three small functions.** `read_and_save`, `extract_line` and `trim` each do one thing and stay within the Norm limits (25 lines, 5 functions per file).
- **Every allocation has one owner.** The line is owned by the caller. The cache is owned by the function, and each helper frees the buffer it replaces: `read_and_save` frees the old cache after the join, and `trim` frees the old cache after building the new one. Every error path (`read` returning -1, `malloc` failing) frees the buffers it holds and returns `NULL`.
- **Cache set to `NULL` when empty.** When the last line consumes everything, `trim` returns `NULL` instead of an empty string, so nothing stays allocated after the end of the file.

### Edge cases

| Case | Handling |
|---|---|
| `BUFFER_SIZE = 1` | one byte per `read`; the loop stops exactly at the newline |
| `BUFFER_SIZE` very large (10000000) | one `read` may return the entire file; the leftover lines stay in the cache |
| file without a final `\n` | the last line is returned without `\n`, then the next call returns `NULL` |
| empty file | the first call returns `NULL` |
| `fd < 0`, or `BUFFER_SIZE <= 0` | returns `NULL` immediately |
| `read` fails (`-1`) | frees everything it holds and returns `NULL` |
| `malloc` fails | frees everything it holds and returns `NULL` |


## Bonus: multiple file descriptors

The bonus version can read from several file descriptors in alternation (for example fd 3, then 4, then 5, then 3 again) without mixing their reading states. It still uses **only one static variable**.

### The idea

Instead of one cache for the whole program, each file descriptor gets its own cache, stored in a node of a linked list. The only static variable is the head of that list.

```
static t_fds *head
      |
      v
 [ fd 3 | cache "cd\nef" ] -> [ fd 7 | cache "xyz" ] -> NULL
```

```c
typedef struct s_fds
{
	int				fd;
	char			*cache;
	struct s_fds	*next;
}	t_fds;
```

### Each call

1. `find_fd` walks the list looking for the node of this `fd`. If there is none, it creates one at the front of the list with an empty cache (`NULL`).
2. The same three steps as the mandatory part (`read_and_save`, `extract_line`, `trim`) run on that node's cache.
3. When a file descriptor has nothing left to remember (end of file, error, or the last line consumed the whole cache), `drop_fd` removes its node from the list and frees the cache and the node.


## Resources

**References**

- `man 2 read`, `man 3 malloc`, `man 3 free`: https://man7.org/linux/man-pages/man2/read.2.html
- Storage duration and static variables in C: https://en.cppreference.com/w/c/language/storage_duration
- Valgrind quick start (leak and invalid-access detection): https://valgrind.org/docs/manual/quick-start.html
- Brian W. Kernighan, Dennis M. Ritchie, *The C Programming Language*.
- Remzi h. arpaci-dusseau, *Operating systems three easy pieces*.
**Use of AI**

AI was used as a research and learning aid:

- **Research:** to understand static variables, file descriptors, how `read` behaves, heap memory, pointers to pointers and linked lists, and to find the edge cases to test.

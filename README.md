
# Text Statistics Tool

A command‑line text statistics utility written in **C99**.  
Reads from a file or standard input and computes character, word, line, and sentence counts, plus word‑frequency analysis.

---

## Features

- Character, word, line, and sentence counting
- Word‑frequency analysis with sorting:
  - descending frequency
  - alphabetical order for ties
- Case‑insensitive counting (optional, can be enabled)
- Read from file or standard input
- Robust error handling (missing files, empty input, etc.)
- Modular C source/header organisation
- Support for multiple input files (optional, extendable)
- Multiple input files
- Case‑insensitive counting (already implemented as optional)
---

## Requirements

- C compiler with **C99** support (GCC recommended)
- GNU Make

On Debian/Ubuntu:

```bash
sudo apt install build-essential
```

---

## Building

Clone the repository:

```bash
git clone git@github.com:AbdullahAbdelaziz122/text_stats_c_language.git
cd text_stats
```

Build with:

```bash
make
```

The executable `stat` will be created in the project root.

---

## Usage

```bash
./stat [FILE]
```

| Argument | Description               |
|----------|---------------------------|
| `FILE`   | Input text file           |
| (none)   | Read from standard input  |

### Examples

**From a file:**

```bash
./stat example.txt
```

**From standard input:**

```bash
echo "hello world" | ./stat
```

or

```bash
cat file.txt | ./stat
```

---

## Output Example

```
Characters: 123
Words: 45
Lines: 6
Sentences: 3

Top 10 most frequent words:
-----------------------------
the   : 12
and   : 8
to    : 5
```

---

## Project Structure

```
text_stats/
├── include/
│   ├── stats.h          # Counting function prototypes
│   ├── word_freq.h      # Frequency structures & prototypes
│   └── utils.h          # Shared helpers
├── src/
│   ├── main.c           # Argument parsing, I/O, orchestration
│   ├── stats.c          # Character, word, line, sentence counting
│   └── word_freq.c      # Frequency tracking, sorting, printing
│    
├── tests/               # Test input files
│   ├── mixed_case.txt
│   ├── test_full.txt
│   └── test_empty.txt
├── build/               # Object files (generated)
├── Makefile
├── README.md
└── LICENSE
```

---

## Development Guidelines

### Compiler Flags

The project is built with:

```text
-Wall -Wextra -Werror -std=c99
```

Warnings are treated as errors.

### Memory Management

All dynamically allocated memory (`malloc`, `calloc`, `realloc`) must be freed.  
The code should be tested for leaks, double frees, use‑after‑free, and buffer overflows.

### Debugging

A debug build includes `-g`. Example:

```bash
make clean
make CFLAGS="-Wall -Wextra -Werror -std=c99 -g"
```

Then use GDB:

```bash
gdb ./stat
```

### Sanitizers

**AddressSanitizer** (memory errors):

```bash
make clean
make CFLAGS="-Wall -Wextra -Werror -std=c99 -g -fsanitize=address"
./stat tests/test_full.txt
```

**UndefinedBehaviorSanitizer**:

```bash
make clean
make CFLAGS="-Wall -Wextra -Werror -std=c99 -g -fsanitize=undefined"
./stat tests/test_full.txt
```

---

## Testing

Run against various inputs to verify correctness.  
Example test cases:

| Input                             | Expected Result                                           |
|-----------------------------------|-----------------------------------------------------------|
| `"hello world"`                   | 11 characters, 2 words                                    |
| `"one two three two one"`         | `one:2`, `two:2`, `three:1`                               |
| Empty file                        | all counts zero                                           |
| `"Hello, world!"`                 | 2 words (`Hello`, `world`)                                |
| `"The... cat and dog."`           | 4 words (`The`, `cat`, `and`, `dog`)                      |
| `"Apple apple APPLE"`             | `apple:3` (case‑insensitive)                              |
| Very large file                   | no crashes, bounded memory usage                          |

Edge cases to consider:

- Multiple spaces, tabs, newlines
- Files without final newline
- Only punctuation or whitespace
- Very long words / large files
- Numbers mixed with letters
- Permission‑denied files

For reference, compare with standard Unix tools:

```bash
wc -c file.txt
wc -w file.txt
wc -l file.txt
```

> Note: `wc -w` may define words differently; discrepancies are not necessarily bugs.

---

## Optional Stretch Features

After core functionality is stable, you may consider adding:

- Stop‑word filtering
- JSON / CSV output
- Longest word and average word length
- Interactive mode
- Parallel processing for very large files

---

## License

This project is distributed under the **MIT License**.  
See [`LICENSE`](LICENSE) for details.

---

## Author

**Abdullah Abdelaziz**  
GitHub: [AbdullahAbdelaziz122](https://github.com/AbdullahAbdelaziz122)

---
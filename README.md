# Text Statistics Tool

## 1. Overview

**Purpose**  
Build a command-line utility that reads text from a file or standard input and computes various statistics. This teaches you how to manipulate strings efficiently, handle files, and build a modular data-processing pipeline.

**Real-World Applications**  
- **Log analysis** – counting error occurrences, frequency of specific events.
- **Configuration parsing** – extracting key-value pairs, counting sections.
- **Data preprocessing** – cleaning and analyzing text data before feeding it to an embedded system.
- **Resource-constrained systems** – implementing efficient string operations without relying on heavy libraries.

**What Employers Expect**  
- Ability to process large text files efficiently (memory and time).
- Understanding of string manipulation in C (pointer arithmetic, null-termination).
- Experience with hash tables or sorting algorithms for frequency analysis.
- Clean argument parsing using `argc`/`argv`.
- Modular design that separates file I/O, statistics computation, and output formatting.

---

## 2. Functional Requirements

Your program shall:

1. **Accept input from:**
   - Standard input (if no file is specified).
   - A file specified as a command-line argument (e.g., `./text_stats file.txt`).

2. **Compute and print:**
   - **Character count** (including spaces, excluding the null terminator).
   - **Word count** – words are sequences of alphanumeric characters (a-z, A-Z, 0-9). Hyphens and apostrophes inside words may be handled as part of the word, but for simplicity, treat any non-alphanumeric as a delimiter.
   - **Line count** – count lines (including empty lines).
   - **Sentence count** – sentences end with `.`, `!`, or `?` (handle abbreviations carefully, or simplify for now).
   - **Word frequency** – list each unique word and how many times it appears, sorted by frequency (descending) and alphabetically (ascending) for ties.

3. **Format output clearly**, e.g.:
   ```
   Characters: 123
   Words: 45
   Lines: 6
   Sentences: 3
   Top 10 most frequent words:
   the   : 12
   and   : 8
   to    : 5
   ...
   ```

4. **Handle errors gracefully:**
   - File not found → print error and exit.
   - Empty file → print all counts as zero.
   - Too many arguments → print usage message.

---

## 3. Optional Stretch Features

1. **Multiple file support** – accept multiple files and print statistics for each.
2. **Case-insensitive counting** – treat "The" and "the" as the same word.
3. **Stop word filter** – ignore common words (e.g., "the", "and", "is") from frequency output.
4. **Output formats** – support `--json` or `--csv` for structured output.
5. **Longest word** – print the longest word and its length.
6. **Average word length** – compute and display.
7. **Parallel processing** – for very large files, use threads to process chunks (stretch goal for later).
8. **Interactive mode** – if no file is provided, prompt the user for text input.

---

## 4. Constraints

**Allowed:**
- `<stdio.h>`, `<stdlib.h>`, `<string.h>`, `<ctype.h>`, `<stdbool.h>`, `<stdint.h>`, `<limits.h>`, `<errno.h>`.

**Forbidden (initially):**
- External libraries (no `regex`, no `sqlite`, no `ncurses`, no `libxml`).
- `strtok()` – you must implement your own tokenization to learn string handling.
- `scanf()` for reading files (use `fgets()` or `fread()`).
- Global variables (except for debugging flags).

**Memory:**
- You may use dynamic allocation (`malloc`/`free`) for storing words and their frequencies.
- For large files (e.g., > 100 MB), consider a streaming approach instead of loading the whole file into memory.

---

## 5. Project Structure

```
text_stats/
├── src/
│   ├── main.c          – Argument parsing, orchestration, output
│   ├── stats.c/h       – Compute character, word, line, sentence counts
│   ├── word_freq.c/h   – Word frequency tracking (insert, update, sort, print)
│   ├── tokenizer.c/h   – Custom tokenizer (split text into words)
│   ├── utils.c/h       – Helper functions (trim, case-insensitive compare, etc.)
│   └── file_reader.c/h – Read file or stdin, chunking logic
├── tests/
│   ├── empty.txt
│   ├── one_word.txt
│   ├── lorem_ipsum.txt
│   ├── mixed_case.txt
│   └── punctuation.txt
├── Makefile
└── README.md
```

---

## 6. Development Milestones

| Milestone | Objective |
|-----------|-----------|
| **1** | Accept input from `stdin` and a file (via `argc`/`argv`). Read the entire file or stream into a buffer. Print the text to verify. Handle file-not-found errors. |
| **2** | Implement basic counting: characters, words, lines, sentences. Use a simple state machine for word detection (traverse characters, update counts). Print results. |
| **3** | Implement word frequency: tokenize text into words, store in a dynamic array or hash table. Count frequencies. Print the top 10 words. |
| **4** | Sort the word frequency list (by count descending, then alphabetically). Print all unique words or a configurable top N. |
| **5** | Add case-insensitive support. Add stop word filter (optional). Improve error handling and edge cases (empty file, huge file). |
| **6** | Refactor into modules. Add a simple test script to verify output against known inputs. Polish README. |

---

## 7. Test Cases

| Input | Expected Output (partial) |
|-------|---------------------------|
| `"hello world"` (stdin) | Characters: 11, Words: 2, Lines: 1, Sentences: 1 (or 0 if no punctuation) |
| `"one two three two one"` | Word freq: one:2, two:2, three:1 |
| Empty file | All counts zero, no frequency list |
| File with 1000-line text | Counts match `wc -l`, `wc -w`, `wc -c` |
| `"Hello, world!"` | Words: "Hello" and "world" (punctuation stripped) |
| `"The... cat and dog."` | Words: "The", "cat", "and", "dog" (treat "..." as delimiter) |
| Mixed case: `"Apple apple APPLE"` (case-insensitive) | `apple: 3` (if implemented) |
| Very long file (e.g., 100 MB) | Must not crash; memory usage bounded |

**Edge Cases:**
- Multiple spaces, tabs, newlines.
- Words with apostrophes: `"don't"` – decide whether to treat as one word or split.
- Numbers: `"100"` – treat as a word? (Yes, alphanumeric).
- Files with no newline at the end.
- File with only punctuation.

---

## 8. Common Beginner Mistakes

1. **Using `feof()` incorrectly** – often leads to double-reading or missing last line. Use `fgets()` return value directly.
2. **Not handling `\r` (Windows CRLF)** – treat `\r` as whitespace.
3. **Memory leaks** – forgetting to `free()` dynamically allocated word entries.
4. **Tokenization bugs** – not skipping delimiters properly, or including delimiters in words.
5. **Case sensitivity** – forgetting to `tolower()` when counting frequencies.
6. **Off-by-one errors** – line count, null-terminator handling.
7. **Inefficient sorting** – using bubble sort on tens of thousands of words; use `qsort()` from `<stdlib.h>`.
8. **Not handling long lines** – `fgets()` with a fixed buffer may truncate; handle partial lines.
9. **Using `strstr()` or `strchr()` incorrectly** – returning pointers without bounds checking.
10. **Ignoring `EOF` conditions** – reading beyond the end of file.

---

### 9. Engineering Best Practices

- **Modularity** – separate concerns: file reading, tokenization, counting, frequency tracking, and output.
- **Use `static` functions** for internal helpers within a module.
- **Use `const`** for input parameters that are not modified.
- **Error codes** – return meaningful error codes from functions; handle in `main()`.
- **Memory management** – always pair `malloc` with `free`. Use tools like Valgrind to check leaks.
- **Efficiency** – process text in chunks (streaming) rather than loading entire file if possible.
- **Portability** – handle Windows and Unix line endings; use `size_t` for sizes.
- **Clear output** – format statistics in a human-readable way.
- **Documentation** – each public function should have a comment describing its purpose, parameters, and return values.

---


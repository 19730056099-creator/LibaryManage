---
artifact_id: project-map
language: en
---

# Project Map

## Purpose

`LibaryManageSrc` is a single-process, single-user C command-line library manager. A user can add, list, search, update, and delete books, borrow and return books, and view borrow records. Runtime state is stored in the relative-path files `books.txt` and `borrows.txt`.

The repository has no README, Makefile, or automated tests. `main.c` directly includes `data_mgr.c` and `business.c`, so the smallest build entry is to pass only `main.c` to gcc. The program must be started from a working directory containing the data files.

## Core User Journey

1. `main()` calls `initSystem()`, which loads two global arrays from the text files.
2. `displayMenu()` shows the menu; `fgets` reads a choice, `atoi` converts it, and `switch` dispatches it.
3. Add, list, search, update, and delete operations read and write the `Book` array.
4. Borrowing checks `available`, decrements inventory, and creates a `BorrowRecord`; returning increments inventory and marks the record.
5. Mutations call `saveData()`; choice 0 calls `saveAllData()` before exit.

## Subsystems

| Subsystem ID | Responsibility | Input | Output | Dependency | Source locations |
|---|---|---|---|---|---|
| `ui-menu` | Menu, prompts, stdin input, and result messages | User text | Calls to business functions | `domain-business` | `main.c::displayMenu`, `main.c::displayHelp`, `main.c::main` |
| `domain-business` | Book CRUD, search, and borrow/return rules | Strings and quantities | Array changes, 0/1 results, save calls | `data-store` | `business.c::addBook`, `searchBook`, `updateBook`, `deleteBook`, `borrowBook`, `returnBook` |
| `data-store` | Structs, fixed-capacity arrays, lookup, file I/O, and dates | Two text files | In-memory and file state | C standard library | `data_mgr.c::Book`, `BorrowRecord`, `loadData`, `saveData` |

## Technology Layer Map

Trace one user action downward through these layers:

- `layer-01`: shell and current working directory; it determines whether gcc finds sources and whether the program finds `books.txt`.
- `layer-02`: C11 compiler; `main.c` is the current translation-unit entry, built with `gcc -std=c11 -Wall -Wextra -pedantic main.c -o library`.
- `layer-03`: single-process stdin/stdout runtime; menu input passes through `fgets`, `atoi`, and `switch`.
- `layer-04`: application components; the UI in `main.c` calls `business.c`, whose functions read and write the global arrays from `data_mgr.c`.
- `layer-05`: text storage; `books.txt` uses `id|title|author|quantity|available`, while `borrows.txt` uses `bookId|borrower|borrowDate|returnDate|returned`.

## Troubleshooting Map

| `failure_id` | Observable symptom | First inspection | Next boundary |
|---|---|---|---|
| `failure-01` | Duplicate-definition or declaration errors at compile time | Check that only `main.c` is compiled; inspect its two `.c` includes | `layer-02` → `main.c` build boundary |
| `failure-02` | Startup list is empty or data was saved elsewhere | Run `pwd` and `ls books.txt borrows.txt` | `layer-01` → `layer-05` |
| `failure-03` | Blank records or shifted fields appear in the list | Use `nl -ba books.txt` and count fields per line | `layer-05` → `data_mgr.c::loadData` |
| `failure-04` | A non-numeric menu or quantity becomes 0 or another number | Trace the input path through `main.c::atoi` | `layer-03` → input validation |
| `failure-05` | Borrowing fails or inventory becomes surprising | Inspect `findBookIndex` and `available` | `layer-04` → `business.c::borrowBook` |

## Evidence Ledger

```text
evidence: code_evidence
source: main.c::main
rationale: main.c::main performs initialization, the menu loop, input reading, switch dispatch, and exit saving, proving the end-to-end control entry.
```

```text
evidence: code_evidence
source: business.c::borrowBook
rationale: borrowBook finds a book, checks availability, writes a borrow record, and saves, proving the borrow state transition.
```

```text
evidence: code_evidence
source: data_mgr.c::loadData
rationale: loadData reads pipe-delimited lines from books.txt and borrows.txt into fixed-capacity arrays.
```

```text
evidence: document_evidence
source: books.txt::lines 1-8
rationale: The sample file shows the book-row format and also contains short malformed rows, useful for observing parsing risk in the hardening stage.
```

## Uncovered Scope

- `.git` metadata, commit history, and remote-platform operations are not part of the learning path; two commits do not establish development chronology.
- Networking, databases, concurrency, accounts/permissions, GUIs, and third-party libraries are excluded because the reference project has none of those boundaries.
- Runtime data is copied into the learner's `student/` directory; the reference repository is never modified.
- The repository has no automated tests; acceptance uses isolated runs, manual scenarios, and file-content checks.

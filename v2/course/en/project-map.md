---
artifact_id: project-map
language: en
---

# Project Map

## Purpose

LibaryManage is a command-line book management system (`code_evidence`: `main.c::main`). It serves a single local user with add, list, search, update, delete, borrow, return, and borrow-record viewing, persisting data to two pipe-delimited text files, `books.txt` and `borrows.txt` (`code_evidence`: `data_mgr.c::loadData/saveData`).

## Core User Journey

1. On startup the system loads data from `books.txt` / `borrows.txt` (`data_mgr.c::initSystem → loadData`).
2. The user picks an action from a menu (`main.c::displayMenu`).
3. Typical journey: add books → list all → borrow (decrement `available`, create a record) → return (increment `available`, mark record returned) → exit saves everything (`business.c::borrowBook/returnBook`, `main.c::case 0`).

## Subsystems

| Subsystem ID | Responsibility | Input | Output | Depends on | Source |
|---|---|---|---|---|---|
| ui-menu | Menu display and input collection | stdin | function calls | business | `main.c` |
| domain-business | Book CRUD and borrow/return rules | function arguments | in-memory array mutations + saves | data-mgr | `business.c` |
| data-store | Structs, array storage, file load/save, date & lookup helpers | text files / arrays | memory state / text files | none | `data_mgr.c` |

## Data Flow

- File → `strtok` split on `|` → global arrays `Book books[]` / `BorrowRecord borrows[]`.
- Business functions mutate arrays → every successful operation immediately calls `saveData()` to rewrite both files wholesale.

## Evidence Ledger

```text
evidence: code_evidence
source: main.c::main
rationale: do-while menu loop + switch dispatch into business functions; fgets input with strcspn newline stripping.
```

```text
evidence: code_evidence
source: data_mgr.c::Book,BorrowRecord
rationale: static arrays capped at MAX_BOOKS/MAX_BORROWS=1000; Book carries dual counters quantity/available.
```

```text
evidence: code_evidence
source: data_mgr.c::saveData
rationale: pipe-delimited full-overwrite persistence with no transaction protection.
```

```text
evidence: teaching_inference
confidence: high
rationale: Saving after every mutation suggests the author cared about data loss on crash/forced exit but chose the simplest whole-file rewrite.
source: business.c::addBook,updateBook,deleteBook,borrowBook,returnBook
```

## Uncovered Scope

- Not compiled/run (static conclusions only); verification command: `gcc main.c -o library && ./library`.
- No README, tests, build scripts, or version history available.
- `books.txt`/`borrows.txt` are sample data files, not treated as code evidence.

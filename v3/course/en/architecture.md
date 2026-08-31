---
artifact_id: architecture
language: en
---

# Architecture

## System Context

This is a single-process, single-user C command-line program: stdin → menu → business functions → global in-memory arrays → two text files. There is no network, database, or concurrency boundary. `books.txt` and `borrows.txt` are resolved relative to the current working directory, not the source directory.

There are no headers. `main.c` directly includes both implementation files, so the code has conceptual UI, business, and data boundaries, but compilation combines them into one translation unit.

## Components

- **UI:** `main.c::displayMenu`, `displayHelp`, and `main`. It reads text, removes newlines with `strcspn`, parses with `atoi`, and prints messages from return values.
- **Business:** `business.c::addBook`, `listAllBooks`, `searchBook`, `updateBook`, `deleteBook`, `borrowBook`, `returnBook`, and `listAllBorrows`. It directly changes global arrays and saves after successful mutations.
- **Data and utilities:** `data_mgr.c::Book`, `BorrowRecord`, `loadData`, `saveData`, `getCurrentDate`, `findBookIndex`, and `findBorrowIndex`. These define the data model, file format, linear lookup, and date strings.

## Data Flow

```text
books.txt ──loadData──▶ books[MAX_BOOKS]
                           │
                           ├── business.c read/update ──saveData──▶ books.txt
                           │
borrows.txt ─loadData──▶ borrows[MAX_BORROWS]
                           │
                           └── business.c borrow/return ──saveData──▶ borrows.txt
```

A book row is `id|title|author|quantity|available`; a borrow row is `bookId|borrower|borrowDate|returnDate|returned`. `strtok` modifies the input buffer in place.

## Control Flow

`main()` calls `initSystem()` and then executes `do { displayMenu(); fgets(...); atoi(...); switch (...) } while (choice != 0)`. Each case collects parameters and calls a business function. Add, update, delete, borrow, and return call `saveData()` inside the business path; the exit branch calls `saveAllData()` again.

## Key Decisions

| Decision | Code mechanism | Pressure addressed | Teaching treatment |
|---|---|---|---|
| Fixed-capacity arrays | `Book books[MAX_BOOKS]`, `BorrowRecord borrows[MAX_BORROWS]`, and counters | Works without malloc or linked lists | Start with arrays; defer capacity pressure to the final stage |
| Two inventory fields | Borrow decrements `available`, return increments it; `quantity` is total stock | Separates total holdings from copies on shelf | Observe the invariant before protecting it |
| Shift on deletion | `deleteBook` shifts later structs left, then decrements `bookCount` | Keeps valid elements contiguous | Compare with lists without introducing one early |
| Full rewrite | `saveData()` opens with `w` and writes every record | Simple restart persistence | Leave atomic replacement outside scope |
| Pipe-delimited text | `fprintf` writes rows and `strtok` splits fields | No third-party dependency and human-readable data | Accept the format first; handle bad rows later |
| Direct `.c` inclusion | `main.c` includes implementation files | Fast composition for a small project | Discuss headers at the end, not as early ceremony |
| Linear lookup | `findBookIndex` and `findBorrowIndex` scan in order | Short implementation for small capacity | Do not build an index before scale pressure appears |

## Evidence Ledger

```text
evidence: code_evidence
source: main.c::main
rationale: The do-while/switch menu and exit saving show the complete control flow.
```

```text
evidence: code_evidence
source: main.c::data_mgr.c::business.c includes
rationale: The two source-file includes show conceptual boundaries, but not a header-based interface boundary.
```

```text
evidence: code_evidence
source: data_mgr.c::saveData
rationale: saveData writes both arrays in full using w mode, proving the full-rewrite mutation mechanism.
```

```text
evidence: teaching_inference
confidence: medium
source: main.c, business.c, data_mgr.c
rationale: Describing the three source files as UI/business/data helps track responsibility, but the repository has no formal architecture document or header declaring those layers.
```

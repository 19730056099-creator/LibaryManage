---
artifact_id: architecture
language: en
---

# Architecture

## System Context

A single-process C program: stdin ↔ menu UI ↔ global in-memory arrays ↔ two text files. No network, no database, no concurrency.

## Components

- `main.c::displayMenu/displayHelp/main` — presentation: menu rendering, `fgets` input collection, `atoi`/`strcspn` cleaning.
- `business.c::addBook/listAllBooks/searchBook/updateBook/deleteBook/borrowBook/returnBook/listAllBorrows/initSystem/saveAllData` — business layer.
- `data_mgr.c::Book/BorrowRecord/loadData/saveData/getCurrentDate/findBookIndex/findBorrowIndex` — data layer and helpers.

## Data Flow

```text
books.txt ──loadData──▶ Book books[1000] ◀──read/write── business.c ◀──calls── main.c
borrows.txt ─loadData─▶ BorrowRecord borrows[1000]
        ▲                                        │
        └────────saveData() (after each op) ◀────┘
```

## Control Flow

In `main()`: `do { displayMenu(); fgets; atoi; switch } while (choice != 0)`. Each case gathers arguments, calls a business function, and prints success/failure from the 0/1 return value.

## Key Decisions

| Decision | Mechanism | Pressure Addressed | Alternatives Visible in Evidence |
|---|---|---|---|
| Static arrays | `Book books[MAX_BOOKS]`, counter `bookCount` | Avoid malloc/linked-list complexity | Linked list or dynamic array (absent from code; teaching_inference: medium) |
| Dual counters quantity/available | borrow decrements `available`, return increments it | Distinguish total holdings from on-shelf copies | Single count field |
| Delete by shift-overwrite | `deleteBook` shifts elements left, `bookCount--` | Keep array compact | Soft delete (not used) |
| Save-all after every write | `saveData()` at end of each mutation | Crash data loss | Save on exit only / append log |
| Pipe-delimited text | `fprintf("%s|%s|...")` + `strtok(line,"|")` | No library dependency, human-readable | CSV/JSON/binary |

## Evidence Ledger

```text
evidence: code_evidence
source: data_mgr.c::deleteBook
rationale: deletion shifts elements left rather than tombstoning, keeping iteration order stable.
```

```text
evidence: code_evidence
source: business.c::updateBook
rationale: update supports "blank keeps old value"; quantity diff syncs available and clamps to >= 0.
```

```text
evidence: teaching_inference
confidence: medium
rationale: Global arrays plus #include of .c files directly into main.c (no headers) is a typical single-binary teaching-project layout.
source: main.c::#include "data_mgr.c"
```

## Not Inspected

- Compile warnings and runtime behavior unverified; `localtime` non-thread-safety is acceptable here (single-threaded).
- Robustness against corrupted files or missing fields not tested.

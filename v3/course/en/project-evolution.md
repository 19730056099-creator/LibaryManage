---
artifact_id: project-evolution
language: en
---

# Project Evolution

## Final Problem and Mature Capabilities

The final problem is: how can a local user maintain a catalog, know how many copies are currently available, track borrowers, and recover state after restart? The mature code supplies fixed-capacity `Book`/`BorrowRecord` arrays, menu dispatch, CRUD, substring search, borrow/return inventory changes, date generation, and two pipe-delimited text files.

## Minimum Viable Starting Point

V0 is a tiny in-memory program: store one `Book`, let the user add and list books, and lose data on exit. It first makes “input → state → output” visible without prematurely adding files, search, borrowing, or header refactoring.

## Evolution Overview

| Stage | Current version | Previous value | New pressure | Introduced change |
|---|---|---|---|---|
| `milestone-01` | Menu + fixed-array add/list | V0 proved the smallest state change | A hard-coded demo cannot be managed repeatedly | `Book`, counter, add/list, menu loop |
| `milestone-02` | In-memory CRUD | M01 can add and view | Duplicate or wrong records cannot be repaired or removed | Unique lookup, partial update, shift-on-delete |
| `milestone-03` | Book persistence | M02 can maintain memory | State disappears on exit | `fopen/fgets/fprintf/fclose`, pipe rows, `strtok` |
| `milestone-04` | Multi-field substring search | M03 survives restart | Manual scanning becomes expensive as the catalog grows | `strstr` over ID, title, and author |
| `milestone-05` | Borrow/return and records | M04 can find a book quickly | Total holdings differ from available copies, and the borrower matters | `available`, `BorrowRecord`, dates, `borrows.txt` |
| `milestone-06` | Input/file/business hardening | M05 normal paths work | `atoi`, short rows, and deleting an open loan create silent inconsistencies | `strtol` validation, bad-row policy, invariant checks, delete policy |

## Stage Causal Chain

### milestone-01

- **Current version:** A repeatable menu program puts entered books into a fixed array and lists them.
- **What the previous version solved:** V0 showed one simple result; this stage makes the result user-driven and repeatable.
- **New user problem:** A book cannot be corrected or removed, and duplicate IDs undermine later lookup.
- **What this stage introduces:** `Book`, a counter, a `do-while`/`switch` menu, add/list, and basic ID lookup.
- **What this stage solves:** Minimum catalog-entry and viewing value.
- **Deferred limit:** Full CRUD, files, search, borrowing, and strict input validation.
- **Why the next stage appears:** Users need to repair and remove wrong records, motivating M02.

### milestone-02

- **Current version:** In-memory unique IDs, partial updates, and shift-on-delete.
- **What the previous version solved:** M01 let users add and view catalog entries.
- **New user problem:** Duplicate or stale entries reduce trust, and middle deletion can leave an iteration hole.
- **What this stage introduces:** `findBookIndex`, partial updates, struct assignment while shifting, and counter maintenance.
- **What this stage solves:** Basic maintenance during one run while keeping valid elements contiguous.
- **Deferred limit:** Restart recovery, search, borrow relationships, and bad-file recovery.
- **Why the next stage appears:** Closing the program loses memory, so M03 introduces persistence.

### milestone-03

- **Current version:** The book array is written to `books.txt` and loaded again at startup.
- **What the previous version solved:** M02 made the in-memory catalog maintainable.
- **New user problem:** State is gone after exit or when the program is opened the next day.
- **What this stage introduces:** `fopen`/`fgets`/`fprintf`/`fclose`, pipe-delimited rows, `strtok`, and full saves after successful mutations.
- **What this stage solves:** Book data survives a process restart.
- **Deferred limit:** Borrow-file persistence, bad-row recovery, indexing, and advanced search.
- **Why the next stage appears:** As the catalog grows, users should not scan every row by eye, motivating M04 search.

### milestone-04

- **Current version:** Persistent books can be found by an ID, title, or author substring.
- **What the previous version solved:** M03 solved restart persistence.
- **New user problem:** Reading the entire list to find a target becomes expensive as the catalog grows.
- **What this stage introduces:** `strstr`, a found flag, and a search path that reuses list-style output.
- **What this stage solves:** Finding a book when the user remembers any one of its fields.
- **Deferred limit:** Indexes, sorting, case normalization, and borrow state.
- **Why the next stage appears:** Finding a book does not prove that a copy is available, motivating M05 inventory and records.

### milestone-05

- **Current version:** Two arrays/files record borrow and return; borrow decrements `available`, while return restores it and marks the record.
- **What the previous version solved:** M04 made books easy to find.
- **New user problem:** The system must distinguish total holdings, shelf stock, and the current borrower without allowing negative stock.
- **What this stage introduces:** `BorrowRecord`, `findBorrowIndex`, `time/localtime`, `borrows.txt`, and the inventory invariant.
- **What this stage solves:** Normal borrow/return behavior with traceable, persistent inventory state.
- **Deferred limit:** Non-numeric input, short rows, overlong strings, and the delete-with-open-loan policy.
- **Why the next stage appears:** Sample files contain short rows, while `atoi` and the parser silently accept bad data, motivating M06.

### milestone-06

- **Current version:** M05 behavior gains explicit input, file, and cross-record boundaries.
- **What the previous version solved:** M05 solved normal borrowing and two-file persistence.
- **New user problem:** Non-numeric input, truncated files, and deleting a borrowed book can corrupt or contradict state.
- **What this stage introduces:** `strtol`/complete input checks, field-count/length/value checks, capacity errors, and the explicit policy “reject deletion while an open record exists.”
- **What this stage solves:** Bad data no longer silently becomes valid state, and inventory/record relationships remain explainable.
- **Deferred limit:** Database transactions, concurrency, atomic file replacement, and network deployment.
- **Why the next stage appears:** This route ends at the reference project's boundary; further work should re-evaluate pressure instead of adding abstraction unconditionally.

## How the Final Architecture Emerges

1. M01 forms UI input and in-memory state.
2. M02 gives lookup, update, and deletion stable semantics.
3. M03 adds a file boundary only after restart loss becomes visible.
4. M04 reuses linear traversal instead of building an index for a small capacity.
5. M05 adds borrow records beside the catalog and connects them with `available`.
6. M06 makes UI input boundaries, file parsing boundaries, and delete policy explicit.

UI/business/data are teaching boundaries for tracking responsibility; the reference still composes `.c` files by direct inclusion and has no formal header API.

## Teaching-Route Disclaimer

This is a teaching reconstruction based on the final code and isolated runtime observation, not a claim about the author's actual development chronology. The repository has only commits `b36e644` and `eccdf9f`, with no design document or tests proving intermediate steps. The order follows “previous value → new pressure → smallest change”; that interpretation is `teaching_inference`.

## Evidence Ledger

```text
evidence: code_evidence
source: data_mgr.c::Book, data_mgr.c::BorrowRecord
rationale: The two structs and fixed-capacity arrays directly provide the mature data model, inventory fields, and borrow-record boundary.
```

```text
evidence: code_evidence
source: business.c::addBook, updateBook, deleteBook, searchBook, borrowBook, returnBook
rationale: The business functions demonstrate mature CRUD, search, borrow/return, and inventory behavior.
```

```text
evidence: code_evidence
source: data_mgr.c::loadData, data_mgr.c::saveData
rationale: The I/O functions show the pipe-delimited format, strtok parsing, and full writes to two files.
```

```text
evidence: teaching_inference
confidence: high
source: main.c, business.c, data_mgr.c
rationale: The six-stage causal order is reconstructed to reveal engineering pressure gradually; it is not commit history.
```

---
artifact_id: milestone-01
language: en
---

# Milestone

milestone_id: milestone-01

## Goal

Build a menu-driven C program: option 1 adds a book (ID, title, author, quantity), option 2 lists all books. Data lives in a static struct array and disappears when the program exits.

## Observable Result

- `gcc main.c -o library && ./library` runs (or your own file names).
- After adding 2 books, option 2 prints two formatted rows; data is gone after restart (expected at this stage).
- Duplicate IDs are rejected (simple linear lookup is fine here).

## Design Pressure

A demo program with hardcoded books has no value — user input must become program data, and a menu loop must let actions repeat.

## Scope

- A `Book` struct: `char id[20]; char title[100]; char author[100]; int quantity; int available;`
- Global array + `bookCount` counter, capacity 1000.
- Three functions: `addBook` / `listAllBooks` / `findBookIndex`.
- `do-while` menu loop + `switch` dispatch.

## Constraints

- No file I/O, no search, no borrow/return in this stage.
- No malloc/linked lists; static arrays only.
- `available` always equals `quantity` for now.

## Prerequisites

- competency_id: tooling.c.gcc-build (blocking)
- competency_id: language.c.structs-strings (blocking)
- competency_id: language.c.arrays-pointers (blocking)

## Tasks

1. Define the struct and global array.
2. Implement `findBookIndex` (strcmp over elements).
3. Implement `addBook`: return 0 when full or duplicate ID; otherwise fill the struct, set `available = quantity`, increment count, return 1.
4. Implement `listAllBooks`: header row + printf loop; hint when empty.
5. Build the menu loop: `fgets` the choice, `atoi` to int, `strcspn` to strip newline.

## Acceptance

- m01-a01: compiles clean; program responds to repeated menu choices.
- m01-a02: after adding two books, listing shows every field.
- m01-a03: re-adding the same ID fails with a message; list still has two books.
- m01-a04: choosing 2 on an empty library prints a "no data" hint instead of crashing.

## Hint 1

Skip the menu at first: write a `main` that calls `addBook` twice then `listAllBooks`. Wire up the menu only after the array logic is right.

## Hint 2

`fgets` keeps the newline in the string; remove it with `s[strcspn(s, "\n")] = '\0'` — otherwise IDs never match.

## Hint 3

Make `addBook` return int 0/1 and let the menu layer decide what to print — business functions should not printf their own results.

## Hint 4

Preview for milestone-02 (deletion): shift every later element left, `books[i] = books[i+1]`, then `bookCount--`.

## Hint 5

Reference bridge: `business.c::addBook/listAllBooks`, `data_mgr.c::findBookIndex`, `main.c::main` cases 1/2. Compare only after writing your own.

## Next Pressure

Everything vanishes on exit. Tomorrow the books are gone — you need persistence (milestone-03), but first finish update/delete/search (milestone-02).

## Source Bridge

`business.c::addBook`, `business.c::listAllBooks`, `data_mgr.c::Book`, `data_mgr.c::findBookIndex`, `main.c::displayMenu`, `main.c::case 1/case 2`

## Evidence Ledger

```text
evidence: code_evidence
source: business.c::addBook
rationale: The mature implementation likewise uses 0/1 returns plus capacity and duplicate checks.
```

```text
evidence: code_evidence
source: main.c::main
rationale: The fgets + strcspn + atoi input-cleaning pattern is the core skill of this milestone.
```

## Completion Decision

(To be filled by review after learner submission.)

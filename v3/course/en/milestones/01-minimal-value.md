---
artifact_id: milestone-01
language: en
---

# Milestone

milestone_id: milestone-01
competency_id: tooling.c.gcc-build
competency_id: language.c.c-control-input
competency_id: language.c.structs-strings
competency_id: language.c.arrays-pointers
foundation_id: foundation-01
foundation_id: foundation-02
acceptance_id: m01-a01
acceptance_id: m01-a02
acceptance_id: m01-a03
acceptance_id: m01-a04
practice_id: m01-p01
manual_action_id: m01-manual-01
ai_boundary_id: m01-ai-01
transfer_check_id: m01-transfer-01
reappears_in: milestone-02, milestone-04, milestone-05
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o library_m01

## Current Version

A repeatable menu program lets the user enter a book ID, title, author, and quantity, stores it in a fixed-capacity in-memory array, and lists current books. Data disappears on exit.

## What the Previous Version Solved

V0 only proved that “one value can be displayed”; it had no user input or repeatable operation. This stage turns the demo into a usable catalog interaction.

## New User Problem

The user can add but cannot correct or remove a wrong entry, and duplicate IDs make later lookup unreliable. Those pressures belong to M02.

## What This Stage Introduces

Introduce the `Book` struct, a valid-count counter, a `do-while`/`switch` menu, add, and list. Use a linear array without files or speculative abstractions.

## Goal

Complete V1: add and view multiple books during one run.

## Observable Result

After entering two different IDs and choosing list, two records with their quantities appear; persistence after restart is not promised yet.

## What This Stage Solves

Establish the first complete user chain: stdin → struct → array state → stdout.

## Scope

- `Book { id, title, author, quantity }` and a fixed-capacity array.
- Add, list, and exit; expose a capacity-full failure.
- Use your own student directory and `main.c`.

## Not Solving Yet

Do not implement update, delete, search, file persistence, borrowing, strict numeric validation, or header refactoring yet. The explicit duplicate-ID policy arrives in M02.

## Prerequisites

Pass `foundation-01` and `foundation-02`: gcc build, input/struct/string basics, array traversal, and shift-on-delete. These are gated in `progress.json`.

## First Touch

Hard-code one `Book` and print it to confirm that fields form one value. Then remove the hard-coded data and read one user input. Finally add a `do-while` menu so “user input changes the list” is the first observable result.

## Tasks

1. Create your program and an empty data directory under `student/milestone-01/`.
2. Write `Book`, a counter, add/list functions, and newline-trimmed string input.
3. Add a menu loop and exit branch; add at least two books in one run.
4. Expose a capacity-full message without implementing all later validation.

## AI Usage Boundary

AI may explain compiler errors, help design test input, or draw the call chain. You must personally write the struct, counter, add/list core, run the build command, and execute the scenario; explain once how choice 1 reaches the list. Do not submit copied reference functions.

## Understanding and Transfer Check

Change the display order to “author, title, ID, quantity” without changing internal data. Add a third book and explain when `count` increases and why listing stops at `[0, count)`.

## Acceptance

```text
acceptance_id: m01-a01
```
The build command produces no errors or warnings and the program runs from the correct directory.

```text
acceptance_id: m01-a02
```
Add two different IDs; the list shows two complete records.

```text
acceptance_id: m01-a03
```
The menu can repeat without losing current-process data, and input 0 exits; restart persistence is outside this stage.

```text
acceptance_id: m01-a04
```
Submit one hand-written core-code record, run output, AI-use note, and transfer answer; trace input through the array to output aloud.

## Hint 1

Predict first: if `count` starts at 0, which indexes should the list loop visit after one addition?

## Hint 2

Split input into three actions: read a line, remove its newline, and copy it into the matching `Book` char array.

## Hint 3

Let `addBook` receive four values; on success write `books[count]`, increment `count`, and list only the valid prefix.

## Hint 4

Pseudocode: `while menu != 0: if menu == 1 read fields; books[count] = new; count++; if menu == 2 for i in [0,count) print`.

## Hint 5

If you explicitly request a complete reference, start with the smallest `Book`, `bookCount`, `addBook`, `listBooks`, and `do-while` version; still change one field order, run it, and explain the control flow yourself.

## Why the Next Stage Appears

M01 can enter but not maintain records. Duplicate IDs and wrong entries force direct source edits, so M02 introduces lookup, update, and shift-on-delete.

## Source Bridge

Compare the fields in `data_mgr.c::Book`, the menu loop in `main.c::main`, and the write order in `business.c::addBook`. Extract behavior here; do not copy the whole project.

## Evidence Ledger

```text
evidence: code_evidence
source: main.c::main
rationale: main.c::main shows menu input, do-while/switch dispatch, and the observable user-result path.
```

```text
evidence: code_evidence
source: data_mgr.c::Book
rationale: Book supplies the ID, title, author, and quantity fields required at this stage.
```

```text
evidence: code_evidence
source: business.c::addBook
rationale: addBook shows the mature fixed-array write, capacity check, count increment, and save path; this stage implements only the in-memory portion.
```

## Completion Decision

After all four acceptance items and direct practice evidence pass, a review may mark M01 `passed`. A successful run with entirely AI-generated core code and no explanation or transfer evidence is not sufficient.

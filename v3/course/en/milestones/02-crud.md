---
artifact_id: milestone-02
language: en
---

# Milestone

milestone_id: milestone-02
competency_id: language.c.arrays-pointers
competency_id: language.c.structs-strings
competency_id: project.array-crud
foundation_id: foundation-02
acceptance_id: m02-a01
acceptance_id: m02-a02
acceptance_id: m02-a03
acceptance_id: m02-a04
practice_id: m02-p01
manual_action_id: m02-manual-01
ai_boundary_id: m02-ai-01
transfer_check_id: m02-transfer-01
reappears_in: milestone-04, milestone-05, milestone-06
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o library_m02

## Current Version

Build on M01's in-memory add/list with unique-ID lookup, partial update, and index-based deletion that keeps the array contiguous after removing a middle element.

## What the Previous Version Solved

M01 turns user input into catalog records, but a wrong record can only disappear when the process is restarted; it cannot be maintained deliberately.

## New User Problem

Duplicate IDs make “find by ID” ambiguous; changed titles, authors, or quantities make old data stale; deleting a middle element without shifting leaves a hole in traversal.

## What This Stage Introduces

Introduce `findBookIndex`, duplicate-ID rejection, empty strings meaning “leave unchanged,” struct-assignment shifting, and `bookCount--`. Explain the minimal quantity relationship only; full inventory belongs to M05.

## Goal

Let the user maintain a trustworthy in-memory catalog during one run, with observable add failure, update, and delete results.

## Observable Result

A duplicate ID fails; updating a book changes the list; deleting a middle book leaves the remaining books contiguous without a repeated tail entry.

## What This Stage Solves

The basic in-memory lifecycle and array compactness, not restart persistence.

## Scope

- Linear ID lookup and duplicate-ID rejection.
- Update non-empty fields; shift later elements left on deletion.
- Return failure for an unknown ID without changing `count`.

## Not Solving Yet

Do not add file I/O, search, borrowing, complex error types, dynamic allocation, or complete numeric validation.

## Prerequisites

Use F01's struct/string skills and F02's shift-on-delete skills; `project.array-crud` is formed through behavior in this stage.

## First Touch

Run a three-label `A B C` middle-delete experiment and observe that the result should be `A C`, then place the same movement in catalog deletion. Make the array pressure visible before discussing abstractions.

## Tasks

1. Add `findBookIndex` to the previous stage and compare IDs with `strcmp`.
2. Reject an existing ID on add; allow empty title/author to mean “keep old value” on update.
3. Implement left-shift deletion and test first, middle, and last positions.
4. Record an unknown-ID failure and explain why `count` does not change.

## AI Usage Boundary

AI may draw before/after arrays, explain `strcmp`, or point out boundary cases. You must personally write the lookup loop, shift loop, and count update and run four scenarios; do not outsource the duplicate/unknown-ID return semantics.

## Understanding and Transfer Check

Change the target to the last element and explain why the shift runs zero times. Then add an integer `year` to `Book` and explain why whole-struct assignment still copies it during shifting.

## Acceptance

```text
acceptance_id: m02-a01
```
Different IDs can be added; a duplicate is rejected and the original record remains unchanged.

```text
acceptance_id: m02-a02
```
An existing book's title, author, or quantity can be updated by the stated rule; an unknown ID has an explicit failure result.

```text
acceptance_id: m02-a03
```
Deleting the first, middle, or last element leaves the valid elements contiguous and ordered, with the correct `count`.

```text
acceptance_id: m02-a04
```
Submit output for the four scenarios, explain the core loops, and show one transfer change; the learner must author the core code.

## Hint 1

Write down which slots remain valid after deleting `B` from `A B C` before writing the menu.

## Hint 2

`findBookIndex` returns an index when found and `-1` after the scan; callers must handle `-1`.

## Hint 3

For deletion, assign `items[i + 1]` to `items[i]` from `index` through `count - 2`, then decrement `count`.

## Hint 4

For update, copy the old record and overwrite only non-empty parameters; both update and delete check the lookup result first.

## Hint 5

A complete reference may unblock you: keep the smallest lookup, shift, and `count--` implementation, then change the deletion position and explain the boundary yourself.

## Why the Next Stage Appears

M02 is reliable only during one run; all changes disappear on exit. That concrete pressure triggers file persistence in M03.

## Source Bridge

Compare `data_mgr.c::findBookIndex`, `business.c::updateBook`, and `business.c::deleteBook`, especially `-1`, struct assignment, and `bookCount`.

## Evidence Ledger

```text
evidence: code_evidence
source: data_mgr.c::findBookIndex
rationale: The reference linearly compares IDs with strcmp and returns -1 when none is found.
```

```text
evidence: code_evidence
source: business.c::updateBook
rationale: updateBook shows the path for changing non-empty fields and quantity by ID.
```

```text
evidence: code_evidence
source: business.c::deleteBook
rationale: deleteBook demonstrates shifting whole records left and decrementing bookCount after a middle deletion.
```

## Completion Decision

After the four acceptance items and direct array-practice evidence pass, a review may mark M02 `passed`. This stage is not required to implement later file or borrowing mechanisms.

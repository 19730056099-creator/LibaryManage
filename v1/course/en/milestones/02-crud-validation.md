---
artifact_id: milestone-02
language: en
---

# Milestone

milestone_id: milestone-02

## Goal

Complete in-memory CRUD on top of milestone-01: update, delete, and stricter ID handling.

## Observable Result

- Menu gains: 4 update, 5 delete (search can wait for milestone-04).
- Deleting a middle book keeps the remaining order and correct count.
- Update semantics: blank string keeps the old value; quantity -1 means unchanged.

## Design Pressure

Duplicate IDs and undeletable stale entries destroy trust in the list; the data structure must support deletion at any position without breaking iteration.

## Scope

- `updateBook(id, title, author, quantity)`: partial-update semantics.
- `deleteBook(id)`: shift-overwrite deletion.
- Quantity changes sync `available` (carry the diff, clamp at >= 0).

## Constraints

- No new data structures.
- No tombstones — shift elements left directly.

## Prerequisites

- competency_id: project.array-crud (blocking)
- competency_id: language.c.arrays-pointers (blocking)

## Tasks

1. Implement `updateBook`: after finding the index, update only non-empty string fields; when quantity >= 0 compute the diff and sync available.
2. Implement `deleteBook`: shift left + decrement count.
3. Wire both into the menu with success/failure messages.

## Acceptance

- m02-a01: add 3 books, delete #2, list shows original #1 and #3 in order.
- m02-a02: leaving title blank preserves it; entering -1 for quantity preserves it.
- m02-a03: changing quantity from 5 to 2 reduces available by exactly 3 and never below zero.
- m02-a04: updating/deleting an unknown ID fails gracefully.

## Hint 1

Partial update is just `if (strlen(new) > 0) strcpy(old, new);` repeated.

## Hint 2

Syncing available: `int diff = newQty - oldQty; available += diff; if (available < 0) available = 0;`.

## Hint 3

The delete loop bound is `for (i = idx; i < count - 1; i++) books[i] = books[i+1];` — note `count - 1`.

## Hint 4

Consider a trap: someone borrowed copies (available < quantity), then quantity is lowered. The mature code clamps to 0 and lets the relationship drift temporarily — what risk does that create?

## Hint 5

Reference: `business.c::updateBook/deleteBook`. Compare only after writing your own.

## Next Pressure

Data still dies on exit. Next, state must survive restarts.

## Source Bridge

`business.c::updateBook`, `business.c::deleteBook`, `data_mgr.c::findBookIndex`

## Evidence Ledger

```text
evidence: code_evidence
source: business.c::updateBook
rationale: The "empty string / -1 means keep old value" partial-update contract comes from the mature code.
```

## Completion Decision

(To be filled by review.)

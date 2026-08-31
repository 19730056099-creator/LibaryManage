---
artifact_id: milestone-06
language: en
---

# Milestone

milestone_id: milestone-06

## Goal

Harden the whole system: garbage input, corrupted/missing files, capacity limits, and update semantics under borrow pressure.

## Observable Result

- Non-numeric quantity input does not silently become 0 books.
- A truncated or field-corrupted line in `books.txt` is skipped (or reported) instead of misaligning every later record.
- Deleting a book with open borrow records either refuses or cleans up records — your choice, documented.

## Design Pressure

Real users type garbage; disks lose files. Silent corruption is worse than a crash because it spreads.

## Scope

- Input validation helper for numeric prompts.
- Defensive parsing in `loadData` (token-count check).
- Policy decision + implementation for delete-with-open-borrows.
- Optional: case-insensitive search; duplicate-borrow guard.

## Constraints

- Keep the text format backward-compatible with files written by milestone-05.
- No external libraries.

## Prerequisites

- competency_id: project.array-crud (ready from earlier milestones)
- competency_id: language.c.file-io (ready)

## Tasks

1. Replace bare `atoi` for quantities with a validated parse (reject non-digits).
2. In `loadData`, count tokens per line; skip lines that do not yield 5 (books) / 5 (borrows) fields.
3. Decide and implement the delete policy; document it in your README/help.
4. Pick at least one optional hardening item and implement it.

## Acceptance

- m06-a01: entering "abc" as quantity prints an error and adds nothing.
- m06-a02: hand-corrupting one line of `books.txt` leaves all other books intact after load.
- m06-a03: deleting a book with an open record behaves per your documented policy and never leaves `available` inconsistent.
- m06-a04: help text describes the chosen policies.

## Hint 1

A strict number parse: reject empty strings and any non-digit character before `atoi`.

## Hint 2

Token counting with strtok: call it five times; if any call returns NULL early, the line is malformed.

## Hint 3

For the delete policy, refusing while records are open is simpler and safer than cascading cleanup — but justify your choice.

## Hint 4

Case-insensitive matching: lowercase both strings into buffers with `tolower` before `strstr`.

## Hint 5

The mature project does NOT fully solve this milestone — compare your solution against `main.c::case 1`, `data_mgr.c::loadData`, and note where you exceeded it. That gap analysis is the point.

## Next Pressure

Course complete: connect your journey back to the mature repository in a final review.

## Source Bridge

`main.c::case 1/case 6`, `business.c::updateBook/deleteBook/borrowBook`, `data_mgr.c::loadData`

## Evidence Ledger

```text
evidence: teaching_inference
confidence: high
rationale: The mature code validates some inputs (strcspn) but trusts atoi and file structure; this milestone deliberately exceeds it.
source: main.c::case 1, data_mgr.c::loadData
```

## Completion Decision

(To be filled by final review.)

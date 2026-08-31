---
artifact_id: milestone-06
language: en
---

# Milestone

milestone_id: milestone-06
competency_id: language.c.c-control-input
competency_id: language.c.file-io
competency_id: language.c.structs-strings
competency_id: project.input-validation
competency_id: project.defensive-parsing
competency_id: project.borrow-delete-policy
acceptance_id: m06-a01
acceptance_id: m06-a02
acceptance_id: m06-a03
acceptance_id: m06-a04
practice_id: m06-p01
manual_action_id: m06-manual-01
ai_boundary_id: m06-ai-01
transfer_check_id: m06-transfer-01
reappears_in: milestone-06
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o library_m06

## Current Version

Add explicit input validation, malformed-row handling, capacity errors, and a delete policy to M05's normal borrow/return system, producing a hardened version for known boundaries.

## What the Previous Version Solved

M05 manages borrowing on normal input and well-formed files, but treats failure as an implicit side effect of the success path.

## New User Problem

A user may enter `12x`, a negative, or an overlarge quantity; a file may contain too few fields; deleting a book with an open loan removes the referenced catalog object. The program should reject or report these cases rather than silently creating state.

## What This Stage Introduces

Replace bare `atoi` with `strtol` or an equivalent complete parse; validate field count, length, and numeric range while loading; expose capacity failure; choose and implement “reject deletion while an open record exists”; check the inventory invariant after key operations.

## Goal

Make predictable bad input and data observable and testable without breaking M05's normal behavior.

## Observable Result

Illegal quantities are rejected with unchanged state; short rows are skipped and reported; a full capacity produces failure; a book with an open loan cannot be deleted; normal borrow/return still passes.

## What This Stage Solves

Failure visibility and cross-record consistency, preventing input and files from silently polluting arrays.

## Scope

- Complete numeric parsing and range checks for menu/quantity input.
- Field-count, string-length, and integer checks for file rows.
- Explicit capacity errors, bad-row reporting, and open-loan delete policy.
- Check `0 <= available <= quantity`.

## Not Solving Yet

Do not add database transactions, concurrency locks, atomic file replacement, internationalization, complex escaping, or a full header/multi-translation-unit refactor; these are not current reference pressures.

## Prerequisites

Use M05's borrow state, M03/F03's file model, and F01's input control flow. Introduce all new concepts just in time here.

## First Touch

Observe the raw `atoi` result for `12x`, `-1`, and `5`, then define an accept/reject table. Next inspect a short row from `books.txt` and count its fields; make the failure visible before changing code.

## Tasks

1. Write a complete numeric parser that rejects empty strings, non-digits, trailing characters, and out-of-range values.
2. Validate field count, field length, and numeric values per row; skip bad rows with a line number.
3. Define observable outcomes for full capacity and file open/write failure.
4. Check open loans before deletion and run normal borrow/return regression tests.

## AI Usage Boundary

AI may explain the `strtol` end pointer, help enumerate boundary tests, or review error messages. You must personally write at least one validation function, choose the bad-row and delete policies, run bad-input/bad-file/regression scenarios, and explain why rejection leaves state unchanged.

## Understanding and Transfer Check

Change “skip a bad row” to “stop loading on the first bad row” and compare user impact and consistency. Then add a quantity upper bound and list the rule that input validation and file validation must share.

## Acceptance

```text
acceptance_id: m06-a01
```
Non-numeric, trailing-character, negative, and out-of-range quantities are rejected without changing existing state.

```text
acceptance_id: m06-a02
```
Rows with missing/overlong/invalid fields do not create half-initialized records and report or count the bad rows.

```text
acceptance_id: m06-a03
```
Full capacity, file open/write failure, and deletion of a book with an open loan have explicit results; code and documentation agree on the delete policy.

```text
acceptance_id: m06-a04
```
Normal add/list/update/delete, search, borrow/return, and restart regression pass; submit boundary tests, explanations, AI-use record, and transfer decision.

## Hint 1

Classify input strings first: complete number, empty, numeric prefix, trailing characters, negative, and overflow.

## Hint 2

After `strtol`, check that `endptr` reached the string end, then check `errno` and bounds; do not inspect only the returned number.

## Hint 3

Before copying or converting a row, confirm every token exists and fits its destination; on failure do not increment the count.

## Hint 4

Scan borrows before deletion; if the same book ID has `returned == 0`, reject it. This is the route's smallest consistency policy.

## Hint 5

A complete reference may provide a parser and delete-policy sample; still change the bad-row policy, run regression, and explain why rejection is safer than silent repair.

## Why the Next Stage Appears

This route now covers the main reference boundaries. Further work should be driven by a new scale or reliability pressure, such as tests, module interfaces, or atomic persistence, rather than automatic abstraction.

## Source Bridge

Compare `main.c::atoi`, the unconditional field copying in `data_mgr.c::loadData`, the lack of borrow-link checks in `business.c::deleteBook`, and the capacity constants in `data_mgr.c`.

## Evidence Ledger

```text
evidence: code_evidence
source: main.c::main
rationale: main.c uses atoi for menu and quantity parsing, without complete error classification for non-numeric input.
```

```text
evidence: code_evidence
source: data_mgr.c::loadData
rationale: loadData copies and increments records without validating field presence, length, or numeric range, so short rows can pollute state.
```

```text
evidence: code_evidence
source: business.c::deleteBook
rationale: deleteBook checks only the book ID and does not inspect open records in borrows, leaving a clear policy pressure.
```

## Completion Decision

After the four acceptance items, bad-input/bad-file and normal-regression evidence, and the policy transfer explanation pass, a review may mark M06 `passed`. This closes the route; the course becomes `complete` only after every milestone passes and a final bridge review exists.

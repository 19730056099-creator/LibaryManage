---
artifact_id: milestone-05
language: en
---

# Milestone

milestone_id: milestone-05
competency_id: language.c.file-io
competency_id: language.c.structs-strings
competency_id: language.c.time-format
competency_id: project.delimited-persistence
competency_id: domain.borrow-inventory
foundation_id: foundation-03
acceptance_id: m05-a01
acceptance_id: m05-a02
acceptance_id: m05-a03
acceptance_id: m05-a04
practice_id: m05-p01
manual_action_id: m05-manual-01
ai_boundary_id: m05-ai-01
transfer_check_id: m05-transfer-01
reappears_in: milestone-06
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o library_m05

## Current Version

M04 can find a book; M05 maintains total `quantity`, shelf stock `available`, and `BorrowRecord`, and persists borrow records in `borrows.txt`.

## What the Previous Version Solved

M04 reduces the cost of finding a book, but “the book exists” does not mean a copy is available, and there is no borrower to track.

## New User Problem

Borrowing must decrease available stock without going negative; returning must match one open record; after restart the system must still know who borrowed what.

## What This Stage Introduces

Introduce `BorrowRecord`, `findBorrowIndex`, dates from `time/localtime`, and a second delimited file. The core invariant is `0 <= available <= quantity`.

## Goal

Complete a normal borrow/return loop while keeping catalog inventory and borrow records explainable and recoverable.

## Observable Result

Borrowing an available book decrements `available` and creates an open record; returning sets a date and status and increments stock; borrowing at zero fails.

## What This Stage Solves

Extend catalog management into traceable inventory and borrow relationships, persisted across restarts.

## Scope

- Find a book, check `available`, and check record capacity before borrowing.
- Create a record with a borrow date; on return set return date and `returned`.
- Save/load `books.txt` and `borrows.txt` and display record status.

## Not Solving Yet

Do not handle bad numbers, malformed rows, date validation, concurrent borrowing, overdue calculation, or deletion of a book with an open loan; M06 makes those boundaries explicit.

## Prerequisites

Complete F03 and reuse M02's arrays and M03's text persistence. Teach `language.c.time-format` just in time here rather than requiring it earlier.

## First Touch

Draw one book with quantity=2 and available=2; after one borrow draw available=1 and one open record, then update both after return. Only then write functions, making the invariant visible first.

## Tasks

1. Add `BorrowRecord` plus its array and counter.
2. Implement borrow: validate book and stock, decrement available, create a date, and append a record.
3. Implement return: find an open record, increment available, write the return date, and mark it returned.
4. Save/reload both files; test zero stock, duplicate return, and restart.

## AI Usage Boundary

AI may draw a state table, explain `time/localtime`, or design borrow/return tests. You must personally maintain the two-array relationship, write at least one stock check, run borrow/return/restart scenarios, and explain when each field changes. Do not outsource the consistency policy.

## Understanding and Transfer Check

Change total quantity from 2 to 3, borrow twice, and write `quantity`, `available`, and record state after each step. Explain why a record with `returned == 1` cannot be returned again.

## Acceptance

```text
acceptance_id: m05-a01
```
Borrowing with stock above zero succeeds, decrements stock, and creates an open record with a valid date.

```text
acceptance_id: m05-a02
```
Borrowing a missing book or zero-stock book fails without creating a partial record.

```text
acceptance_id: m05-a03
```
The matching open record can be returned once: stock increments, a return date appears, and status becomes returned; a second return fails.

```text
acceptance_id: m05-a04
```
After exit and restart, both record types can be listed and `0 <= available <= quantity` is checked; submit the state table and AI-use record.

## Hint 1

Track one book only: write both inventory values and the record status before, after borrow, and after return.

## Hint 2

Borrowing needs a `Book` and available stock; returning needs a matching bookId, borrower, and `returned == 0` record.

## Hint 3

Borrow order should be check → decrement → fill record → increment count → save; a failure must not change only half the state.

## Hint 4

Wrap date formatting in `getCurrentDate`; store dates as strings first instead of expanding the persistence model.

## Hint 5

A complete reference may show `BorrowRecord` fields and state transitions; still change the quantity scenario, test duplicate return, and prove the invariant.

## Why the Next Stage Appears

Normal cases work, but `atoi` swallows non-numbers, sample files contain short rows, and deleting a borrowed book creates a relationship problem. M06 makes failures explicit.

## Source Bridge

Compare `data_mgr.c::BorrowRecord`, `data_mgr.c::findBorrowIndex`, `data_mgr.c::getCurrentDate`, and `business.c::borrowBook`/`returnBook`.

## Evidence Ledger

```text
evidence: code_evidence
source: data_mgr.c::BorrowRecord
rationale: BorrowRecord defines book ID, borrower, borrow/return dates, and returned status.
```

```text
evidence: code_evidence
source: business.c::borrowBook, business.c::returnBook
rationale: The two functions decrement/increment available and create or complete a borrow record.
```

```text
evidence: code_evidence
source: data_mgr.c::getCurrentDate
rationale: getCurrentDate uses time/localtime and a fixed format to produce a date string.
```

## Completion Decision

After the four acceptance items, direct state practice, and restart evidence pass, a review may mark M05 `passed`. Hardening remains for M06.

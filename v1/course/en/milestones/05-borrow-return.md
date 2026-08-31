---
artifact_id: milestone-05
language: en
---

# Milestone

milestone_id: milestone-05

## Goal

Implement borrow/return with a second data structure: `BorrowRecord`, the quantity/available invariant, current dates, and persistence of both files.

## Observable Result

- Option 6 borrows: `available` drops by 1, a record with today's date is appended to `borrows.txt`.
- Option 7 returns by (bookId, borrower): `available` rises by 1, the record is stamped returned.
- Option 8 lists records with status Borrowing/Returned.
- Both files round-trip across restarts.

## Design Pressure

Owning copies is not having them on the shelf. The system must answer "who currently holds what" and never lend below zero.

## Scope

- `BorrowRecord {bookId, borrower, borrowDate, returnDate, returned}` + parallel array.
- `borrowBook`, `returnBook`, `listAllBorrows`, `findBorrowIndex`, `getCurrentDate`.
- Extend save/load to `borrows.txt`.

## Constraints

- One borrower may hold multiple copies of the same title (mature behavior; note it).
- Return matches only unreturned records.

## Prerequisites

- competency_id: domain.borrow-inventory (blocking)
- competency_id: project.delimited-persistence (blocking)

## Tasks

1. Add the struct, counter, and `getCurrentDate` (`localtime`, `%04d-%02d-%02d`).
2. `borrowBook`: check book exists AND available > 0 AND capacity; decrement; append record; save.
3. `returnBook`: find the open record; increment available; stamp returnDate and returned = 1; save.
4. Persist borrows alongside books in load/save.

## Acceptance

- m05-a01: quantity 2 → borrow twice succeeds, third borrow fails with stock message.
- m05-a02: after one return, available is 1 again and the record shows Returned with a date.
- m05-a03: returning for a borrower with no open record fails gracefully.
- m05-a04: restart preserves both files' state exactly.

## Hint 1

Two counters, one rule: `quantity` only changes via add/update; `available` changes on borrow/return. Never recompute one from the other except at add time.

## Hint 2

`findBorrowIndex` must filter on `returned == 0` or you will "return" an already-returned record.

## Hint 3

`getCurrentDate`: `time(NULL)` → `localtime` → `sprintf(dateStr, "%04d-%02d-%02d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday)`.

## Hint 4

Empty `returnDate` for open records: write an empty field and treat empty as "not returned" when displaying.

## Hint 5

Reference: `business.c::borrowBook/returnBook/listAllBorrows`, `data_mgr.c::findBorrowIndex/getCurrentDate`.

## Next Pressure

Real users type garbage into every prompt, delete files, and exceed limits — hardening time.

## Source Bridge

`business.c::borrowBook`, `business.c::returnBook`, `business.c::listAllBorrows`, `data_mgr.c::BorrowRecord`, `data_mgr.c::findBorrowIndex`, `data_mgr.c::getCurrentDate`

## Evidence Ledger

```text
evidence: code_evidence
source: business.c::borrowBook
rationale: Existence check + available > 0 + capacity check precede any mutation.
```

```text
evidence: teaching_inference
confidence: medium
rationale: No duplicate-borrow guard exists — the same borrower can drain all copies; flagged as milestone-06 discussion material.
source: business.c::borrowBook
```

## Completion Decision

(To be filled by review.)

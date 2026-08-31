---
artifact_id: milestone-04
language: en
---

# Milestone

milestone_id: milestone-04

## Goal

Add substring search across id, title, and author in one pass.

## Observable Result

Menu option 3 takes a keyword and prints every book whose id OR title OR author contains it; no match prints a clear message.

## Design Pressure

A growing catalog cannot be scanned by eye. One keyword must cover every field a user might remember.

## Scope

- `searchBook(keyword)` using `strstr` on three fields.
- Reuse the same row-printing format as the list view.

## Constraints

- Case-sensitive matching is acceptable (note it for milestone-06).
- No index/hashtable — linear scan.

## Prerequisites

- competency_id: project.array-crud (blocking)

## Tasks

1. Implement `searchBook` with a found flag.
2. Wire option 3 into the menu.

## Acceptance

- m04-a01: searching a title fragment prints exactly the matching books.
- m04-a02: an ID that appears inside another ID's prefix matches both (document the behavior).
- m04-a03: no match prints "no matching books", not an empty table with header only being ambiguous.

## Hint 1

`strstr(haystack, needle) != NULL` means "contains".

## Hint 2

Three conditions OR-ed in one if covers id/title/author.

## Hint 3

Reuse printing code or extract a `printBookRow` helper — copy-paste drift between views is a classic bug source.

## Hint 4

Empty keyword matches everything (`strstr(x, "") == x`). Decide whether to reject it up front.

## Hint 5

Reference: `business.c::searchBook`.

## Next Pressure

The system can track ownership, but not circulation: who has a book right now?

## Source Bridge

`business.c::searchBook`

## Evidence Ledger

```text
evidence: code_evidence
source: business.c::searchBook
rationale: The mature search scans all three fields with strstr and tracks a found flag.
```

## Completion Decision

(To be filled by review.)

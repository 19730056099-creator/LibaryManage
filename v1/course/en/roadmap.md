---
artifact_id: roadmap
language: en
---

# Reconstruction Roadmap

## Roadmap Principles

- Order by engineering pressure, not file order or commit history (none exists).
- Every stage must be runnable and explainable by the limitation of the previous stage.
- The mature implementation is a reference bridge, not the only valid solution.

## Milestone Overview

| ID | File | Goal (observable result) | New pressure introduced |
|---|---|---|---|
| milestone-01 | `01-minimal-value.md` | Menu-driven program that adds one book and lists books from a static array | A hardcoded demo is useless; user input must become data |
| milestone-02 | `02-crud-validation.md` | Full CRUD with unique-ID enforcement and delete-by-shift | Duplicate IDs and stale entries corrupt trust in the list |
| milestone-03 | `03-durability.md` | Data survives restart: save to / load from pipe-delimited text files | In-memory state dies on exit |
| milestone-04 | `04-search.md` | Substring search across id/title/author | Scanning a growing list by eye does not scale |
| milestone-05 | `05-borrow-return.md` | Borrow/return flow with quantity vs available invariant and dated records | Owning copies is not the same as having them on the shelf |
| milestone-06 | `06-robustness.md` | Harden inputs, missing files, capacity limits, and update semantics | Real users type garbage; disks lose files |

## Coverage

Covers all three source files' behavior: menu/UI (`main.c`), business rules (`business.c`), persistence & helpers (`data_mgr.c`). Uncovered: none within the repository's own scope.

## Teaching Inferences

```text
evidence: teaching_inference
confidence: high
rationale: The stage order (CRUD → durability → search → borrow → robustness) is chosen for pedagogical pressure; it is not claimed to be the author's development chronology.
source: main.c, business.c, data_mgr.c
```

```text
evidence: teaching_inference
confidence: medium
rationale: milestone-06 exists because the mature code shows partial hardening (strcspn newline stripping, blank-means-keep update, MAX caps) but leaves gaps (atoi accepts garbage as 0, no duplicate-borrow guard).
source: main.c::case 1, business.c::updateBook, data_mgr.c::loadData
```

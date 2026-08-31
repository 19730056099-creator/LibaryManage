---
artifact_id: roadmap
language: en
---

# Reconstruction Roadmap

## Roadmap Principles

- Order stages by “observable value of the previous version → new pressure → smallest change,” not by directories or commits.
- Let the learner produce a runnable result first, then bridge it to mature source.
- The reference implementation is evidence and a comparison point, not the only valid answer; it also leaves input and file-validation gaps.
- Add prerequisites just before first use rather than front-loading `strtok`, borrowing, and hardening.
- All runtime data uses a copy in the learning workspace so `/home/mengzhouyi/LibaryManageSrc` is not polluted.

## Milestone Overview

| ID | File | Observable goal | New pressure | Main source bridge |
|---|---|---|---|---|
| `milestone-01` | `01-minimal-value.md` | Add and list in-memory books through a menu | A hard-coded demo cannot be managed | `main.c::main`, `data_mgr.c::Book`, `business.c::addBook` |
| `milestone-02` | `02-crud.md` | In-memory add/list/update/delete with unique IDs | Wrong entries cannot be maintained | `business.c::updateBook`, `deleteBook` |
| `milestone-03` | `03-durability.md` | Save and load `books.txt` | Exit loses state | `data_mgr.c::loadData`, `saveData` |
| `milestone-04` | `04-search.md` | Search ID/title/author substrings | Manual scanning is slow | `business.c::searchBook`, `main.c::case 3` |
| `milestone-05` | `05-borrow-return.md` | Borrow/return, inventory, dates, and records | Total holdings differ from available copies | `business.c::borrowBook`, `returnBook`, `data_mgr.c::BorrowRecord` |
| `milestone-06` | `06-robustness.md` | Harden input, bad rows, and delete policy | Silent bad data corrupts state | `main.c::atoi`, `data_mgr.c::loadData`, `business.c::deleteBook` |

## Coverage

The route covers the main behavior of all three source files: menu input (`main.c`), book/borrow business (`business.c`), and structs/lookup/dates/persistence (`data_mgr.c`). It uses `books.txt` and `borrows.txt` as format evidence. Learner code always lives under `student/`.

Networking, databases, concurrency, accounts/permissions, GUIs, and external libraries are intentionally excluded. Direct `.c` inclusion is explained in M01; header refactoring is only an optional closing discussion.

## Teaching Inferences

```text
evidence: teaching_inference
confidence: high
source: main.c, business.c, data_mgr.c
rationale: M01→M02→M03→M04→M05→M06 is a teaching reconstruction: each main mechanism waits until the previous limitation becomes visible; it is not the author's chronology.
```

```text
evidence: teaching_inference
confidence: medium
source: data_mgr.c::saveData, data_mgr.c::loadData, books.txt::lines 4-7, borrows.txt::lines 3-4
rationale: Using the sample short rows as the M06 trigger is supported by code and data, but the repository does not say whether those rows are intentional test fixtures.
```

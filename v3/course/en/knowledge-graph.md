---
artifact_id: knowledge-graph
language: en
---

# Knowledge Graph

## Concept Dependencies

```text
tooling.c.gcc-build ───────────────────────────────┐
language.c.c-control-input ────────────────────────┤
language.c.structs-strings ──▶ language.c.arrays-pointers ──▶ project.array-crud
          │                    │                         │
          └──▶ language.c.file-io ──▶ project.delimited-persistence ──┘
                                                              │
                                      project.array-crud ──────┴──▶ domain.borrow-inventory
language.c.time-format ───────────────────────────────────────▶ domain.borrow-inventory
language.c.c-control-input ──▶ project.input-validation
language.c.file-io + project.delimited-persistence ──▶ project.defensive-parsing
 domain.borrow-inventory ──▶ project.borrow-delete-policy
```

This is a map of project requirements, not a rating of the learner. Foundations appear just before their first pressure; project concepts are introduced through milestone behavior.

## Learning Priority

| competency_id | Category | Smallest observable capability | First needed | Blocking |
|---|---|---|---|---|
| `tooling.c.gcc-build` | tooling | Compile `main.c` with gcc and run it from the correct working directory | milestone-01 | blocking |
| `language.c.c-control-input` | language | Build menu input with `fgets`, `atoi`, `do-while`, and `switch` | milestone-01 | blocking |
| `language.c.structs-strings` | language | Operate on structs containing fixed-size char arrays | milestone-01 | blocking |
| `language.c.arrays-pointers` | language | Traverse a struct array and shift elements left on deletion | milestone-01 | blocking |
| `language.c.file-io` | language | Read and write text with `fopen/fgets/fprintf/fclose` | milestone-03 | blocking |
| `language.c.time-format` | language | Produce `YYYY-MM-DD` with `time/localtime` | milestone-05 | non-blocking, taught just in time |
| `project.array-crud` | project_concept | Implement unique-ID add/list/update/delete on a fixed-capacity array | milestone-02 | introduced by milestone |
| `project.delimited-persistence` | project_concept | Write pipe-delimited rows and restore fields with `strtok` | milestone-03 | introduced by F03/milestone |
| `domain.borrow-inventory` | domain | Maintain `0 <= available <= quantity` and track borrowers | milestone-05 | introduced by milestone |
| `project.input-validation` | project_concept | Reject non-numeric and out-of-range quantities instead of silently accepting `atoi` | milestone-06 | introduced by milestone |
| `project.defensive-parsing` | project_concept | Validate field count, length, and numeric values before accepting a row | milestone-06 | introduced by milestone |
| `project.borrow-delete-policy` | project_concept | Define an explicit policy for deleting a book with open records | milestone-06 | introduced by milestone |

## Source Locations

- `tooling.c.gcc-build`, `language.c.c-control-input`: `main.c::main`.
- `language.c.structs-strings`: `data_mgr.c::Book`, `data_mgr.c::BorrowRecord`, `business.c::addBook`.
- `language.c.arrays-pointers`: `data_mgr.c::books`, `data_mgr.c::findBookIndex`, `business.c::deleteBook`.
- `language.c.file-io`: `data_mgr.c::loadData`, `data_mgr.c::saveData`.
- `language.c.time-format`: `data_mgr.c::getCurrentDate`.
- `project.array-crud`: `business.c::addBook`, `updateBook`, `deleteBook`, `listAllBooks`.
- `project.delimited-persistence`: `strtok` and `fprintf` in `data_mgr.c::loadData`, `saveData`.
- `domain.borrow-inventory`: `business.c::borrowBook`, `returnBook`, `data_mgr.c::findBorrowIndex`.
- Hardening pressures appear in `main.c::atoi`, `data_mgr.c::loadData`, and `business.c::deleteBook`.

## Minimal Exercises

1. Read one ID, copy it into `Item.code`, and print it.
2. Create three structs, delete index 1, and prove that the remaining order is preserved.
3. Write `B001|Title|2` to a temporary file and read its fields with `fgets` + `strtok`.
4. Draw inventory and record state after quantity=3, two borrows, and one return.

## Spiral Recurrence and Understanding Depth

These are planned recurrences in the course, not evidence that the learner already mastered them. `practice_depth` is the target depth for this route, and `reappears_in` identifies later use.

competency_id: tooling.c.gcc-build
practice_depth: touched
reappears_in: milestone-01
competency_id: language.c.c-control-input
practice_depth: explained
reappears_in: milestone-01, milestone-06
competency_id: language.c.structs-strings
practice_depth: explained
reappears_in: milestone-01, milestone-02, milestone-03, milestone-05, milestone-06
competency_id: language.c.arrays-pointers
practice_depth: explained
reappears_in: milestone-01, milestone-02, milestone-04, milestone-05
competency_id: language.c.file-io
practice_depth: debugged
reappears_in: milestone-03, milestone-06
competency_id: language.c.time-format
practice_depth: touched
reappears_in: milestone-05
competency_id: project.array-crud
practice_depth: debugged
reappears_in: milestone-02, milestone-04, milestone-06
competency_id: project.delimited-persistence
practice_depth: debugged
reappears_in: milestone-03, milestone-05, milestone-06
competency_id: domain.borrow-inventory
practice_depth: transferred
reappears_in: milestone-05, milestone-06
competency_id: project.input-validation
practice_depth: transferred
reappears_in: milestone-06
competency_id: project.defensive-parsing
practice_depth: transferred
reappears_in: milestone-06
competency_id: project.borrow-delete-policy
practice_depth: explained
reappears_in: milestone-06

```text
evidence: code_evidence
source: data_mgr.c::Book, data_mgr.c::BorrowRecord
rationale: The two structs define book fields, inventory fields, and borrow-record fields, forming the core project data model.
```

```text
evidence: code_evidence
source: main.c::main, data_mgr.c::loadData, business.c::borrowBook
rationale: Input, parsing, and business-state transitions appear in these paths, supporting the dependency-ordered route.
```

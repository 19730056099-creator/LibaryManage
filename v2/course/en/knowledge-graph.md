---
artifact_id: knowledge-graph
language: en
---

# Knowledge Graph

## Concept Dependencies

```text
tooling.c.gcc-build
language.c.structs-strings ──▶ language.c.arrays-pointers
language.c.arrays-pointers ──▶ project.array-crud
language.c.arrays-pointers ──▶ language.c.file-io
language.c.file-io + language.c.structs-strings ──▶ project.delimited-persistence
project.array-crud ──▶ domain.borrow-inventory
```

## Learning Priority

| competency_id | Category | Smallest Capability | Required By (candidates) | Blocking |
|---|---|---|---|---|
| tooling.c.gcc-build | tooling | Compile a multi-file C program with gcc and run the binary from a working directory so relative file paths resolve | milestone-01 | yes |
| language.c.structs-strings | language | Define a struct with char-array fields, use strcpy/strcmp/strlen/strstr, and pass structs by index | milestone-01 | yes |
| language.c.arrays-pointers | language | Keep a parallel counter over an array of structs, shift elements for delete, pass arrays via globals | milestone-01, milestone-02 | yes |
| language.c.file-io | language | Open/read/write text files with fopen/fgets/fprintf/fclose | milestone-03 | yes |
| project.array-crud | project_concept | Implement add/list/update/delete with unique-ID lookup on a fixed-capacity array | milestone-02 | yes |
| project.delimited-persistence | project_concept | Serialize records to pipe-delimited lines and parse them back with strtok | milestone-03 | yes |
| domain.borrow-inventory | domain | Maintain an invariant between total quantity and available copies across borrow/return with dated records | milestone-05 | yes |

## Source Locations

- gcc-build: whole repo; entry `main.c::main`.
- structs-strings: `data_mgr.c::Book/BorrowRecord`, `business.c::addBook`.
- arrays-pointers: `data_mgr.c::findBookIndex`, `deleteBook` in `business.c`.
- file-io: `data_mgr.c::loadData/saveData`.
- array-crud: `business.c::addBook/updateBook/deleteBook/listAllBooks/searchBook`.
- delimited-persistence: `data_mgr.c::loadData/saveData` (`strtok`, `fprintf`).
- borrow-inventory: `business.c::borrowBook/returnBook`, `findBorrowIndex`.

## Minimal Exercises

- gcc-build: compile a two-file "hello + helper" program.
- structs-strings: define a `Point {char name[20]; int x;}` and print it.
- arrays-pointers: given an int array, remove one element by shifting and update a count.
- file-io: write three lines to a file and read them back.
- array-crud: in-memory contact list with add/find/delete.
- delimited-persistence: save/load `name|age` lines with strtok.
- borrow-inventory: stock counter that cannot go below zero.

Each exercise must be smaller than the mature implementation; none may copy it verbatim.

---
artifact_id: milestone-03
language: en
---

# Milestone

milestone_id: milestone-03
competency_id: language.c.file-io
competency_id: language.c.structs-strings
competency_id: project.delimited-persistence
foundation_id: foundation-03
acceptance_id: m03-a01
acceptance_id: m03-a02
acceptance_id: m03-a03
acceptance_id: m03-a04
practice_id: m03-p01
manual_action_id: m03-manual-01
ai_boundary_id: m03-ai-01
transfer_check_id: m03-transfer-01
reappears_in: milestone-05, milestone-06
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o library_m03

## Current Version

Add `books.txt` to M02's in-memory CRUD: after successful mutations, write the book array as pipe-delimited rows and load it again at startup.

## What the Previous Version Solved

M02 makes the catalog maintainable during one run, but all state disappears when the process ends.

## New User Problem

A librarian opening the program tomorrow still needs yesterday's catalog; memory alone is not useful persistence.

## What This Stage Introduces

Introduce `fopen`, `fgets`, `fprintf`, `fclose`, and the simple row format `id|title|author|quantity|available`. Persist books only; do not add borrow records at the same time.

## Goal

Make book data survive a restart after add, update, or delete.

## Observable Result

Add a book and exit; start again and see it in the list. Open `books.txt` and see one text row in the same field order used by the loader.

## What This Stage Solves

Restart durability for the catalog and the boundary between an in-memory model and a text representation.

## Scope

- Load `books.txt` at startup and rewrite all books after a successful mutation.
- Split five fields with `strtok` and convert numeric fields to integers.
- Start with an empty catalog when the file cannot be opened, with an observable message.

## Not Solving Yet

Do not persist `borrows.txt`, handle short rows, overlong fields, embedded `|`, atomic writes, or half-written-file recovery; those pressures belong to F03/M06.

## Prerequisites

Complete `foundation-03`'s file and `strtok` exercise; use M02's `Book` array and CRUD.

## First Touch

Write one in-memory `Book` to a temporary file with `fprintf`, close it, and read the raw line back with `fgets`; then add `strtok` to restore fields. Only then connect I/O to the menu and observe the before/after restart difference.

## Tasks

1. Define the row format and make the five write/read positions explicit.
2. Load the file into the array and save all books after each successful add/update/delete.
3. In an isolated `student/milestone-03/` directory, test “add → exit → restart → list.”
4. Remove the data file deliberately and record how a missing file is handled.

## AI Usage Boundary

AI may explain file modes, `strtok` state, or draw a sequence diagram. You must personally write the load/save loops, choose field order, check `fopen`, run two processes, and inspect the file; do not submit only AI-generated persistence code.

## Understanding and Transfer Check

Temporarily rename `available` to `on_shelf` in your own format and list every write/read location that must change. Then add a short row and explain why it cannot be accepted as a valid `Book`.

## Acceptance

```text
acceptance_id: m03-a01
```
The program builds without warnings and finds its own `books.txt` from the correct working directory.

```text
acceptance_id: m03-a02
```
Add at least two books, exit, restart, and recover the same fields and quantities.

```text
acceptance_id: m03-a03
```
Inspect `books.txt`; each valid record's order matches the loader, and a missing file does not dereference a null file pointer.

```text
acceptance_id: m03-a04
```
Submit the two-process run record, file contents, load/save explanation, and transfer answer.

## Hint 1

If the write order is ID, title, author, total, available, in what order must `strtok` be called during reading?

## Hint 2

Failure of `fopen("books.txt", "r")` can mean a first run; do not pass the resulting `FILE *` to `fgets`.

## Hint 3

Save by iterating `[0, bookCount)`; while loading, fill one array slot only when enough fields exist.

## Hint 4

Separate the boundaries: `saveBooks` maps array to text, and `loadBooks` maps text to array. Validate each on a temporary file first.

## Hint 5

If you explicitly request a complete reference, start with the five-field `fprintf`/`fgets`/`strtok` loops; still rename one field, restart-test, and explain short-row risk.

## Why the Next Stage Appears

A persistent catalog can grow, and users should not scan every row to find a target. M04 reuses array traversal and adds `strstr` multi-field search.

## Source Bridge

Compare the `strtok` chain in `data_mgr.c::loadData` with the `fprintf` format in `saveData`. The reference also reads and writes borrow data; this stage isolates book-file pressure first.

## Evidence Ledger

```text
evidence: code_evidence
source: data_mgr.c::loadData
rationale: loadData opens books.txt, splits five fields with strtok, and fills the books array.
```

```text
evidence: code_evidence
source: data_mgr.c::saveData
rationale: saveData writes each book as an id|title|author|quantity|available row with fprintf and rewrites the file in w mode.
```

```text
evidence: document_evidence
source: books.txt::lines 1-3
rationale: The first three sample rows show the valid five-field book-record order for checking serialization.
```

## Completion Decision

After restart acceptance, file inspection, and direct file-I/O practice evidence pass, a review may mark M03 `passed`; short and malformed fields are intentionally left for later.

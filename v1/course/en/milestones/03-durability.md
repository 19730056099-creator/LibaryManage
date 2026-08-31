---
artifact_id: milestone-03
language: en
---

# Milestone

milestone_id: milestone-03

## Goal

Make data survive restarts: after every successful write, save all books to `books.txt` (pipe-delimited); load them back on startup.

## Observable Result

- After add/update/delete, `books.txt` matches memory.
- Restarting the program restores the full list.
- A missing `books.txt` starts cleanly with an empty library.

## Design Pressure

In-memory state dies on exit. The simplest reliable answer: one human-readable text file, rewritten wholesale.

## Scope

- `saveData()`: `fprintf(file, "%s|%s|%s|%d|%d\n", ...)`.
- `loadData()`: `fgets` a line + field-by-field `strtok(line, "|")`.
- Call save at the end of every write path; load on startup.

## Constraints

- Books only; borrow-record persistence merges into milestone-05.
- No escaping for embedded `|` or newlines in fields.
- Capacity caps unchanged (stop reading at MAX).

## Prerequisites

- competency_id: language.c.file-io (blocking)
- competency_id: project.delimited-persistence (blocking)

## Tasks

1. Write `saveData`, call it from `addBook`'s success path; verify the format in a text editor.
2. Write `loadData`: first `strtok` call takes the line, later calls take NULL; numbers via `atoi`.
3. Handle a missing file (NULL from fopen means empty library).
4. Add save calls to the update/delete paths.

## Acceptance

- m03-a01: after adding two books, `cat books.txt` shows two lines of five pipe-separated fields.
- m03-a02: after restart, list output equals pre-exit output.
- m03-a03: delete a book, restart; it is gone.
- m03-a04: renaming away `books.txt` does not crash; the list is empty.

## Hint 1

The parse pattern is fixed: `char *tok = strtok(line, "|"); ... tok = strtok(NULL, "|");` — with a fixed field count you just take five positional tokens.

## Hint 2

`atoi(NULL)` is undefined — check each token before use.

## Hint 3

Save uses mode `"w"` rewriting the whole file; never append or restarts will duplicate rows.

## Hint 4

Use a generous line buffer (e.g. 512) so a long title cannot be truncated and misalign the next record's parse.

## Hint 5

Reference: `data_mgr.c::loadData/saveData`. The mature code zeroes the counters before the read loop to avoid stacking duplicate loads.

## Next Pressure

Eyeballing a growing list stops working; and "owned copies" vs "on-shelf copies" now need separate management.

## Source Bridge

`data_mgr.c::loadData`, `data_mgr.c::saveData`

## Evidence Ledger

```text
evidence: code_evidence
source: data_mgr.c::saveData
rationale: The pipe-delimited full-overwrite persistence format comes from the mature code.
```

```text
evidence: teaching_inference
confidence: medium
rationale: A field value containing '|' corrupts the data; the mature code does not handle it — material for milestone-06 discussion.
source: data_mgr.c::loadData
```

## Completion Decision

(To be filled by review.)

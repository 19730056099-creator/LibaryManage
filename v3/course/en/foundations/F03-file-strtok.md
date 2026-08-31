---
artifact_id: foundation-03
language: en
---

# Foundation Unit

foundation_id: foundation-03
competency_id: language.c.file-io
competency_id: project.delimited-persistence
required_by: milestone-03
required_by: milestone-05
required_by: milestone-06
acceptance_id: f03-a01
practice_id: f03-p01
manual_action_id: f03-manual-01
ai_boundary_id: f03-ai-01
transfer_check_id: f03-transfer-01
reappears_in: milestone-03, milestone-05, milestone-06
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o foundation03

## Why It Is Needed Now

M03 faces “data disappears after exit.” Before wiring persistence into the whole project, use a temporary file to practice `fopen`, line reads, `strtok`, `fprintf`, and closing the file, keeping file APIs separate from CRUD at first.

## Dependencies

This depends on the struct/string and array basics; no database knowledge is needed. Perform every experiment in your student directory and never modify the reference `books.txt`.

## Minimal Concepts

- `fopen` can return `NULL`; close files after reading or writing.
- `fgets` returns one line; `strtok(line, "|")` writes `\0` at delimiters and returns field pointers.
- `fprintf` can serialize fields into one row; write and read order must agree.
- Accept the simple format for now; missing fields, overflow, and delimiters inside values wait for M06.

## Small Example

```c
char line[64] = "B001|Title|2\n";
for (char *token = strtok(line, "|"); token; token = strtok(NULL, "|")) {
    printf("%s\n", token);
}
```

## First Touch

Write `B001|Title|2` in the exercise directory, read it with `fgets`, and print each token. Open the generated file to confirm it is ordinary text; then observe that `strtok` has split `line` in place.

## Hands-on Exercise

In `student/foundation/F03-file-strtok/main.c`, create `probe.txt`, write two pipe-delimited records, reopen it, read line by line, split three fields, and print them. Handle open failure and close the file. Do not copy `data_mgr.c::loadData` directly.

## AI Usage Boundary

AI may explain `FILE *`, `NULL`, `strtok(NULL, ...)`, and file modes, or help design one malformed row. You must personally choose the filename, write the read/write loops, run the program, and inspect the file. Explain why the first `strtok` receives `line` and later calls receive `NULL`.

## Understanding and Transfer Check

Change the record from three fields to four while keeping write/read order aligned. Then add a two-field row, describe what the current exercise does, and explain why M06 must validate field count first.

## Exit Criteria

```text
acceptance_id: f03-a01
```

- The program compiles without warnings, runs, and creates `probe.txt` with two expected rows.
- Re-reading prints each field, and an open failure does not dereference a null file pointer.
- Explain first/subsequent `strtok` calls and short-row risk, and submit the transfer result.

## Project Bridge

Revisit the book-row format in `data_mgr.c::loadData` and `saveData`. M03 first makes `books.txt` survive restart, M05 adds `borrows.txt`, and M06 exposes gaps in the current parser.

## Not Learning Yet

Do not study databases, binary serialization, transactions, atomic replacement, concurrent file locks, or complex escaping; none is a boundary in the reference project.

## Completion Decision

Only after submitting the hand-written file program, file contents, run record, and transfer explanation may F03 be marked `passed`. It does not unlock milestone-01; it becomes active just before the related stages.

```text
evidence: code_evidence
source: data_mgr.c::loadData
rationale: loadData uses fopen, fgets, strtok, and atoi to restore fields from books.txt and borrows.txt.
```

```text
evidence: code_evidence
source: data_mgr.c::saveData
rationale: saveData uses fopen in w mode and fprintf to write array records back to pipe-delimited text files.
```

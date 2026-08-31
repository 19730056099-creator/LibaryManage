---
artifact_id: review-f02
language: en
---

# Stage Review

review_id: review-01-02
milestone_id: foundation-01
verdict: passed

## Strengths

- f02-a01 complete: array of 5 `struct Point` initialized in-place, delete at index 2, print remaining names. Compiles with zero warnings; output correct (Naruto/Sasuke/Yamato/Kakashi).
- Your comments show correct and deep understanding:
  - A struct array = each element is a whole group of data ✅
  - Arrays need `= {...}` initialization; `char name[20] = "..."` works only at definition, afterwards you must use strcpy — your summary "initialize as a whole at birth, modify contents with strcpy after" is exactly right ✅
  - Your error-chain analysis of the three missing semicolons (declaration fails → cascading undeclared errors) is completely correct ✅
- You asked the key question proactively: "This doesn't truly delete — it overwrites and stops visiting the last slot. O(n) complexity. Is there a better approach, e.g. a third-party library?"

## Correctness

- Shift loop bound `i < count - 1` is right; whole-struct assignment `Points[i] = Points[i+1]` is right.
- Deleting the last element runs the loop zero times (only count--) — your code uses idx=2, but the mechanism already supports this.

## Acceptance Evidence

- f02-a01: `student/foundation/F02-array-delete/main.c` — demonstrated (compiled and run locally).
- Command: `gcc -Wall -Wextra main.c -o main && ./main`

## Current-Stage Tradeoffs

- Answering your question: **O(n) IS the cost of this data structure; there is no free upgrade**. Linked lists delete in O(1) but lose random access by index. The mature project chose static arrays precisely to trade flexibility for simplicity under a 1000-book cap. "Not visiting the last slot" is not a hack — it's the counter semantics working as designed, and it is exactly what milestone-02's `deleteBook` does.

## Next Scale Pressure

In-memory books vanish on exit. F03 teaches writing structs to a file and parsing them back (fopen/fgets/strtok) — the entire basis of milestone-03 persistence.

## Reference Comparison

Your shift-deletion matches `business.c::deleteBook` exactly (same loop bound and count--). The difference is only that the mature code wraps lookup-by-ID plus deletion into one function.

## Required Changes

None. (The "forgot ;" notes are learning annotations, not code issues.)

## Optional Improvements

- The exercise asked to delete a middle element — done; consider adding a step that deletes the LAST element to verify the loop runs zero times.
- On "third-party libraries": C's standard library has no ready-made dynamic collection; real projects use glib's GArray or hand-rolled dynamic arrays, but this project deliberately stays dependency-free.

## Verdict

**passed** — foundation-02 complete. Competency `language.c.arrays-pointers` upgraded to `ready / demonstrated`. Proceed to foundation-03 (`course/en/foundations/F03-file-strtok.md`).

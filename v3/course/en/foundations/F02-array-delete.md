---
artifact_id: foundation-02
language: en
---

# Foundation Unit

foundation_id: foundation-02
competency_id: language.c.arrays-pointers
required_by: milestone-01
required_by: milestone-02
acceptance_id: f02-a01
practice_id: f02-p01
manual_action_id: f02-manual-01
ai_boundary_id: f02-ai-01
transfer_check_id: f02-transfer-01
reappears_in: milestone-01, milestone-02, milestone-04
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o foundation02

## Why It Is Needed Now

M01 needs to hold more than one book, and M02 needs to remove a middle element. A fixed-capacity struct array, valid count, and shift-on-delete are the smallest skills needed for both stages.

## Dependencies

This depends on the struct/string basics and the ability to compile and run a small program from `foundation-01`.

## Minimal Concepts

- Array elements are contiguous; `count` names the valid prefix `[0, count)`, while capacity is different.
- After deleting `index`, assign each element from `index + 1` through the end into the previous slot, then decrement `count`.
- Choose loop bounds that never read `items[count]`; deleting the last element needs no move.

## Small Example

```c
Item items[3] = {{"A", 1}, {"B", 2}, {"C", 3}};
int count = 3;
int index = 1;
for (int i = index; i < count - 1; i++) items[i] = items[i + 1];
count--; /* items[0], items[1] are now A, C */
```

## First Touch

Print `A B C` on paper or in the terminal, delete index 1, and print the valid prefix. Deliberately omit `count--` and observe why old `C` appears twice; then fix only the count rather than adding an abstraction.

## Hands-on Exercise

In `student/foundation/F02-array-delete/main.c`, define a small struct array, insert three elements, delete by index, and print the remaining valid elements. Test deleting the first, last, and middle element. Do not copy `business.c::deleteBook`.

## AI Usage Boundary

AI may draw the shift diagram, explain index bounds, or help design the three deletion cases. You must personally write the shift loop, change `count`, compile, and test all three positions; be able to point out both sides of each assignment.

## Understanding and Transfer Check

Change the exercise to delete index 0 and explain why the loop still starts at `index`. Then change capacity to 5 and explain why valid length is still controlled by `count`.

## Exit Criteria

```text
acceptance_id: f02-a01
```

- The program compiles without warnings and runs.
- Deleting the first, middle, or last element prints only the remaining valid elements in the correct order.
- Explain `[0, count)`, shifting, and `count--`, and submit one transfer result.

## Project Bridge

Revisit `data_mgr.c::books`, `bookCount`, and `business.c::deleteBook`. M01 uses the array for add/list first; M02 turns this exercise's shift into project deletion.

## Not Learning Yet

Do not study malloc, linked lists, sorting, hash tables, pointer-arithmetic optimization, or concurrency; the reference project's fixed capacity and linear scan are enough for now.

## Completion Decision

Only after submitting the hand-written shift loop, three position runs, and transfer explanation may `foundation-02` be marked `passed` and the array prerequisite for milestone-01 be unlocked.

```text
evidence: code_evidence
source: data_mgr.c::books, bookCount
rationale: The reference uses a fixed-capacity Book array and bookCount for the valid prefix, directly matching this unit's array model.
```

```text
evidence: code_evidence
source: business.c::deleteBook
rationale: deleteBook shifts later structs left from the target index and decrements bookCount, providing direct shift-on-delete evidence.
```

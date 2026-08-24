---
artifact_id: review-f01
language: en
review_id: review-01-01
milestone_id: foundation-01
verdict: passed
---

# Stage Review

```
evidence: code_evidence
source: student/foundation/F01-c-minimum/main.c
rationale: Learner's f01-a01 exercise, compiled and run locally with correct output.
```

## Strengths

- Exercise f01-a01 fully implemented: `struct Point`, two instances, printf output, and an strcmp comparison. Compiles with zero warnings (`gcc -Wall -Wextra`) and runs correctly.
- Your comments proactively clarified key concepts: C has no true string type, only char arrays; strcpy/strcmp are string-only while ints assign directly; the struct needs a trailing `;`; strlen returns size_t printed with %zu. All correct.
- You experimented beyond the unit: compiler command differences (`-o` names the output), `./` and Linux program lookup, and encoding-related mojibake on Windows vs Linux.

## Correctness

- `main.c` compiles and runs: prints both records and correctly reports "names differ".
- Understanding of %zu / size_t is accurate.

## Acceptance Evidence

- f01-a01: `student/foundation/F01-c-minimum/main.c` — demonstrated (compiled and run locally).
- Command: `gcc -Wall -Wextra main.c -o main && ./main`

## Current-Stage Tradeoffs

- Using Chinese strings with strcmp is fine (byte-wise comparison), but note each hanzi is 3 bytes in UTF-8, so `name[20]` holds roughly 6 characters — echoing the "terminator needs room" lesson.

## Next Scale Pressure

One book is not enough, and separate variables don't scale — you need "struct array + counter" and shift-deletion. That is exactly F02.

## Reference Comparison

Your `struct Point` matches the mature project's `data_mgr.c::Book` shape (char-array fields + primitive fields). The mature code additionally relies on a strcmp loop in `findBookIndex` — F02 covers the array side.

## Required Changes

None.

## Optional Improvements

- Small correction: your comment saying output files "default to .exe" is inaccurate — on Linux `-o main` produces an extension-less executable; .exe is only a Windows convention. Does not affect the verdict.
- Add `\n` after "两个名字不同" for tidier output.

## Verdict

**passed** — foundation-01 complete. Competency `language.c.structs-strings` upgraded to `ready / demonstrated`. Proceed to foundation-02 (`course/en/foundations/F02-array-delete.md`).

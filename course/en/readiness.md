---
artifact_id: readiness
language: en
---

# Learning Readiness

## Project-Required Competencies

See `knowledge-graph.md` for the full DAG: 7 competencies (1 tooling, 3 language, 2 project_concept, 1 domain), all blocking for their first milestone.

competency_id: tooling.c.gcc-build
state: needs_refresh
competency_id: language.c.structs-strings
state: ready
competency_id: language.c.arrays-pointers
state: needs_refresh
competency_id: language.c.file-io
state: needs_refresh
competency_id: project.array-crud
state: needs_refresh
competency_id: project.delimited-persistence
state: needs_refresh
competency_id: domain.borrow-inventory
state: needs_refresh

## Learner Baseline

**Not yet calibrated.** No learner evidence has been recorded. The course structure is complete, but the personalized route (which foundation units to create) depends on your answers.

## Gaps and Decisions

Choose one calibration mode:

1. **`assume_beginner`** — I create foundation units F01–F03 (C structs/strings, arrays + delete-by-shift, file I/O with strtok) before milestone-01. Safest, adds ~2–4 hours.
2. **`self_report` / `mixed`** — answer the 5 questions below; I create foundations only where you are uncertain.
3. **`waived`** — skip straight to milestone-01 with risks recorded (you may hit C syntax or strtok walls mid-milestone).

Calibration questions (capability-based, ~5 minutes):

- Q1 (gcc-build): Can you compile a program split across two .c files with `gcc a.c b.c -o app` and explain why including `.c` files directly works here?
- Q2 (structs-strings): Given `char id[20]; strcpy(id, "B001"); if (strcmp(id,"B001")==0) ...` — what happens, and why must the array be size ≥ 6?
- Q3 (arrays-pointers): An array of 5 structs with count=5: write the loop that removes element 2 by shifting. Can you do it without looking anything up?
- Q4 (file-io): Explain what `fopen(path, "w")` does on an existing file, and what `strtok(NULL, "|")` continues doing on the second call.
- Q5 (domain): If quantity=3 and two copies are borrowed, what should `available` be, and which operation changes it back?

## Foundation Route

Created just in time after calibration:

| Candidate | Competencies | Unlocks |
|---|---|---|
| F01-c-minimum | language.c.structs-strings | milestone-01 |
| F02-array-delete | language.c.arrays-pointers | milestone-01/02 |
| F03-file-strtok | language.c.file-io, project.delimited-persistence | milestone-03 |


foundation_id: foundation-01
foundation_id: foundation-02
foundation_id: foundation-03

## Entry Conditions

Milestone-01 may start when gcc-build, structs-strings, and arrays-pointers are `ready` (self-reported or demonstrated) or explicitly waived with risk notes.

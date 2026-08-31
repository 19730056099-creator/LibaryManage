---
artifact_id: readiness
language: en
---

# Learning Readiness

## Project-Required Competencies

This competency DAG is expanded backward from the main user journey. `state` describes the current foundation plan, not a broad rating of the learner.

competency_id: tooling.c.gcc-build
state: learning
required_by: milestone-01

competency_id: language.c.c-control-input
state: learning
required_by: milestone-01, milestone-06

competency_id: language.c.structs-strings
state: learning
required_by: milestone-01, milestone-02, milestone-03, milestone-04, milestone-05, milestone-06

competency_id: language.c.arrays-pointers
state: needs_refresh
required_by: milestone-01, milestone-02, milestone-04, milestone-05, milestone-06

competency_id: language.c.file-io
state: needs_refresh
required_by: milestone-03, milestone-05, milestone-06

competency_id: language.c.time-format
state: unknown
required_by: milestone-05

competency_id: project.array-crud
state: unknown
required_by: milestone-02, milestone-04, milestone-06

competency_id: project.delimited-persistence
state: unknown
required_by: milestone-03, milestone-05, milestone-06

competency_id: domain.borrow-inventory
state: unknown
required_by: milestone-05, milestone-06

competency_id: project.input-validation
state: unknown
required_by: milestone-06

competency_id: project.defensive-parsing
state: unknown
required_by: milestone-06

competency_id: project.borrow-delete-policy
state: unknown
required_by: milestone-06

## Learner Baseline

This generation reuses the learner evidence already supplied for this project: the learner has studied C syntax but has no hands-on project-building experience and needs to refresh many details; they selected `assume_beginner`. The stated goal is to understand and reconstruct the C library-management path in LibaryManageSrc from zero.

## Gaps and Decisions

- `tooling.c.gcc-build`, `language.c.c-control-input`, and `language.c.structs-strings` are assigned to F01 to restore compilation, input loops, and structs/strings.
- `language.c.arrays-pointers` is assigned to F02 and must be practiced before milestone-01.
- `language.c.file-io` and `project.delimited-persistence` are assigned to F03 just before milestone-03 rather than front-loaded.
- The remaining concepts are introduced through small experiments in the milestone where their pressure first appears.

The generated route selects `balanced`: the goal explicitly combines building the product with understanding its mechanisms. AI may reduce mechanical scaffolding, but the learner must personally run, modify, explain, and diagnose critical paths.

learner_choice: assume_beginner

## Learning Mode and AI Boundary

learning_mode: balanced

AI may explain compiler messages, help design test inputs, point to likely failure locations, and provide focused scaffolding after the learner attempts the task. AI may not replace the critical actions: the learner must create or modify the concept-bearing C code, run commands, observe output, inspect files, and explain the causal path from input to state change.

## Foundation Route

| Unit | Covered capability | Placement | Unlocks |
|---|---|---|---|
| `foundation-01` / `F01-c-build-and-structs.md` | gcc, menu control flow, structs/strings | **currently selected** | First three prerequisites for milestone-01 |
| `foundation-02` / `F02-array-delete.md` | `language.c.arrays-pointers` | After F01 passes | milestone-01 and milestone-02 |
| `foundation-03` / `F03-file-strtok.md` | File I/O and delimited parsing | Just before milestone-03 | milestone-03, milestone-05, milestone-06 |

foundation_id: foundation-01
foundation_id: foundation-02
foundation_id: foundation-03

## Entry Conditions

The route is generated, but generation does not grant mastery. After F01 and F02 meet their observable exit criteria, the blocking competencies for milestone-01 become `ready`; F03 is gated just before milestone-03. Every passed unit requires a learner-authored action, observable result, explanation, and AI-usage record.

```text
evidence: code_evidence
source: main.c::main
rationale: The entry point uses a gcc-buildable single translation unit, menu control flow, and the fgets/atoi input path.
```

```text
evidence: code_evidence
source: data_mgr.c::Book
rationale: Book's fixed-size char arrays and quantity fields establish the project's struct, string, and inventory requirements.
```

---
artifact_id: getting-started
language: en
---

# Learning Guide

## What This Course Is

Rebuild [LibaryManage](../../../LibaryManage) from zero — a C command-line book management system (~570 lines, 3 source files) — and master: C structs and strings, array CRUD with shift-deletion, pipe-delimited text persistence (strtok), the quantity/available inventory invariant, and borrow/return flows. The reference repo is read-only; your code goes in `student/`.

## File Overview and Reading Order

1. `en/readiness.md` — calibrate first; decides whether foundation units are needed.
2. (if created) `en/foundations/FNN-*.md` — close gaps.
3. `en/milestones/01-minimal-value.md` → `06-robustness.md` — rebuild in order.
4. `en/project-map.md` / `architecture.md` / `knowledge-graph.md` / `roadmap.md` — consult when comparing against the mature design.
5. `course/GETTING_STARTED.md` — this file.

## Quick File Reference

| File | Purpose | When to Read |
|---|---|---|
| readiness.md | Competency calibration and gap decisions | Required before starting |
| roadmap.md | Overview of 6 milestones | Once at course start |
| milestones/NN-*.md | Goal/tasks/acceptance/5 hints per stage | While working that stage |
| foundations/FNN-*.md | Personalized prerequisite bridges | When calibration shows a gap |
| project-map.md | Subsystems and evidence ledger | "Where is this in the mature code?" |
| architecture.md | Architecture and key decisions | Comparing your own design |
| knowledge-graph.md | Competency DAG and minimal exercises | Planning your path |

## Usage Rules

- **Answer calibration**: reply with answers to Q1–Q5 in readiness.md, or say "assume_beginner", or say "waive".
- **Start a unit**: say "start milestone-01" (or the current unit).
- **Request hints**: stuck? say "hint" — lowest level by default; specify e.g. "hint 3" for deeper.
- **Submit for review**: after meeting acceptance items, say "please review"; verdicts are written to `reviews/`.
- **Check progress**: ask "my progress" anytime.
- Later foundations arrive just in time, never front-loaded.

## Start Now

Current state: **awaiting calibration**. Your first action:

> Open `course/en/readiness.md`, answer Q1–Q5 (or just reply "assume_beginner").

Afterwards I will create any needed foundation units and set milestone-01 as current.

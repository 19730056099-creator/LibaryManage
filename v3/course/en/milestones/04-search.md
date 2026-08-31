---
artifact_id: milestone-04
language: en
---

# Milestone

milestone_id: milestone-04
competency_id: language.c.arrays-pointers
competency_id: language.c.structs-strings
competency_id: project.array-crud
acceptance_id: m04-a01
acceptance_id: m04-a02
acceptance_id: m04-a03
practice_id: m04-p01
manual_action_id: m04-manual-01
ai_boundary_id: m04-ai-01
transfer_check_id: m04-transfer-01
reappears_in: milestone-05, milestone-06
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o library_m04

## Current Version

On M03's persistent catalog, a user can enter a keyword and search for it as a substring of ID, title, or author.

## What the Previous Version Solved

M03 keeps the catalog across restarts, but listing still requires a full scan.

## New User Problem

As the catalog grows, users usually remember only part of a title, author, or ID and should not read every row.

## What This Stage Introduces

Introduce `strstr`, a found flag, and one linear scan; print a record when any field matches. Do not build an index because fixed capacity and current scale have not created that pressure.

## Goal

Provide predictable multi-field contains-search with an explicit no-results behavior.

## Observable Result

Searching `C语言`, an author fragment, and an ID fragment finds records; an absent keyword reports no matches.

## What This Stage Solves

Reduce the operational cost of finding a catalog entry while showing the value of reusing the existing array traversal.

## Scope

- Apply `strstr` to `id`, `title`, and `author`.
- Print each matching record once and use `found` for an empty result.
- Keep case and ordering simple; do not add an index.

## Not Solving Yet

Do not implement case-insensitive search, relevance ranking, regular expressions, fuzzy matching, or database full-text search.

## Prerequisites

Use M02's array/string skills and M03's book loading; no new foundation unit is needed.

## First Touch

Test `strstr("C language", "lang")` and an absent fragment on three plain strings, then put the same predicate inside the book loop. Observe `NULL` versus non-`NULL` before connecting the menu.

## Tasks

1. Add a search menu branch and read a keyword.
2. Traverse valid books and test the three fields for containment.
3. Use a match count or `found` flag so one book prints only once.
4. Validate ID, title, author, and no-match inputs.

## AI Usage Boundary

AI may explain the pointer returned by `strstr` or help generate four test datasets. You must personally write the predicate, prevent duplicate output, run the tests, and explain why an empty result is not a crash.

## Understanding and Transfer Check

Change search to authors only, then restore all three fields and describe the condition change. Add a `publisher` field and list the matching/output locations that would need modification.

## Acceptance

```text
acceptance_id: m04-a01
```
ID, title, and author fragments each find the correct records.

```text
acceptance_id: m04-a02
```
An absent keyword has an explicit no-result response; a record matching multiple fields prints once.

```text
acceptance_id: m04-a03
```
Submit four run records, explain the predicate, and show one transfer change; search must not mutate the catalog or persistence.

## Hint 1

Print whether `strstr` returns `NULL` before debugging the menu.

## Hint 2

A record matches when `id hit || title hit || author hit`; print it once after the combined condition.

## Hint 3

Initialize `found = 0`, set it after output, and print no-results only if it remains 0 after the loop.

## Hint 4

Let the search function traverse and print; let the menu read the keyword and call it. Do not copy the array.

## Hint 5

A complete reference may show only the `strstr` predicate and found pattern; still change the field scope, run a no-result case, and explain linear cost.

## Why the Next Stage Appears

Finding a book does not say whether a copy is available or who has it. M05 adds inventory and borrow records beside the existing catalog.

## Source Bridge

Compare the three `strstr` conditions in `business.c::searchBook` and the input path in `main.c::case 3`; note that it reuses the array and has no index.

## Evidence Ledger

```text
evidence: code_evidence
source: business.c::searchBook
rationale: searchBook uses strstr on id, title, and author and uses found for the empty result.
```

```text
evidence: code_evidence
source: main.c::case 3
rationale: Menu case 3 reads a keyword and calls searchBook, proving the user-input path into the business layer.
```

## Completion Decision

After the three acceptance items and direct search practice pass, a review may mark M04 `passed`; indexing and other scale mechanisms remain deferred.

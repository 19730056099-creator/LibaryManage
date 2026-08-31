---
artifact_id: foundation-01
language: en
---

# Foundation Unit

foundation_id: foundation-01
competency_id: tooling.c.gcc-build
competency_id: language.c.c-control-input
competency_id: language.c.structs-strings
required_by: milestone-01
acceptance_id: f01-a01
practice_id: f01-p01
manual_action_id: f01-manual-01
ai_boundary_id: f01-ai-01
transfer_check_id: f01-transfer-01
reappears_in: milestone-01
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o foundation01

## Why It Is Needed Now

The first chain in milestone-01 is “compile → menu input → struct state → list output.” Learn the smallest gcc build, string, and struct path first so attention stays on project behavior.

## Dependencies

None. You only need to create directories and files; this unit restores the C syntax used by the project instead of becoming a full C course.

## Minimal Concepts

- For this repository, compile only `main.c`: it directly includes `data_mgr.c` and `business.c`.
- A `struct` groups fields into one value; `char text[N]` must reserve space for the terminating `\0`.
- `strcpy` copies strings, `strcmp(a, b) == 0` means equality, and `strcspn` can remove the newline left by `fgets`.
- `do-while` runs at least once and `switch` dispatches an integer; `atoi` is only the minimum parser, with bad-input handling deferred to milestone-06.

## Small Example

```c
#include <stdio.h>
#include <string.h>

typedef struct { char code[8]; int pages; } Item;

int main(void) {
    Item item;
    char line[32];
    if (!fgets(line, sizeof line, stdin)) return 1;
    line[strcspn(line, "\n")] = '\0';
    strcpy(item.code, line);
    item.pages = 10;
    printf("%s %d\n", item.code, item.pages);
    return 0;
}
```

## First Touch

First create a `main.c` containing only `printf("hello\\n")`, run the gcc command, and execute `./foundation01`. After seeing output, change it to use `Item`; observe “source file → executable → terminal output” before memorizing terminology.

## Hands-on Exercise

In `student/foundation/F01-c-build-and-structs/main.c`, hand-write a smaller version: define `Item`, read a code of at most 7 characters, read an integer pages value, and print both. Put a menu in a `do-while` and exit only when input is `0`. Do not copy reference-project functions.

## AI Usage Boundary

AI may explain compiler messages, help design test input, and point to likely newline or type issues. You must personally create `main.c`, write `Item`, the input loop, and the exit condition, run gcc, and save one output record; report any AI use. A successful AI-generated program alone is not exit evidence.

## Understanding and Transfer Check

- Change `code[8]` to `code[12]`, enter 11 characters, and explain why the accepted length changes.
- Explain aloud why `strcmp(...) == 0` means equality, why a newline is removed after `fgets`, and why this repository compiles only `main.c`.

## Exit Criteria

```text
acceptance_id: f01-a01
```

- The gcc command produces no errors or warnings, and `./foundation01` runs.
- One input prints the same code and pages; input `0` exits the loop.
- Submit `main.c`, build output, one run record, and the explanation/transfer answers.

## Project Bridge

Revisit `data_mgr.c::Book`, `main.c::main`, and `main.c::displayMenu`, and map your `Item` and input loop to the reference. The next unit handles struct arrays and deletion.

## Not Learning Yet

Do not study pointer arithmetic, dynamic allocation, file persistence, `strtok`, borrow business, complete input validation, or header refactoring yet; each appears only when later pressure requires it.

## Completion Decision

Only after the learner submits the hand-written exercise, build/run evidence, and explanation/transfer check may `progress.json` mark this unit `passed` and mark the three competencies `ready`.

```text
evidence: code_evidence
source: data_mgr.c::Book
rationale: Book uses fixed-size id/title/author character arrays and integer quantity fields, directly supporting this unit's struct/string bridge.
```

```text
evidence: code_evidence
source: main.c::main
rationale: main.c::main uses fgets, strcspn, atoi, do-while, and switch, providing the control/input evidence for this unit.
```

```text
evidence: code_evidence
source: main.c::data_mgr.c::business.c includes
rationale: main.c directly includes both implementations, which determines the repository's smallest gcc build entry.
```

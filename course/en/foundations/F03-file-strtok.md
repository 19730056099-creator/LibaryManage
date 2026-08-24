---
artifact_id: foundation-03
language: en
---

# Foundation Unit

foundation_id: foundation-03
competency_id: language.c.file-io
competency_id: project.delimited-persistence

## Why It Is Needed Now

Milestone-03 makes data survive restarts by writing pipe-delimited lines to `books.txt` and parsing them back. You need fopen/fgets/fprintf plus the strtok parsing pattern before that milestone starts.

## Dependencies

foundation-01 (strings), foundation-02 (arrays).

## Minimal Concepts

- **Write mode**: `fopen(path, "w")` on an EXISTING file truncates it to empty first. `"r"` reads; NULL return means missing file.
- **Write a line**: `fprintf(f, "%s|%d\n", name, age);` then `fclose(f)`.
- **Read back**:
  ```c
  char line[256];
  while (fgets(line, sizeof(line), f)) {   // one line per call, keeps '\n'
      char *tok = strtok(line, "|");       // 1st call: pass the line
      while (tok) {
          printf("[%s]\n", tok);           // each |-separated field in turn
          tok = strtok(NULL, "|");         // later calls: pass NULL
      }
  }
  ```
- `strtok` modifies the buffer in place (replaces `|` with `\0`) — parse a copy if you need the original.
- Numbers come back as strings: convert with `atoi`.

## Small Example

```c
#include <stdio.h>
#include <string.h>

int main() {
    FILE *f = fopen("demo.txt", "w");
    fprintf(f, "alice|30\nbob|25\n");
    fclose(f);

    f = fopen("demo.txt", "r");
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = '\0';
        char *name = strtok(line, "|");
        char *age = strtok(NULL, "|");
        if (name && age) printf("%s will be %d\n", name, atoi(age) + 1);
    }
    fclose(f);
    return 0;
}
```

## Hands-on Exercise

f03-a01: Write a program that saves two `name|age` records to a file, then reads them back into two struct instances and prints them. Then delete the file and run again — your program must not crash when fopen returns NULL.

## Exit Criteria

- The round-trip prints identical data;
- You can explain what strtok's NULL argument means and why atoi(NULL) must be avoided;
- Missing file is handled without crashing.

## Project Bridge

This IS the mechanism of `data_mgr.c::loadData/saveData`, used by milestone-03 and extended to borrows in milestone-05. required_by: milestone-03.

## Not Learning Yet

Binary files, fseek/ftell, CSV escaping rules, error codes beyond NULL-check.

```
evidence: code_evidence
source: data_mgr.c::saveData
rationale: The unit's mechanism mirrors this mature-code location.
```

## Completion Decision

(not started)

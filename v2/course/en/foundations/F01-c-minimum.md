---
artifact_id: foundation-01
language: en
---

# Foundation Unit

foundation_id: foundation-01
competency_id: language.c.structs-strings

## Why It Is Needed Now

Every book in this project is a struct with fixed-size char-array fields (`data_mgr.c::Book`). Before milestone-01 you must be able to define such structs, copy and compare their strings, and pass them around by index.

## Dependencies

None (first unit). Basic C syntax assumed from your earlier exposure — this is a refresh.

## Minimal Concepts

- **Struct with char arrays**:
  ```c
  struct Book {
      char id[20];
      char title[100];
      int quantity;
  };
  struct Book b;            // one instance
  struct Book books[1000];  // array of instances
  ```
- **String copy**: `strcpy(dst, src)` — copies including the terminating `'\0'`.
- **String compare**: `strcmp(a, b)` returns 0 when equal. Equality test is `== 0`, not `== 1`.
- **Length**: `"B001"` occupies 6 bytes — 4 chars + hidden `'\0'` terminator. Every string needs room for it.
- **Strip newline after fgets**: `s[strcspn(s, "\n")] = '\0';`

## Small Example

```c
#include <stdio.h>
#include <string.h>

int main() {
    struct Book b;
    strcpy(b.id, "B001");
    strcpy(b.title, "C Programming");
    b.quantity = 3;

    if (strcmp(b.id, "B001") == 0)
        printf("match: %s, qty=%d\n", b.id, b.quantity);
    printf("id length = %zu\n", strlen(b.id));   // 4, buffer needs >= 5
    return 0;
}
```

## Hands-on Exercise

f01-a01: Define `struct Point {char name[20]; int x;}`. Create two instances with different names, print each with `printf("%s %d\n", ...)`, then write an if/else using `strcmp` that reports whether the names are equal.

## Exit Criteria

- The exercise compiles and prints correct output;
- You can say why the name buffer must be at least 6 for a 5-letter name.

## Project Bridge

Directly maps to `data_mgr.c::Book/BorrowRecord` field handling and the ID matching in `business.c::addBook`. required_by: milestone-01.

## Not Learning Yet

Dynamic memory (malloc/free), pointers to structs (`->`), string functions beyond strcpy/strcmp/strlen/strcspn/strstr.

```
evidence: code_evidence
source: data_mgr.c::Book
rationale: The unit's mechanism mirrors this mature-code location.
```

## Completion Decision

(not started)

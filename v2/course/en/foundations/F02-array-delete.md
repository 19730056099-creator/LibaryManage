---
artifact_id: foundation-02
language: en
---

# Foundation Unit

foundation_id: foundation-02
competency_id: language.c.arrays-pointers

## Why It Is Needed Now

This project keeps every book in one global array with a counter tracking "how many are real". Deleting a book is not punching a hole — it shifts all later elements left by one. This is the core mechanic of milestone-01/02.

## Dependencies

foundation-01 (structs and strings).

## Minimal Concepts

- **Struct array + counter**:
  ```c
  struct Item items[100];
  int count = 0;              // count is "number of valid elements", not array length
  items[count++] = new_item;   // append: use the index, then increment
  ```
- **Index access**: `items[i].quantity`; iterate with `for (int i = 0; i < count; i++)`.
- **Delete by shift**: move each element after the deleted one left by one, then decrement the counter:
  ```c
  for (int i = idx; i < count - 1; i++) {
      items[i] = items[i + 1];   // structs assign wholesale
  }
  count--;
  ```

## Small Example

```c
#include <stdio.h>

int main() {
    int a[5] = {10, 20, 30, 40, 50};
    int count = 5;

    int idx = 1;                     // delete 20
    for (int i = idx; i < count - 1; i++) {
        a[i] = a[i + 1];
    }
    count--;

    for (int i = 0; i < count; i++) printf("%d ", a[i]);  // 10 30 40 50
    return 0;
}
```

## Hands-on Exercise

f02-a01: Convert the example to structs — 3 `struct Point {char name[20]; int x;}`, delete the middle one, print remaining names. Then reason: if you delete the LAST element, how many loop iterations run? (Answer: zero — only `count--`.)

## Exit Criteria

- The exercise prints the correct remaining elements in order;
- You can explain why the loop bound is `count - 1`, not `count`.

## Project Bridge

This is the entire mechanism of milestone-02's `deleteBook` (see `business.c::deleteBook`) and underpins linear lookup in `findBookIndex`. required_by: milestone-01, milestone-02.

## Not Learning Yet

Pointer arithmetic, the equivalence of `items[i]` and `*(items+i)`, linked lists — static arrays suffice; pointer details come when needed.

```
evidence: code_evidence
source: business.c::deleteBook
rationale: The unit's mechanism mirrors this mature-code location.
```

## Completion Decision

(not started)

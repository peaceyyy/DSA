# DSA Journal

2025-10-27 00:00

Stripped kernel:

- Use unsigned machine words for bit-level control data; reconcile 1-based IDs (user-facing) with 0-based array indexing to avoid off-by-one bit shifts.

Pseudocode:

- initClearances(keys[], n): for i in 0..n-1 keys[i] = 0u
- grantAccess(keys, id, chamber): keys[id - 1] |= (1u << chamber)   // id -> 0-based index; use unsigned shift
- revokeAccess(keys, id, chamber): keys[id - 1] &= ~(1u << chamber)
- checkAccess(keys, id, chamber): return (keys[id - 1] & (1u << chamber)) != 0

Reference / solution file:

- Story Problems/quantumAccessPanel.c

Complexity:

- Bit operations: O(1) time per op, O(1) extra space. Printing all keys is O(n * WORD_SIZE).

Study lines:

- Use unsigned types (e.g., `unsigned int`, `unsigned`, `uint16_t`) whenever the problem states the word is unsigned — signedness changes shifts and comparisons and caused my bugs.
- Be explicit about bit indexing: a chamber number maps to a bit position; ensure you shift the correct amount and use `id - 1` when scientist numbering starts at 1.
- Print routines should use the same mapping (index-to-id) as your access functions to avoid offset confusion.
- Quick check tip: when debugging bit masks, print numeric value in decimal and binary to confirm which bit flipped.

Reflection question:

- How will you systematically check other modules for signedness and off-by-one indexing before running tests?

Tags: [Computer Word] [Bitwise] [Indexing] [StoryProblem]

Extra: XOR (^)

- Definition: Exclusive OR — true when exactly one input is true. Applied per-bit for integers.
- Truth table (A ^ B): 0^0=0, 0^1=1, 1^0=1, 1^1=0.
- Useful properties: commutative, associative, identity a^0=a, self-inverse a^a=0 (useful for toggling).
- Implementations:
  - Boolean form (single-bit): (a && !b) || (!a && b)
  - Bitwise forms (full word): (x | y) & ~(x & y)  OR  (x & ~y) | (~x & y)
  - For booleans you can also use: a != b
- Caveats: Use unsigned types with bitwise ~ and shifts to avoid signedness/undefined behavior. Parenthesize expressions to avoid precedence mistakes.

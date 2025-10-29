```markdown
### Title: Dictionary Collision Handling - The Newline Anomaly

**Date:** 2025-10-29 14:30
Tags: [Dictionary] [Hashing] [VirtualHeap] [C] [Debugging]

**Stripped problem (1 line):** Implement a hash dictionary with a prime table and a separate virtual heap for synonym chaining, handling insert, delete, and find operations without duplicates.
**DS / Archetype:** Hash Table with Separate Chaining (Array-based Virtual Heap)

****Key Takeaways/Learnings:****
- Test case sensitivity to output formatting (e.g., missing `\n`) can mask fundamental algorithmic correctness.
- Prepending vs. appending in array-based linked lists can both be valid, depending on problem constraints.
- Strict adherence to problem notes (e.g., "otherwise leave as is" for links on deletion) is paramount, even if a more "optimal" strategy (like promotion) seems intuitive.

---

**Pseudocode:** (Refer to `dictionaryCollisionHandling.c` for full implementation details)

**Complexity:**
- **Insert:** O(1) average, O(N) worst-case (due to chain traversal)
- **Delete:** O(1) average, O(N) worst-case (due to chain traversal)
- **Find:** O(1) average, O(N) worst-case (due to chain traversal)
- **Space:** O(MAX) for both prime table and virtual heap.

**Edge cases:**
- Empty hash table.
- Full virtual heap.
- Element already exists (duplicate).
- Element not found.
- Deleting prime table element with/without synonyms.
- Deleting synonym from chain (first, middle, last).

**Study-note (journal-ready 1-3 lines):** Debugging output format (missing `\n`) can obscure correct logic; always verify exact output requirements. Prepending/appending in array-based chains are both valid, but strict adherence to problem-specific deletion rules (e.g., no promotion, leave links) is crucial for passing tests.

**Reflection Qs:**
- How would the complexity change if the virtual heap was dynamically resized?
- What are the trade-offs between marking as `DELETED` vs. physically removing and shifting elements in a closed hashing scheme?
- How would this implementation adapt to different hash functions or collision resolution strategies?

**Process Notes:**
Initial `insertAuto` had a `found` flag logic error for prime table duplicates. `deleteAuto` initially implemented synonym promotion, which violated problem notes ("otherwise leave as is" for prime table links if synonyms exist). The final fix for hidden test cases was a missing `\n` in an `printf` statement, highlighting the importance of exact output matching.
```
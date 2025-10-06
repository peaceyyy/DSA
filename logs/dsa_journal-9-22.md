# 📘 DSA Journal

This file logs my Data Structures & Algorithms practice.
Format is consistent for easy review and search.

---

### Title: Chess Tournament Multi-Criteria Sorted Insertion

**Date:** 2025-09-22 12:30
**Tags:** [Array] [SortedInsertion] [MultiCriteria] [Structs]

**Stripped problem (1 line):** Insert players into array maintaining sorted order by wins (desc), rating (desc), name (asc).
**DS / Archetype:** Sorted Array with Custom Comparator

**Pseudocode:**

```
1. Create new player struct
2. Find insertion position using wins comparison
3. Shift existing elements right
4. Handle tie-breaking (rating, then name)
5. Insert and increment count
```

**C snippet / Path:**

```c
// Path: Story Problems/chess_tournament_ranking.c
// Key insight: strcpy() for arrays, not assignment
// Multi-level if-else for tie-breaking logic
```

**Complexity:** Time = O(n), Space = O(1)

**Edge cases:** Empty tournament, duplicate wins/ratings, alphabetical ordering

**Study-note (journal-ready 1-3 lines):**

> Problem reading took 5+ minutes - need faster story → DSA kernel translation.
> Struct creation was missed initially. Multi-criteria sorting requires careful if-else ordering.

**Reflection Q:** How can I reduce story problem analysis time from 5min to <2min?

- Immediately find the essential terms
- Practice recognizing common patterns like in cubing (keywords, i guess)

---

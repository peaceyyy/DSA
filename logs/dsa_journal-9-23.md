# 📘 DSA Journal

This file logs my Data Structures & Algorithms practice.
Format is consistent for easy review and search.

---

### Title: Update Player Wins with Re-ranking

**Date:** 2025-09-23 14:45
**Tags:** [Array] [SearchAndUpdate] [DeleteAndInsert] [Optimization][PseudoCode][Shifting]

**Stripped problem (1 line):** Find player by name, update wins, remove from current position, reinsert maintaining sorted order.
**DS / Archetype:** Array Search-Update-Reposition

**Pseudocode:**

```
1. Single traversal: find current position AND new position simultaneously
2. Store player in temp, update wins  
3. Delete from current position (shift left)
4. Insert at new position (shift right)
5. Handle edge case: no position change
```

**Complexity:** Time = O(n), Space = O(1)

**Edge cases:** Player not found, same position (no movement), new lowest rank

**Study-note (journal-ready 1-3 lines):**

> Pseudocode-first approach: 30-35min total but faster implementation phase.
> Discovered single-traversal optimization using OR condition.
> Trade-off: upfront planning time vs faster coding execution.

**Reflection Q:** Is pseudocode-first worth the time investment for exam scenarios, or should I reserve it for complex problems only?

- Depends if the problems leans towards more a narrative
  - Turn synonyms into DSA terms or in code language (remove -> delete -> shift left from index)
  - Just don't comment on the obvious stuff

**Exam Pseudocode Strategy:**

- **Always pseudocode:** Multi-step algorithms, 3+ edge cases, when unsure of next step
- **Skip pseudocode:** Single operations, pure syntax translations, when solution is instantly clear
- **60-second rule:** Mental pseudocode first, write only if you can't see past step 2
- **1-line anchors:** Use brief comment roadmaps instead of full pseudocode when coding urge hits
- **Red flags to stop and pseudocode:** Pausing mid-typing, backspacing blocks, missed edge cases

**Story Problem Approach:**

- **Story → DSA translation time:** Target <2min (currently 5min)
- **Keyword extraction:** Focus on action verbs (insert, maintain, update) and data constraints
- **Narrative filtering:** Strip characters/context, keep only algorithmic requirements
- **Pattern recognition:** Link story elements to known DSA archetypes quickly

**Process Notes:**

- Pseudocode as comments before coding helped translate logic directly
- Edge case awareness improved (newPos = -1 issue caught late)
- Combined search optimization discovered mid-implementation

---

# DSA Learning Journal (Dictionaries)

Personal study notes and problem-solving sessions for Data Structures and Algorithms course.

---

## 2025-10-03 09:30

**Topic:** Closed Hashing V3 - Delete & isMember Functions
**Complexity:** O(1) avg, O(n) worst for both operations
**Archetype:** Dictionary ADT with collision resolution via synonym chains
**Tags:** [ClosedHashing] [DeleteFunction] [IsMember] [SynonymChains] [DeletedNodes] [PointerToPointer] [ExamPrep] [VariableConfusion] [LinearProbing] [CopyPasteBug]

### DSA Kernel

Given dictionary with closed hashing, implement delete and membership check with proper DELETED node handling.

### Key Takeaways

• **isMember**: Check EMPTY first, traverse full chain, validate both `trav != -1` AND `data != DELETED`
• **Delete home position**: Move synonym up if exists, else mark DELETED
• **Delete synonym**: Use pointer-to-pointer to unlink and return to avail
• **Story trap**: "Check enrollment" = isMember, "Remove student" = delete
• **Debug tip**: Don't confuse index (`trav`) with data (`D.Nodes[trav].data`)

### Pattern Recognition

Always handle DELETED nodes as "logically removed but structurally present"

### Implementation Notes

```c
// Safe isMember pattern
return (trav != -1 && D.Nodes[trav].data != DELETED) ? 1 : 0;
```

**Reflection:** What happens when searching for an element in a chain where the home position is DELETED but synonyms exist?

## 2025-10-03 10:15

**Topic:** My own Closed Hashing Implementation - Copy/Paste Variable Bug
**Context:** First personal implementation with linear probing

### Critical Bug Pattern

**⚠️ Copy/paste hazard:** When copying loop structures, `hashValue` and `temp` are often identical initially, leading to accidental use of `hashValue` instead of `temp` in loop conditions.

**Example:**

```c
// WRONG: checks home position repeatedly
for (temp = hashValue + 1; flag == 0 && temp != hashValue; temp = (temp + 1) % MAX){
    if (strcmp(D[temp], name) == 0) { found = 1; flag = 1; }
    else if (strcmp(D[hashValue], EMPTY) == 0) { flag = 1; }  // ← BUG HERE
}

// CORRECT: checks current probe position
else if (strcmp(D[temp], EMPTY) == 0) { flag = 1; }
```

### Exam Strategy

• **Variable discipline:** Always use loop variable (`temp`) inside loop, never initial value (`hashValue`)
• **Search length formula:** `(currentPos - hashValue + MAX) % MAX + 1`
• **Flag pattern:** Use `found` + `stopFlag` to avoid breaks while maintaining readability

**Pattern:** In linear probing, the probe variable (`temp`) should be used consistently throughout the loop body.

---

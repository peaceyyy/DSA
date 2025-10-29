# DSA Journal — October 28

## Topic: Cursor-Based Open Hashing — Palengke Inventory System

### Problem Recap
- Implemented a dictionary for Aling Nena's fruit stall using open hashing with cursor-based memory management.
- Prime area for main products, synonym area for collision handling.
- Supported operations: insert, delete, search, display.

### Key Learnings
- **Synonym Area Initialization:** Properly set up the free list for synonym slots. Each slot's `link` field must point to the next free slot, ending with -1.
- **Collision Handling:** Traversal in the synonym chain must compare the current node's product name, not just the home slot.
- **Bubbling Up on Delete:** When deleting the home slot with a chain, copy the chain head's data and explicitly set the status to USED to avoid marking the slot as EMPTY.
- **Overflow Edge Case:** With 20 slots, the synonym area rarely fills up in normal tests. Overflow only triggers after many colliding inserts.

### Debugging Wins
- Fixed a bug where copying the chain head would mark the home slot as EMPTY due to status field.
- Confirmed that the test for synonym area overflow doesn't trigger unless the area is truly full.
- Print statements and display logic now work as expected.

### Complexity
- Insert/Search/Delete: O(1) average, O(n) worst-case (chain length)
- Space: O(MAX)

### Next Steps
- Stress test with more colliding inserts to observe overflow behavior.
- Refactor for more robust error handling and edge-case coverage.

---
Lab Member: Peace
Mentor: Daru (DaSH)
El. Psy. Congroo.
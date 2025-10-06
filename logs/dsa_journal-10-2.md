# DSA Learning Journal (Variation 3 Dictionary)

*Tracking progress in Data Structures & Algorithms*



---

**Tags:** [OpenHashing] [ComplementSearch] [CollisionChaining] [TwoSum] [CISCode] [EdgeCases] [NegativeNumbers] [HashCollisions] [NullPointerCheck] 

=== Closed Hashing Variation 3: Synonym Chaining ===
Date: 2025-10-02 14:30

**Core Concept:** Fixed array split into prime area (direct hash) + synonym area (collision overflow)
**Architecture:** Prime slots act as chain heads, synonyms linked via cursor-based allocation
**Collision Strategy:** Insert-first chaining - new collisions become immediate successors
**Memory Model:** Two-zone design with free list management via `avail` pointer

**Key Optimizations Added:**

- Bounds checking: `D->avail != -1` (synonym space available)
- Duplicate prevention: `D->Nodes[hashval].data != x`
- Convention compliance: Avoiding early returns/breaks per university standards

**Complexity:**

- Insert: O(1) best, O(1) average (assuming low collision rate)
- Search: O(1) best, O(chain_length) worst
- Space: O(n) fixed allocation

**Pattern:** [ClosedHashing] [SynonymChaining] [CursorBased] [DictionaryV3] [LinkManagement] [AvailPointer] [InsertFirst] [CollisionResolution]

**Link Initialization Strategy:** Prime area links set to -1 only when occupied, not during init
**Next:** Debug isMember logic for no-return constraint compliance

=== Closed Hashing: Link Field Management ===
Date: 2025-10-02 14:45

**Question:** Why set `link = -1` during insert, not initialization?

**Answer:** **Semantic vs. Structural separation**

**During initialize():**

- Prime area: Only `data = EMPTY`, links undefined/garbage
- Synonym area: Links form free list chain (10→11→12→...→19→-1)

**During insert():**

- Prime slot gets `link = -1` to mark "end of chain"
- This happens **only when slot becomes occupied**

**Why this matters:**

- Empty slots don't need valid links (they're not part of any chain)
- Only occupied prime slots need `link = -1` to terminate their synonym chains
- Synonym area links are pre-chained for allocation purposes

**Memory efficiency:** Don't initialize what you don't need until you need it

---

## SESSION BREAK: CISCODE

---

=== Two-Sum CISCode Problem: The Edge Case Detective Story ===
Date: 2025-10-02 15:15

**The Mystery:** Given an array and target sum, find two indices whose elements add up to the target using open hashing with collision chaining.

**Initial Confusion:** Started questioning why we needed open hashing at all when Python dictionaries make this trivial. The lightbulb moment came when realizing that C's fixed hash table size (MAX=31) with arbitrary input numbers creates inevitable collisions that need proper handling.

**The Journey of Bugs:**

1. **Field Identity Crisis** - Got completely tangled up between `key` (the actual array value), `val` (the array index), and the hash slot number. Kept mixing them up in comparisons.
2. **The Null Pointer Trap** - Forgot the golden rule of C: always check if a pointer is NULL before dereferencing. Was trying to access `twoSumHashMap[hash]->key` when the slot might be empty.
3. **The Wrong Comparison Saga** - Spent way too long comparing the hash value to the stored key instead of comparing the complement value to the stored key. Classic case of overthinking the problem.

**The Edge Case That Almost Got Away:	**
Negative numbers! The hash function converts negatives to positives, meaning -5 and +5 both hash to slot 5. This creates intentional collisions that the chaining logic had to handle correctly. Tested with arrays like `[-1, -2, -3]` to make sure the traversal logic works.

**Final Algorithm That Works:**

```
For each number in the array:
  Calculate what its complement should be (target - current_number)
  Hash the complement to find which slot to check
  
  If that slot has entries:
    Walk through the collision chain looking for exact complement match
    If found: return the stored index and current index
  
  If not found:
    Insert current number with its index into the hash table
```

**What I Learned for Exams:**

- Edge cases aren't random - they follow patterns (boundaries, duplicates, negatives, overflows)
- Always trace through collision scenarios manually, don't just assume they work
- In hash problems, be crystal clear about what you're storing vs what you're searching for
- The "check first, then insert" pattern is powerful for complement-finding problems

**Complexity:** Time O(n) average case, O(n²) worst case | Space O(n)


**Reflection:** The debugging process taught me more about systematic edge case hunting than just getting the right answer. Next time I'll categorize potential edge cases upfront instead of discovering them through failed test cases.

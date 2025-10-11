# DSA Study Notes - October 9, 2024
## Priority Queues & Heap Operations - Introduction

---

## 🎯 **Key Concepts Learned Today**

### **1. Heap Operations Overview**
- **Heapify**: Convert array into heap structure (maintains POT property)
- **Insert POT**: Add element and sift-up to maintain heap
- **Delete Min/Max**: Remove root, replace with last element, sift-down
- **HeapSort**: Use heap operations to sort array

### **2. Two Core Movement Patterns**
| Operation | Direction | When Used | Starting Point |
|-----------|-----------|-----------|----------------|
| **Sift-Up** (Insert POT) | ↑ Leaf → Root | Adding new element | Last position |
| **Sift-Down** (Heapify) | ↓ Root → Leaf | Fixing violations | Any parent node |

---

## 🔧 **Critical Implementation Details**

### **Parent-Child Index Formulas** (0-based indexing)
```c
// Given parent at index i:
leftChild = (i * 2) + 1
rightChild = (i * 2) + 2

// Given child at index i:
parent = (i - 1) / 2
```

### **Last Parent Formula**
```c
lastParentIndex = (lastNdx - 1) / 2
```
**Why this works**: Parent of last element is the rightmost parent in the tree.

---

## 📝 **Heapify Algorithm (Bottom-Up Approach)**

### **Key Insight**: Process parents from **leaves toward root**
```c
// Shane's MinHeapify approach:
for (parentNdx = (H->lastNdx - 1) / 2; parentNdx >= 0; parentNdx--) {
    // Sift-down each parent to correct position
}
```

**Why bottom-up?**
1. Leaf nodes are already valid heaps (trivially)
2. Each parent assumes children are already heapified  
3. By root, entire tree satisfies heap property

---

## 🎪 **The "Follow the Element" Pattern**

### **Critical Understanding**: After swapping, track where the displaced element goes
```c
// After swap in sift-down:
currentNdx = smallestNdx;  // Follow the element to its new position
```

**Without this**: Algorithm checks same position repeatedly instead of following element down the tree.

---

## 🚨 **Common Pitfalls & Solutions**

### **1. Bounds Checking**
**Problem**: Accessing non-existent children
```c
// Safe approach (if-else-if structure):
if (leftChildNdx <= lastNdx && rightChildNdx <= lastNdx) {
    // Both children exist - find smaller
} else if (leftChildNdx <= lastNdx) {
    // Only left child exists
} else {
    // No children - current is smallest
}
```

### **2. Break Conditions**
```c
if (smallestNdx == currentNdx) {
    break; // Element is in correct position
}
```
**When this happens**: Node is smaller than all children OR is a leaf node.

---

## 📋 **Code Snippets for Reference**

### **Min-Heap Sift-Down (Shane's approach)**
```c
while (1) {
    int smallestNdx = currentNdx;
    int leftChildNdx = 2 * currentNdx + 1;
    int rightChildNdx = 2 * currentNdx + 2;
    
    // Find smallest among parent and children
    if (leftChildNdx <= H->lastNdx && H->Elem[leftChildNdx] < H->Elem[smallestNdx]) {
        smallestNdx = leftChildNdx;
    }
    if (rightChildNdx <= H->lastNdx && H->Elem[rightChildNdx] < H->Elem[smallestNdx]) {
        smallestNdx = rightChildNdx;
    }
    
    // If parent is already smallest, done
    if (smallestNdx == currentNdx) {
        break;
    }
    
    // Swap and continue from new position
    swap(H->Elem[currentNdx], H->Elem[smallestNdx]);
    currentNdx = smallestNdx;
}
```

### **Max-Heap Sift-Up (Insert POT)**
```c
while (childNdx > 0 && H->Elem[childNdx] > H->Elem[parentNdx]) {
    swap(H->Elem[parentNdx], H->Elem[childNdx]);
    childNdx = parentNdx;
    parentNdx = (childNdx - 1) / 2;
}
```

---

## 💡 **Key Realizations**

### **Delete = Replace + Heapify**
1. **Replace root** with last element (maintains complete tree)
2. **Heapify from root** to restore heap property
3. The "heapify from root" is exactly sift-down operation

### **HeapifySubtree Purpose**
- **Single-level**: Fix immediate parent-child relationship
- **Complete subtree**: Ensure entire subtree satisfies heap property (recursive/iterative sift-down)
- Most practical use cases need the complete approach

---

## 🔄 **Next Session Topics**
- [ ] Implement own heapifySubtree function (both recursive and iterative)
- [ ] Build complete priority queue with insert/delete operations
- [ ] HeapSort implementation and analysis
- [ ] Boundary condition edge cases and testing

---

## 📊 **Complexity Summary**
| Operation | Time | Space | Notes |
|-----------|------|-------|-------|
| Insert POT | O(log n) | O(1) | Sift-up from leaf |
| Delete Min/Max | O(log n) | O(1) | Sift-down from root |
| Heapify Array | O(n) | O(1) | Bottom-up approach |
| HeapSort | O(n log n) | O(1) | n deletions |

---

## 🎯 **Reflection Question**
Why is the iterative approach with "follow the element" pattern equivalent to the recursive heapifySubtree calls? How do both ensure the displaced element reaches its final correct position?

---
*Study session focused on understanding core heap mechanics and Shane's implementation patterns. Next: hands-on implementation and edge case handling.*
typedef struct {
    int taskId;
    int priority;
    int deadline;
} Task;

// Insert task with priority consideration
void scheduleTask(minHeap *H, Task task) {
    /*
    PSEUDOCODE:
    calculate effective priority (consider deadline urgency)
    insert based on effective priority
    handle tie-breaking rules
    */
    
    // Your implementation here
}


typedef struct {
    minHeap maxHeap; // for smaller half (use negative values)
    minHeap minHeap; // for larger half
} MedianFinder;

void addNumber(MedianFinder *mf, int num) {
    /*
    PSEUDOCODE:
    IF both heaps empty OR num <= current median THEN
        add to max heap (smaller half)
    ELSE
        add to min heap (larger half)
    balance heaps if size difference > 1
    */
    
    // Your implementation here
}

int getMedian(MedianFinder *mf) {
    /*
    PSEUDOCODE:
    IF heap sizes equal THEN
        return average of both tops
    ELSE
        return top of larger heap
    */
    
    // Your implementation here
}

typedef struct {
    int playerId;
    int score;
    int lives;
} Player;

// Process tournament round with elimination rules
void processRound(minHeap *winners, minHeap *losers, Player players[], int count) {
    /*
    PSEUDOCODE:
    FOR each match pair DO
        winner goes to winners heap
        IF loser still has lives THEN
            decrement lives, add to losers heap
        ELSE
            eliminate player
    */
    
    // Your implementation here
}
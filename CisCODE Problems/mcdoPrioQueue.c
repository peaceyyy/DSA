    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define MAX 20

    typedef struct {
        char *meals[10];
        char *drinks[10];
        char *sides[10];
    }PRODUCT;

    typedef struct {
        int orderNumber;
        PRODUCT items;
    }ORDER;

    typedef struct {
        ORDER *orderQueue;
        int last;
    }QUEUE;


    QUEUE* initializeQueue(){

        QUEUE* Q = (QUEUE* ) malloc(sizeof(QUEUE));
        Q->last = 0;
        Q->orderQueue = malloc(sizeof(ORDER) * MAX);

        return Q;   
    }

    void swap(ORDER *a, ORDER *b){
    ORDER temp = *a;
    *a = *b;
    *b = temp;
    
    }

    void priorityHeapifyDown(QUEUE **PrioQueue, int root){

    int curr = root;

    while ((curr * 2) + 1 < (*PrioQueue)->last)
    {
            int smallest = curr;
            int LC = (curr * 2) + 1;
            int RC = (curr * 2) + 2;

            if (LC < (*PrioQueue)->last &&  (*PrioQueue)->orderQueue[LC].orderNumber < (*PrioQueue)->orderQueue[smallest].orderNumber) smallest = LC;
            if (RC < (*PrioQueue)->last &&  (*PrioQueue)->orderQueue[RC].orderNumber <  (*PrioQueue)->orderQueue[smallest].orderNumber) smallest = RC;
            
            if (curr != smallest)
            {
            swap(&(*PrioQueue)->orderQueue[curr], &(*PrioQueue)->orderQueue[smallest]);
            curr = smallest;
            }  else {
            break;
            }
        }
    }

    void createQueue(QUEUE **PrioQueue, ORDER samples[], int size){
        //inserting all orders into array initially
        //---dont touch---
        for(int i=0;i<size;i++)
            (*PrioQueue)->orderQueue[i] = samples[i];
        (*PrioQueue)->last = size-1;


        //minHeapify the entire queue tree
        for (int i = ( (*PrioQueue)->last / 2 ) - 1; i >= 0; i--) priorityHeapifyDown(PrioQueue, i);
    }

    void priorityHeapifyUp(QUEUE **PrioQueue, int index){

        int curr = index;
        while (curr > 0)
        {
        int parent = (curr - 1)/2; 

        if ((*PrioQueue)->orderQueue[parent].orderNumber > (*PrioQueue)->orderQueue[curr].orderNumber)
        {
            swap(&(*PrioQueue)->orderQueue[parent], &(*PrioQueue)->orderQueue[curr]);
            curr = parent; 
            
        } else {

            break;
        }
        
        }
    }

    void enqueueOrder(QUEUE **PrioQueue, ORDER newOrder){
        if((*PrioQueue)->last == MAX){ //check full
            printf("Order Queue is full!");
            return;
        }
        
        for(int i = 0; i < MAX; i++){  //check duplicate
            if((*PrioQueue)->orderQueue[i].orderNumber == newOrder.orderNumber){
                printf("! --- DUPLICATE order number [%d] found. Please retry order --- !\n", newOrder.orderNumber);
                printf("...Failed to enqueue order [%d]\n", newOrder.orderNumber);
                return;
            } }

    
        (*PrioQueue)->orderQueue[(*PrioQueue)->last++] = newOrder;
        priorityHeapifyUp(PrioQueue, (*PrioQueue)->last);
    }


    ORDER dummy = {-1, {{"-"}, {"-"}, {"-"}}};

    ORDER dequeueOrder(QUEUE **PrioQueue){

        ORDER nextOrder = (*PrioQueue)->orderQueue[--(*PrioQueue)->last];
    
        if((*PrioQueue)->last == 0){
            printf("Queue is empty");
            return dummy;
        }
        
        return nextOrder;
    }
    void displayQueue(QUEUE *PriorityQueue){
        //check empty
        
        if((PriorityQueue)->last == 0){
            printf("Queue is empty");
        
        }
        for(int i=0;i<=PriorityQueue->last;i++){
            printf("\n\n[%d] OrderNumber:", PriorityQueue->orderQueue[i].orderNumber);
            printf("\n  Meals - ");
            for(int j=0;PriorityQueue->orderQueue[i].items.meals[j] != NULL;j++)
                printf("%s, ", PriorityQueue->orderQueue[i].items.meals[j]);
            printf("\n  Drinks - ");
            for(int j=0;PriorityQueue->orderQueue[i].items.drinks[j] != NULL;j++)
                printf("%s, ", PriorityQueue->orderQueue[i].items.drinks[j]);
            printf("\n  Sides - ");
            for(int j=0;PriorityQueue->orderQueue[i].items.sides[j] != NULL;j++)
                printf("%s, ", PriorityQueue->orderQueue[i].items.sides[j]);
        } printf("\n_________________________________________________________________________ END\n\n");
    }
    int main(){
        QUEUE *PreparingQueue = initializeQueue();
        QUEUE *ServingQueue = initializeQueue();
    
        ORDER sampleOrders[] = {
            {6, {{"Chicken", "Spicy Chicken"}, {"Coke Zero"}, {"Sundae"}}},
            {3, {{"Chicken Curry", "6pc Bucket"}, {"Sprite", "Iced Tea"}, {"Matcha McFlurry"}}},
            {1, {{"Ala King", "Spicy Chicken"}, {"Coke Zero"}, {"Chicken Sandwich"}}},
            {13, {{"Chicken Fillet", "Ala King"}, {"Ice Tea", "Coke"}, {"Oreo McFlurry"}}},
            {5, {{"8pc Bucket", "6pc Bucket"}, {"Coke", "Royal"}, {"Small Fries"}}},
            {7, {{"Original Chicken", "Spicy Chicken"}, {"Sprite", "Iced Tea"}, {"Large Fries"}}},
            {13, {{"Ala King", "Burger Steak"}, {"Coke", "Sprite"}, {"Deluxe Burger"}}},
            {10, {{"Burger Steak", "Chicken Fillet"}, {"Royal", "Sprite"}, {"Sundae"}}},
            {9, {{"Ala King", "Burger Steak"}, {"Coke Zero", "Iced Tea"}, {"Matcha McFlurry"}}},
            {16, {{"Burger Steak", "Spicy Chicken"}, {"Royal", "Sprite"}, {"Small Fries"}}},
            {2, {{"Original Chicken", "Burger Steak"}, {"Royal", "Iced Tea"}, {"Large Fries"}}},
            {12, {{"Ala King", "Chicken Fillet"}, {"Coke", "Coke Zero"}, {"Medium Fries"}}},
            {11, {{"6pc Bucket", "Original Chicken"}, {"Coke", "Sprite"}, {"Sundae"}}},
            {14, {{"Spicy Chicken", "8pc Bucket"}, {"Royal", "Coke"}, {"Sundae"}}},
            {4, {{"Original Chicken", "6pc Bucket"}, {"Coke Zero"}, {"Oreo McFlurry"}}},
        };
        int sampleSize = sizeof(sampleOrders)/ sizeof(ORDER);

        int choice;
        printf("\n\n<-----ENTER CHOICE---->\n");
        printf("Case 1. Initial Preparing Queue\nCase 2. Enqueue New Entries\nCase 3. Enqueue Duplicate Entry\nCase 4. Dequeue Preparing Order to Serving Queue\nCase 5. Dequeue Serving Queue\nCase 6. Dequeue and Display Empty\n");
        printf("\nEnter choice: ");
        scanf("%d", &choice);


        switch(choice){
            case 1: 
                createQueue(&PreparingQueue, sampleOrders, sampleSize);
                printf("\n\n-----PREPARING QUEUE (initial heapified)-----");
                displayQueue(PreparingQueue);
                break;
            case 2: 
                createQueue(&PreparingQueue, sampleOrders, sampleSize);
                printf("\n\n-----PREPARING QUEUE (initial heapified)-----");
                displayQueue(PreparingQueue);
                ORDER newOrder1 = {8, {{"Mushroom Soup", "Chicken Katsu"}, {"Root Beer"}, {"Apple Pie"}}};
                ORDER newOrder2 = {15, {{"Chicken Katsu", "Burger Steak", "6pc Bucket", "Ala King"}, {"Royal", "Sprite", "Root Bear"}, {"Apple Pie", "Matcha McFlurry", "Large Fries"}}};
                printf("\n\n---Enqueue to Preparing Queue---");
                enqueueOrder(&PreparingQueue, newOrder1);
                enqueueOrder(&PreparingQueue, newOrder2);
                printf("\n\n-----PREPARING QUEUE (enqueued new entries)-----");
                displayQueue(PreparingQueue);
                break;
            case 3: 
                createQueue(&PreparingQueue, sampleOrders, sampleSize);
                printf("\n\n-----PREPARING QUEUE (initial heapified)-----");
                displayQueue(PreparingQueue);
                ORDER newOrder3 = {8, {{"Chicken Curry"}, {"Miranda"}, {"Mango Pie"}}};
                ORDER newOrder4 = {6, {{"Ala King", "Original Chicken"}, {"Miranda", "Root Beer"}, {"Small Fries", "Sundae"}}}; //error duplicate
                ORDER newOrder5 = {15, {{"Chicken Katsu", "Burger Steak", "6pc Bucket", "Ala King"}, {"Royal", "Sprite", "Root Bear"}, {"Apple Pie", "Matcha McFlurry", "Large Fries"}}};
                printf("\n\n---Enqueue to Preparing Queue---");
                enqueueOrder(&PreparingQueue, newOrder3);
                enqueueOrder(&PreparingQueue, newOrder4);
                enqueueOrder(&PreparingQueue, newOrder5);
                printf("\n\n-----PREPARING QUEUE (enqueued new entries)-----");
                displayQueue(PreparingQueue);
                break;
            case 4: 
                createQueue(&PreparingQueue, sampleOrders, sampleSize);
                printf("\n\n-----PREPARING QUEUE (initial heapified)-----");
                displayQueue(PreparingQueue);
                printf("\n\n---Dequeue Preparing Queue---");
                ORDER servingOrder1 = dequeueOrder(&PreparingQueue);
                ORDER servingOrder2 = dequeueOrder(&PreparingQueue);
                printf("\n\n---Enqueue to Serving Queue---");
                enqueueOrder(&ServingQueue, servingOrder1);
                enqueueOrder(&ServingQueue, servingOrder2);
                printf("\n\n-----PREPARING QUEUE (updated)-----");
                displayQueue(PreparingQueue);
                printf("\n\n-----SERVING QUEUE-----");
                displayQueue(ServingQueue);
                break;
            case 5:
                createQueue(&PreparingQueue, sampleOrders, sampleSize);
                ORDER newOrder6 = {8, {{"Chicken Curry"}, {"Miranda"}, {"Mango Pie"}}};
                ORDER newOrder7 = {17, {{"Ala King", "Original Chicken"}, {"Miranda", "Root Beer"}, {"Small Fries", "Sundae"}}}; 
                ORDER newOrder8 = {15, {{"Chicken Katsu", "Burger Steak", "6pc Bucket", "Ala King"}, {"Royal", "Sprite", "Root Bear"}, {"Apple Pie", "Matcha McFlurry", "Large Fries"}}};
                printf("\n---Enqueue to Preparing Queue---");
                enqueueOrder(&PreparingQueue, newOrder6);
                enqueueOrder(&PreparingQueue, newOrder7);
                enqueueOrder(&PreparingQueue, newOrder8);

                printf("\n\n-----PREPARING QUEUE (updated)-----");
                displayQueue(PreparingQueue);

                printf("\n\n---Dequeue Preparing Queue---");
                ORDER servingOrder3 = dequeueOrder(&PreparingQueue);    
                ORDER servingOrder4 = dequeueOrder(&PreparingQueue);

                printf("\n\n---Enqueue to Serving Queue---");
                enqueueOrder(&ServingQueue, servingOrder3);
                enqueueOrder(&ServingQueue, servingOrder4);

                printf("\n\n-----SERVING QUEUE (updated)-----");
                displayQueue(ServingQueue);

                printf("\n\n---Dequeue Serving Queue---");
                ORDER receiveOrder1 = dequeueOrder(&ServingQueue);
                ORDER receiveOrder2 = dequeueOrder(&ServingQueue);

                printf("\n\n---Serving Finished Orders to Customers---\n");
                printf("RECEIVED AND SERVED order [%d]...\n", receiveOrder1);
                printf("RECEIVED AND SERVED order [%d]...\n", receiveOrder2);

                printf("\n\n-----SERVING QUEUE (dequeued)-----");
                displayQueue(ServingQueue);
                break;
            case 6:
                displayQueue(PreparingQueue);
                ORDER servingOrderX = dequeueOrder(&PreparingQueue);
                displayQueue(ServingQueue);
                ORDER receiveOrderX = dequeueOrder(&ServingQueue);
                break;
            default:
                printf("\n\n! ---- INVALID Choice ---- !\n\n");
        }
        return 0;
    }
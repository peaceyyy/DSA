    #include <stdio.h>
    #include <stdlib.h>

    #define MAX 31

    /*********************************/
    /*    USER-DEFINED DATA TYPES    */
    /*********************************/
    typedef struct node
    {
        int key; // index in array
        int val; // element value
        struct node *link;
    } *LIST;

    typedef LIST Dictionary[MAX];

    /*********************************/
    /*       HELPER FUNCTIONS        */
    /*********************************/
    void initDict(Dictionary D);

    /*********************************/
    /*          YOUR TASKS           */
    /*********************************/
    void insert(Dictionary D, int data, int index);
    int *twoSum(int *nums, int numsSize, int target, int *returnSize);
    int hash(int elem);

    int main(void)
    {
        int n, target;
        printf("Enter number of elements: ");
        scanf("%d", &n);

        int *nums = (int *)malloc(n * sizeof(int));
        printf("Enter the elements: ");
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &nums[i]);
        }

        printf("Enter target: ");
        scanf("%d", &target);

        int returnSize;
        int *result = twoSum(nums, n, target, &returnSize);

        if (result != NULL)
        {
            printf("Indices: [%d, %d]\n", result[0], result[1]);
            free(result);
        }
        else
        {
            printf("No solution found.\n");
        }

        free(nums);
        return 0;
    }

    /*********************************/
    /*       HELPER FUNCTIONS        */
    /*********************************/
    void initDict(Dictionary D)
    {
        for (int i = 0; i < MAX; i++)
        {
            D[i] = NULL;
        }
    }

    /*********************************/
    /*          YOUR TASKS           */
    /*********************************/
    void insert(Dictionary D, int data, int index)
    {

        int hashVal = hash(data);


        LIST newNode = (LIST)malloc(sizeof(struct node));
        newNode->val = index;
        newNode->key = data;
        newNode->link = NULL;

        // try to insert in home slot (head is NULL)
        if (D[hashVal] == NULL)
        {
            D[hashVal] = newNode;
        }
        else
        {

            LIST *trav;

            for (trav = &D[hashVal]; *trav != NULL; trav = &(*trav)->link)
            {
            };
            (*trav) = newNode;
        }
    }

    int *twoSum(int *nums, int numsSize, int target, int *returnSize)
    {

        int *indices = (int *)malloc(sizeof(int) * 2);
        int found = 0;

        Dictionary twoSumHashMap;
        initDict(twoSumHashMap);

        for (int i = 0; i < numsSize && found != 1; i++)
        {
            int complement = target - nums[i];
            int complementHash = hash(complement);  

            if (twoSumHashMap[complementHash] != NULL){

                if (twoSumHashMap[complementHash]->key == complement){
                    indices[0] = twoSumHashMap[complementHash]->val;
                    indices[1] = i;
                    found = 1; 
                } else {

                    LIST trav;

                    for (trav = twoSumHashMap[complementHash]; trav != NULL && trav->key != complement; trav = trav->link){};

                    if (trav != NULL)
                    {
                        indices[0] = trav->val;
                        indices[1] = i;
                        found = 1;
                    }
                }

            } else {
                insert(twoSumHashMap, nums[i], i);
            }


        }

        return (found != 0) ? indices : NULL;
    }



    int hash(int elem)
    {   
        if (elem < 0){
            elem *= -1;
        }
        int hash = elem % MAX;
        return hash;
    }

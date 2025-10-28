/*
Timeline Displacement
By Aldwin Miguel Fernandez

DSA
Categories:

None
Background:
A "Key Event" is an event that causes alterations across multiple timelines, and we may have just experienced one of the most widespread in this sector. All of the people in half of the timelines have been displaced in another timeline. At the time of writing, the cause of this Key Event is unknown.

Many organizations have been able to establish contact with parallel timelines previously thought not to exist, and it was ruled that the Key Event will not be prevented. Research to prevent the Key Event was already underway at this time, but was later scrapped due to the new ruling. 

The technology to travel across parallel timelines is still relatively new, and your research institute has just completed an "Event seeder" which is a device can simulate key events the effect of key event and their outcomes across multiple timelines, grouped into "Timeline Clusters".

As one of the first trained operators of the Event Seeder, you have been assigned to a research team who has found that if a singular "Anti-Key Event" is performed on each person across multiple timelines, the displacement caused by the Key Event can be corrected.

Your team has already managed to recreate the Key Event in a simulation, as well as several other possible outcomes of the Key Event with test clusters. Your task now is to program the Event Seeder such that it can produce a Timeline Cluster that will have everyone back in their correct timeline.

Requirements:
You are to make the following functions:

eve_key_anti() 
this function will perform the Anti-Key Event on the entity with the given id, and returns the code for its correct timeline in the timeline cluster.

tc_ent_seed_key_anti(timeline_cluster tc, ent_code id)
this function will run a simulation of the Anti-Key Event with the given id, and insert the entity in the correct timeline within the given cluster.

timeline_cluster tc_create_key_anti(timeline_cluster tc)
this function will produce a new Timeline Cluster based on the given cluster. It will seed each entity in the given cluster into the new one using the seed function running the Anti-Key Event, then return the new cluster.


Constraints:
Your team's research with the Key Event, as well as the functionality already provided in the Event Seeder, must not be modified.

The test run in the main() function must not be modified.

The Key Event test cluster must remain intact during the entire process, as any changes will cause an alteration of the past, which is grounds to put your entire team in stasis.
*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE_TC 10

typedef int ent_code;
typedef int tc_tl_code;

typedef struct node
{
    ent_code id;
    struct node* link;
}entity, *timeline;

typedef timeline *timeline_cluster;


//helper functions to use
timeline_cluster tc_create(); /*NOTE: each timeline in the returned cluster is already NULL*/
entity* ent_create(ent_code id); /*NOTE: link of the returned entity is a garbage value*/

void tc_readout(timeline_cluster tc);

//create the definition only for the following, do not change anything else
tc_tl_code eve_key_anti(ent_code id);

void tc_ent_seed_key_anti(timeline_cluster tc, ent_code id);

timeline_cluster tc_create_key_anti(timeline_cluster tc);

//DO NOT USE
void tc_test_eve_seed(timeline_cluster tc, int size);
void tc_destroy(timeline_cluster tl);


int main()
{
    int eventSeed;
    printf("Enter timeline cluster to test: ");
    scanf("%d", &eventSeed);
    srand(eventSeed);

    timeline_cluster test = tc_create();
    tc_test_eve_seed(test, 100);
    timeline_cluster testAnti = tc_create_key_anti(test);

    printf("\n\n--Test Results--\n");
    printf("\n--Key Event Test Cluster--\n");
    tc_readout(test);
    printf("\n--Anti-key Event Cluster--\n");
    tc_readout(testAnti);

    tc_destroy(test);
    tc_destroy(testAnti);
    return 0;
}


//helper functions to use
timeline_cluster tc_create() {return (timeline_cluster)calloc(SIZE_TC, sizeof(timeline));}
entity* ent_create(ent_code id)
{
    entity* newEnt = (entity*)malloc(sizeof(entity));
    newEnt->id = id;
    return newEnt;
}
void tc_readout(timeline_cluster tc)
{
    printf("\nTimeline Cluster Readout:\n");
    for(int tl = 0; tl < SIZE_TC; tl++)
    {
        printf("Timeline %d: ", tl);
        for(timeline tl_read = tc[tl]; tl_read != NULL; tl_read = tl_read->link)
        {
            printf("%d",tl_read->id);
            if(tl_read->link != NULL) {printf(", ");}
        }printf("\n");
    }
}

//create the definition only for the following, do not change anything else
tc_tl_code eve_key_anti(ent_code id) 
{
    return id % 10;
}

void tc_ent_seed_key_anti(timeline_cluster tc, ent_code id)
{
    int anti_key = eve_key_anti(id);
    entity* new_ent = ent_create(id);
    

     new_ent->link = (tc[anti_key]!= NULL) ? tc[anti_key] : NULL;
  
    
    tc[anti_key] = new_ent;

}

timeline_cluster tc_create_key_anti(timeline_cluster tc)
{
    timeline_cluster anti_timeline_cluster = tc_create(); 
    for (int i = 0; i < SIZE_TC; i++)
    {
        for (timeline trav = tc[i]; trav != NULL; trav = trav->link ){
            tc_ent_seed_key_anti(anti_timeline_cluster, trav->id);
        }
    }

    return anti_timeline_cluster;
  
}


//DO NOT USE
void tc_test_eve_seed(timeline_cluster tc, int numEnts)
{
    for(int i = 1; i <= numEnts; i++)
    {
        tc_tl_code newTlCode = (i % 2) ? i % 10: rand() % 10;

        entity* newEnt = ent_create(i);
        newEnt->link = tc[newTlCode];
        tc[newTlCode] = newEnt;
    }
}
void tc_destroy(timeline_cluster tc)
{
    for(int tl = 0; tl < SIZE_TC; tl++)
    {
        timeline del;

        while(tc[tl] != NULL)
        {
            del = tc[tl];
            tc[tl] = tc[tl]->link;
            free(del);
        }
    }
    free(tc);
}
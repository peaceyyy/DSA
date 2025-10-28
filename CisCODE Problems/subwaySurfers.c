//Started September 30
//Finished October 2 

// The solution came to me in a dream lollll

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void displayRoad(char trains[], unsigned char surfer);
void testCode(char trains[], int cases);
bool escapeAttempt(char trains[],unsigned char surfer, int* moves);
int *planEscape(char trains[], unsigned char surfer);

int main(){
    char trains[5];
    unsigned char surfer = 128;

    int testCase;
    printf("What test case would you like to try?\n");
    printf("1, 2, 3, 4, or 5?\n");
    scanf(" %d", &testCase);    
    
    testCode(trains, testCase);
      
    displayRoad(trains, surfer);

    int *moves;
    moves = planEscape(trains, surfer);
    printf("\nYour moves: ");
    for(int i = 0; i < 5; i++){
        printf("%d ", moves[i]);
    }

    printf(escapeAttempt(trains, surfer, moves) ?  "\nYou escaped!" : "\nOuch.");
    return 0;
}

int *planEscape(char trains[], unsigned char surfer){
    int *returnValue = malloc(sizeof(int)*5);
    int count = 0;
    
    for (int i = 0; i < 5; i++)
    {
      
        unsigned char complement =  ~(trains[i]);
        printf("\n--------------------\n");
        printf("\nCurrent surfer val: %d\n", surfer);
        printf("Current train val: %d\n\n", complement);
        int move = 0;

        if (surfer > complement){ //move right
        printf("we have to move right\n");
            while (surfer > complement){
                surfer >>= 1;
               printf("\nMoving surfer val to the right: %d\n", surfer);
                move++;
      
            }
        } else if (surfer < complement){ // move left
        printf("we have to move left\n");
            while (surfer < complement){
                surfer <<= 1;
                move++;

            }

            move *= -1;  // bcs we're moving left

        } else { // dont move
        printf("stay\n");
            move = 0;
        }
          printf("Current Move Count: %d\n", move);
        returnValue[count++] = move;
    }

    
    
    return returnValue;
}

void displayRoad(char trains[], unsigned char surfer){
    printf("\nSurfer:\n");
    for(int mask = 1<<7; mask; mask >>=1){
        printf("%d ", (surfer&mask) ? 1 : 0);
    }
    printf("\nThe Tracks Ahead:\n");
    for(int i = 0; i < 5; i++){
        for(int mask = 1<<7; mask; mask >>=1){
            printf("%d ", (trains[i]&mask) ? 1 : 0);
        }
        printf("\n");
    }
}

void testCode(char trains[], int cases){
    switch(cases){
        case 1:
            trains[0] = 247;
            trains[1] = 223;
            trains[2] = 254;
            trains[3] = 127;
            trains[4] = 253;
            break;
        case 2:
            trains[0] = 127;  
            trains[1] = 191;   
            trains[2] = 223;   
            trains[3] = 239;   
            trains[4] = 247;   
            break;
        case 3:
            trains[0] = 251;   
            trains[1] = 253;   
            trains[2] = 254;   
            trains[3] = 254;   
            trains[4] = 127;   
            break;
        case 4:
            trains[0] = 254;   
            trains[1] = 254;    
            trains[2] = 254;    
            trains[3] = 254;    
            trains[4] = 254;    
            break;
        case 5:
            trains[0] = 127; 
            trains[1] = 127; 
            trains[2] = 127; 
            trains[3] = 127; 
            trains[4] = 127; 
            break;
        default:
            break;
        }
}

bool escapeAttempt(char trains[],unsigned char surfer, int* moves){
    bool stat = true;
    printf("\n\nEscape Attempt:\n");
    for(int i = 0; i < 5 && stat; i++){
        if(moves[i] > 0){
            printf("\nSurfer shifts to the right %d %s", moves[i], (moves[i] >= 2) ? "times" : "time");
            surfer >>= moves[i];
        }else if(moves[i] < 0){
            printf("\nSurfer shifts to the left %d %s", -moves[i], (moves[i] <= 2) ? "times" : "time");
            surfer <<= -moves[i];
        }else{
            printf("\nSurfer doesn't change lanes");
        }

        printf("\nSurfer:\n");
        for(int mask = 1<<7; mask; mask >>=1){
            printf("%d ", (surfer&mask) ? 1 : 0);
        }
        printf("\nCurrent Track\n");
        for(int mask = 1<<7; mask; mask >>=1){
            printf("%d ", (trains[i]&mask) ? 1 : 0);
        }
        if((trains[i] & surfer || surfer == 0) != 0){
            stat = false;
            if(surfer == 0) printf("\nYou hit the walls.");
            else printf("\nYou hit a train.");
        } 
        printf("\n");
    }
    return stat;
}


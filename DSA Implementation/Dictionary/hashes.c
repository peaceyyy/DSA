#include <stdio.h>

int hashUnder19 (int elem){

    int temp = 0;

    while (elem > 0){

        temp += elem % 10;
        elem /= 10;
    
    }

    return temp % 19;
}

int hASCHII (char name[]){

    int asciiCount = 0, i = 0;

    while (name[i] != '\0')
    {
        asciiCount += name[i];
        i++;
    }

    return asciiCount % 49;

}
int main(){

    // printf("%d", hashUnder19(21));
    printf("\n");
    printf("%d", hASCHII("supercalifragilisticse"));

}
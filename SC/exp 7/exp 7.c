#include <stdio.h>
#include <stdlib.h>

float maxf(float a,float b){
    if(a>b){
        return a;
    }
    return b;
}

float minf(float a,float b){
    if(a<b){
        return a;
    }
    return b;
}

int main(int argc, char const *argv[])
{
    float *plane = malloc(5 * sizeof(float));
    float *train = malloc(5 * sizeof(float));

    for(int i = 0; i < 5; i++){
        printf("Enter plane fuzzy set data: ");
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int activation_function(float yin,float theta){
    if(yin > theta)
    {
        return 1;
    }
    else if((yin >= -1*theta) && (yin <= theta))
    {
        return 0;
    }
    else if (yin < theta)
    {
        return -1;
    }
}

float * step_calc(int step_num,int** vector,int* targets,int bias,float theta,int learning_rate,float* weights,int n)
{
    float yin = weights[0] * bias;
    for (int i = 1; i < n+1; i++)
    {
        yin = yin + (vector[step_num-1][i-1] * weights[i]);
    }
    int y = activation_function(yin,theta);
    // printf("Y after activation: %d\n",y);
    if(targets[step_num-1] == y)
    {
        return weights;
    }
    // printf("Y after activation: %d\n",y);
    weights[0] = weights[0] + (learning_rate*targets[step_num-1]);
    for (int i = 1; i < n+1; i++)
    {
        weights[i] = weights[i] + (learning_rate * targets[step_num-1] * vector[step_num-1][i-1]);
    }

    return weights;
}

int main()
{
    int n,vec,epoch,bias,learning_rate,threshhold;
    printf("Enter number of vectors: ");
    scanf("%d",&vec);
    printf("Enter number of elements per vector: ");
    scanf("%d",&n);
    int** vector = malloc(vec * sizeof(int *));
    for (int i = 0; i < vec; i++)
    {
        vector[i] = (int*)malloc(n * sizeof(int));
    }
    int* targets = malloc(vec * sizeof(int));
    float* weights = malloc((n+1) * sizeof(float));

    for (int i = 0; i < vec; i++)
    {
        printf("\nFor vector %d\n",i+1);
        for(int j = 0; j < n; j++)
        {
            printf("Enter element %d: ",j+1);
            scanf("%d",&vector[i][j]);
        }
        printf("Enter target for vector %d: ",i+1);
        scanf("%d",&targets[i]);
    }

    for (int i = 0; i < n+1; i++)
    {
        printf("Enter initial weight %d: ",i);
        scanf("%d",&weights[i]);
    }
    printf("Enter threshhold: ");
    scanf("%f",&threshhold);
    printf("Enter bias: ");
    scanf("%d",&bias);
    printf("Enter learning rate: ");
    scanf("%d",&learning_rate);
    printf("Enter number of epochs: ");
    scanf("%d",&epoch);

    for(int ep = 0;ep < epoch; ep++)
    {
        printf("\nEpoch %d\n",ep+1);
        for(int step = 1; step <= vec; step++)
        {
            weights = step_calc(step,vector,targets,bias,0.2,learning_rate,weights,n);
        }
        for (int i = 0; i < n+1; i++)
        {
            printf("Weight %d after epoch %d: %f\n",i,ep+1,weights[i]);
        }
    }


    // weights = epoch_calc(1,vector,vec,targets,bias,learning_rate,weights,n);
    // weights = epoch_calc(2,vector,vec,targets,bias,learning_rate,weights,n);
    // weights = epoch_calc(3,vector,vec,targets,bias,learning_rate,weights,n);
    // weights = epoch_calc(4,vector,vec,targets,bias,learning_rate,weights,n);

    // for (int i = 0; i < n+1; i++)
    // {
    //     printf("Weight %d after epochs: %f\n",i,weights[i]);
    // }
}

//4 4 1 1 1 1 1 -1 1 -1 -1 1 1 1 1 -1 -1 1 -1 -1 1 -1 0 0 0 0 0 0.2 1 1 4
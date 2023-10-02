#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_array(float* arr,int num,char* c){
    printf("%s",c);
    for(int i = 0; i < num ; i++){
        printf("%f ",arr[i]);
    }
    printf("\n");
}

void print_array_int(int* arr,int num,char* c){
    printf("%s",c);
    for(int i = 0; i < num ; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void print_weights(float** arr,int row, int col){
    for(int i = 0; i < row ; i++){
        for(int j = 0; j < col; j++){
            printf("%f ",arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

float* allocate_1Dmem(float* arr,int size,char* desc){
    printf("Allocating memory for %s\n",desc);
    arr = (float*)malloc(size * sizeof(float));
    return arr;
}

int* allocate_1Dmem_int(int* arr,int size,char* desc){
    printf("Allocating memory for %s\n",desc);
    arr = (int*)malloc(size * sizeof(int));
    return arr;
}

float** fill_weights(float** weights,int i,int j,char* desc){
    printf("Allocating %s\n",desc);
    weights = (float**)malloc(i * sizeof(float*));
    for(int x = 0; x<j ; x++){
        weights[x] = (float*)malloc(j * sizeof(float));
    }
    for(int a = 0; a < i; a++){
        for(int b = 0; b < j; b++){
            printf("Enter weight for cluster %d to vector %d: ",a+1,b+1);
            scanf("%f",&weights[a][b]);
        }
    }
    printf("\n");
    return weights;
}

float** allocate_2Dmem(float** vector,int i,int j,char* desc){
    printf("Allocating memory for %s\n",desc);
    vector = (float**)malloc(i * sizeof(float*));
    for(int x = 0; x<j ; x++){
        vector[x] = (float*)malloc(j * sizeof(float));
    }

    for(int a = 0; a < i; a++){
        printf("For vector %d\n",a+1);
        for(int b = 0; b < j; b++){
            printf("Enter value %d: ",b+1);
            scanf("%f",&vector[a][b]);
        }
    }
    printf("\n");

    return vector;
}


int calc_winning_cluster(float* vector, float** weights, int clusters, int vect_cnt){
    
    float dist[] = {0,0}; 
    for(int i = 0; i < clusters; i++){
        for(int j = 0; j < vect_cnt; j++){
            dist[i] = dist[i] + pow((weights[i][j]-vector[j]),2);
        }
    }
    if(dist[0] >= dist[1]){
        return 1;
    }
    else{
        return 0;
    }
}

float* update_weights(float* weights, float* vector,float learning_rate, int vector_len){
    print_array(vector,vector_len,"Vector: ");
    for(int i = 0; i < vector_len; i++){
        weights[i] = weights[i] + learning_rate * (vector[i] - weights[i]);
        // printf("Weight from vector %d is %f:",i,weights[i]);
        // printf("\n");
    }
    print_array(weights,vector_len,"Updated cluster weight: ");

    return weights;
}

float** KSOFM(float** vectors, float** weights, int* winning_cluster, int num_of_vectors, int num_of_clusters, float learning_rate, int vect_len){
    
    for (int i = 0; i < num_of_vectors; i++)
    {   
        printf("\nTraining on vector %d\n",i+1);
        winning_cluster[i] = calc_winning_cluster(vectors[i], weights, num_of_clusters, num_of_vectors);
        weights[winning_cluster[i]] = update_weights(weights[winning_cluster[i]],vectors[i],learning_rate,vect_len);
    }
    
    return weights;
}

void main()
{
    int* winning_cluster;     //winning cluster info
    float** vectors;       //input vectors
    float** weights;      //vector to cluster weight
    int vect_len,input,clusters;      // vector len, vector num, cluster num
    float learning_rate;     //learning rate and target
    printf("Enter number of vectors: ");
    scanf("%d",&input);
    printf("Enter number of elements per vector: ");
    scanf("%d",&vect_len);

    vectors = allocate_2Dmem(vectors,input,vect_len,"vectors");

    printf("Enter number of clusters: ");
    scanf("%d",&clusters);

    winning_cluster = allocate_1Dmem_int(winning_cluster,input,"winning cluster info");
    weights = fill_weights(weights,clusters,input,"weights");

    printf("Enter learning rate: ");
    scanf("%f",&learning_rate);
    printf("\n");

    weights = KSOFM(vectors, weights, winning_cluster, input, clusters, learning_rate, vect_len);
    printf("\nFinal weights are : \n");
    print_weights(weights,clusters,input);
}

//4 4 0 0 1 1 1 0 0 0 0 1 1 0 0 0 0 1 2 0.2 0.4 0.6 0.8 0.9 0.7 0.5 0.3 0.5
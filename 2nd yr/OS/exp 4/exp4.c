#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define arrsize 10000000
// #define num_t 4
int array[arrsize]; 
struct thread_data 
{ 
    int thread_id; 
    int start; 
    int end; 
}; 
int largest = 0; 

void *find_largest(void *thread_arg) 
{ 
    struct thread_data *my_data; 
    my_data = (struct thread_data *) thread_arg; 
    int start = my_data->start; 
    int end = my_data->end; 
    int i; 
    int local_largest = 0; 
    for (i = start; i < end; i++) 
    { 
        if (array[i] > local_largest) 
        { 
            local_largest = array[i]; 
        } 
    } 
    if (local_largest > largest) 
    { 
        largest = local_largest; 
    } 
    pthread_exit(NULL); 
} 
int findLargest(int arr[],int n) 
{ 
    int lower=1, upper = n, count=n; 
    for(int i=0;i<n;i++) 
    { 
        int num=(rand()); 
        arr[i]=num; 
    } 
    int largest=arr[0]; 
    for(int i=0;i<n;i++) 
    { 
        if(arr[i]>largest) 
        largest=arr[i]; 
    } 
    return largest; 
} 
int main() 
{ 
    int *tp=(int *)malloc(sizeof(int)*10000000); 
    int lower=1, upper = 10000000, count=10000000; 
    clock_t start, end; 
    start = clock(); 
    int ans=findLargest(tp,count); 
    end = clock(); 
    double duration = ((double)end - start)/CLOCKS_PER_SEC; 
    printf("Largest is: %d and time is: %lf\n",ans,duration); 
    int i, num_t; 
    printf("\nEnter no.of threads to create: "); 
    scanf("%d",&num_t); pthread_t
    threads[num_t]; 
    struct thread_data thread_args[num_t]; 
    for (i = 0; i < arrsize; i++) 
    { 
        array[i] = rand() % 1000000; 
    } 
    for (i = 0; i < num_t; i++)
    { 
        thread_args[i].thread_id = i; 
        thread_args[i].start = i * (arrsize / num_t); 
        thread_args[i].end = (i + 1) * (arrsize / num_t); 
        clock_t start, end; 
        start = clock(); 
        pthread_create(&threads[i], NULL, find_largest, (void *) &thread_args[i]); 
        end = clock(); 
        double duration = ((double)end - start)/CLOCKS_PER_SEC; 
        printf("\ntime taken is: %f\n", duration); 
        pthread_create(&threads[i], NULL, find_largest, (void *) &thread_args[i]);
    } 
    for (i = 0; i < num_t; i++) 
    { 
        pthread_join(threads[i], NULL); 
    } 
    // printf("Largest element in array is %d\n", largest);
    return 0; 
} 
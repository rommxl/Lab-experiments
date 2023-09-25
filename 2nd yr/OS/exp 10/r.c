#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <semaphore.h>

#define TOTAL_ELEMENTS 40

int main()
{
    printf("Process r:\n");

    key_t key;
    key = ftok("my_unique_key_gg", 0);

    // sem_t *sem;
    // sem = sem_open("my_semaphore_for_count", 0);
    sem_t *sem = sem_open("my_semaphore_for_count", O_CREAT, S_IRUSR | S_IWUSR, 1);
    sem_t *over_sem = sem_open("my_semaphore_for_r", O_CREAT, S_IRUSR | S_IWUSR, 0);

    if (sem == SEM_FAILED)
    {
        perror("sem_open");
        exit(1);
    }

    int shmid = shmget(key, (TOTAL_ELEMENTS+1) * sizeof(int), IPC_CREAT | 0666);
    int *arr = (int *)shmat(shmid, NULL, 0);

    printf("Waiting for arr to be filled.....\n");
    sem_post(sem);
    sleep(1);

    while(1){
        sem_wait(sem);
        if(arr[TOTAL_ELEMENTS] >= TOTAL_ELEMENTS-1){
            sem_post(sem);
            break;
        }
        sem_post(sem);
        sleep(1);
    }

    // bubble sort the arr
    for (int i = 0; i < TOTAL_ELEMENTS; i++)
    {
        for (int j = i; j < TOTAL_ELEMENTS; j++)
        {
            if (arr[i] > arr[j])
            {
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
    }

    int min = arr[0];
    printf("Sorted array: ");
    for (int i = 0; i < TOTAL_ELEMENTS; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    sem_post(over_sem);

    shmdt(arr);
    sem_close(sem);
    sem_close(over_sem);
    // sem_unlink("my_semaphore_for_count");
    // sem_unlink("my_semaphore_for_r");
    return 0;
}
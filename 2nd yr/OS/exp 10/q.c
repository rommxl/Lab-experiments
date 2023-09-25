#include <stdio.h>
#include "semaphore.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>

#define TOTAL_ELEMENTS 40

int main()
{
    printf("Process q:\n");

    key_t key;
    key = ftok("my_unique_key_gg", 0);

    // sem_t *sem;
    // sem = sem_open("my_semaphore_for_count", 0);
    sem_t *sem = sem_open("my_semaphore_for_count", O_CREAT, S_IRUSR | S_IWUSR, 1);

    if (sem == SEM_FAILED)
    {
        perror("sem_open");
        exit(1);
    }

    int shmid = shmget(key, (TOTAL_ELEMENTS + 1) * sizeof(int), IPC_CREAT);
    int *arr = (int *)shmat(shmid, NULL, 0);

    srand(time(NULL));

    printf("Waiting for instruction from r\n\n");
    while (1)
    {
        sem_wait(sem);

        int count = arr[TOTAL_ELEMENTS];
        if (count >= TOTAL_ELEMENTS - 1)
        {
            sem_post(sem);
            break;
        }
        int val = rand() % 500;
        printf("Index: %d, Value: %d\n", count + 1, val);
        arr[count + 1] = val;
        arr[TOTAL_ELEMENTS] = count + 1;
        sem_post(sem);
        sleep(1);
    }

    shmdt(arr);
    return 0;
}
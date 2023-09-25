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
    printf("Main:\n");
    key_t shmkey = ftok("my_unique_key_gg", 0);
    sem_t *sem = sem_open("my_semaphore_for_count", O_CREAT, S_IRUSR | S_IWUSR, 0);
    sem_t *over_sem = sem_open("my_semaphore_for_r", O_CREAT, S_IRUSR | S_IWUSR, 0);

    if (sem == SEM_FAILED || over_sem == SEM_FAILED)
    {
        perror("sem_open");
        exit(1);
    }

    // Intial value of semaphore set to 0
    sem_init(sem, 1, 0);
    sem_init(over_sem, 1, 0);

    int shmid = shmget(shmkey, (TOTAL_ELEMENTS + 1) * sizeof(int), IPC_CREAT | 0666);
    // Last one for maintaining count

    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }

    int *array = (int *)shmat(shmid, NULL, 0);

    if (array == (int *)-1)
    {
        perror("shmat");
        exit(1);
    }

    array[TOTAL_ELEMENTS] = -1;

    printf("Waiting for r to complete\n");
    sem_wait(over_sem);

    printf("\nAll operation done\n");

    shmdt(array);
    shmctl(shmid, IPC_STAT, NULL);
    sem_destroy(sem);
    sem_close(sem);
    sem_destroy(over_sem);
    sem_close(over_sem);
    sem_unlink("my_semaphore_for_count");
    sem_unlink("my_semaphore_for_r");
    return 0;
}
#include <stdio.h>

#include <semaphore.h>

#include <sys/wait.h>

#include <sys/shm.h>

#include <stdlib.h>

#include <string.h>

#include <fcntl.h>

#include <error.h>

// extern int errno;

int main(void)
{
  
  // common key for identifing the shared memory
  
  key_t key = 107;
   
 // shared mem id
    
int sh_id = shmget(key, 40 * sizeof(int), 0666);
   
 int *sh;
 
   sh = (int *)shmat(sh_id, NULL, 0);

    printf("%d\n", 
sh[0]);

  
  return 0;

}
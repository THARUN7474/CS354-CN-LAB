#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>

int main() {
    int shmid;
    void *shared_memory;


    shmid = shmget((key_t)2345, 1024, 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (void *)-1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    printf("Data read from shared memory is: %s\n", (char *)shared_memory);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>

int main() {
    int shmid;
    void *shared_memory;
    char buff[100];

    shmid = shmget((key_t)2345, 1024, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (void *)-1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    if (read(0, buff, 100) == -1) {
        perror("read failed");
        exit(EXIT_FAILURE);
    }

    strcpy(shared_memory, buff);

    return 0;
}
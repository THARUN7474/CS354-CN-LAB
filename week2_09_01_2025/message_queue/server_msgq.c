#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define KEY 1234
#define BUFFER_SIZE 256

struct message {
    long type; 
    char text[BUFFER_SIZE]; 
};

int main() {
    struct message msg;
    int msgid;


    msgid = msgget(KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    printf("Server: Message queue created. Waiting for messages...\n");

    while (1) {
      
        if (msgrcv(msgid, &msg, sizeof(msg.text), 0, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
        
        printf("Server received: %s\n", msg.text);
        
 
        if (strcmp(msg.text, "exit") == 0) {
            printf("Server shutting down...\n");
            break;
        }
    }

    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
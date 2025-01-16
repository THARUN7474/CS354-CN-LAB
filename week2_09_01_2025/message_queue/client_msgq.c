#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>

#define KEY 1234
#define BUFFER_SIZE 256


struct message {
    long type;
    char text[BUFFER_SIZE]; 
};

int main() {
    struct message msg;
    int msgid;

    // Connect to the message queue
    msgid = msgget(KEY, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Client: Connected to message queue. Type your messages (type 'exit' to quit):\n");

    while (1) {
       
        printf("> ");
        fgets(msg.text, sizeof(msg.text), stdin);
        msg.text[strcspn(msg.text, "\n")] = '\0'; 

        msg.type = 1; 

    
        if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }

        if (strcmp(msg.text, "exit") == 0) {
            printf("Client exiting...\n");
            break;
        }
    }

    return 0;
}
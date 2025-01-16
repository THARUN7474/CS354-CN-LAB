#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 256

int main() {
    char buffer[BUFFER_SIZE];
    
    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    printf("Client: Type your messages (type 'exit' to quit):\n");
    while (1) {
        
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; 
        
        if (write(fd, buffer, strlen(buffer)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        
        if (strcmp(buffer, "exit") == 0) {
            printf("Client exiting...\n");
            break;
        }
    }
    
    close(fd);
    return 0;
}
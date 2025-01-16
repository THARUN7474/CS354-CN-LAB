#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 256

int main()
{
    char buffer[BUFFER_SIZE];

    // Create the FIFO if it doesn't exist
    if (mkfifo(FIFO_NAME, 0666) == -1)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    printf("Server: Waiting for clients...\n");

    // Open the FIFO for reading
    int fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        // Read messages from the FIFO
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0)
        {
            buffer[bytes_read] = '\0'; // Null-terminate the string
            printf("Server received: %s\n", buffer);

            if (strcmp(buffer, "exit") == 0)
            {
                printf("Server shutting down...\n");
                break;
            }
        }
    }

    close(fd);
    unlink(FIFO_NAME); // Remove the FIFO
    return 0;
}
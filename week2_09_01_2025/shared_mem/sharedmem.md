### **Step 3: Shared Memory**

#### **Concept of Shared Memory**
Shared memory is the fastest Inter-Process Communication (IPC) mechanism as it allows multiple processes to access the same memory region. Unlike message queues or FIFOs, data transfer happens directly through memory, bypassing the overhead of copying data between kernel and user spaces.

However, shared memory requires careful synchronization between processes to avoid race conditions or data corruption. This is often achieved using semaphores or other synchronization tools.

---

### **How Shared Memory Works**
1. A process (typically the server) creates a shared memory segment using `shmget()`.
2. Processes attach the shared memory segment to their address space using `shmat()`.
3. Data is written to and read directly from the shared memory region.
4. Processes detach the shared memory segment using `shmdt()` after usage.
5. Finally, the shared memory segment can be deleted using `shmctl()`.

---

### **Steps to Implement Shared Memory**

1. **Key Setup**:
   - Shared memory segments are identified by a unique key, similar to message queues.
2. **Creating Shared Memory**:
   - The server creates a shared memory segment using `shmget()` and attaches it using `shmat()`.
3. **Reading/Writing**:
   - Both client and server can directly access the shared memory to read/write data.
4. **Synchronization**:
   - Use mechanisms like flags or semaphores to coordinate access to shared memory.
5. **Cleanup**:
   - Detach the memory segment (`shmdt()`) and delete it (`shmctl()`) when done.

---

### **Code Example for Shared Memory**

#### **Server Code (`server_shm.c`)**:
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define KEY 1234
#define BUFFER_SIZE 256

int main() {
    int shmid;
    char *shared_memory;

    // Create a shared memory segment
    shmid = shmget(KEY, BUFFER_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    printf("Server: Shared memory created.\n");

    // Attach the shared memory segment
    shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    printf("Server: Waiting for client...\n");

    while (1) {
        // Wait for a message from the client
        if (strlen(shared_memory) > 0) {
            printf("Server received: %s\n", shared_memory);

            // If the client sends "exit", stop the server
            if (strcmp(shared_memory, "exit") == 0) {
                printf("Server shutting down...\n");
                break;
            }

            // Clear the shared memory for the next message
            memset(shared_memory, 0, BUFFER_SIZE);
        }
    }

    // Detach the shared memory segment
    if (shmdt(shared_memory) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Delete the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
```

#### **Client Code (`client_shm.c`)**:
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define KEY 1234
#define BUFFER_SIZE 256

int main() {
    int shmid;
    char *shared_memory;

    // Connect to the shared memory segment
    shmid = shmget(KEY, BUFFER_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment
    shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("Client: Connected to shared memory. Type your messages (type 'exit' to quit):\n");

    while (1) {
        // Get user input
        printf("> ");
        fgets(shared_memory, BUFFER_SIZE, stdin);
        shared_memory[strcspn(shared_memory, "\n")] = '\0'; // Remove trailing newline

        // If the client sends "exit", stop the client
        if (strcmp(shared_memory, "exit") == 0) {
            printf("Client exiting...\n");
            break;
        }
    }

    // Detach the shared memory segment
    if (shmdt(shared_memory) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    return 0;
}
```

---

### **Compiling and Running the Shared Memory Example**

1. **Compile the programs**:
   ```bash
   gcc server_shm.c -o server_shm
   gcc client_shm.c -o client_shm
   ```
2. **Run the server**:
   ```bash
   ./server_shm
   ```
3. **Run the client in another terminal**:
   ```bash
   ./client_shm
   ```

4. **Communicate**:
   - Type messages in the client terminal.
   - The server will receive and print them.
   - Type `exit` to stop the server.

---

### **Key Differences Between FIFO, Message Queues, and Shared Memory**

| Feature                 | FIFO             | Message Queues         | Shared Memory       |
|-------------------------|------------------|------------------------|---------------------|
| Communication Style     | Byte Stream      | Structured Messages    | Direct Memory Access |
| Performance             | Moderate         | Faster than FIFO       | Fastest             |
| Synchronization Needed? | No               | No (by message types)  | Yes (manual sync)   |
| Complexity              | Low              | Medium                 | High                |

---

### **What’s Next?**
- Explore **semaphores** for synchronizing access to shared resources like shared memory.
- Use **hybrid IPC mechanisms** (e.g., shared memory + semaphores) for more advanced use cases.
- Dive deeper into **real-world client-server systems** for scalable applications.

Let me know if you'd like to explore these topics further!
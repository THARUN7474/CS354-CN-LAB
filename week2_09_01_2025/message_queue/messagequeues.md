### **Step 2: Message Queues**

#### **Concept of Message Queues**
Message Queues allow processes to send and receive discrete messages. Unlike FIFO, which handles continuous streams, message queues allow messages to be organized in a structured way, with each message identified by a **type**. This is useful for asynchronous communication.

#### **How Message Queues Work**
1. A **server** creates a message queue using `msgget()`.
2. Clients and servers use `msgsnd()` to send messages and `msgrcv()` to receive messages.
3. Messages are stored in the queue until they are retrieved by the recipient.
4. The queue can be deleted when it's no longer needed.

---

### **Steps to Implement Message Queues**

1. **Key Setup**:
   - Both the client and server use the same **key** to access the same message queue.
2. **Creating the Queue**:
   - The server creates the queue using `msgget()`.
3. **Message Structure**:
   - Define a structure for the message, typically containing a message type (`long`) and a text payload.
4. **Sending Messages**:
   - Use `msgsnd()` to send messages to the queue.
5. **Receiving Messages**:
   - Use `msgrcv()` to read messages from the queue based on type.
6. **Cleanup**:
   - Delete the queue when it’s no longer needed using `msgctl()`.

---

### **Code Example for Message Queues**

#### **Server Code (`server_msgq.c`)**:
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define KEY 1234
#define BUFFER_SIZE 256

// Define the message structure
struct message {
    long type; // Message type (must be long)
    char text[BUFFER_SIZE]; // Message text
};

int main() {
    struct message msg;
    int msgid;

    // Create a message queue
    msgid = msgget(KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    printf("Server: Message queue created. Waiting for messages...\n");

    while (1) {
        // Receive a message from the queue
        if (msgrcv(msgid, &msg, sizeof(msg.text), 0, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
        
        printf("Server received: %s\n", msg.text);
        
        // If the client sends "exit", stop the server
        if (strcmp(msg.text, "exit") == 0) {
            printf("Server shutting down...\n");
            break;
        }
    }

    // Delete the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
```

#### **Client Code (`client_msgq.c`)**:
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define KEY 1234
#define BUFFER_SIZE 256

// Define the message structure
struct message {
    long type; // Message type (must be long)
    char text[BUFFER_SIZE]; // Message text
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
        // Get user input
        printf("> ");
        fgets(msg.text, sizeof(msg.text), stdin);
        msg.text[strcspn(msg.text, "\n")] = '\0'; // Remove trailing newline

        msg.type = 1; // Set the message type

        // Send the message
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
```

---

### **Compiling and Running the Message Queue Example**

1. **Compile the programs**:
   ```bash
   gcc server_msgq.c -o server_msgq
   gcc client_msgq.c -o client_msgq
   ```
2. **Run the server**:
   ```bash
   ./server_msgq
   ```
3. **Run the client in another terminal**:
   ```bash
   ./client_msgq
   ```

4. **Communicate**:
   - Type messages in the client terminal.
   - The server will receive and print them.
   - Type `exit` to stop the server.

---

### **What’s Next?**
The next IPC mechanism, **Shared Memory**, is even faster and allows direct access to memory regions shared between processes. It is a great choice when performance is critical, but it requires more synchronization mechanisms like semaphores. Let me know when you're ready to explore it!
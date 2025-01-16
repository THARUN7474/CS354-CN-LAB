### **What is CRC (Cyclic Redundancy Check)?**

CRC (Cyclic Redundancy Check) is an error-detection technique used in digital networks and storage devices to detect accidental changes to raw data. It is based on **polynomial division**. Here's how it works:

1. A **generator polynomial (G)** is predefined for the system.
2. Data bits are treated as a binary number and appended with a sequence of zero bits (equal to the degree of the generator polynomial).
3. Polynomial division is performed to compute the **remainder**.
4. The remainder (known as the CRC) is appended to the data before transmission.
5. At the receiver’s end, the same division is performed. If the remainder is zero, the data is assumed to be error-free.

---

### **Steps in CRC Calculation**:

1. **Sender Side**:
   - Append zeros (degree of the polynomial) to the data bits.
   - Perform binary division using XOR and get the remainder.
   - Append the remainder to the original data.

2. **Receiver Side**:
   - Receive the transmitted data (original + CRC bits).
   - Perform the same binary division.
   - If the remainder is zero, the data is correct; otherwise, an error has occurred.

---

### **C++ Program for CRC**

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Function to perform XOR operation
void XOR(vector<int>& dividend, vector<int>& divisor, int start) {
    for (int i = 0; i < divisor.size(); i++) {
        dividend[start + i] ^= divisor[i];
    }
}

// Function to perform CRC computation
vector<int> computeCRC(vector<int> data, vector<int> generator) {
    int n = generator.size();
    vector<int> dividend = data;

    // Append zeros (degree of generator - 1) to the data
    for (int i = 0; i < n - 1; i++) {
        dividend.push_back(0);
    }

    // Perform division
    for (int i = 0; i <= dividend.size() - n; i++) {
        if (dividend[i] == 1) {
            XOR(dividend, generator, i);
        }
    }

    // Extract remainder
    vector<int> remainder(dividend.end() - (n - 1), dividend.end());
    return remainder;
}

// Function to verify the CRC at the receiver side
bool verifyCRC(vector<int> receivedData, vector<int> generator) {
    int n = generator.size();

    // Perform division on received data
    for (int i = 0; i <= receivedData.size() - n; i++) {
        if (receivedData[i] == 1) {
            XOR(receivedData, generator, i);
        }
    }

    // Check if remainder is all zeros
    for (int i = receivedData.size() - (n - 1); i < receivedData.size(); i++) {
        if (receivedData[i] != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    // Input data and generator
    vector<int> data = {1, 0, 1, 1};           // Example data
    vector<int> generator = {1, 0, 1};         // Example generator (polynomial x^2 + 1)

    // Compute CRC
    vector<int> crc = computeCRC(data, generator);

    // Display original data and CRC
    cout << "Original Data: ";
    for (int bit : data) cout << bit;
    cout << "\nCRC: ";
    for (int bit : crc) cout << bit;

    // Transmitted data
    vector<int> transmittedData = data;
    transmittedData.insert(transmittedData.end(), crc.begin(), crc.end());

    cout << "\nTransmitted Data: ";
    for (int bit : transmittedData) cout << bit;

    // Verify CRC at receiver
    bool isValid = verifyCRC(transmittedData, generator);

    cout << "\nData Verification Result: " << (isValid ? "No Error" : "Error Detected") << endl;

    return 0;
}
```

---

### **Explanation of the Program**

1. **`computeCRC`**:  
   - Appends zeros to the data for CRC calculation.  
   - Performs XOR-based binary division to calculate the remainder (CRC).  

2. **`verifyCRC`**:  
   - Checks if the received data (data + CRC) has a remainder of zero after division.  

3. **Main function**:  
   - Input data and generator polynomial.  
   - Compute the CRC, append it to the data, and transmit.  
   - Verify at the receiver if the data is error-free.

---

### **Example Input/Output**

**Input:**  
Data: `1011`  
Generator Polynomial: `101` (x² + 1)  

**Output:**  
```
Original Data: 1011
CRC: 10
Transmitted Data: 101110
Data Verification Result: No Error
```

---

### **Key Points**

1. **Generator Polynomial**: Choose a polynomial based on the protocol (e.g., CRC-8, CRC-16).  
2. **Efficiency**: XOR-based division is computationally efficient for hardware and software implementation.  
3. **Real-world Application**: Used in Ethernet, file storage systems, and communication protocols (e.g., TCP/IP).  

Let me know if you need additional modifications or examples! 😊



Let's take a simple example to go through the 

computeCRC

 function line by line.

### Test Case
- **Data**: `1101` (in binary, represented as a vector of integers `[1, 1, 0, 1]`)
- **Generator**: `1011` (in binary, represented as a vector of integers `[1, 0, 1, 1]`)

### Step-by-Step Execution

1. **Initialization**:
    ```cpp
    vector<int> data = {1, 1, 0, 1};
    vector<int> generator = {1, 0, 1, 1};
    vector<int> dividend = data;
    int n = generator.size(); // n = 4
    ```

2. **Appending Zeros**:
    ```cpp
    for (int i = 0; i < n - 1; i++) {
        dividend.push_back(0);
    }
    // dividend becomes {1, 1, 0, 1, 0, 0, 0}
    ```

3. **Division Process**:
    ```cpp
    for (int i = 0; i <= dividend.size() - n; i++) {
        if (dividend[i] == 1) {
            XOR(dividend, generator, i);
        }
    }
    ```

    - **First Iteration (i = 0)**:
        ```cpp
        if (dividend[0] == 1) {
            XOR(dividend, generator, 0);
        }
        // XOR operation:
        // dividend[0] ^= generator[0] -> 1 ^= 1 -> 0
        // dividend[1] ^= generator[1] -> 1 ^= 0 -> 1
        // dividend[2] ^= generator[2] -> 0 ^= 1 -> 1
        // dividend[3] ^= generator[3] -> 1 ^= 1 -> 0
        // dividend becomes {0, 1, 1, 0, 0, 0, 0}
        ```

    - **Second Iteration (i = 1)**:
        ```cpp
        if (dividend[1] == 1) {
            XOR(dividend, generator, 1);
        }
        // XOR operation:
        // dividend[1] ^= generator[0] -> 1 ^= 1 -> 0
        // dividend[2] ^= generator[1] -> 1 ^= 0 -> 1
        // dividend[3] ^= generator[2] -> 0 ^= 1 -> 1
        // dividend[4] ^= generator[3] -> 0 ^= 1 -> 1
        // dividend becomes {0, 0, 1, 1, 1, 0, 0}
        ```

    - **Third Iteration (i = 2)**:
        ```cpp
        if (dividend[2] == 1) {
            XOR(dividend, generator, 2);
        }
        // XOR operation:
        // dividend[2] ^= generator[0] -> 1 ^= 1 -> 0
        // dividend[3] ^= generator[1] -> 1 ^= 0 -> 1
        // dividend[4] ^= generator[2] -> 1 ^= 1 -> 0
        // dividend[5] ^= generator[3] -> 0 ^= 1 -> 1
        // dividend becomes {0, 0, 0, 1, 0, 1, 0}
        ```

    - **Fourth Iteration (i = 3)**:
        ```cpp
        if (dividend[3] == 1) {
            XOR(dividend, generator, 3);
        }
        // XOR operation:
        // dividend[3] ^= generator[0] -> 1 ^= 1 -> 0
        // dividend[4] ^= generator[1] -> 0 ^= 0 -> 0
        // dividend[5] ^= generator[2] -> 1 ^= 1 -> 0
        // dividend[6] ^= generator[3] -> 0 ^= 1 -> 1
        // dividend becomes {0, 0, 0, 0, 0, 0, 1}
        ```

4. **Extracting Remainder**:
    ```cpp
    vector<int> remd(dividend.end() - (n - 1), dividend.end());
    // remd becomes {0, 0, 1}
    ```

5. **Return Remainder**:
    ```cpp
    return remd;
    ```

### Final Output
The remainder for the given data and generator is `{0, 0, 1}`.


Let's take the same example and go through the `verifyCRC` function line by line.

### Test Case
- **Received Data**: `1101100` (in binary, represented as a vector of integers `[1, 1, 0, 1, 1, 0, 0]`)
- **Generator**: `1011` (in binary, represented as a vector of integers `[1, 0, 1, 1]`)

### Step-by-Step Execution

1. **Initialization**:
    ```cpp
    vector<int> rData = {1, 1, 0, 1, 1, 0, 0};
    vector<int> gen = {1, 0, 1, 1};
    int n = gen.size(); // n = 4
    ```

2. **Division Process**:
    ```cpp
    for (int i = 0; i <= rData.size() - n; i++) {
        if (rData[i] == 1) {
            XOR(rData, gen, i);
        }
    }
    ```

    - **First Iteration (i = 0)**:
        ```cpp
        if (rData[0] == 1) {
            XOR(rData, gen, 0);
        }
        // XOR operation:
        // rData[0] ^= gen[0] -> 1 ^= 1 -> 0
        // rData[1] ^= gen[1] -> 1 ^= 0 -> 1
        // rData[2] ^= gen[2] -> 0 ^= 1 -> 1
        // rData[3] ^= gen[3] -> 1 ^= 1 -> 0
        // rData becomes {0, 1, 1, 0, 1, 0, 0}
        ```

    - **Second Iteration (i = 1)**:
        ```cpp
        if (rData[1] == 1) {
            XOR(rData, gen, 1);
        }
        // XOR operation:
        // rData[1] ^= gen[0] -> 1 ^= 1 -> 0
        // rData[2] ^= gen[1] -> 1 ^= 0 -> 1
        // rData[3] ^= gen[2] -> 0 ^= 1 -> 1
        // rData[4] ^= gen[3] -> 1 ^= 1 -> 0
        // rData becomes {0, 0, 1, 1, 0, 0, 0}
        ```

    - **Third Iteration (i = 2)**:
        ```cpp
        if (rData[2] == 1) {
            XOR(rData, gen, 2);
        }
        // XOR operation:
        // rData[2] ^= gen[0] -> 1 ^= 1 -> 0
        // rData[3] ^= gen[1] -> 1 ^= 0 -> 1
        // rData[4] ^= gen[2] -> 0 ^= 1 -> 1
        // rData[5] ^= gen[3] -> 0 ^= 1 -> 1
        // rData becomes {0, 0, 0, 1, 1, 1, 0}
        ```

    - **Fourth Iteration (i = 3)**:
        ```cpp
        if (rData[3] == 1) {
            XOR(rData, gen, 3);
        }
        // XOR operation:
        // rData[3] ^= gen[0] -> 1 ^= 1 -> 0
        // rData[4] ^= gen[1] -> 1 ^= 0 -> 1
        // rData[5] ^= gen[2] -> 1 ^= 1 -> 0
        // rData[6] ^= gen[3] -> 0 ^= 1 -> 1
        // rData becomes {0, 0, 0, 0, 1, 0, 1}
        ```

3. **Check Remainder**:
    ```cpp
    for (int i = rData.size() - (n - 1); i < rData.size(); i++) {
        if (rData[i] != 0) {
            return false;
        }
    }
    return true;
    ```

    - **Checking Remainder**:
        ```cpp
        for (int i = 4; i < 7; i++) {
            if (rData[i] != 0) {
                return false;
            }
        }
        // rData[4] = 1, which is not 0, so the function returns false.
        ```

### Final Output
The `verifyCRC` function returns `false` for the given received data and generator, indicating that the data contains errors.
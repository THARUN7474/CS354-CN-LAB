### **What is Bit Stuffing?**

**Bit Stuffing** is a technique used in data transmission to ensure that a specific bit pattern (usually a flag or delimiter) doesn't accidentally appear in the data itself. 

- In communication protocols, like **HDLC (High-Level Data Link Control)**, a special bit sequence (e.g., `01111110`) is used as a **frame delimiter** to mark the start and end of a frame.
- To avoid confusion, if this bit sequence appears in the actual data, additional bits are "stuffed" into the data stream to distinguish it from the delimiter.

### **Bit Stuffing Example**

1. **Input Data**: `0111111101`
2. **Stuffing Rule**:
   - After **five consecutive `1`s** in the data, insert a `0`.
3. **Stuffed Data**: `0111110101`

---

### **Steps to Perform Bit Stuffing**
1. Scan the data bit by bit.
2. Count consecutive `1`s.
3. If five consecutive `1`s are found, insert a `0` immediately after.
4. Continue until the entire bit stream is processed.

---

### **Output**
```
Original Data:  0111111101
Stuffed Data:   0111110101
```

---

### **Unstuffing the Data**
To decode the stuffed data:
1. Scan for sequences of `1`s.
2. If five consecutive `1`s are followed by a `0`, remove the `0`.

---

### **Output**
```
Stuffed Data:   0111110101
Decoded Data:   0111111101
```

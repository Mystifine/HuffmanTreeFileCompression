
---

# HuffmanTreeFileCompression

This project was developed as a **bonus assignment** worth 5% of the final course grade. The objective was to implement a compression and decompression algorithm using the **Huffman Tree** data structure, ensuring that compressed files were stored in a **binary format** for efficient storage.

The assignment involved handling specific constraints and using fundamental data structures like **Linked Lists**, **Min Heaps**, **Hashmaps**, and the **Huffman Tree**. This implementation adheres to strict requirements as outlined in the project description.

---

## **Features**

### **Compression Program**
The compression program performs the following tasks:
1. Reads an input text file and preprocesses the data:
   - Converts all characters to lowercase.
   - Converts all whitespace characters (e.g., tabs, newlines) to a single space (`' '`).
   - Ignores non-encodable characters (only encodes `a–z`, `0–9`, spaces, commas, and periods).
2. Calculates the frequency of each encodable character and writes this data to `frequency.txt`.
3. Generates Huffman codes for the characters based on their frequency and writes the codes to `codes.txt`.
4. Compresses the input file into a binary file (`compressed.bin`) using the generated Huffman codes.
5. Optionally stores metadata in a separate file (`tree.txt`) or within `compressed.bin` for decoding.

### **Decompression Program**
The decompression program performs the following tasks:
1. Reconstructs the Huffman tree using the files generated during compression (`frequency.txt`, `codes.txt`, or `tree.txt`).
2. Decodes the binary file (`compressed.bin`) using the reconstructed tree.
3. Writes the decompressed data to `decoded.txt`, ensuring that:
   - All alphabetical characters are lowercase.
   - Whitespace and special characters (`space`, `comma`, `period`) are retained.
   - All other characters are ignored.

---

## **Technical Details**

### **Data Structures Used**
- **Linked List**:
  Used for representing the priority queue before constructing the Huffman Tree.
- **Min Heap**:
  Used to efficiently build the Huffman Tree based on character frequencies.
- **Huffman Tree**:
  A binary tree where each leaf node represents an encodable character. Shorter paths are assigned to more frequent characters.
- **Hashmap**:
  Used for:
  - Storing character-to-code mappings for compression.
  - Storing metadata for decoding.

---

### **Compression Algorithm**
1. **Preprocessing**:
   - Read and clean the input file.
   - Convert all characters to lowercase.
   - Replace all whitespace characters with a single space.
   - Ignore non-encodable characters.

2. **Frequency Table Generation**:
   - Count the frequency of each encodable character (`a–z`, `0–9`, space, comma, period).
   - Write the frequency table to `frequency.txt` in the format:  
     ```
     c:n
     ```
     where `c` is the character and `n` is its frequency.

3. **Huffman Tree Construction**:
   - Use a priority queue to build the Huffman Tree:
     - Insert each character as a node in the priority queue, ordered by frequency.
     - Combine the two smallest nodes until a single root node is formed.

4. **Huffman Code Generation**:
   - Traverse the tree to assign binary codes to each character.
   - Write these codes to `codes.txt` in the format:
     ```
     c:h
     ```
     where `c` is the character and `h` is its Huffman code.

5. **Binary File Compression**:
   - Replace each character in the input file with its Huffman code.
   - Write the encoded bits to `compressed.bin` using bitwise operations.

---

### **Decompression Algorithm**
1. **Reconstruct the Huffman Tree**:
   - Use the data from `frequency.txt` or `tree.txt` to rebuild the Huffman Tree.

2. **Binary File Decoding**:
   - Read the binary file (`compressed.bin`) bit by bit.
   - Traverse the Huffman Tree using the read bits to decode characters.

3. **Output the Decoded File**:
   - Write the decoded text to `decoded.txt`.
   - Ensure proper formatting (lowercase characters, whitespace, and special characters).

---

## **File Structure**

### Compression Output:
1. **`frequency.txt`**:
   - Contains the frequency table of characters.
   - Example:
     ```
     a:15
     b:5
     c:10
     ...
     ```

2. **`codes.txt`**:
   - Contains the Huffman codes for each character.
   - Example:
     ```
     a:101
     b:1101
     c:100
     ...
     ```

3. **`compressed.bin`**:
   - The binary file containing the compressed data.

4. **`tree.txt`** (Optional):
   - Metadata required to reconstruct the Huffman Tree.

### Decompression Output:
1. **`decoded.txt`**:
   - The decompressed file, matching the original input.

---

## **File Constraints**

- Input files are between **0 KB and 100 KB** in size.
- Only the following characters are encoded:
  - Lowercase letters (`a–z`).
  - Digits (`0–9`).
  - Space (`' '`), comma (`','`), period (`'.'`).
- Whitespace characters (e.g., tabs, newlines) are converted to spaces.
- Uppercase letters are converted to lowercase.

---

## **How to Run**

### **Compression Program**
1. Compile the compression program:
   ```
   gcc -o compress compress.c
   ```
2. Run the program and provide the input file name:
   ```
   ./compress
   ```
   - Enter the file name when prompted.

3. Outputs:
   - `frequency.txt`
   - `codes.txt`
   - `compressed.bin`

### **Decompression Program**
1. Compile the decompression program:
   ```
   gcc -o decompress decompress.c
   ```
2. Run the program:
   ```
   ./decompress
   ```

3. Outputs:
   - `decoded.txt`

---

## **Error Handling**
- **File Errors**:
  - Handles missing or unreadable input files gracefully.
- **Memory Allocation**:
  - Ensures proper allocation and deallocation of memory.
- **Invalid Characters**:
  - Ignores characters that cannot be encoded.

---

## **Limitations**
- Not thread-safe.
- Relies on strict adherence to the specified input and output formats.
- Assumes that `compressed.bin` is correctly formatted for decoding.

---

## **Conclusion**
This project demonstrates the implementation of **Huffman Encoding** and **Decoding** using fundamental data structures and bitwise operations. The solution is optimized for variable-length codes and produces significantly smaller files when compressing text.


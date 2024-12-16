/**
 * Author: Iverson Jiang
 * StudentId: 169025755
 * Description: Due to requirements of the bonus assignment, all encoding and decoding logic must be within it's own file. I've attempted to separate as much as possible and organize. Otherwise additional header and implementation files would exist.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CREATE LINKED LIST DATA STRUCTURE
typedef struct Node {
  char* key;
  char* data;
  struct Node *next;
} Node;

typedef struct LinkedList {
  Node *front;
  Node *end;
} LinkedList;

LinkedList* createLinkedList();
Node* createNode(const char* data);
void freeNode(Node* node);
void linkedListInsertFront(LinkedList* linked_list, Node* node);
void linkedListInsertEnd(LinkedList* linked_list, Node* node);
void printLinkedList(LinkedList* linked_list);
void linkedListRemoveFront(LinkedList* linked_list);
void linkedListRemoveEnd(LinkedList* linked_list);
void freeLinkedList(LinkedList* linked_list);

/**
 * Function Name: createLinkedList
 * Purpose: Creates a linked list.
 * Parameters:
 *  None
 * 
 * Return Value:
 *  - LinkedList*: the pointer to the created linked list
 */
LinkedList* createLinkedList() {
  LinkedList* linked_list = (LinkedList*) malloc(sizeof(LinkedList));

  if (linked_list == NULL) {
    printf("Failed to allocate memory");
    return NULL;
  }

  linked_list->front = NULL;
  linked_list->end = NULL;

  return linked_list;
} 

/**
 * Function Name: createNode
 * Purpose: creates a node provided the data. Key should be manually set.
 * Parameters:
 *  - int data: The data associated with the node
 * 
 * Return Value:
 *  - Node*: the pointer to the node
 */
Node* createNode(const char* data) {
  Node* node = (Node*) malloc(sizeof(Node));

  if (node == NULL) {
    printf("Failed to allocate memory");
    return NULL;
  }

  node->data = strdup(data);
  node->next = NULL;

  return node;
}

/**
 * Function Name: freeNode
 * Purpose: frees a node from dynamically allocted memory. 
 * Parameters:
 *  - Node* node: The node to be freed
 * 
 * Return Value:
 *  - void
 * 
 * Note:
 * it will free the *char property of the node too.
 */
void freeNode(Node* node) {
  if (node == NULL) {
    printf("node is NULL freeNode");
    return;
  }
  free(node->key);
  free(node->data);
  free(node);
}

/**
 * Function Name: linkedListInsertFront
 * Purpose: Inserts a node to the front of a linked_list
 * Parameters:
 *  - LinkedList* linked_list: The linked_list to be modified
 * 
 * Return Value:
 *  - void
 */
void linkedListInsertFront(LinkedList* linked_list, Node* node) {

  if (linked_list == NULL) {
    printf("LinkedList is NULL.");
    return;
  }

  if (node == NULL) {
    printf("Node is NULL linkedListInsertFront.");
    return;
  }

  if (linked_list->front == NULL) {
    linked_list->front = node;
    linked_list->end = node;
  } else {
    node->next = linked_list->front;
    linked_list->front = node;
  }
}

/**
 * Function Name: linkedListInsertEnd
 * Purpose: Inserts a node to the end of a linked_list
 * Parameters:
 *  - LinkedList* linked_list: The linked_list to be modified
 * 
 * Return Value:
 *  - void
 */
void linkedListInsertEnd(LinkedList* linked_list, Node* node) {
  if (linked_list == NULL) {
    printf("LinkedList is NULL");
    return;
  }

  if (node == NULL) {
    printf("Node is NULL linkedListInsertEnd.");
    return;
  }

  if (linked_list->front == NULL) {
    linked_list->front = node;
    linked_list->end = node;
  } else {
    linked_list->end->next = node;
    linked_list->end = node;
  }
}

/**
 * Function Name: printLinkedList
 * Purpose: Iterates through the linked list and outputs the list
 * Parameters:
 *  - LinkedList* linked_list: The linked_list to be printed
 * 
 * Return Value:
 *  - void
 */
void printLinkedList(LinkedList* linked_list) {
  if (linked_list == NULL || linked_list->front == NULL) {
    printf("LinkedList is empty.");
    return;
  }

  Node* current_node = linked_list->front;
  while (current_node != NULL) {
    printf("%d -> ", current_node->data);
    current_node = current_node->next;
  }
  printf("NULL\n");
}

/**
 * Function Name: linkedListRemoveEnd
 * Purpose: Removes the first element in a linked_list. Takes O(1) time
 * Parameters:
 *  - LinkedList* linked_list: The linked_list to be modified
 * 
 * Return Value:
 *  - void
 */
void linkedListRemoveFront(LinkedList* linked_list) {
  if (linked_list == NULL) {
    printf("LinkedList is NULL");
    return;
  }

  if (linked_list->front != NULL) {
    Node* current_front = linked_list->front;
    linked_list->front = current_front->next;

    if (linked_list->front == NULL) {
      linked_list->end = NULL;
    }

    freeNode(current_front);
  }
}

/**
 * Function Name: linkedListRemoveEnd
 * Purpose: Removes the last element in a linked_list. Takes O(n) time due to no prev attribute
 * Parameters:
 *  - LinkedList* linked_list: The linked_list to be modified
 * 
 * Return Value:
 *  - void
 */
void linkedListRemoveEnd(LinkedList* linked_list) {
  if (linked_list == NULL) {
    printf("LinkedList is NULL");
    return;
  }

  if (linked_list->front == NULL) {
    printf("LinkedList is empty.");
    return;
  }

  if (linked_list->front == linked_list->end) {
    freeNode(linked_list->front);
    linked_list->front = NULL;
    linked_list->end = NULL;
    return;
  }

  Node* current_node = linked_list->front;

  while (current_node->next != linked_list->end) {
    current_node = current_node->next;
  }

  freeNode(linked_list->end);
  linked_list->end = current_node;
  current_node->next = NULL;
}

/**
 * Function Name: freeLinkedList
 * Purpose: Cleans up a linked list
 * Parameters:
 *  - LinkedList* linked_list: The linked_list to be cleaned up
 * 
 * Return Value:
 *  - void
 */
void freeLinkedList(LinkedList* linked_list) {
  if (linked_list == NULL) {
    printf("Error: LinkedList is NULL in freeLinkedList.\n");
    return;
  }

  while (linked_list->front != NULL) {
    linkedListRemoveFront(linked_list);
  }

  free(linked_list);
}

// CREATING HASHMAP USING OUR LINKED LIST
typedef struct HashMap {
  LinkedList** buckets; // array of pointers to linked list (pointer of pointer)
  size_t size; // number of buckets
} HashMap;

size_t hash(const char *key, size_t size);
HashMap* createHashMap(size_t size);
void hashMapInsert(HashMap* hash_map, const char* index, const char* data);
char* hashMapGet(HashMap* hash_map, const char* index);
int hashMapUpdate(HashMap* hash_map, const char* index, const char* data);
void hashMapRemove(HashMap* hash_map, const char* index);
void freeHashMap(HashMap* hash_map);

/**
 * Function Name: hash
 * Purpose: Hashes a key provided the size of the hashmap
 * Parameters:
 *  - const char *key: The hashmap key to be hashed
 *  - size_t size: The size of the hash map
 * 
 * Returns:
 *  - size_t: the hashed index
 */
size_t hash(const char *key, size_t size) {
  size_t hash = 0;
  while (*key) {
    hash = (hash * 31) + *key;  // Simple hash function (multiplicative)
    key++;
  }
  return hash % size; // Return the bucket index
}

/**
 * Function Name: createHashMap
 * Purpose: Creates a hash map
 * Parameters:
 *  - size_t size: the hash_map size, determines how many buckets there will be
 * 
 * Returns:
 *  - HashMap*: The pointer to the created hashmap
 */
HashMap* createHashMap(size_t size) {
  HashMap* hash_map = (HashMap*) malloc(sizeof(HashMap));

  if (hash_map == NULL) {
    printf("Failed to allocate memory for HashMap");
    return NULL;
  }

  // allocate enough memory for a linked_list pointer times the amount of buckets we want
  hash_map->buckets = (LinkedList**) malloc(size * sizeof(LinkedList*));
  if (hash_map->buckets == NULL) {
    printf("Failed to allocate memory for Buckets");
    free(hash_map);
    return NULL;
  }

  for (size_t i = 0; i < size; i++) {
    *(hash_map->buckets + i) = createLinkedList(); 
  }

  hash_map->size = size;
  return hash_map;
}

/**
 * Function Name: hashMapInsert
 * Purpose: Inserts a element into the hash map
 * Parameters:
 *  - HashMap* hash_map: the hash_map to be modified
 *  - const char* index: the index/key to be removed
 *  - int data: the data to be inserted
 * Returns:
 *  - void
 */
void hashMapInsert(HashMap* hash_map, const char* index, const char* data) {

  if (hash_map == NULL) {
    printf("HashMap is NULL hashMapInsert");
    return;
  }

  size_t hash_index = hash(index, hash_map->size);
  Node* node = createNode(data);
  // strdup automatically calls malloc, must clean up after.
  node->key = strdup(index);
  
  linkedListInsertEnd(*(hash_map->buckets + hash_index), node);
}

/**
 * Function Name: hashMapUpdate
 * Purpose: Updates a element in the hash map
 * Parameters:
 *  - HashMap* hash_map: the hash_map to be modified
 *  - const char* index: the index/key to be updated
 *  - int data: the new data
 * Returns:
 *  - int: -1 if failed and 1 if successful
 */
int hashMapUpdate(HashMap* hash_map, const char* index, const char* data) {
  if (hash_map == NULL) {
    printf("HashMap is NULL hashMapUpdate");
    return -1;
  }

  size_t hash_index = hash(index, hash_map->size);
  LinkedList* linked_list = *(hash_map->buckets + hash_index);
  
  Node* current_node = linked_list->front;
  while (current_node != NULL) {
    if (strcmp(index, current_node->key) == 0) {
      
      if (current_node->data != NULL) {
        free(current_node->data);
      }
      current_node->data = strdup(data);
      return 1;
    };
    current_node = current_node->next;
  }

  // failed to update
  return -1;
}

/**
 * Function Name: hashMapGet
 * Purpose: Retrieves a element from the hashmap
 * Parameters:
 *  - HashMap* hash_map: the hash_map to be modified
 *  - const char* index: the index/key to be accessed
 * 
 * Returns:
 *  - int: the value retrieved, -1 if nothing is found
 */
char* hashMapGet(HashMap* hash_map, const char* index) {
  if (hash_map == NULL) {
    printf("HashMap is NULL hashMapGet");
    return NULL;
  }

  size_t hash_index = hash(index, hash_map->size);

  // current pointing to the first item at index hash_index
  LinkedList* linked_list = *(hash_map->buckets + hash_index);
  Node* current_node = linked_list->front;

  while (current_node != NULL) {
    if (strcmp(index, current_node->key) == 0) {
      return current_node->data;
    };
    current_node = current_node->next;
  }

  return NULL;
}

/**
 * Function Name: hashMapRemove
 * Purpose: Removes a element from the hashmap
 * Parameters:
 *  - HashMap* hash_map: the hash_map to be modified
 *  - const char* index: the index/key to be removed
 * 
 * Returns:
 *  - void
 */
void hashMapRemove(HashMap* hash_map, const char* index) {
  if (hash_map == NULL) {
    printf("HashMap is NULL hashMapRemove");
    return;
  }

  size_t hash_index = hash(index, hash_map->size);
  LinkedList* linked_list = *(hash_map->buckets + hash_index);
  
  Node* current_node = linked_list->front;
  Node* previous_node = NULL;

  while (current_node != NULL) {
    // we found the node in which the key resides in
    if (strcmp(index, current_node->key) == 0) {
      if (previous_node == NULL) {
        linked_list->front = current_node->next;
      } else {
        previous_node->next = current_node->next;
      }

      // node is the last element
      if (current_node == linked_list->end) {
        linked_list->end = previous_node;
      }

      freeNode(current_node);
      return;
    }

    previous_node = current_node;
    current_node = current_node->next;
  }
}

/**
 * Function Name: freeHashMap
 * Purpose: Frees the hashmap and cleans everything up
 * Parameters:
 *  - HashMap* hash_map: the hash_map to be cleaned
 * 
 * Returns:
 *  - void
 */
void freeHashMap(HashMap* hash_map) {
  if (hash_map == NULL) {
    printf("HashMap is NULL freeHashMap");
    return;
  }

  for (size_t i = 0; i < hash_map->size; i++) {
    LinkedList* linked_list = *(hash_map->buckets + i);
    freeLinkedList(linked_list);
  }

  free(hash_map->buckets);
  free(hash_map);
}

// HUFFMAN PRIORITY QUEUE STRUCTURE
typedef struct MinHeapNode {
  int freq;
  char data;
  struct MinHeapNode *left;
  struct MinHeapNode *right;
} MinHeapNode;

typedef struct MinHeap {
  struct MinHeapNode **array;
  int capacity;
  int size;
} MinHeap;

MinHeapNode* createMinHeapNode(char data, int freq);
MinHeap* createMinHeap(int capacity);
void swapNodes(MinHeapNode** a, MinHeapNode** b);
void minHeapify(MinHeap* min_heap, int i);
MinHeapNode* extractMin(MinHeap* min_heap);
void insertMinHeap(MinHeap* min_heap, MinHeapNode* node);

/**
 * Function Name: createMinHeapNode
 * Purpose: Creates a min heap node
 * Parameters:
 *  - char data: the character
 *  - int freq: frequency of the character
 * 
 * Returns:
 *  - MinHeapNode*: a new min heap node
 */
MinHeapNode* createMinHeapNode(char data, int freq) {
  MinHeapNode* node = (MinHeapNode*) malloc(sizeof(MinHeapNode));
  node->data = data;
  node->freq = freq;
  node->left = NULL;
  node->right = NULL;
  return node;
}

/**
 * Function Name: createMinHeap
 * Purpose: Creates a min heap
 * Parameters:
 *  - int capacity: The max capacity of the min heap
 * 
 * Returns:
 *  - MinHeap*: Min heap pointer
 */
MinHeap* createMinHeap(int capacity) {
  MinHeap* min_heap = (MinHeap*) malloc(sizeof(MinHeap));
  min_heap->size = 0;
  min_heap->capacity = capacity;
  min_heap->array = (MinHeapNode**) malloc(min_heap->capacity * sizeof(MinHeapNode*));
  return min_heap;
}

/**
 * Function Name: swapNodes
 * Purpose: Swaps the location of 2 min heap nodes
 * Parameters:
 *  - MinHeapNode** a: Pointer to the first min heap node pointer
 *  - MinHeapNode** b: Pointer to hte second min heap node pointer
 * 
 * Returns:
 *  - void
 */
void swapNodes(MinHeapNode** a, MinHeapNode** b) {
  MinHeapNode* t = *a;
  *a = *b;
  *b = t;
}

/**
 * Function Name: minHeapify
 * Purpose: Min Heapify to maintain heap properties
 * Parameters:
 *  - MinHeap* min_heap: The min_heap to operate on
 *  - int i: The index of the current node
 * 
 * Returns:
 *  - void
 */
void minHeapify(MinHeap* min_heap, int i) {
  int smallest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < min_heap->size && min_heap->array[left]->freq < min_heap->array[smallest]->freq)
    smallest = left;

  if (right < min_heap->size && min_heap->array[right]->freq < min_heap->array[smallest]->freq)
    smallest = right;

  if (smallest != i) {
    swapNodes(&min_heap->array[smallest], &min_heap->array[i]);
    minHeapify(min_heap, smallest);
  }
}

/**
 * Function Name: extractMin
 * Purpose: Extracts the root min heap node
 * Parameters:
 *  - MinHeap* min_heap: The min_heap to operate on
 * 
 * Returns:
 *  - MinHeapNode*: the min heap node that was extracted
 */
MinHeapNode* extractMin(MinHeap* min_heap) {
  MinHeapNode* temp = min_heap->array[0];
  min_heap->array[0] = min_heap->array[min_heap->size - 1];
  min_heap->size--;
  minHeapify(min_heap, 0);
  return temp;
}

/**
 * Function Name: insertMinHeap
 * Purpose: inserts min heap node into the min heap
 * Parameters:
 *  - MinHeap* min_heap: The min_heap to operate on
 *  - MinHeapNode* node: the node to be inserted
 * Returns:
 *  - void
 */
void insertMinHeap(MinHeap* min_heap, MinHeapNode* node) {
  if (min_heap->size >= min_heap->capacity) {
    printf("Error: MinHeap is full!\n");
    return;
  }

  min_heap->size++;

  int current_index = min_heap->size - 1;
  int parent_index = (current_index - 1)/2;

  // while the node that we are currently trying to insert has a smaller frequency compared to parent
  while (current_index > 0 && node->freq < min_heap->array[parent_index]->freq) {
    min_heap->array[current_index] = min_heap->array[parent_index];
    current_index = parent_index;
    parent_index = (current_index - 1) / 2;
  }
  min_heap->array[current_index] = node;
}

// ENCODING LOGIC
char* readFile(const char *file_name);
void getUserStringInput(char *string_input_buffer, size_t size);
void lowerString(char *string, size_t size);
void convertWhitespaceToSpace(char *string, size_t size);
char* applyCharacterFilter(char *string, size_t size);
HashMap* createFrequencyData(char *string, size_t size);
MinHeapNode* buildHuffmanTree(HashMap* hash_map);
void generateHuffmanCodes(HashMap* hash_map);
void writeHuffmanCodes(MinHeapNode* root, int codes_array[], int codes_array_index, FILE* codes_file);
void removeTrailingNewline(const char* file_name); 
HashMap* getCodesHashmap();
HashMap* getMetaDataHashmap();
void compressStringToBinary(char* string, HashMap* codes);
const char* intToString(int num);

/**
 * Function Name: intToString
 * Purpose: Int to string
 * Parameters:
 *  - const char *file_name: File name string
 * 
 * Return Value:
 *  - char* : The pointer to the starting character of the read file
 */
const char* intToString(int num) {
  static char buffer[20]; // Static buffer to hold the result
  sprintf(buffer, "%d", num); // Convert int to string
  return buffer; // Return pointer to the static buffer
}

/**
 * Function Name: readFile
 * Purpose: Reads a provided file_name and returns a pointer to the start 
 * Parameters:
 *  - const char *file_name: File name string
 * 
 * Return Value:
 *  - char* : The pointer to the starting character of the read file
 */
char* readFile(const char *file_name) {
  FILE *file = fopen(file_name, "r");

  // the file doesn't exist!
  if (file == NULL) {
    printf("File: '%s' could not be found in the local directory!", file_name);
    return NULL;
  }

  size_t buffer_size = 1024; // start with 1 KB buffer
  size_t content_size = 0;
  char *buffer = malloc(buffer_size);

  if (buffer == NULL) {
    printf("An error has occured while allocating memory.");
    fclose(file);
    return NULL;
  } 

  size_t bytes_read = 0;
  do {
    size_t item_size = sizeof(*buffer);
    size_t available_space = buffer_size - content_size;

    // read to buffer + content_size
    bytes_read = fread(buffer + content_size, item_size, available_space, file);
    content_size += bytes_read;

    if (content_size == buffer_size) {
      buffer_size *= 2;
      char *temp = realloc(buffer, buffer_size);
      if (temp == NULL) {
        printf("An error has occured while re-allocating memory");
        free(buffer);
        fclose(file);
        return NULL;
      }

      // upon successful reallocation we will update the pointer
      buffer = temp;
    }
  } while (bytes_read > 0);
  
  buffer[content_size] = '\0'; // null terminate after reading

  // shrink buffer to exact size needed;
  char *temp = realloc(buffer, content_size + 1);
  if (temp != NULL) {
    buffer = temp;
  }

  fclose(file);
  return buffer;
}

/**
 * Function Name: removeTrailingNewline
 * Purpose: Removes the trailing newline character from a file
 * Parameters:
 *  - const char *file_name: File name string
 * 
 * Return Value:
 *  - void
 */
void removeTrailingNewline(const char* file_name) {
  // Open the file for reading
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    perror("Error opening file for reading");
    return;
  }

  // Determine file size
  if (fseek(file, 0, SEEK_END) != 0) {
    perror("Error seeking to end of file");
    fclose(file);
    return;
  }

  long file_size = ftell(file);
  if (file_size < 0) {
    perror("Error getting file size");
    fclose(file);
    return;
  }
  rewind(file); // Move file pointer to the beginning

  // Allocate memory for the file content
  char* buffer = (char*)malloc(file_size + 1); // +1 for null terminator
  if (buffer == NULL) {
    perror("Error allocating memory");
    fclose(file);
    return;
  }

  // Read file into the buffer
  size_t bytes_read = fread(buffer, 1, file_size, file);
  buffer[bytes_read] = '\0'; // Null-terminate the buffer
  fclose(file); // Close the file after reading

  // Check and remove the trailing newline
  if (bytes_read > 0 && buffer[bytes_read - 1] == '\n') {
    buffer[bytes_read - 1] = '\0';
  }

  // Open the file for writing
  file = fopen(file_name, "w");
  if (file == NULL) {
    perror("Error opening file for writing");
    free(buffer);
    return;
  }

  // Write the modified content back to the file
  fprintf(file, "%s", buffer);
  fclose(file);

  // Free allocated memory
  free(buffer);
}

/**
 * Function Name: lowerString
 * Purpose: lowers the string to lower case
 * Parameters:
 *  - char *string: The pointer to the string buffer
 *  - size_t size: size of the string buffer
 * 
 * Return Value:
 *  - void
 */
void lowerString(char *string, size_t size) {

  int A_ASCII_value = 'A';
  int Z_ASCII_value = 'Z';

  // offset of the capital letters
  int offset = 'A' - 'a';

  int i = 0;

  while (*(string + i) != '\0') {
    char c = *(string + i);
    if ( c >= A_ASCII_value && c <= Z_ASCII_value) {
      *(string + i) = c - offset;
    }

    i += 1;
  }
}

/**
 * Function Name: convertWhiteSpaceToSpace
 * Purpose: Converts all whitespaces to normal space
 * Parameters:
 *  - char *string: The pointer to the string buffer
 *  - size_t size: size of the string buffer
 * 
 * Return Value:
 *  - void
 */
void convertWhitespaceToSpace(char *string, size_t size) {
  
  int i = 0;

  while (*(string + i) != '\0') {
    char c = *(string + i);
    if (c == '\t' || c == '\n' || c == '\r' || c == ' ') {
      *(string + i) = ' ';
    }

    i += 1;
  }
}

/**
 * Function Name: getUserStringInput
 * Purpose: gets user string input
 * Parameters:
 *   - char *string_input_buffer: buffer to store the string input
 *   - size_t size: the size of the string_input_buffer
 * 
 * Return Value:
 *   - void
 */
void getUserStringInput(char *string_input_buffer, size_t size) {
   // read the input and place into file_name_buffer
  if (fgets(string_input_buffer, size, stdin) != NULL) {

    // we want to remove any trailing new lines;
    // iterate while c is not \0
    int input_length = size / sizeof(*(string_input_buffer));
    int i = 0;

    // iterate size - 1 to account for \0 character
    while (i < (size - 1) && *(string_input_buffer + i) != '\0') {
      if ( *(string_input_buffer + i) == '\n') {
        *(string_input_buffer + i) = '\0'; // sets that character to \0 ending the string.
        break; // break the loop
      }
      i += 1;
    }
  } else {
    *(string_input_buffer) = '\0';
  }
}

/**
 * Function Name: applyCharacterFilter
 * Purpose: Applies a character filter which only cares for alphanumeric, 0-9, period comma and space
 * Parameters:
 *  - char *string: string to apply filter on, contents will be modified.
 *  - size_t size: size of the string
 * 
 * Return Value:
 *  - char* the starting point of the filtered string
 */
char* applyCharacterFilter(char *string, size_t size) {
  // iterate through string and apply filters;
  int filtered_index = 0;
  int i = 0;
  size_t bytes_size = 0;
  while (*(string + i) != '\0') {
    char c = *(string + i);
    if (
      c >= '0' && c <= '9' || 
      c >= 'a' && c <= 'z' || 
      c >= 'A' && c <= 'Z' || 
      c == '.' || 
      c == ',' || 
      c == ' ') {
      *(string + filtered_index) = c;
      filtered_index += 1;
      bytes_size += sizeof(c);
    }
    i += 1;
  }

  *(string + filtered_index) = '\0';

  // reallocate memory to the exact size;
  char *temp = realloc(string, bytes_size + 1);
  if (temp != NULL) {
    string = temp;
  }

  return string;
} 

/**
 * Function Name: createFrequencyData
 * Purpose: Creates a frequency.txt file and writes to it with the frequency of all the characters
 * Parameters:
 *  - char *string: string to apply filter on, contents will be modified.
 *  - size_t size: size of the string
 * 
 * Return Value:
 *  - HashMap*: The created hashmap with the frequency data.
 */
HashMap* createFrequencyData(char *string, size_t size) {
  // we want to count the frequency of each character;
  HashMap* hash_map = createHashMap(100);

  FILE* frequency_file = fopen("frequency.txt", "w");
  if (frequency_file == NULL) {
    printf("An error has occured opening the frequency.txt file");
    return NULL;
  }

  // iterate through the string and start counting;
  int i = 0;
  while (*(string + i) != '\0') {
    // every single character should be valid.

    char key[2] = { *(string+i), '\0' }; // Convert char to string key
    
    char* result = hashMapGet(hash_map, key);
    int count = 0;
    if (result == NULL) {
      hashMapInsert(hash_map, key, "1");
      count = 1;
    } else {
      count = atoi(result);
      hashMapUpdate(hash_map, key, intToString((count) + 1));
    }

    i += 1;
  }

  // requirements of the assignment require us to include any items that do not exist in the string as well.
  // this means we need to iterate through all possible characters and insert as 0 if it doesn't exist.
  // kinda disgusting but no other choice
  char comma_key[2] = ",\0";
  char space_key[2] = " \0";
  char period_key[2] = ".\0";

  int count = atoi( hashMapGet(hash_map, comma_key));
  if (count == -1) {
    hashMapInsert(hash_map, comma_key, intToString(0));
  };

  count = atoi( hashMapGet(hash_map, space_key));
  if (count == -1) {
    hashMapInsert(hash_map, space_key, intToString(0));
  };

  count = atoi( hashMapGet(hash_map, period_key));
  if (count == -1) {
    hashMapInsert(hash_map, period_key, intToString(0));
  }

  // now a-z
  char a = 'a';
  char z = 'z';
  for (char i = a; i <= z; i++) {
    char key[2] = {i, '\0'};
    count = atoi(hashMapGet(hash_map, key));

    if (count == -1) {
      hashMapInsert(hash_map, key, intToString(0));
    }
  }

  // now 0-9
  char zero = '0';
  char nine = '9';
  for (char i = zero; i <= nine; i++) {
    char key[2] = {i, '\0'};
    count = atoi(hashMapGet(hash_map, key));

    if (count == -1) {
      hashMapInsert(hash_map, key, intToString(0));
    }
  }

  // time to create the string
  size_t buffer_size = 1024; // initial buffer size
  char* buffer = malloc(sizeof(char) * buffer_size);
  size_t buffer_index = 0;

  // let's build the string to write to frequency
  // iterate through hasmap
  int hash_map_index = 0;
  while (hash_map_index < hash_map->size) {

    LinkedList* linked_list = *(hash_map->buckets + hash_map_index);
    // iterate through the linked list;
    Node* current_node = linked_list->front;
    while (current_node != NULL) {
      // process the node;
      const char *c = current_node->key;
      int count = atoi(current_node->data);

      // now we want to convert the number to string and copy it into the buffer.
      char entry[64];
      snprintf(entry, sizeof(entry), "%s:%d\n", c, count); // write our entry line
      //printf(entry);
      size_t entry_length = strlen(entry);

      // ensure buffer has enough space
      if (buffer_index + entry_length >= buffer_size) {
        buffer_size *= 2; // Double the buffer size
        char* temp = (char*)realloc(buffer, buffer_size);
        if (temp == NULL) {
          printf("Memory reallocation failed\n");
          free(buffer);
          freeHashMap(hash_map);
          fclose(frequency_file);
          return NULL;
        }
        buffer = temp;
      }

      // iterate through string and paste into buffer;
      memcpy(buffer + buffer_index, entry, entry_length);
      buffer_index += entry_length;
      current_node = current_node->next;
    }

    hash_map_index += 1;
  }

  // close the string
  // the reason for -1 is because the last character should be a \n 
  // however the amount of lines we want is very strict.
  *(buffer + buffer_index-1) = '\0';
  //printf(buffer);

  // write the buffer to the file
  fprintf(frequency_file, "%s", buffer);

  // clean up
  free(buffer);
  fclose(frequency_file);

  return hash_map;
}

/**
 * Function Name: buildHuffmanTree
 * Purpose: Creates a codes.txt file and builds a huffman tree
 * Parameters:
 *  - HashMap* hash_map: hash_map with frequency data
 * 
 * Return Value:
 *  - MinHeapNode*: The root node for the min_heap
 */
MinHeapNode* buildHuffmanTree(HashMap* hash_map) {
  // First create the min heap and then build it
  MinHeap* min_heap = createMinHeap(hash_map->size);
  for (int i = 0; i < hash_map->size; i++) {
    // Get every single linked_list in the hash_map;
    LinkedList* linked_list = *(hash_map->buckets + i);
    Node* current_node = linked_list->front;
    while (current_node != NULL) {
      MinHeapNode* node = createMinHeapNode(*(current_node->key), atoi(current_node->data));
      insertMinHeap(min_heap, node);
      current_node = current_node->next;
    }
  }

  MinHeapNode* left; 
  MinHeapNode* right; 
  MinHeapNode* top;

  while (min_heap->size != 1) {
    left = extractMin(min_heap);
    right = extractMin(min_heap);

    // create a node to act as a "buffer" node
    top = createMinHeapNode('$', left->freq + right->freq);
    top->left = left;
    top->right = right;
    insertMinHeap(min_heap, top);
  }

  return extractMin(min_heap);
}

/**
 * Function Name: writeHuffmanCodes
 * Purpose: Writes to a codes_file and creates the codes from the root of the min heap node
 * Parameters:
 *  - MinHeapNode* root: hash_map with frequency data
 *  - int[] codes_array: an array holding the current code
 *  - int codes_array_index: The current index for the codes array
 *  - FILE* codes_file: The opened codes.txt file
 * Return Value:
 *  - void;
 */
void writeHuffmanCodes(MinHeapNode* root, int codes_array[], int codes_array_index, FILE* codes_file) {
  if (root->left) {
    codes_array[codes_array_index] = 0;
    writeHuffmanCodes(root->left, codes_array, codes_array_index + 1, codes_file);
  }

  if (root->right) {
    codes_array[codes_array_index] = 1;
    writeHuffmanCodes(root->right, codes_array, codes_array_index + 1, codes_file);
  }

  if (!(root->left) && !(root->right)) {
    fprintf(codes_file, "%c:", root->data);
    //fprintf(meta_data_file, "%c:", root->data);

    int i = 0;
    while (i < codes_array_index) {
      fprintf(codes_file,"%d", codes_array[i]);
      i++;
    }

    //fprintf(meta_data_file, "%d\n", i);
    fprintf(codes_file,"\n");
  }
}

/**
 * Function Name: generateHuffmanCodes
 * Purpose: generates the huffman codes from hash map
 * Parameters:
 *  - HashMap* hash_map: hash_map with frequency data
 * Return Value:
 *  - void;
 */
void generateHuffmanCodes(HashMap* hash_map) {
  
  MinHeapNode* root = buildHuffmanTree(hash_map);

  // open a file
  const char* codes_file_name = "codes.txt";
  //const char* meta_data_file_name = "tree.txt";
  
  FILE* codes_file = fopen(codes_file_name, "w");
  //FILE* meta_data_file = fopen(meta_data_file_name, "w");

  if (codes_file == NULL) {
    printf("An error has occured opening the %s file", codes_file_name);
    return;
  }

  //if (meta_data_file == NULL) {
    //printf("An error has occured opening the %s file", meta_data_file_name);
    //return;
  //}

  // should clear the contents of codes_file;
  fclose(codes_file);
  //fclose(meta_data_file);

  codes_file = fopen(codes_file_name, "a");
  //meta_data_file = fopen(meta_data_file_name, "a");
  if (codes_file == NULL) {
    printf("An error has occured opening the %s file", codes_file_name);
    return;
  }

  //if (meta_data_file == NULL) {
    //printf("An error has occured opening the %s file", meta_data_file_name);
    //return;
  //}

  // Array is current code
  int code_array[100];
  int code_array_index = 0;
  
  writeHuffmanCodes(root, code_array, code_array_index, codes_file);
  
  fclose(codes_file);
  //fclose(meta_data_file);

  removeTrailingNewline(codes_file_name);
  //removeTrailingNewline(meta_data_file_name);
}

/**
 * Function Name: getCodesHashmap
 * Purpose: Generates a hashmap from the codes.txt file 
 * Parameters:
 * Return Value:
 *  - HashMap*: The hashmap pointer
 */
HashMap* getCodesHashmap() {
  HashMap* hash_map = createHashMap(100);

  FILE* codes_file = fopen("codes.txt", "r");
  if (codes_file == NULL) {
    perror("Error opening file for reading");
    return NULL;
  }

  // Determine file size
  if (fseek(codes_file, 0, SEEK_END) != 0) {
    perror("Error seeking to end of file");
    fclose(codes_file);
    return NULL;
  }

  long file_size = ftell(codes_file);
  if (file_size < 0) {
    perror("Error getting file size");
    fclose(codes_file);
    return NULL;
  }
  rewind(codes_file); // Move file pointer to the beginning

  // Allocate memory for the file content
  char* buffer = (char*)malloc(file_size + 1); // +1 for null terminator
  if (buffer == NULL) {
    perror("Error allocating memory");
    fclose(codes_file);
    return NULL;
  }

  // Read file into the buffer
  size_t bytes_read = fread(buffer, 1, file_size, codes_file);
  buffer[bytes_read] = '\0'; // Null-terminate the buffer
  fclose(codes_file); // Close the file after reading
  //printf("Buffer: %s\n", buffer);
  
  if (bytes_read == 0) {
    return NULL; // empty file
  }

  // split the buffer string;
  const char delim[] = "\n";

  // First token
  char *line_save_ptr;
  char *line = strtok_r(buffer, delim, &line_save_ptr);

  char *key;
  char *value;
  char *key_value_save_ptr;

  while (line != NULL) {
    //printf("Line: %s\n", line);

    key = strtok_r(line, ":", &key_value_save_ptr);
    value = strtok_r(NULL, ":", &key_value_save_ptr); 

    if (key != NULL && value != NULL) {
      hashMapInsert(hash_map, key, value);
    }

    line = strtok_r(NULL, delim, &line_save_ptr); // Get next token
  }

  return hash_map;
}

/**
 * Function Name: getMetaDataHashmap
 * Purpose: Generates a hashmap from the tree.txt file 
 * Parameters:
 * Return Value:
 *  - HashMap*: The hashmap pointer
 */
HashMap* getMetaDataHashmap() {
  HashMap* hash_map = createHashMap(100);

  FILE* meta_data_file = fopen("tree.txt", "r");
  if (meta_data_file == NULL) {
    perror("Error opening file for reading");
    return NULL;
  }

  // Determine file size
  if (fseek(meta_data_file, 0, SEEK_END) != 0) {
    perror("Error seeking to end of file");
    fclose(meta_data_file);
    return NULL;
  }

  long file_size = ftell(meta_data_file);
  if (file_size < 0) {
    perror("Error getting file size");
    fclose(meta_data_file);
    return NULL;
  }
  rewind(meta_data_file); // Move file pointer to the beginning

  // Allocate memory for the file content
  char* buffer = (char*)malloc(file_size + 1); // +1 for null terminator
  if (buffer == NULL) {
    perror("Error allocating memory");
    fclose(meta_data_file);
    return NULL;
  }

  // Read file into the buffer
  size_t bytes_read = fread(buffer, 1, file_size, meta_data_file);
  buffer[bytes_read] = '\0'; // Null-terminate the buffer
  fclose(meta_data_file); // Close the file after reading
  //printf("Buffer: %s\n", buffer);
  
  if (bytes_read == 0) {
    return NULL; // empty file
  }

  // split the buffer string;
  const char delim[] = "\n";

  // First token
  char *line_save_ptr;
  char *line = strtok_r(buffer, delim, &line_save_ptr);

  char *key;
  char *value;
  char *key_value_save_ptr;

  while (line != NULL) {
    //printf("Line: %s\n", line);

    key = strtok_r(line, ":", &key_value_save_ptr);
    value = strtok_r(NULL, ":", &key_value_save_ptr); 

    if (key != NULL && value != NULL) {
      hashMapInsert(hash_map, key, value);
    }

    line = strtok_r(NULL, delim, &line_save_ptr); // Get next token
  }

  return hash_map;
}

/**
 * Function Name: compressStringToBinary
 * Purpose: Creates a compressed.bin file with the string contents using codes and metadata
 * Parameters:
 *  - char* string: The contents
 *  - HashMap* codes: The hashmap that contains the codes as strings (e.g., "0110")
 * Return Value:
 *  - void
 */
void compressStringToBinary(char* string, HashMap* codes) {
  const char* file_name = "compressed.bin";

  // Open file in binary write mode
  FILE* file = fopen(file_name, "wb");
  if (file == NULL) {
    perror("Error opening file for writing");
    return;
  }

  // FOR DEBUGGING PURPOSES ONLY
  //FILE* encoding_debug_file = fopen("encoding_debug_file.txt", "a");
  //if (encoding_debug_file == NULL) {
    //printf("Failed to load encoding_debug_file.txt");
    //return;
  //}

  // 8 bit buffer to accumulate bits
  unsigned char buffer = 0;
  int buffer_bits = 0;

  int current_index = 0;
  while (*(string + current_index) != '\0') {
    
    // temporary buffer to create a const key
    char temp[2]; 
    temp[0] = *(string + current_index); 
    temp[1] = '\0';                     
    const char* key = temp;  

    const char* code = (hashMapGet(codes, key));
    if (code == NULL) {
      fprintf(stderr, "Error: Code not found for key '%s'\n", key);
      fclose(file);
      //fclose(encoding_debug_file);
      return;
    }

    // FOR DEBUGGING PURPOSES ONLY
    //fprintf(encoding_debug_file, "KEY: %s, CODE: %s\n", key, code);

    // Process the code bit by bit
    for (int i = 0; code[i] != '\0'; i++) {
      buffer <<= 1;                
      buffer |= (code[i] - '0');   
      buffer_bits++;

      // If the buffer is full (8 bits), write it to the file
      if (buffer_bits == 8) {
        fwrite(&buffer, 1, 1, file);
        buffer = 0;            
        buffer_bits = 0;        
      }
    }

    current_index += 1;
  }

 // Write remaining bits in the buffer (if any)
  if (buffer_bits > 0) {
    buffer <<= (8 - buffer_bits); // Pad remaining bits with zeros
    fwrite(&buffer, 1, 1, file);
  }

  fclose(file);
}

int main() {

  // prompt the user to enter file name
  printf("Enter the file name to compress: ");

  // first grab user input for the file 
  char file_name_buffer[50];
  getUserStringInput(file_name_buffer, sizeof(file_name_buffer));
  printf("Input: %s", file_name_buffer);

  // next grab the file_contents
  char* file_contents = readFile(file_name_buffer);
  //printf(file_contents);

  // lower the string of the file contents
  lowerString(file_contents, sizeof(file_contents));
  //printf(file_contents);

  // change all whitespaces to normal spaces
  convertWhitespaceToSpace(file_contents, sizeof(file_contents));
  //printf(file_contents);

  // apply character filter from requirements
  file_contents = applyCharacterFilter(file_contents, sizeof(file_contents));
  //printf(file_contents);

  // create frequency data and generates a hash_map with the frequency data
  HashMap* hash_map = createFrequencyData(file_contents, sizeof(file_contents));

  // generate huffman codes 
  generateHuffmanCodes(hash_map);

  // write to binary
  HashMap* codes_hash_map = getCodesHashmap();
  //HashMap* meta_data_hash_map = getMetaDataHashmap();

  // finally compress and finish;
  compressStringToBinary(file_contents, codes_hash_map);

  freeHashMap(hash_map);
  freeHashMap(codes_hash_map);

  return 1;
}

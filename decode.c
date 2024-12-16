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

// MAIN LOGIC
HashMap* getCodesHashmap();

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
      // here we want to reverse the order so we can search the code instead;
      //printf("KEY: %s | VALUE: %s\n", key, value);
      //printf("INSERTED KEY: %s | INSERTED CHAR: %c\n", value, (char) char_ascii);
      hashMapInsert(hash_map, value, key);
    }

    line = strtok_r(NULL, delim, &line_save_ptr); // Get next token
  }

  return hash_map;
}

/**
 * Function Name: displayBinaryFileBits
 * Purpose: displays binary file 
 * Parameters:
 * Return Value:
 *  - HashMap*: The hashmap pointer
 */
void displayBinaryFileBits(const char* filename) {
  FILE* file = fopen(filename, "rb"); // Open the file in binary read mode
  if (file == NULL) {
    perror("Error opening file");
    return;
  }

  // FOR DEBUGGING ONLY
  FILE* debug_file = fopen("decoding_debug_file.txt", "a");
  if (debug_file == NULL) {
    printf("Failed to open decoding_debug_file.txt");
    fclose(file);
    return;
  }

  unsigned char byte;
  int byte_index = 0;

  fprintf(debug_file, "Bits in %s:\n", filename);

  while (fread(&byte, 1, 1, file) == 1) {
    fprintf(debug_file, "Byte %d: ", byte_index++);
    for (int i = 7; i >= 0; i--) {
      // Extract each bit and print
      fprintf(debug_file, "%d", (byte >> i) & 1);
    }
    fprintf(debug_file, "%s", "\n");
  }

  fclose(debug_file);
  fclose(file);
}

/**
 * Function Name: decompressBinaryFile
 * Purpose: decompresses the compressed.bin file
 * Parameters:
 *  - HashMap* codes_hashmap: The codes hash map
 * Return Value:
 *  - void
 */
void decompressBinaryFile(HashMap* codes_hashmap) {
  const char* file_name = "compressed.bin";

  FILE* file = fopen(file_name, "rb");
  if (file == NULL) {
    perror("Error opening file");
    return;
  }

  unsigned char byte;
  char bit_string[32]; // to store the bits

  int allocated_memory_size = 1024;
  char *contents = malloc(sizeof(char) * allocated_memory_size);

  int bit_string_index = 0;
  int contents_index = 0;

  if (contents == NULL) {
    printf("Failed to allocate memory for content");
    fclose(file);
    return;
  }

  int bytes_added = 0;

  while (fread(&byte, 1, 1, file) == 1) {
    // Extract bits
    int i = 0;
    while (i < 8) {
      char bit_char = ((byte >> (7 - i)) & 1) + '0';
      bit_string[bit_string_index] = bit_char;
      bit_string_index += 1;

      // temporarily add null character to use the bit_string
      bit_string[bit_string_index] = '\0';

      // everytime we add a character into the bit_string check if it exist as code.
      const char* val = hashMapGet(codes_hashmap, bit_string);
      if (val != NULL) {
        // printf("Code: %s, Valid Character: %c\n", bit_string, (char) val);
        // reallocate enough memory if not enough memory
        if (bytes_added >= allocated_memory_size) {
          allocated_memory_size *= 2;
          char* new_contents = realloc(contents, allocated_memory_size);

          if (new_contents == NULL) {
            printf("An error has occured reallocating memory");
            fclose(file);
            free(contents);
            return;
          }
          contents = new_contents;
        }

        // add the extracted value to contents
        strcpy(&(*(contents + contents_index)), val);
        bytes_added += 1;
        contents_index += 1;

        // reset bit_string_index to 0 so we are extracting a new character code
        bit_string_index = 0;
      }

      i += 1;
    }
  }
  fclose(file);

  // after retrieving all information write;
  FILE* decoded_file = fopen("decoded.txt", "w");

  if (decoded_file == NULL) {
    printf("Failed to open decoded.txt for writing");
    free(contents);
    return;
  }

  fprintf(decoded_file, "%s", contents);
  free(contents);
  fclose(decoded_file);
}

int main() {

  // for debugging only
  // displayBinaryFileBits("compressed.bin");

  HashMap* code_hash_map = getCodesHashmap();
  decompressBinaryFile(code_hash_map);

  return 1;
}
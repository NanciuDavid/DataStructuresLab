#pragma once
#include "DataUtil.h" // Include header file for Student structure and related functions
#define HASHT_SIZE 26 // Define hash table size

// Define structure for each node in the hash table
typedef struct HashN
{
    Student* info; // Pointer to student information
    struct HashN* next; // Pointer to the next node in case of collisions
} HashNode, *PHashNode;

typedef HashNode** HashTable; // Define HashTable as an array of pointers to HashNode

// Function to calculate hash value for a given key
int fHash(const char* key)
{
    return key[0] % HASHT_SIZE;
}

// Function to create a new HashNode with given student information
HashNode* createHashNode(Student* info)
{
    HashNode* node = (HashNode*)malloc(sizeof(HashNode)); // Allocate memory for new node
    node->info = info; // Set student information
    node->next = NULL; // Initialize next pointer to NULL
    return node; // Return the new node
}

// Function to delete a node with given key from the hash table
void deleteHT(HashNode** hashTable, const char* key)
{
    int hashValue = fHash(key); // Calculate hash value for the key
    HashNode* collisionList = hashTable[hashValue]; // Get the collision list for the hash value

    // Search and delete the key
    if (collisionList)
    {
        if (strcmp(collisionList->info->name, key) == 0) // If key found at the head of the list
        {
            hashTable[hashValue] = collisionList->next; // Update head of the list
            deleteStudent(collisionList->info); // Delete student information
            free(collisionList); // Free memory for the node
        }
        else // Key found in middle or end of the list
        {
            while (collisionList && collisionList->next) // Traverse the list
            {
                if (strcmp(collisionList->next->info->name, key) == 0) // If next node contains the key
                {
                    HashNode* tmp = collisionList->next; // Temporarily store the next node
                    collisionList->next = tmp->next; // Update pointers to skip the node to be deleted
                    deleteStudent(tmp->info); // Delete student information
                    free(tmp); // Free memory for the node
                }
                collisionList = collisionList->next; // Move to next node
            }
        }
    }
}

// Function to get student information associated with a given key from the hash table
Student* getHT(HashNode** hashTable, const char* key)
{
    int hashValue = fHash(key); // Calculate hash value for the key
    HashNode* collisionList = hashTable[hashValue]; // Get the collision list for the hash value

    // Search for the key in the collision list
    while (collisionList)
    {
        if (strcmp(collisionList->info->name, key) == 0) // If key found
            return collisionList->info; // Return student information
        collisionList = collisionList->next; // Move to next node
    }
    return NULL; // Return NULL if key not found
}

// Function to insert student information into the hash table
void putHT(HashNode ***hashTable, Student *stud) {
    if (*hashTable == NULL) {
        (*hashTable) = (HashNode **)malloc(sizeof(HashNode *) * HASHT_SIZE);
        for (int i = 0; i < HASHT_SIZE; i++)
            (*hashTable)[i] = NULL;
    }
    
    HashNode *node = createHashNode(stud);
    int hashValue = fHash(stud->name);

    if ((*hashTable)[hashValue] == NULL) { // No collision, insert directly
        (*hashTable)[hashValue] = node;
    } else { // Collision occurred, append to collision list
        HashNode *current = (*hashTable)[hashValue];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}

// Function to print the contents of the hash table
void printHashTable(HashNode **HashTable) {
    printf("\n\tSTART");
    for(int i = 0; i<HASHT_SIZE ; i++) {
        if(HashTable[i] == NULL) {
            printf("\n\t%d, %s", i+1, "-----"); // Print empty slot if no node exists
        } else {
            printf("\n\t%d , %s", i+1, HashTable[i]->info->name); // Print student name if node exists
        }
    } 
    printf("\n\tEND");
}


void deleteLastElement(HashNode **hashTable, Student *stud) {
    if (*hashTable == NULL) {
        return;
    } else {
        int hashValue = fHash(stud->name);
        HashNode *current = hashTable[hashValue];
        HashNode *prev = NULL;

        // Traverse the linked list to find the last node
        while (current != NULL && current->next != NULL) {
            prev = current;
            current = current->next;
        }

        // Check if the last node is found
        if (current != NULL) {
            // If the last node is also the first node
            if (prev == NULL) {
                hashTable[hashValue] = NULL;
            } else {
                prev->next = NULL; // Disconnect the last node
            }
            free(current->info); // Free memory for the Student structure
            free(current); // Free memory for the HashNode structure
        }
    }
}

Student **internalStudens(HashNode **hashNode)
{
    Student** array = (Student**)malloc((HASHT_SIZE+1) * sizeof(Student));

    for(int i = 0 ; i < HASHT_SIZE ; i ++) {
        array[i] = NULL;
    }

    int index = 0 ;
    for(int i = 0 ; i < HASHT_SIZE ; i++) {
        if(hashNode[i] != NULL) {
            HashNode *collisionList = hashNode[i];
            while(collisionList != NULL && collisionList->next != NULL) {
                if(collisionList->info->reference.intRef != 0) {
                array[index] = collisionList->info;
                index ++;
                }
                collisionList = collisionList->next;
            }
        }
    }
    
    return array;
    
}

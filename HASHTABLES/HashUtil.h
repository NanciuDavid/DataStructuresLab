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
void putHT(HashNode*** hashTable, Student* stud)
{
    if (*hashTable == NULL) // If hash table is not initialized
    {
        (*hashTable) = (HashNode**)malloc(sizeof(HashNode*) * HASHT_SIZE); // Allocate memory for hash table
        for (int i = 0; i < HASHT_SIZE; i++) // Initialize each element of hash table to NULL
            (*hashTable)[i] = NULL;
    }
    HashNode* node = createHashNode(stud); // Create a new node with student information
    int hashValue = fHash(stud->name); // Calculate hash value for the student name

    // Insert the new node into the hash table
    node->next = (*hashTable)[hashValue]; // Update next pointer of the new node
    (*hashTable)[hashValue] = node; // Update hash table with the new node
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

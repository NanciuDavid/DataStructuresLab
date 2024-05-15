#define _CRT_SECURE_NO_WARNINGS
#include "stdbool.h"
#include "PQueueUtil.h"

#define LINE_SIZE 256

void printQueue(PriorityQueue* pQueue)
{
    if (pQueue->position == 0)
    {
        printf("Priority Queue is empty.\n");
        return;
    }

    printf("Priority Queue:\n");
    for (int i = 0; i < pQueue->position; i++)
    {
        printf("Name: %s, Income: %.2f, Reference: %hu\n",
               pQueue->items[i]->name,
               pQueue->items[i]->income,
               pQueue->items[i]->reference);
    }
    printf("\n");
}

int main()
{
    PriorityQueue pQueue = { .items = NULL, .position = 0, .size = 0 };

    FILE* pFile = fopen("Data.txt", "r");
    if (pFile)
    {
        char delimiter[] = ",";
        char* token = NULL;
        float income; int index = 0;
        unsigned short reference;
        char buffer[LINE_SIZE], name[LINE_SIZE];
        while (fgets(buffer, sizeof(buffer), pFile))
        {
            token = strtok(buffer, delimiter);
            strcpy(name, token);
            token = strtok(NULL, delimiter);
            income = atof(token);
            token = strtok(NULL, delimiter);
            reference = atoi(token);
            Student* stud = createStudent(name, income, reference);
            enqueue(&pQueue, stud);
        }

        // Testing changeToMinHeap function
        printf("Max Heap:\n");
        printQueue(&pQueue); // Assuming you have a printQueue function to print the priority queue
        printf("\n");

        changeToMinHeap(&pQueue);
        printf("Min Heap:\n");
        printQueue(&pQueue);
        printf("\n");

        // Testing changeToMaxHeap function
        changeToMaxHeap(&pQueue);
        printf("Reverted to Max Heap:\n");
        printQueue(&pQueue);
        printf("\n");

        //data structure operation
        Student* info = dequeue(&pQueue);
        printStudent(info);
    }
    return 0;
}

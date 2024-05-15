#pragma once
#include "DataUtil.h"
#define PQUEUE_SIZE 7
typedef struct PQueue
{
    Student** items;
    int size;
    int position;
}PriorityQueue;

void ReheapUp(Student** items, int currentIndex)
{
    if (currentIndex > 0)
    {
        int parentIndex = (currentIndex - 1) / 2;
        if (items[parentIndex]->income < items[currentIndex]->income)
        {
            Student* aux = items[parentIndex];
            items[parentIndex] = items[currentIndex];
            items[currentIndex] = aux;
            ReheapUp(items, parentIndex);
        }
    }
}

void enqueue(struct PQueue* pQueue, Student* info)
{
    if ((*pQueue).items == NULL)
    {
        (*pQueue).items = (Student**)malloc(sizeof(Student*) * PQUEUE_SIZE);
        memset((*pQueue).items, 0, sizeof(Student*) * PQUEUE_SIZE);
        (*pQueue).size = PQUEUE_SIZE;
    }
    if ((*pQueue).size > (*pQueue).position)
    {
        (*pQueue).items[(*pQueue).position] = info;
        ReheapUp((*pQueue).items, (*pQueue).position);
        (*pQueue).position++;
    }
}

void ReheapDown(PriorityQueue* pQueue, int parentIndex)
{
    int lChildIndex = 2 * parentIndex + 1;
    int rChildIndex = 2 * parentIndex + 2;

    int maxIndex = parentIndex;
    if (lChildIndex < pQueue->position)
    {
        if (pQueue->items[lChildIndex]->income > pQueue->items[parentIndex]->income)
            maxIndex = lChildIndex;
        if (rChildIndex < pQueue->position &&
            pQueue->items[rChildIndex]->income > pQueue->items[parentIndex]->income)
            maxIndex = rChildIndex;
        if (maxIndex != parentIndex)
        {
            Student* aux = pQueue->items[maxIndex];
            pQueue->items[maxIndex] = pQueue->items[parentIndex];
            pQueue->items[parentIndex] = aux;
            ReheapDown(pQueue, maxIndex);
        }
    }
}

Student* dequeue(PriorityQueue* pQueue)
{
    Student* result = NULL;
    if (pQueue->position > 0)
    {
        result = pQueue->items[0];
        pQueue->items[0] = pQueue->items[pQueue->position-1];
        pQueue->position--;
        ReheapDown(pQueue, 0);
    }
    return result;
}
void ReheapUpMin(Student** items, int currentIndex)
{
    if (currentIndex > 0)
    {
        int parentIndex = (currentIndex - 1) / 2;
        if (items[parentIndex]->income > items[currentIndex]->income)
        {
            Student* aux = items[parentIndex];
            items[parentIndex] = items[currentIndex];
            items[currentIndex] = aux;
            ReheapUpMin(items, parentIndex);
        }
    }
}

void ReheapDownMin(PriorityQueue* pQueue, int parentIndex)
{
    int lChildIndex = 2 * parentIndex + 1;
    int rChildIndex = 2 * parentIndex + 2;

    int minIndex = parentIndex;
    if (lChildIndex < pQueue->position)
    {
        if (pQueue->items[lChildIndex]->income < pQueue->items[parentIndex]->income)
            minIndex = lChildIndex;
        if (rChildIndex < pQueue->position &&
            pQueue->items[rChildIndex]->income < pQueue->items[minIndex]->income)
            minIndex = rChildIndex;
        if (minIndex != parentIndex)
        {
            Student* aux = pQueue->items[minIndex];
            pQueue->items[minIndex] = pQueue->items[parentIndex];
            pQueue->items[parentIndex] = aux;
            ReheapDownMin(pQueue, minIndex);
        }
    }
}

void changeToMinHeap(PriorityQueue* pQueue)
{

    for (int i = (pQueue->position - 2) / 2; i >= 0; i--)
    {
        ReheapDownMin(pQueue, i);
    }
}


void changeToMaxHeap(PriorityQueue* pQueue)
{
    // Reheapify all nodes starting from the last non-leaf node
    for (int i = (pQueue->position - 2) / 2; i >= 0; i--)
    {
        ReheapDown(pQueue, i);
    }
}

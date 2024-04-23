#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct LinkedListNode {
    int value;
    struct LinkedListNode *next;
    struct LinkedListNode *prev;
}Node;

Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

Node* insertNode(Node* head, Node *node) {
    if(head == NULL)  {
        return node;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
    }
    return head;
}

void displayList(Node *head) {
    if(head == NULL) {
        printf("List is empty");
    } else {
        Node *tmp = head;
        while(tmp) {
            printf("\nNode has the value : %d", tmp->value);
            // if(tmp->prev != NULL) // Check if prev pointer is not NULL
            //     printf("\nIts prev value is : %d", tmp->prev->value);
            // if(tmp->next != NULL) 
            //     printf("\nIts next value is : %d", tmp->next->value);
            tmp = tmp->next;
        }
    }
}


Node *mergeLists(Node *listOne, Node* listTwo) {
    if (listOne == NULL) {
        return listTwo; // If listOne is empty, simply return listTwo
    }

    Node *tmp = listOne;
    while (tmp->next != NULL) {
        tmp->next->prev = tmp;
        tmp = tmp->next;
    }

    tmp->next = listTwo; // Attach listTwo to the end of listOne

    if (listTwo != NULL) {
        listTwo->prev = tmp; // Update the prev pointer of the first node in listTwo
    }


    return listOne;
}


int main() {
    // Initialize the lists
    Node *list1 = NULL;
    Node *list2 = NULL;
    int length = 0;
    printf("Length of the lists: ");
    scanf("%d", &length);

    // Insert nodes into list1
    for (int i = 0; i < length; i++) {
        list1 = insertNode(list1, createNode(i));
    }

    // Insert nodes into list2
    for (int i = 0; i < length; i++) {
        list2 = insertNode(list2, createNode(length - i));
    }

    // Merge the lists
    list1 = mergeLists(list1, list2);
    
    // Display the merged list
    displayList(list1);

    return 0;
}

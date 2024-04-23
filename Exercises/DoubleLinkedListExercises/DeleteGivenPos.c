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
               // printf("\nIts prev value is : %d", tmp->prev->value);
            //if(tmp->next != NULL) 
              //  printf("\nIts next value is : %d", tmp->next->value);
            tmp = tmp->next;
        }
    }
}

void deleteGivenPos(Node **head, int pos) {
    if (pos <= 0) {
        printf("Position must be a positive integer");
        return;
    } 
    if (*head == NULL) {
        printf("List is empty");
        return;
    }
    if (pos == 1) {
        if ((*head)->next != NULL) {
            *head = (*head)->next;
            if ((*head)->prev != NULL) {
                (*head)->prev = NULL;
            }
        } else {
            *head = NULL;
        }
        return;
    }

    printf("\n\tSearching for position : %d", pos);
    int index = 1; 
    Node *tmp = *head;
    while (tmp != NULL && index < pos - 1) {
        tmp = tmp->next;
        index++;
    }
    if (tmp == NULL || tmp->next == NULL) {
        printf("Position exceeds the length of the list");
        return;
    }
    Node *nodeToDelete = tmp->next;
    tmp->next = tmp->next->next;
    if (tmp->next != NULL) {
        tmp->next->prev = tmp;
    }
}


int main() {
    //Initialize the list
    Node * head = NULL;
    int length = 0 ;
    printf("Length of the list : ");
    scanf("%d", &length);

    for(int i = 0 ; i < length ; i++) {
        head =  insertNode(head, createNode(i));
    }
    displayList(head);
    deleteGivenPos(&head, 2);
    displayList(head);
    return 0;
}
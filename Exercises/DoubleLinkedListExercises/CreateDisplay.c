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
            if(tmp->prev != NULL) // Check if prev pointer is not NULL
                printf("\nIts prev value is : %d", tmp->prev->value);
            if(tmp->next != NULL) 
                printf("\nIts next value is : %d", tmp->next->value);
            tmp = tmp->next;
        }
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
    return 0;
}
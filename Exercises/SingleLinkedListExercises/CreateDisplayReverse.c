#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct LinkedListNode {
    int value;
    struct LinkedListNode *next;
}Node;

Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}

Node* insertNode(Node* head, Node *node) {
    if(head == NULL)  {
        return node;
    } else {
        node->next = head;
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
            tmp = tmp->next;
        }
    }
}

void reverseList(Node **head) {
    Node *prevNode = NULL, *curNode = *head, *nextNode = NULL;

    while (curNode != NULL) {
        nextNode = curNode->next;
        curNode->next = prevNode;
        prevNode = curNode;
        curNode = nextNode;
    }
    *head = prevNode;
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
    reverseList(&head);
    displayList(head);
    return 0;
}
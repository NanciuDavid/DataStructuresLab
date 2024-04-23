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

int countNodes(Node *head) {
    Node *tmp = head;
    int count = 0 ; 
    while(tmp) {
        count ++;
        tmp = tmp->next;  
    }
    return count;
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
    int nodes = countNodes(head);
    displayList(head);

    printf("\n\t\tThe total number of nodes : %d",nodes);
    return 0;
}
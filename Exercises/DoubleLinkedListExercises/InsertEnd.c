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
    node->next = node->prev =  NULL;
    return node;
}

Node* insertNode(Node* head, Node *node) {
    if(head == NULL)  {
        return node;
    } else {
        head->prev = node;
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

void insertAtEnd(Node*head, int value){

    Node *node = (Node*)malloc(sizeof(Node));
    node->value = value;
    if(head == NULL) {
        head = node;
    }
    Node *tmp = head;
    while(tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = node;
    node->prev = tmp;
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
    printf("\n\n\t Before inserting");
    displayList(head);

    insertAtEnd(head, 8);
    printf("\n\n\t After inserting");
    displayList(head);

    return 0;
}
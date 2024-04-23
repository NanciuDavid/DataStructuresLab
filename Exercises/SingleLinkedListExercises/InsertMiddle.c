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
}

void insertMiddle(Node **head) {
    int value, pos;
    int index = 0 ;
    printf("\nEnter the value for the added node :");
    scanf("%d", &value);
    
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;

    printf("\nEnter the position where you want to add the node : ");
    scanf("%d", &pos);

    if (pos == 1) {
        node->next = *head;
        *head = node;
        return;
    }

    Node *tmp = *head;
    while(tmp) {
        index++;
        if(index + 1== pos) {
            node->next = tmp->next;
            tmp->next = node;
            return;
        }
        tmp=tmp->next;
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
    printf("\n\n\t Before inserting");
    displayList(head);
    
    insertMiddle(&head);
    printf("\n\n\t After inserting");
    displayList(head);

    return 0;
}
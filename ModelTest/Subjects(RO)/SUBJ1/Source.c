#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CRT_SECURE_NO_WARNINGS

typedef struct Farmacie{ 
    char *nume;
    float suprafata;
    unsigned char angajati;
    char* adresa;
}Farmacie;

typedef struct DoubleLinkedList{
    Farmacie* Farmacie;
    struct DoubleLinkedList* next;
    struct DoubleLinkedList *prev;
}Node;

Farmacie* createFarmacie(const char* nume, float suprafata, unsigned char angajati, char*adresa){
    Farmacie *farmacie = (Farmacie*)malloc(sizeof(Farmacie));
    farmacie->nume = (char*)malloc(strlen(nume)+1);
    strcpy(farmacie->nume, nume);
    farmacie->suprafata = suprafata;
    farmacie->angajati = angajati;
    farmacie->adresa = (char*)malloc(strlen(adresa)+1);
    strcpy(farmacie->adresa, adresa);

    return farmacie;
}

Node* createNode(Farmacie *farmacie) {
    Node* node = (Node*)malloc(sizeof(Node*));
    node->Farmacie = farmacie;
    node->next = node->prev = NULL;
    return node;
}

Node* insertNode(Node *head, Node *createdNode) {
    if(head == NULL) return createdNode;
    else {
        head->prev = createdNode;
        createdNode->next = head;
        head = createdNode;
    }
    return head;
}

void removeByEmployees(Node **head, unsigned char value) {
    Node *tmp = *head;
    Node *prev = NULL;
    
    while (tmp != NULL) {
        
        if (tmp->Farmacie->angajati > value) {
            if (prev == NULL) { // If current node is head
                *head = tmp->next; // Update head to the next node
                if (tmp->next != NULL) {
                    tmp->next->prev = NULL; // Update previous pointer of the new head
                }
                tmp = tmp->next; // Move to the next node
            } else {
                prev->next = tmp->next; // Connect previous node to next node
                if (tmp->next != NULL) {
                    tmp->next->prev = prev; // Connect next node to previous node
                }
                tmp = tmp->next; // Move to the next node
            }
        } else {
            prev = tmp; // Update previous node
            tmp = tmp->next; // Move to the next node
        }
    }
}



int countByArea(Node *head, float area) {
    int count = 0 ; 
    Node *tmp = head;
    while(tmp) {
        if(tmp->Farmacie->suprafata < area) {
            count ++;
        }
        tmp = tmp->next;
    }
    return count;
}

Farmacie ** arrayOfFarmacies(Node *head, char *name) {
    //Compute number of nodes 
    int size = 1 ;
    int index = 0; 
    Node* tmp = head;
    while(tmp) {
        tmp=tmp->next;
        size++;
    }


    Farmacie **vector = (Farmacie**)malloc((size+1)*sizeof(Farmacie*));

    for(int i = 0 ; i < size ; i++) {
        vector[i] = NULL;
    }

    tmp = head;
    while(tmp) {
        if(strcmp(tmp->Farmacie->nume, name) == 0 ) {
            vector[index] = tmp->Farmacie;
            index++;
        }
        tmp=tmp->next;
    }

    return vector;
}

void displayFarmacie(Farmacie *Farmacie){
    printf("\n%s, %.2f, %d, %s", Farmacie->nume, Farmacie->suprafata, Farmacie->angajati, Farmacie->adresa);
}

void displayList(Node *head) {
    if(head == NULL) return ;
    Node* tmp = head;
    while(tmp) {
        displayFarmacie(tmp->Farmacie);
        tmp =  tmp->next;
    }
}
int main(){
    
    Farmacie **vector = NULL;
    Node *head = NULL;
    FILE* fp = fopen("Data.txt", "r");
    if(fp) {
        char buffer[256], *token;
        while(fgets(buffer, sizeof(buffer), fp)) {
            char* name;
            char* addres;
            float surface;
            unsigned char no;
            token = strtok(buffer, ",");
            name = (char*)malloc(strlen(token) + 1);
            strcpy(name, token);
            token = strtok(NULL, ",");
            surface = atof(token);
            token = strtok(NULL, ",");
            no = atoi(token);
            token = strtok(NULL, ",");
            addres = (char*)malloc(strlen(token) + 1);
            strcpy(addres, token);
            Farmacie *farmacie = createFarmacie(name, surface, no, addres);
            head = insertNode(head, createNode(farmacie));
        }
    }
    displayList(head);


    vector = arrayOfFarmacies(head, "VitaCare");
    for(int i = 0 ; ; i++) {
        if(vector[i] == NULL) {
            break;
        } else 
        displayFarmacie(vector[i]);
    }
    int count = countByArea(head, 300);
    printf("\nThe nr of pharmacies with over 300sq : %d", count);

    removeByEmployees(&head, 20);

    printf("\nThe updated list : ");
    displayList(head);

}
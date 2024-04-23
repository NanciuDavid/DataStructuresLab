#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LINE_SIZE 256

union Reference {
    unsigned char intRef;
    unsigned short extRef;
};

typedef union Reference Reference;

typedef struct student {
    char *name;
    float income;
    Reference reference;
} Student;

typedef struct Node {
    struct Node* prev;
    Student* info;
    struct Node* next;
} ListNode, *PListNode;

Student* createStudent(const char*, float, unsigned short);
void printStudent(Student*);
void deleteStudent(Student*);
ListNode* createNode(Student*);
ListNode* insertTail_DLNode(ListNode*, Student*);
ListNode* mergeCircularLists(ListNode*, ListNode*);
void displayCircularList(ListNode*);
float percentageExt(ListNode*) ;
ListNode* reverseDLinkedList(ListNode **);

int main() {
    ListNode* headList = NULL;
    ListNode* headList2 = NULL;
    FILE* pFile = fopen("Data.txt", "r");
    if (pFile) {
        char delimiter[] = ",";
        char* token = NULL;
        float income;
        unsigned short reference;
        char buffer[LINE_SIZE], name[LINE_SIZE];
        while (fgets(buffer, sizeof(buffer), pFile)) {
            token = strtok(buffer, delimiter);
            strcpy(name, token);
            token = strtok(NULL, delimiter);
            income = atof(token);
            token = strtok(NULL, delimiter);
            reference = atoi(token);
            Student* stud = createStudent(name, income, reference);
            headList = insertTail_DLNode(headList, stud);
            stud = createStudent("David", 1200.3, 12);
            headList2 = insertTail_DLNode(headList2, stud);
        }
        ListNode* head = mergeCircularLists(headList, headList2);
        displayCircularList(head);
        printf("\nThe percentage of external students is : %.2f ", percentageExt(head));
        reverseDLinkedList(&head);
        displayCircularList(head);
        fclose(pFile);
    }
    return 0;
}

Student* createStudent(const char* name, float income, unsigned short ref) {
    Student* student = (Student*)malloc(sizeof(Student));
    if (student == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    student->name = (char*)malloc(strlen(name) + 1);
    if (student->name == NULL) {
        // Handle memory allocation failure
        free(student);
        return NULL;
    }
    strcpy(student->name, name);
    student->income = income;
    student->reference.extRef = ref;
    return student;
}

void printStudent(Student* stud) {
    if (stud != NULL) {
        printf("Name: %s, income: %f\n", stud->name, stud->income);
        if (stud->reference.extRef >> 15 == 1) {
            short uid = stud->reference.extRef >> 8 & 127;
            printf("University ref: %d\n", uid);
            printf("External ref: %d\n", stud->reference.extRef & 255);
        } else {
            printf("Internal ref: %d\n", stud->reference.intRef);
        }
    }
}

void deleteStudent(Student* stud) {
    if (stud != NULL) {
        free(stud->name);
        free(stud);
    }
}

ListNode* createNode(Student* stud) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    if (node == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    node->info = stud;
    node->next = node->prev = NULL;
    return node;
}

ListNode* insertTail_DLNode(ListNode* headList, Student* stud) {
    ListNode* node = createNode(stud);
    if (node == NULL) {
        // Handle memory allocation failure
        return headList; // Return original headList unchanged
    }
    if (headList == NULL) {
        node->next = node->prev = node;  // For an empty list, node points to itself
        return node;  // Return the newly created node as the head of the list
    } else {
        node->prev = headList->prev;
        node->next = headList;
        headList->prev->next = node;
        headList->prev = node;
        return headList; // Return the original head of the list
    }
}

ListNode* mergeCircularLists(ListNode* listOne, ListNode* listTwo) {
    if (listOne == NULL) {
        return listTwo; // If listOne is empty, return listTwo
    }
    if (listTwo == NULL) {
        return listOne; // If listTwo is empty, return listOne
    }

    ListNode* tailOne = listOne->prev; // Tail of listOne
    ListNode* tailTwo = listTwo->prev; // Tail of listTwo

    // Link the last node of listOne to the first node of listTwo
    tailOne->next = listTwo;
    listTwo->prev = tailOne;

    // Link the last node of listTwo to the first node of listOne
    tailTwo->next = listOne;
    listOne->prev = tailTwo;

    // Return either listOne or listTwo as the merged list
    return listOne;
}

ListNode* reverseDLinkedList(ListNode **head) {
    ListNode* current, *prev = NULL, *next = NULL;    
    current = (*head);
    while(current->next != *head) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    (*head)->next = prev; // Adjusting the next pointer of the last node
    *head = prev; // Updating the head pointer
    return *head;
}

void displayCircularList(ListNode* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    ListNode* current = head;
    do {
        printStudent(current->info);
        current = current->next;
    } while (current != head);
}

float percentageExt(ListNode* head) {
    ListNode *tmp = head;
    int size = 1;
    int count = 0 ;
    while(tmp->next != head) {
        if(tmp->info->reference.extRef >> 15 == 1) {
            count ++;
        }
        tmp = tmp->next;
        size++;
    }
    return 1.0*size/count*10;
}
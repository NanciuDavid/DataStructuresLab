#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



//CERINTE 


/*
you are given 2 simple linked lists
make them circular
make a print function to show both of them
merge the two lists so that they are sorted by internal reference

*/
union Reference
{
	unsigned char intRef;
	unsigned short extRef;
};

typedef union Reference RefInfo;

struct Student
{
	char* name;
	double income;
	RefInfo reference;
};

typedef struct Student StudentInfo;

struct Node
{
	StudentInfo* info;
	struct Node* next;
};

typedef struct Node ListNode;

//useful info memory management
StudentInfo* createStudentInfo(const char*, double, unsigned short);
void* deleteStudentInfo(StudentInfo*);
void displayStudent(StudentInfo*);
ListNode* createNode(StudentInfo*);
void insertNode(ListNode**, ListNode*);
void loadListFromFile(ListNode**, FILE*);
void printCircularList(ListNode*);
ListNode* mergeList(ListNode*, ListNode*);
ListNode* testMerge(ListNode*, ListNode*);

#define LINE_SIZE 128
#define AGENDA_SIZE 26
int main()
{
	FILE* pFileInt = fopen("Data.txt", "r");
	FILE* pFileExt = fopen("Data.txt", "r");
	ListNode* listInt = NULL;
	ListNode* listExt = NULL;
	if (pFileInt)
	{
		loadListFromFile(&listInt, pFileInt);
		fclose(pFileInt);
	}
	if (pFileExt)
	{
		loadListFromFile(&listExt, pFileExt);
		fclose(pFileExt);
	}

	// make the first list circular
	// make the second list circular

	// displaying the students 
	printf("1. Internal student print:\n\n");
	printCircularList(listInt);
	printf("\n\n2. External student print:\n\n");
	printCircularList(listExt);

	// merge lists
	listInt = mergeList(listInt, listExt);
	printf("\n\n3. Merged students print:\n\n");
	printCircularList(listInt);
}

ListNode* mergeList(ListNode* list1, ListNode* list2)
{
	ListNode* aux = list1;
	while (aux->next != list1)
	{
		aux = aux->next;
	}
	aux->next = list2;
	aux = list2;
	while (aux->next != list2)
	{
		aux = aux->next;
	}
	aux->next = list1;

	aux = list1;
	while (aux->next != list1)
	{
		ListNode* aux2 = aux->next;
		while (aux2 != list1)
		{
			if (aux->info->reference.intRef > aux2->info->reference.intRef)
			{
				StudentInfo* auxStud = aux->info;
				aux->info = aux2->info;
				aux2->info = auxStud;
			}
			aux2 = aux2->next;
		}
		aux = aux->next;
	}

	return list1;
}

void loadListFromFile(ListNode** list, FILE* pFile)
{
	char* token; char delimiter[] = ",\n";
	double income; unsigned short ref;
	char lineBuffer[LINE_SIZE], name[LINE_SIZE];
	int index = 0;
	while (fgets(lineBuffer, sizeof(lineBuffer), pFile))
	{
		token = strtok(lineBuffer, delimiter);
		strcpy(name, token);
		token = strtok(NULL, delimiter);
		income = atof(token);
		token = strtok(NULL, delimiter);
		ref = atoi(token);
		StudentInfo* stud = createStudentInfo(name, income, ref);
		ListNode* node = createNode(stud);
		insertNode(list, node);
	}
}

void printCircularList(ListNode* list)
{
	ListNode* aux = list;
	while (aux)
	{
		displayStudent(aux->info);
		aux = aux->next;
		if (aux == list)
			break;
	}
}

void displayStudent(StudentInfo* stud)
{
	if (stud)
	{
		printf("Name: %s, income: %f\n", stud->name, stud->income);
		if (stud->reference.extRef >> 15 == 1)
		{
			short uid = stud->reference.extRef >> 8 & 127;
			printf("University ref: %d\n", uid);
			printf("External ref: %d\n", stud->reference.extRef & 255);
		}
		else
		{
			printf("Internal ref: %d\n", stud->reference.intRef);
		}
	}
}
void* deleteStudentInfo(StudentInfo* stud)
{
	if (stud != NULL)
	{
		free(stud->name);
		free(stud);
	}
	return NULL;
}
void insertNode(ListNode** list, ListNode* node)
{
	if (*list == NULL)
	{
		node->next = node;
		*list = node;
	}
	else
	{
		ListNode* aux = *list;
		while (aux->next != *list) {
			aux = aux->next;
		}
		aux->next = node;
		node->next = *list;
	}
}
ListNode* createNode(StudentInfo* stud)
{
	ListNode* result = NULL;
	result = (ListNode*)malloc(sizeof(ListNode));
	result->info = stud;
	result->next = NULL;
	return result;
}


StudentInfo* createStudentInfo(const char* name, double income, unsigned short ref)
{
	StudentInfo* result = NULL;
	result = (StudentInfo*)malloc(sizeof(StudentInfo));
	result->name = (char*)malloc(strlen(name) + 1);
	strcpy(result->name, name);
	result->income = income;
	result->reference.extRef = ref;
	return result;
}
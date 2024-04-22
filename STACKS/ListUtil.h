#pragma once
#include "DataUtil.h"

typedef struct Node
{
	Student* info;
	struct Node* next;
}ListNode, *PListNode;

ListNode* createNode(Student* stud)
{
	ListNode* node = NULL;
	node = (ListNode*)malloc(sizeof(ListNode));
	node->info = stud;
	node->next = NULL;
	return node;
}
ListNode* insertStudent(ListNode* headList, Student* stud)
{
	ListNode* node = createNode(stud);
	node->next = headList;
	return node;
}
void insertListStudent(ListNode** headList, Student* stud)
{
	ListNode* node = createNode(stud);
	node->next = (*headList);
	(*headList) = node;
}
void deleteNode(ListNode* node)
{
	if (node != NULL)
	{
		//free(node->info->name);
		//free(node->info);
		deleteStudent(node->info);
		free(node);
	}
}

void printList(ListNode *head) {
	ListNode *tmp = head;
	do{
		printStudent(tmp->info);
		tmp=tmp->next;
	}while(tmp != head);
}
void deleteList(ListNode** pHeadList)
{
	while ((*pHeadList) != NULL)
	{
		ListNode* tmp = *pHeadList;
		*pHeadList = tmp->next;
		printStudent(tmp->info);
		deleteNode(tmp);
	}
}

void makeListCircular(ListNode *head) {
		if(head != NULL) {
			ListNode* tmp = head;
			while(tmp->next!= NULL) {
				tmp = tmp->next;
			}
			tmp->next = head;
		}
}


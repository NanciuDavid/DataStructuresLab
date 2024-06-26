#include "DataUtil.h"
typedef struct Node
{
	struct Node* prev;
	Student* info;
	struct Node* next;
}ListNode, *PListNode;

ListNode* createNode(Student* stud)
{
	ListNode* node = NULL;
	node = (ListNode*)malloc(sizeof(ListNode));
	node->info = stud;
	node->next = node->prev = NULL;
	return node;
}
ListNode* insertTail_DLNode(ListNode* headList, Student* stud)
{
	ListNode* node = createNode(stud);
	if (headList == NULL)
		return node;
	else
	{
		ListNode* tmp = headList;
		while (tmp->next)
			tmp = tmp->next;
		//1.connect the node to the structure
		node->prev = tmp;
		//2.connect the structure to the node
		tmp->next = node;
		return headList;
	}
}

ListNode* insertHead_SLNode(ListNode* headList, Student* stud)
{
	ListNode* node = createNode(stud);

	node->next = headList;
	return node;
}
//void insertHead_SLNode(ListNode** pHeadList, Student* stud)
//{
//	ListNode* node = createNode(stud);
//	node->next = (*pHeadList);
//	(*pHeadList) = node;
//}
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

void deleteNodeByKey(ListNode** head, const char* key)
{
    ListNode *tmp = *head;

    while(tmp) {
        if(strcmp(tmp->info->name, key) == 0) {
            if (tmp->prev != NULL) {
                tmp->prev->next = tmp->next;  // Update next of previous node
            }
            if (tmp->next != NULL) {
                tmp->next->prev= tmp->prev;  // Update prev of next node
            }
            if (tmp == *head) {
                *head = tmp->next;  // Update head if deleting the first node
            }
            deleteNode(tmp);  // Free memory for the node
            return;  // Exit after deleting the node
        }
        tmp = tmp->next;
    }
}

#define _CRT_SECURE_NO_WARNINGS
#include "HashUtil.h"
#include "main.h"

#define LINE_SIZE 256

int main(void)
{
	HashNode** hashTable = NULL;
	//PHashNode* hashTable1;
	//HashTable hashTable2;

	FILE* pFile = fopen("Data.txt", "r");
	if (pFile)
	{
		char delimiter[] = ",";
		char* token = NULL;
		float income; int index = 0;
		unsigned short reference;
		char buffer[LINE_SIZE], name[LINE_SIZE];
		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			strcpy(name, token);
			token = strtok(NULL, delimiter);
			income = atof(token);
			token = strtok(NULL, delimiter);
			reference = atoi(token);
			Student* stud = createStudent(name, income, reference);
			putHT(&hashTable, stud);
		}
		printHashTable(hashTable);
		deleteHT(hashTable, "Popa Maria");
		deleteHT(hashTable, "Paunescu Alina");
		deleteHT(hashTable, "Petre Laura");
		printHashTable(hashTable);
		//data structure operation
		Student* info = getHT(hashTable, "Popa Maria");
		printStudent(info);
	}
}
/*******************************************************************************************
* File Name          : AbhishaBhesaniya_Assignment1.cpp
* Description        : Prog8130 - Assignment 1: Linked Lists
*					   This program uses linked lists to hold and print a list of words
*					   organized by index number assosciated with each word. Each word can
*					   consist of maximum 30 characters.
*
* Author:              Abhisha Bhesaniya
* Date:                17th June, 2020
********************************************************************************************/

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_DATA_ITEMS   10					// the number of data items to be used in list

int PrevousIndex = 0;
// structure/typedef used for holding data
typedef struct {
	char name[30]; // the name to be stored
	int index; // index number of given data
} inputData;

// definition of linked list data nodes
typedef struct LinkedListNode {
	struct LinkedListNode* ptrNextNode;		// pointer to next node in list (NULL if the end)
	char						NameData[30];		// the name to be stored (no need to store index)
} LinkedListNodeDef;

// prototypes

LinkedListNodeDef* AddToLinkedList(LinkedListNodeDef* ptrHead, char* NameData, int DataIndex);// AddToLinkedList function Defination 
void PrintLinkedList(LinkedListNodeDef* ptrHead);//PrintLinkedList function Defination


// make the data positions the last 5 digits of student number
// for example if my student number ended in 94330 the data will be as supplied

// data used for test
// paste the data here that was created by Prog8130Assign1DataCreator.exe
inputData iData[10] = {
		{ "pickels", 1 },
		{ "fish", 6 },
		{ "butter", 7 },
		{ "chocolate", 5 },
		{ "car", 5 },
		{ "carrot", 3 },
		{ "orange", 6 },
		{ "milk", 1 },
		{ "allan", 9 },
		{ "kiwi", 9 }
};

// Correct order after inserting into list is:
// 1. milk
// 2. pickels
// 3. fish
// 4. carrot
// 5. butter
// 6. chocolate
// 7. orange
// 8. car
// 9. kiwi
// 10. allan

int main(void) {
	int i;

	// define linked list head
	struct LinkedListNode* ptrHead = NULL;

	// Print out the input data
	printf("Data before Linked List is:\n");
	for (i = 0; i < NUMBER_OF_DATA_ITEMS; i++)
	{
		printf("%s , %d\n", iData[i].name, iData[i].index);
	}
	// insert the data into Linked List
	for (i = 0; i < NUMBER_OF_DATA_ITEMS; i++)
	{
		ptrHead = AddToLinkedList(ptrHead, iData[i].name, iData[i].index);
	}
		

	// now print out the list in order it is stored starting at head
	PrintLinkedList(ptrHead);

	return 0;
}

// FUNCTION      : AddToLinkedList()
// DESCRIPTION   : This function takes an input of Data of 30 Char word and an index and 
//				   places them in a linked list organized by priority of index number. 
// PARAMETERS    : LinkedListNodeDef *ptrHead	- variable to store address of ptrHead
//				   char *NameData				- Array of Characters with data 
//		           int DataIndex				- Index of data
// RETURNS       : possibly updated pointer to the head of the list
LinkedListNodeDef* AddToLinkedList(LinkedListNodeDef* ptrHead, char* NameData, int DataIndex)
{
	// put code in here to add the item(s) to the linked list

	//Initialization 
	LinkedListNodeDef* ptrNewNode = NULL;
	LinkedListNodeDef* ptrCurrent = NULL;
	LinkedListNodeDef* ptrTemp = NULL;
	int CurrentIndex = 1;

	ptrNewNode = (LinkedListNodeDef*)malloc(sizeof(LinkedListNodeDef));//creating a temporary node

	strcpy_s(ptrNewNode->NameData, NameData); // storing NameData input variable into structure element NameData

	// checking weatrher memory allocation is succefull or not
	if (ptrNewNode == NULL)
	{
		printf("malloc failure !!!\n");
		return NULL;
	}

	// this if loop will execute when the function will be called for 1st time
	if (ptrHead == NULL)
	{
		ptrHead = ptrNewNode;
		ptrNewNode->ptrNextNode = NULL;
		
	}
	else 
	{
		
		// when DataIndex is 1 this if loop will add new node at start of the link list
		if (DataIndex == 1)
		{
			ptrCurrent = ptrHead;
			ptrHead = ptrNewNode;
			ptrNewNode->ptrNextNode = ptrCurrent;
			
		}
		
		else
		{

			ptrCurrent = ptrHead; // pasing head location to current 

			while (ptrCurrent->ptrNextNode != NULL)
			{
				CurrentIndex++;
				ptrCurrent = ptrCurrent->ptrNextNode;
			}
			// when the DataIndex is greater then Current index this if loop will add new node at the end of previous node
			if (DataIndex > CurrentIndex)
			{
				ptrCurrent->ptrNextNode = ptrNewNode;
				ptrNewNode->ptrNextNode = NULL;

			}
			else
			{
				ptrCurrent = ptrHead;
				ptrTemp = ptrCurrent;
				CurrentIndex = 1;

				// this block will add new node in between two node
				while (CurrentIndex != DataIndex)
				{
					ptrTemp = ptrCurrent;
					ptrCurrent = ptrCurrent->ptrNextNode;
					CurrentIndex++;
				}
				ptrTemp->ptrNextNode = ptrNewNode;
				ptrNewNode->ptrNextNode = ptrCurrent;
			
			}

		}
	}

	return ptrHead;
}

// FUNCTION      : PrintLinkedList()
// DESCRIPTION   : This function takes an input of the head of the linked list, then loops through
//				   and prints each word in the linked list until the ptrNextNode is NULL.
// PARAMETERS    : LinkedListNodeDef *ptrHead 
// RETURNS       : void
void PrintLinkedList(LinkedListNodeDef* ptrHead)
{
	// put code in here to print the linked list out

	int i = 1; // integer variable initialization with value 1

	printf(" \n Data After Linked List :\n");// this function will print Value on terminal 

	for (i = 1; i < 11; i++) // for loop to print linked list data will repete 10 times
	{

		printf(" %d. %s\n", i, ptrHead->NameData); // Display Linked list with correct order as per index number
		ptrHead = ptrHead->ptrNextNode; //Storing next linked node's value in head
	}
}
	


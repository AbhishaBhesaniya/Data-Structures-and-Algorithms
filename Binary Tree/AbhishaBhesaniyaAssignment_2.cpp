/*******************************************************************************************
* File Name          : AbhishaBhesaniyaAssignment_2.cpp
* Description        : Prog8130 - Assignment 2: Binarry Tree
*					   This program uses concept of Binarry Tree to short, hold and print a list of
*                      words in to alphabetical order without recursion.
*
* Author:              Abhisha Bhesaniya
* Date:                11th July, 2020
********************************************************************************************/

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure defining a binary tree node.  Lower sorted values will go the the left, higher to the right.
typedef struct nodeData 
{
	char name[30];				// character string of the data being stored in the node
	struct nodeData* left;		// pointer to the next node in the tree that is less than current node OR NULL if empty
	struct nodeData* right;		// pointer to the next node in the tree that is greater than current node OR NULL if empty
}node;

// structure defining a stack
typedef struct stack 
{
	node * Data;  // pointer of binary tree node
	struct stack* next;   // pointer to the next of element stack
}stack_tree;

// data to be stored in tree.  In this case there is just a character string but this could have contained more
const char* inputData[12] = {
		{ "lbshp"},
		{ "yrpmg"},
		{ "nhqgb"},
		{ "ooyyv"},
		{ "ciugl"},
		{ "hyyoy"},
		{ "fyocy"},
		{ "vnjky"},
		{ "nalxm"},
		{ "abtnf"},
		{ "gjcnb"},
		{ "kuqil"}
};

// The correct sorted order using a binary tree is:
//      abtnf
//      ciugl
//      fyocy
//      gjcnb
//      hyyoy
//      kuqil
//      lbshp
//      nalxm
//      nhqgb
//      ooyyv
//      vnjky
//      yrpmg

//Function Initialization 
node* addToBinaryTree(const char* newString, node* tree);
void printBinaryTree(node* tree);
void pushNode(stack_tree** treeHead, node* node);
node* popNode(stack_tree** treeHead);

//node* head = NULL;

int main() 
{
		//initialize required variable
		node* head = NULL;
		int i;

		//print data which we wants to enter in to binary tree
		printf("The Order Of String befor entering in to the tree is:\n");
		for (i = 0; i < 12; i++)
		{
			printf("%s\n", inputData[i]);
		}

		// put all the data into the binary tree
		for (i = 0; i < 12; i++)
		{
			head = addToBinaryTree(inputData[i], head);
		}

		//Print all the data from binary tree without recursion
		printf("\nThe Order Of String inside the tree is given below:\n");
		printBinaryTree(head);

		//return value
		return 0;
}

// FUNCTION      : addToBinaryTree
//
// DESCRIPTION   : This function will store the data in newNode into a binary tree according to alphabetical order
//
// PARAMETERS    : newString - the string that is to be stored in the binary tree in alphabetical order
//
// RETURNS       : Nothing

node* addToBinaryTree(const char* newString, node* tree)
{
	 	node* newNode = NULL;
		newNode = (node*)malloc(sizeof(node));

		strcpy_s(newNode->name, newString);
		newNode->left = NULL;
		newNode->right = NULL;
        
		//head node
		if (tree == NULL)
		{
			tree = newNode;
		}
		
		else 
		{
			nodeData* current = tree;
			nodeData* prev = NULL;

			while (current != NULL)
			{
				prev = current;
				
				//move to right node of tree if the newnode name is greterthen current name
				if (strcmp(newNode->name, current->name) < 0)
				{
					current = current->left;
				}
				//move to left node of tree if the newnode name is lessthen current name
				else 
				{
					current = current->right;
				}
			}
			if (prev != NULL)
			{
				//add data to right node off tree
				if (strcmp(newNode->name, prev->name) < 0)
				{
					prev->left = newNode;
				}
				//add data to left node off tree
				else
				{
					prev->right = newNode;
				}
			}			

		}
		//return tree
		return tree;
}

// FUNCTION      : printBinaryTree
//
// DESCRIPTION   : This function will print the entire binary tree out.  You can choose to print
//                 it using recursion but more marks will be awarded if you do it non recursively.
//
// PARAMETERS    : tree - head node of tree
//
// RETURNS       : Nothing

void printBinaryTree(node* tree)
{
	node* current = tree; 
	stack_tree* tree_stack = NULL; 
	int i = 1;

	while (i)
	{
		if (current != NULL) 
		{
			//push to data in to stack
			pushNode(&tree_stack, current);
			current = current->left;
		}
		else 
		{
			//pop data from stack
			if (tree_stack != NULL) 
			{
				current = popNode(&tree_stack);
				printf("%s\n", current->name);
				current = current->right;
			}
			else
			{
			    i = 0;
			}
		}
	}

	
}

// FUNCTION      : pushNode
//
// DESCRIPTION   : This function will store the given tree node into the stack
//
// PARAMETERS    :1] treeHead - pointer which will point to the top of the stack
//	              2] node    - it is a structure pointer to a binary tree node
// RETURNS       : Nothing

void pushNode(stack_tree** treeHead, node* node) 
{
	stack_tree* newStack; // creates a new stack element

	newStack = (stack_tree*)malloc(sizeof(stack)); // allocates memory to the new stack element

	if (newStack != NULL)
	{
		newStack->Data = node; //add data to stack
		newStack->next = (*treeHead); //linking old list with new list
		(*treeHead) = newStack; // treehead will point to newStack
		
	}
	else
	{
		printf("STACK OVERFLOW\n"); // this message will print on screen when malloc will fail
	}

}

// FUNCTION      : popNode
//
// DESCRIPTION   : This function is going to pop out the node data at the top of the stack
//
// PARAMETERS    : treeHead - pointer which will point to the top of the stack
//
// RETURNS       : treeNode - the data which is popped out of the stack

node* popNode(stack_tree** treeHead) 
{
	node* treeNode = NULL;
	stack_tree* start = NULL;

	if (*treeHead != NULL)
	{
		start = *treeHead; //pointer will point to start of stack
		treeNode = start->Data; //copy the stack data to treeNode
		*treeHead = start->next; //treeHead will point to next
		free(start); // will free the stack
		
	}

	else
	{
		printf("STACK UNDERFLOW \n"); // this message will print on screen when treeHead will be NULL
	}

	return treeNode;

}
/*******************************************************************************
* File Name          : hashAssignmentV2.cpp
* Description        : Implemenation of a hash skelleton
*
* Author:              PROG8130 / Abhisha Bhesaniya
* Date:                August 22, 2020
******************************************************************************
*/

#include "stdafx.h"
#include <string.h>
#include <stdlib.h>

unsigned int putIntoHashTable(char *ptrInputData, unsigned int bufferLength);    // function to add to hash table
unsigned int getFromHashTable(char *ptrOutputData, unsigned int bufferLength);   // function to retrieve data from hash table
unsigned int deleteFromHashTable(char* ptrOutputData, unsigned int bufferLength);
void AddToLinkList(char* Data, unsigned int bufferLength);

#define INPUT_BUFFER_SIZE         200             // local buffer used for adding data to the hash table (there is no reason in this assignment to change this value)

#define HASH_SIZE    1                           // size of hash table to be used (for testing I suggest making this number much lower)

												  // data structure used to keep track of hashed data
struct myHashStruct {
	char *ptrBuffer = NULL;                       // pointer to data stored in hash (you will need to malloc space for string to be stored)
	struct myHashStruct *ptrNextHashData = NULL;  // pointer to next item in this hash bucket (or NULL if no more)
};

struct myHashStruct *myHash[HASH_SIZE];           // create an empty hash table structure (note this is basically an arrary of linked list heads)

int main()
{
	char    inputBuffer[INPUT_BUFFER_SIZE];

	// initialize the hash table to empty one
	for (int i = 0; i < HASH_SIZE; i++)
	{
		if ((myHash[i] = (struct myHashStruct *)calloc(1, sizeof(struct myHashStruct))) == NULL)
		{
			printf("calloc failed!\n");
			return(-1);
		}
	}

	// add to hash table loop
	while (1)
	{
		printf("enter data to be added to hash table or exit when done\n");

		// get strings from the console and place in hash until nothing entered
		scanf_s("%s", inputBuffer, INPUT_BUFFER_SIZE);

		// stop adding data into hash table when "exit" is entered
		if (strcmp(inputBuffer, "exit") == 0)
			break;

		if (putIntoHashTable(inputBuffer, strlen(inputBuffer)) == HASH_SIZE)
			printf("Error putting into hash table\n");
	}

	// check if data is in hash table
	while (1)
	{
		unsigned int hashIndexNumber = 0;

		printf("Enter data to find, done when complete\n");

		// get strings from the console and check if in hash table
		scanf_s("%s", inputBuffer, INPUT_BUFFER_SIZE);

		// stop adding data into hash table when "done" is entered
		if (strcmp(inputBuffer, "done") == 0)
			break;

		if ((hashIndexNumber = getFromHashTable(inputBuffer, strlen(inputBuffer))) == HASH_SIZE)
			printf("%s not found in hash table\n", inputBuffer);
		else
			printf("%s found in hash table at %u\n", inputBuffer, hashIndexNumber);
	}
	while (1)
	{
		unsigned int hashIndexNumber = 0;

		printf("Enter data to delete, finish when complete\n");

		// get strings from the console and check if in hash table
		scanf_s("%s", inputBuffer, INPUT_BUFFER_SIZE);

		// stop adding data into hash table when "done" is entered
		if (strcmp(inputBuffer, "finish") == 0)
			break;

		if ((hashIndexNumber = deleteFromHashTable(inputBuffer, strlen(inputBuffer))) == HASH_SIZE)
			printf("%s not found in hash table\n", inputBuffer);
		else
			printf("%s deleted from  hash table at %u\n", inputBuffer, hashIndexNumber);
	}
	
	

	return 0;
}

// FUNCTION      : myHashFunction
// DESCRIPTION   :
//   Calculate a hash value to use in storing the data into the hash table
// PARAMETERS    :
//   ptrInputBuffer - a pointer to the buffer to be put into the hash table
//
// RETURNS       :
//   Hash value calculated ( HASH_SIZE on failure)

unsigned int myHashFunction(char *ptrInputBuffer)
{
	unsigned int calculatedHashValue = 5381;

	// add code to create a hashed value here!!!
	int c;

	//djb2 Algorithms
	while (c = *ptrInputBuffer++)
	{
		calculatedHashValue = c + ((calculatedHashValue << 5) + calculatedHashValue );
	}
	// make sure if hash value is bigger than the table size, the value wraps
	return calculatedHashValue % HASH_SIZE;
}

// FUNCTION      : putIntoHashTable
// DESCRIPTION   :
//   Put the supplied data into a hash table
// PARAMETERS    :
//   ptrInputBuffer - a pointer to the buffer to be put into the hash table
//   bufferLength   - how many characters are in the buffer being put into the hash table
//
// RETURNS       :
//   Hash value used ( HASH_SIZE on failure)

unsigned int putIntoHashTable(char *ptrInputData, unsigned int bufferLength)
{
	unsigned int hashValue = myHashFunction(ptrInputData); // function call to get hash value for myhash structure array index
	
	// check if the value is in the hash is null
	if (myHash[hashValue]->ptrBuffer == NULL)
	{
		myHash[hashValue]->ptrBuffer = (char*)malloc(bufferLength + 1); // allocate memory
		strcpy_s(myHash[hashValue]->ptrBuffer, bufferLength + 1, ptrInputData); // copy the ptrTnputdata data into ptrBuffer
		myHash[hashValue]->ptrNextHashData = NULL; // put NULL 
	}

	else if (myHash[hashValue]->ptrBuffer != NULL)
	{
		AddToLinkList(ptrInputData, bufferLength);//ADDToLinkList function call to add value enterd by user for same hash value
		/*this function will put new value to hed of link list*/
	}

	
	// add code to put data into the hash table!!!

	return hashValue;
}

// FUNCTION      : AddToLinkList
// DESCRIPTION   :
//   add data o start of link list
// PARAMETERS    :
//   data - a pointer to the buffer data enterd by user
//   bufferLength    - maxiumum number of characters that can be entered
//
// RETURNS       : N/A
//   
void AddToLinkList(char *Data, unsigned int bufferLength) // function call to get hash value for myhash structure array index
	
{
	unsigned int hashValue = myHashFunction(Data);

		struct myHashStruct* head = (struct myHashStruct*)malloc(sizeof(struct myHashStruct));// make head of link list
		head->ptrBuffer = (char*)malloc(bufferLength + 1); // allocate memory
		
		strcpy_s(head->ptrBuffer, bufferLength + 1, Data);// copy data into hed->ptrBuffer
		head->ptrNextHashData = myHash[hashValue];//make previously enterd value to tail
		myHash[hashValue] = head; // store recently enterd valye to head

	
	
}

// FUNCTION      : getFromHashTable
// DESCRIPTION   :
//   Read as much data as there is room for from the hash table
// PARAMETERS    :
//   ptrOutputBuffer - a pointer to the buffer to place the data read from hash table
//   bufferLength    - maxiumum number of characters that can be read
//
// RETURNS       :
//   Hash value used ( return HASH_SIZE value on failure)

unsigned int getFromHashTable(char *ptrOutputData, unsigned int bufferLength)
{
	unsigned int hashValue = myHashFunction(ptrOutputData);

	// check if the data is in the hash table here!!!
	if (myHash[hashValue]->ptrBuffer != NULL)
	{
		struct myHashStruct* getData = myHash[hashValue]; // make new temperarory structure
		while (getData->ptrBuffer != NULL) //check ptrBuffer value weather it is null or not
		{
			if (strcmp(getData->ptrBuffer, ptrOutputData) == 0) // comparesion of stored value and enterd value
			{
				printf("Data which you are looking for is ' ");// print message
				return hashValue;//reture haseValue on sucess
			}
			getData = getData->ptrNextHashData; // point to next element of list
			
		}
	}
	else 
	{
		return HASH_SIZE; //return HASH_SIZE on failure
	}

	return hashValue; //return hashValue on success
}

// FUNCTION      : deleteFromHashTable
// DESCRIPTION   :
//  delete the data enterd by user
// PARAMETERS    :
//   ptrOutputBuffer - a pointer to the buffer to place the data delete from hash table
//   bufferLength    - maxiumum number of characters that can be read
//
// RETURNS       :
//   Hash value used ( return HASH_SIZE value on failure)
unsigned int deleteFromHashTable(char* ptrOutputData, unsigned int bufferLength)
{
	
	unsigned int hashValue = myHashFunction(ptrOutputData);
	int i = 0;
	// check if the data is in the hash table here!!!
	if (myHash[hashValue]->ptrBuffer != NULL)
	{
		struct myHashStruct* deleteData = myHash[hashValue];//temp structure to store data
		struct myHashStruct* prevData = myHash[hashValue]; //to store prev data
		struct myHashStruct* nextData = myHash[hashValue]; // to store next data

		while (deleteData->ptrBuffer != NULL) //check condition to check data in ptrBuffer
		{

		    if(deleteData->ptrNextHashData != NULL)//check condition to check data in ptrNextHashData
			{
				if (i == 0)//to check 1st node of list
				{
					if (strcmp(deleteData->ptrBuffer, ptrOutputData) == 0) //compare ptrOutputData with ptrBuffer
					{
						/* remove 1st node of list*/
						myHash[hashValue] = deleteData->ptrNextHashData; //move second node of list to head of list
						free(deleteData);//free memory
						printf("Data which you want to delete for is '");// print data on screen
						
						return hashValue;// return hashValue on sucess
					}
					else
					{
						return HASH_SIZE; //return HASH_SIZE on failure
					}
				}
				else
				{
					/* remove middle nodes of list*/
					if (strcmp(deleteData->ptrBuffer, ptrOutputData) == 0) //compare ptrOutputData with ptrBuffer
					{
						nextData = deleteData->ptrNextHashData; //store current node's nextHAshData to nextData
						prevData->ptrNextHashData = nextData; //store nextData's data into prevData's next node element
						free(deleteData);//free memory
						printf("Data which you want to delete for is '");//print data on screen
						
						return hashValue; //return hashValue on success
					}
					
					prevData = deleteData; // store deleteData's value into preData

				}
				
			}
			else
			{
				/* remove last node of list*/
				deleteData->ptrBuffer = NULL; 
				deleteData->ptrNextHashData = NULL;
			   	printf("Data which you want to delete for is '");
				return hashValue; //return hashValue on success
			}
									
			i++; //increment flag
			deleteData = deleteData->ptrNextHashData; //increment node
		}
	}
	else
	{
		return HASH_SIZE; //return HASH_SIZE on failure
	}

	return hashValue; //returen hashValue on success
}

// end code *    *     *   

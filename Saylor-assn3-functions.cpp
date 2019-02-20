//***************************************************************************
//  CODE FILENAME: Saylor-assn3-funcs.cpp
//  DESCRIPTION:   Functions used in hash testing program
//	CLASS/TERM:    CS372 Summer 8 week 1
//  DESIGNER:      James Saylor
//  FUNCTIONS:     InsertIntoArray, HashTableSize, DeclareArray, InitializeArray, 
//				   AccessIntegerArray, ModuloDivision, Pseudorandom, InsertChainedHash,
//				   LinearProbing, QuadraticProbing   
//***************************************************************************
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

#include "SimmsSaylorSchnorbus-assn3-common.h"		//Global Constants	
#include "Saylor-assn3-functions.h"					//Saylor function .cpp
#include "Simms-assn3-funcs.h"						//Simms function .cpp

//*********************************************************************
//  FUNCTION: 		InsertIntoArray()
//  DESCRIPTION:	Inserts Random Integers into an array of ARRAY_SIZE 
//					without duplicates
//	INPUT:
//		Parameters:	randomArray[] - array of random integers without duplicates
//  OUTPUT:	
//		Parameters:	randomArray[] - array of random integers without duplicates
//	CALLS TO:		duplicateNumCheck(), createRandInt()
//**********************************************************************
void InsertIntoArray (int randomIntArray[]) //arrays are always passed as reference?
{
	int randNum;					//random number
	
	srand( time(NULL) );     		// seed random number generator	
	
	//generate random array of ARRAY_SIZE numbers, no duplicates!
	for ( int i = 0; i < ARRAY_SIZE; i++)
	{
		randNum = createRandInt();	
		if( duplicateNumCheck(randomIntArray, i, randNum) )
		{
			i--;
		}
		else
		{
			randomIntArray[i] = randNum;
		}	
	}	
}

//*********************************************************************
//  FUNCTION: 		HashTableSize()
//  DESCRIPTION:	Prompts the user for the size of the hash table, must be 
//					greater than or equal to MIN_HASH_SIZE
//  OUTPUT:	
//		Return Val:	int - hashTableSize - the size of the hash table 
//**********************************************************************
int HashTableSize()
{
	int hashTableSize = 0;
	
	while (hashTableSize < MIN_HASH_SIZE)
	{
		cout << "Please enter a number for your hash table that is greater or equal" 
			 << " to " << MIN_HASH_SIZE << endl; //prompt user for hash table >= 6700
		 cin >> hashTableSize;
		if (hashTableSize < MIN_HASH_SIZE) //error check user input
		{
			cout << "Error! Please enter a number that is greater than or equal"
				 << " to " << MIN_HASH_SIZE << endl << endl;
		}
	}
	return hashTableSize;
}

//*********************************************************************
//  FUNCTION: 		DeclareArray()
//  DESCRIPTION:	Dynamically Allocates memory for an array of hashTableSize
//	INPUT:
//		Parameters:	hashTableSize - size of the hashTable array	
//  OUTPUT:	
//		Return Val:	pointer to hashTable array
//**********************************************************************
/*
int *DeclareArray (int hashTableSize)
{
	int *hashTable;
	hashTable = new (nothrow) int[hashTableSize]; //place variable into dynamically allocated array
	
//	if (hashTable[0] == NULL) //confirm memory allocation
/*	{
		cout << " Error! Memory allocation failed." << endl << endl;
	}
	
	return hashTable; //return pointer to main
}
*/
//*********************************************************************
//  FUNCTION: 		InitializeArray()
//  DESCRIPTION:	Initializes all values in the hash table to 0 
//	INPUT:
//		Parameters:	hashTable[] - hash table array of hashes
//					hashTableSize - size of the hashTable array
//  OUTPUT:	
//		Parameters:	hashTable[] - hash table array of hashes
//**********************************************************************
void InitializeArray(int hashTable[], int hashTableSize)
{
	
	for (int i = 0; i < hashTableSize; i++)
	{
		hashTable[i] = 0;
	}
	
	hashTable[hashTableSize] =  0 ; //{0}; //not sure which one you guys prefer
}

//*********************************************************************
//  FUNCTION: 		AccessIntegerInArray()
//  DESCRIPTION:	Access a random Integer in the Array
//	INPUT:
//		Parameters:	randomIntArray[] - array of ints
//					count - address of integer
//  OUTPUT:	
//		Parameters:	hashTable[] - hash table array of hashes
//**********************************************************************
/*int AccessIntegerInArray (int randomIntArray[], int count)
{
	int key;
	
	if (count <= ARRAY_SIZE) //count will not access an out of bound element
	{
		key = randomIntArray[count]; //initialize count to 0 in main
	}
	return key;	
}
*/
//*********************************************************************
//  FUNCTION: 		ModuloDivision()
//  DESCRIPTION:	uses the Modulo Division technique to determine the hash
//					value for an integer in an array
//	INPUT:
//		Parameters:	hashTableSize - size of the hashTable array
//					key - the key generated using modulo division
//  OUTPUT:	
//		Return Val:	key - the key generated using modulo division
//**********************************************************************
int ModuloDivision (int hashTableSize, int key)
{
																							//std::cout << (key % hashTableSize) << std::endl;
	return ( key % hashTableSize ); //return key % hash table size
}

//*********************************************************************
//  FUNCTION: 		Pseudorandom
//  DESCRIPTION:	uses the pseudorandom technique to determine the hash
//					value for an integer in an array using the formula 
//					hash value = (key * COEFF1) + COEFF2
//  OUTPUT:	
//		Return Val:	int - hashTableSize - the size of the hash table 
//**********************************************************************
int  Pseudorandom (int hashTableSize, int key)
{
	int result;
	
	result = (key * COEFF1) + COEFF2; //y = (key * coefficient) + coefficient
	
	return ModuloDivision (hashTableSize, result);//return hash value
}

//*********************************************************************
//  FUNCTION: 		InsertChainedHash()
//  DESCRIPTION:	
//	INPUT:
//		Parameters:	hashTableSize - size of the hashTable array
//					key - the key generated using modulo division
//  OUTPUT:	
//		Return Val:	key - the key generated using modulo division
//**********************************************************************
void InsertChainedHash (chainNode **hashTable, int hashTableSize, int key)
{
	int hashValue;
	
	hashValue = ModuloDivision (hashTableSize, key); //int = ModuloDivision (key);
	
		chainNode *node = new (nothrow) chainNode;//create new node
		chainNode *temp;
	
		if (node == NULL) //check for memory allocation
		{
			cout << " Error! Memory allocation failed." << endl << endl;
		}
		else
		{
			node->num = key;
			node->next = NULL; //assign key to new node and set pointer to NULL
		
			if (hashTable[hashValue]->num == 0) //insert node at front of bucket list
			{
				hashTable[hashValue] = node;
			}
			else //if (hashTable[hashValue] != 0) //if location occupied link the nodes
			{
				node->next = hashTable[hashValue];
				hashTable[hashValue] = node;
				/*temp = hashTable[hashValue];
				
				while (temp->next != NULL){
					temp = temp->next;
				}
				
				temp->next = node;
				*/
			}
		}
}

//*********************************************************************
//  FUNCTION: 		LinearProbing()
//  DESCRIPTION:	 
//	INPUT:
//		Parameters:	hashTableSize - size of the hashTable array
//					key - the key generated using modulo division
//  OUTPUT:	
//		Return Val:	key - the key generated using modulo division
//**********************************************************************
void LinearProbing (int &hashValue, int &probeCount)
{
																					//std::cout << "inside LinearProbing" << std::endl;
	probeCount++;
	
	hashValue = hashValue + 1; //run hash value/address through collision function
																					//std::cout << "hashValue = " << hashValue << std::endl << "probeCount= " << probeCount << std::endl; 
}

//*********************************************************************
//  FUNCTION: 		QuadraticProbing()
//  DESCRIPTION:	
//	INPUT:
//		Parameters:	hashTableSize - size of the hashTable array
//					key - the key generated using modulo division
//  OUTPUT:	
//		Return Val:	key - the key generated using modulo division
//**********************************************************************
void QuadraticProbing (int &hashValue, int &probeCount)
{
	probeCount++;
	
	hashValue = (probeCount * probeCount) + hashValue;
}

//*********************************************************************
//  FUNCTION: 		RetrieveNumber()
//  DESCRIPTION:	
//	INPUT:
//		Parameters:	hashTableSize - size of the hashTable array
//					key - the key generated using modulo division
//  OUTPUT:	
//		Return Val:	key - the key generated using modulo division
//**********************************************************************
/*int RetrieveChainedNumber (chainNode **hashTable, int hashTableSize, int *randomIntArray[])
{
	int num;
	int address;
	bool numFound = false;
	int probe = 0;
	chainNode **tempHashPointer;
	
	*tempHashPointer = *hashTable[0];
	//read in odd or even random array element
	for (int i = 0; i < hashTableSize; i = i + 2)
	{
		num = randomIntArray[i];
		address = ModuloDivision (hashTableSize, num);
		probe++;
		if(tempHashPointer[address]->num == randomIntArray[i])
		{
			numFound = true;
			i = hashTableSize;
		}
		else
		{
			while (tempHashPointer[address]->next != NULL && !numFound)
			{
				probe++;
				tempHashPointer = tempHashPointer[address]->next;
				if (tempHashPointer[address]->num == randomIntArray[i])
				{
					numFound = true;
					i = hashTableSize;
				}
			}
			
		}
	
	} return probe;
	//hash the random array element/key for address
	//increment probe count
	//if adress contains correct key search is done
	//else run adress through collision function
	//if the value in the adress does not match key then run again
	//increment the probe count everytime the key is compared against the element
}

//*********************************************************************
//  FUNCTION: 		CalculateResults()
//  DESCRIPTION:	
//	INPUT:
//		Parameters:	hashTableSize - size of the hashTable array
//					key - the key generated using modulo division
//  OUTPUT:	
//		Return Val:	key - the key generated using modulo division
//**********************************************************************
double CalculateResults ()
{
	//divide items examned (probe count) by 2500 for avg
}
*/



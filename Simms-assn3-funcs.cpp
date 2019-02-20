//***************************************************************************
//  CODE FILENAME:  Simms-assn3-funcs.cpp
//  DESCRIPTION:    Functions used in hash testing program
//	CLASS/TERM: 	CS372 Summer 8 week 1
//  DESIGNER:       Chad Simms
//  FUNCTIONS:      
//***************************************************************************

#include "SimmsSaylorSchnorbus-assn3-common.h"		//Global Constants	
#include "Simms-assn3-funcs.h"						//Simms function .cpp
#include "Saylor-assn3-functions.h"					//Saylor function .cpp
#include <cstdlib>                     // for srand and rand functions
#include <iostream>						//for test purposes only

//*********************************************************************
//  FUNCTION: 		duplicateNumCheck()
//  DESCRIPTION: 	checks the array of random integers to see if there is a 
//					duplicate number
//  OUTPUT:	
//      Return Val:	bool - if duplicate is found bool is true
//**********************************************************************
bool duplicateNumCheck(int array[], int arrayLength, int numCheck)
{
	bool duplicate = false;
	
	for(int i = 0; i < arrayLength; i++)
	{
		if(numCheck == array[i])
		{
			duplicate = true;
		}
	}
	
	return duplicate;
}

//*********************************************************************
//  FUNCTION: 		createRandInt()
//  DESCRIPTION: 	creates a random number between 1 and MAX_RAND_NUM
//  OUTPUT:	
//      Return Val:	num - a random number between 1 and MAX_RAND_NUM 
//**********************************************************************
int createRandInt()
{
	int num;
	
	num = (rand() % MAX_RAND_NUM) + 1;  // random num between 1 and MAX_RAND_NUM
		
	return num;
}
//*********************************************************************
//  FUNCTION: 		InitializeChainArray()
//  DESCRIPTION:	Initializes all values in the hash table to 0 
//	INPUT:
//		Parameters:	hashTable[] - hash table array of hashes
//					hashTableSize - size of the hashTable array
//  OUTPUT:	
//		Parameters:	hashTable[] - hash table array of hashes
//**********************************************************************
void InitializeChainArray(chainNode** hashTable, int hashTableSize)
{
	for (int i = 0; i < hashTableSize; i++)
	{
		//hashTable[i] = new chainNode;
		hashTable[i]->num = 0;
		hashTable[i]->next = NULL;	
	}	
}

//*********************************************************************
//  FUNCTION: 		InsertNumIntoHash()
//  DESCRIPTION: test	
//	INPUT:
//		Parameters:	hashTableSize - size of the hashTable array
//					key - the key generated using modulo division
//  OUTPUT:	
//		Return Val:	key - the key generated using modulo division
//**********************************************************************
void InsertNumIntoHash(int hashTable[], int hashTableSize, int numArray[], 
					  testType collisionRes, keyType keyMethod)	
{
	int probeCount,			//number of attempts to find an empty key value
		key,				//key value for hash table assignment.
		keyIncrease;		//key increase amount for double hash collision

	
	//loop for each value in the random integer array
	for (int i = 0; i < ARRAY_SIZE; i++)
	{	
		probeCount = 0;			//probeCount set to 0
		keyIncrease = 0;		//keyIncrease set to 0
		
		//if the keyMethod is MODULODIVISION, then use modulo to get key
		if(keyMethod == MODULO)	
		{
			key = ModuloDivision(hashTableSize, numArray[i]);
		}
		
		//else use pseudorandom method for key
		else
		{
			key = Pseudorandom(hashTableSize, numArray[i]);	
		}
		
		keyIncrease = DoubleHash(key, hashTableSize);
		
		//while the hashTable at key location is occupied by a value
		while(hashTable[key] != 0)
		{


			//if collision resolution is to use linear probing
			if(collisionRes == LINEAR)
			{

				/*key = */LinearProbing(key, probeCount);	
				
				//Ensure key is in range of table																			
				key = key % hashTableSize;															
			}
			//if collision resolution is to use quadratic probing
			else if(collisionRes == QUADRATIC)
			{
				/*key = */QuadraticProbing(key, probeCount);
				//Ensure key is in range of table																			
				key = key % hashTableSize;	

			}
			
			//else collision resolution is double hash method
			else
			{
				//if this is the first probe attempt, get the key increase amt.
				//for the double hash method.

				probeCount++;
				
				//else increase the key by the keyincrease amount	
				key += keyIncrease;	
				
				//Ensure key is in range of table
				key = key % hashTableSize;
				
			}	//end of if
	
		}  //end of while hashtable != 0
																		
		//assign hashtable array at key location with the random int array at value i																
		hashTable[key] = numArray[i];
	
	}  //end of for loop	
	
}

//*********************************************************************
//  FUNCTION: 		DoubleHash()
//  DESCRIPTION:	
//	INPUT:
//		Parameters:	hashTableSize - size of the hashTable array
//					key - the key generated using modulo division
//  OUTPUT:	
//		Return Val:	key - the key generated using modulo division
//**********************************************************************
int DoubleHash (int hashValue, int hashTableSize)
{
	int keyIncrease;
	
	// 1st formula is moduloDivision()
	// 2nd formula(key % (hashTableSize – 2)) + 1
	keyIncrease = ModuloDivision((hashTableSize - 2), hashValue); 
	keyIncrease++;
	
	return keyIncrease;
}

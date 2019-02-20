#include "SimmsSaylorSchnorbus-assn3-common.h"		//Global Constants	
#include "Simms-assn3-funcs.h"						//Simms function .cpp
#include "Saylor-assn3-functions.h"					//Saylor function .cpp
#include <cstdlib>                     // for srand and rand functions
#include <iostream>						//for test purposes only
#include <cmath>						

//*********************************************************************
//  FUNCTION: 		RetrieveNumber()
//  DESCRIPTION:	
//	INPUT:
//		Parameters:	hashTableSize - size of the hashTable array
//					key - the key generated using modulo division
//  OUTPUT:	
//		Return Val:	key - the key generated using modulo division
//**********************************************************************
int RetrieveNumber (int *array, int *hashTable, int hashTableSize, testType resolveThisWay, keyType hashThisWay)
{
	int key;
	int count = 0;
	int keyIncrease;						//used with DoubleHash function
	int quadCount;
	bool needIncrease = true;
	
	//read in odd or even random array element
	for (int i = 0; i < ARRAY_SIZE; i++){
			//hash the random array element/key for address
		
		quadCount = 0;						//used for QuadraticProbing

			if (hashThisWay == MODULO)
				key = ModuloDivision(hashTableSize, array[i]);
			else
				key = Pseudorandom (hashTableSize, array[i]);
			
			//get the increase amount for double hash
			keyIncrease = DoubleHash (key, hashTableSize);
			
			//See if the number is at the key hash	
			while (array[i] != hashTable[key]){
				//else run address through collision function
				if (resolveThisWay == LINEAR){
				
					LinearProbing (key, count);
					
					key = key % hashTableSize;
				}
				else if (resolveThisWay == QUADRATIC){

					QuadraticProbing (key, quadCount);

					count++;
					key = key % hashTableSize;
				}
				else{

					key = keyIncrease + key;
					key = key % hashTableSize;

					count++;
				}
				
			}
			//increase count for the point where it was found
			count++;
			//increase i to evaluate every other one
			i++;
		
	}
	
	return count;
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
double CalculateResults (int findCount)
{
	double numDouble = findCount;
	//divide items examned (probe count) by 2500 for avg
	
	numDouble = numDouble/(ARRAY_SIZE/2);
	
	return numDouble;
	
}
//*********************************************************************
// FUNCTION: calculateKnuthAvg
// DESCRIPTION:  Receives the load of the hash table and returns the 
//				average according to Knuth's formulas.
// INPUT:
// Parameters: 
// File:
// OUTPUT:
// Return Val: 
// Parameters:
// File:
// CALLS TO:
//**********************************************************************
double calculateKnuthAvg (double load, testType collisionRes){
	double result;
	
	switch (collisionRes){
		case LINEAR:
			//result = (1 + (1 / (1 - load))) / 2;

			result = 1 - load;
			result = 1/result;
			result = 1 + result;
			result = result/2;
			break;
		case QUADRATIC:
			//result = 1 - log(1 - load) - (load / 2);
			result = 1 - load;
			result = log (result);
			result = 1 - result;
			result = result - (load/2);
			break;
		case DOUBLEHASH:
			//result = (- log (1 - load)) / load;
			result = 1 - load;
			result = log (result);
			result = result * (-1);
			result = result / load;
			break;

		
	}
	
	return result;
}

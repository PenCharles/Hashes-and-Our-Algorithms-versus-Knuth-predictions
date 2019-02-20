//*********************************************************************
// CODE FILENAME: 	SimmsSaylorSchnorbus-assn3-main.cpp
// DESCRIPTION:		Main program - This program demonstrates the use of
//					hashes and the efficiency of our algorithms vrs the
//					Knuth predictions.
// CLASS/TERM: 		CS372 Summer 8 week 1
// DESIGNER:		Chad Simms, James Saylor, Kenneth Schnorbus	
// FUNCTIONS:		
//	James Saylor 	InsertIntoArray(int randomIntArray[])
//						Inserts Random integers into an array of
//						ARRAY_SIZE without duplicates; passes array by
//						reference

//	James Saylor	HashTableSize - Prompts the user for
//						the size of the hash table, must be greater than
//						or equal to MIN_HASH_SIZE; returns an int with
//						the size

//	James Saylor	InitializeArray(int hashTable[], int hashTableSize)
//						Receives an int array and an int array size, 
//						sets all values in the to 0

//	James Saylor	AccessIntegerInArray(int randomIntArray[], int count, int key)
//						accesses the array based on count and assigns integer to
//						the key, returns key to main	

//	James Saylor	ModuloDivision(int hashTableSize, int key)
//						hashes the key and returns address to main
						
//	James Saylor	Pseudorandom(int hashTableSize, int key)
//						hashes the key and returns address to main

//	James Saylor	InsertChainedHash(chainNode* hashTable[], int hashTableSize, int key)
//						call ModuloDivision to hash key. Creates a new node and 
//						confirms memory allocation and inserts node into chained array

//	James Saylor	LinearProbing(int &hashValue, int &probeCount)
//						rehashes the hash value by adding 1 and returns it to main

//	James Saylor	QuadraticProbing(int &hashValue, int &probeCount)
//						squares the probeCount and adds that to the address to get
//						a new hash value and returns it to main

//	Ken Schnorbus 	RetrieveNumber

//	Ken Schnorbus	CalculateResults

//	Chad Simms		CreateRandomInt ()
//						Creates a random number between 1 and
//						MAX_RAND_NUM, returns that number

//	Chad Simms		duplicateNumberCheck(int array[], int arrayLength,
//										 int numCheck)
//						Verifies numCheck is not in the array, then
//						returns true if it is, false if not

//	Chad Simms		InitializeChainArray(chainNode* hashTable[],
//										 int hashTableSize)
//						Initializes all values in the hash table to 0

//	Chad Simms		InsertNumIntoHash(int hashTable[],
//									int hashTableSize, int numArray[],
//									testType collisionRes,
//									keyType keyMethod)
//						takes each random int inside numArray[] and inserts it 
//						into the hashTable of hashTableSizeusing the keyMethod 
//						and collision resolution types passed in.
//
//  Chad Simms		DoubleHash() - returns the increase amount for double hash 
//						collision resolution  
//**********************************************************************

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime> 

using namespace std;

#include "SimmsSaylorSchnorbus-assn3-common.h"      

// Function Prototypes =================================================
#include "Simms-assn3-funcs.h"    			  	//Functions by Chad Simms
#include "Saylor-assn3-functions.h"    			//Functions by James Saylor
#include "Schnorbus-assn3-functions.h"    		//Functions by Kenneth Schnorbus



// Main Program ========================================================
//*********************************************************************
// FUNCTION: 	main
// DESCRIPTION: This function is the main part of the hashing program.  
//				It calls functions to create a list of random integers, 
//				hashes those integers into a hash table, and runs collision 
//				resolution if needed.
// INPUT:
// 		Parameters: 
// 		File:
// OUTPUT:
// 		Return Val: 4 - Memory allocation error
// 		Parameters:
// CALLS TO:
//**********************************************************************

int main (){
	
	int hashSize;					//stores user input for hash table size
	char userInput;					//userInput for questions asked
	bool input = false;				//bool for verified input
	testType testThisWay;			//used to send out the way we want to
									// resolve collisions
	keyType hashThisWay;			//Hash the numbers in this manner
	int *hashTable;
	int *numArray;
	int findCount = 0;				//keeps track of the numbers probed before found
	int key;
	double numDouble;
	double load;					//used to calculate the load
	double avg;
	double KnuthAvg;
	chainNode **chainTable = NULL;	//Table for the chain hash
	chainNode *tempNode = NULL;		//used for deleting the array
	chainNode *delNode;				//used to delete node
	
	// Create Array for random numbers
	numArray = new (std::nothrow) int[ARRAY_SIZE];
	
	if (numArray == NULL){
		return 4;			//memory allocation error return
		
	}
	
	
	//Introduction
	cout << "  Welcome to the Knuth Algorithm Compare program." << endl
		 << "==================================================" << endl
		 << " Written and compiled by Chad Simms, James Saylor," << endl
		 << " and Ken Schnorbus for CS 372 Assignment 3." << endl << endl;
	
		
	// Create Unsorted List
	InsertIntoArray (numArray);
																
	// Get Hash Table Size
	hashSize = HashTableSize();


	// Run Tests - Run a test by sending each random number through
	// the hash algorithm.  If there are collisions, resolve using one
	// of the four collision resolution methods: Linear Probing,
	// Quadratic Probing, Double Hashing, Seperate Chaining.  The 
	// test will display after each test

	// Ask for Modulo or Pseudorandom
	do{
	
	std::cout << " Would you like to use (M)odulo or (P)seudorandom hashing? " << std::endl;
		std::cin >> userInput;
		userInput = toupper(userInput);
		
		switch (userInput){
			
			case 'M':
				input = true;
				hashThisWay = MODULO;
				break;
			case 'P':
				input = true;
				hashThisWay = PSEUDO;
				break;
			default:
				std::cout << std::endl << "Incorrect response.  Please try again." << std::endl << std::endl;
				break;
		}
	}
	while (!input);
	
	//calculate the load ratio of the hash tables
	double temp = ARRAY_SIZE;																					
	load = temp/hashSize;

	//Begin display of results
	cout << " There were " << ARRAY_SIZE << " random numbers loaded into a " << hashSize
		 << " element hash table." << endl << " Load Factor: " << fixed << showpoint << setprecision(3) << load << endl << endl << endl;
		 
	cout << "Results for searching " << ARRAY_SIZE/2 << " items:" << endl << endl;
		 
		// Run Test
			// Create hash table
			hashTable = new (std::nothrow) int[hashSize];
			
			if (hashTable == NULL){
			//	std::cout << ALLOCATE_ERROR << EXITING << std::endl;
				return 4;
			} 
		
			// Initialize hash table
			InitializeArray (hashTable, hashSize);
			
			// Fill hash table using Linear Probing
				InsertNumIntoHash (hashTable, hashSize, numArray, testThisWay,
									hashThisWay);

				
			// Search for half the values again, odd or even
				// Hash first value/2
				
					// Increase count by 1
					// Compare value stored at location
					// If not found, increase address by one
					// Repeat until found
				// Repeat until end of list
				findCount = RetrieveNumber(numArray, hashTable, hashSize, testThisWay, hashThisWay);



			// Calculate search results
			avg = CalculateResults (findCount);
			// Calculate Knuth Predictions
			KnuthAvg = calculateKnuthAvg (load, testThisWay);
				
			// Display Results to screen
			cout << "     Linear Probing:" << endl
				 << "           " << findCount << " items examined: avg = " << fixed << showpoint << setprecision(3) << avg << " per item searched" << endl
				 << "          Knuth predicted avg: " << KnuthAvg << " per item searched" << endl << endl;
			
			
		//Repeat for the first three tests
			//Initialize hashTable
			InitializeArray (hashTable, hashSize);
			
			//Set the collision resolution to Quadratic Probing
			testThisWay = QUADRATIC;
		
		
			//Fill hash table using Quadratic Probing	
			InsertNumIntoHash (hashTable, hashSize, numArray, testThisWay,
								hashThisWay);

			//Search for half the numbers
			findCount = RetrieveNumber(numArray, hashTable, hashSize, testThisWay, hashThisWay);

			// Calculate search results
			avg = CalculateResults (findCount);
			// Calculate Knuth Predictions
			KnuthAvg = calculateKnuthAvg (load, testThisWay);

			//Display Quadratic Probing results
			cout << "     Quadratic Probing:" << endl
				 << "           " << findCount << " items examined: avg = " << fixed << showpoint << setprecision(3) << avg << " per item searched" << endl
				 << "          Knuth predicted avg: " << KnuthAvg << " per item searched" << endl << endl;

			//Initialize hashTable
			InitializeArray (hashTable, hashSize);
			
			//Set the collision for double hashing
			testThisWay = DOUBLEHASH;
			
			//Fill hash table using Quadratic Probing	
			InsertNumIntoHash (hashTable, hashSize, numArray, testThisWay,
								hashThisWay);
		
			//Search for half the numbers
			findCount = RetrieveNumber(numArray, hashTable, hashSize, testThisWay, hashThisWay);

			// Calculate search results
			avg = CalculateResults (findCount);
			// Calculate Knuth Predictions
			KnuthAvg = calculateKnuthAvg (load, testThisWay);
			
			//Display DoubleHash Results
			cout << "     Double Hashing:" << endl
				 << "           " << findCount << " items examined: avg = " << fixed << showpoint << setprecision(3) << avg << " per item searched" << endl
				 << "          Knuth predicted avg: " << KnuthAvg << " per item searched" << endl << endl;						

		
		// Run Test for chaining
			// Create hash table
			chainTable = new (nothrow) chainNode*[hashSize];
			
			if (chainTable == NULL){
				//cout << ALLOCATE_ERROR << EXITING << endl;
				return 4;
			}
																			
			for (int i = 0; i < hashSize; i++){
			
				chainTable[i] = new (nothrow) chainNode;
			
			}
			
			//Initialize the chain table
			InitializeChainArray (chainTable, hashSize);
			
			// Fill hash table
				// Hash first value
				// Create node at hash value
				// Link node into chain
				// Store value in node
			// Repeat until end of list
		for (int i = 0; i < ARRAY_SIZE; i++){
			
			InsertChainedHash (chainTable, hashSize, numArray[i]);
			
		}

	findCount = 0;
	
	// Search for half the values again
	for (int i = 0; i < ARRAY_SIZE; i = i + 2){
		bool found = false;
		key = ModuloDivision(hashSize, numArray[i]);
		findCount++;
		if (chainTable[key]->num == numArray[i]){
			found = true;
			
		}
		else{
			tempNode = chainTable[key]->next;
			while(!found){
				findCount++;
				if (tempNode == NULL)
					return 3;
				if (tempNode->num == numArray[i]){						
					found = true;
				}
				else
					tempNode = tempNode->next;
			}
		}
		
	}
	
	// Calculate search results
	numDouble = findCount;
	avg = numDouble/(ARRAY_SIZE/2);
	// Calculate Knuth Predictions
	KnuthAvg = 1 + (load/2);
	
	// Display Results for Chained hashing
	cout << "     Seperate Chaining Hashing:" << endl
		 << "           " << findCount << " items examined: avg = " << avg << " per item searched" << endl
		 << "          Knuth predicted avg: " << KnuthAvg << " per item searched" << endl << endl;
			

	//deallocate memory
	delete [] numArray;
	delete [] hashTable;
	delete [] chainTable;				
	
	return 0;
}


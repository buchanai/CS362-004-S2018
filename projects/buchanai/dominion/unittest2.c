/**********************************************************
 * Created by: Ian Buchanan
 * Course: CS362-400
 * Description: Unit Test 2 - tests the update coins function
 *	in the dominion.c implementation.
**********************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
/**********************************************************
 * Test helper functions
**********************************************************/
int testCount(int post, int pre){
	//Make sure the player handCount remained unchanged.
	if(post != pre){
		return -1;
	}	
	else{
		return 0;
	}
}
/*
int testCoinCount(strcut gameState *st, int pre){
//Test the manual pre count vs the post count.
	int post = *st->coins;
	if(post != pre){
		return -1;
	}
	else{
		return 0;
	}
}*/


/*********************************************************
 * Main
*********************************************************/
int main(){
	//variables
	struct gameState testState;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int seed = 30;
	int currentPlayer = 0;
	int tempCount = 5;
	int bonusNone = 0;
	int bonusOne = 1;
	int bonusFive = 5;
	int coinPre = 0;
	int r = 0;
	int retVal = 0;
	int fail = 0;
	int f = 0;
	initializeGame(2, k, seed, &testState);

	//Set necessary variables
	testState.handCount[currentPlayer] = tempCount;

	printf("\n-----UNIT TEST 2-----\n");
	printf("Testing updateCoins() function in dominion.c.\n");

	/*************************************************
 	* TEST HAND 1
 	*************************************************/
	printf("   TEST AVERAGE RANGE WITH BONUSES - 6 coins + 0/1/5.\n"); 	
	//coin value = 6 + no bonus
	testState.hand[currentPlayer][0] = copper;
	testState.hand[currentPlayer][1] = silver;
	testState.hand[currentPlayer][2] = gold;	
	testState.hand[currentPlayer][3] = village;
	testState.hand[currentPlayer][4] = estate;

	//coin total
	coinPre = 6 + bonusNone;

	r = updateCoins(currentPlayer, &testState, bonusNone);	
	if(r != 0){
		printf("CRITICAL FAILURE IN FUCNTION!");
	}
	//test hand count
	retVal = testCount(*testState.handCount, tempCount);
	if (retVal != 0){
		fail = -1;
	}
	//test coin count
	retVal = testCount(testState.coins, coinPre);
	if (retVal != 0){
		fail = -1;
	}	
	//State success
	if (fail == 0){
		printf("\tTest hand 1 SUCCESSFUL.\n");
	}
	else{
		printf("\tTest hand 1 FAIL.\n");
		f = -1;	//function fail
	}
	
	/*************************************************
 	* TEST HAND 2
 	*************************************************/ 	
	//coin value = 6 + 1 bonus
	testState.hand[currentPlayer][0] = copper;
	testState.hand[currentPlayer][1] = silver;
	testState.hand[currentPlayer][2] = gold;	
	testState.hand[currentPlayer][3] = village;
	testState.hand[currentPlayer][4] = estate;
	//coin total
	coinPre = 6 + bonusOne;

	r = updateCoins(currentPlayer, &testState, bonusOne);	
	if(r != 0){
		printf("CRITICAL FAILURE IN FUCNTION!");
	}

	//test hand count
	retVal = testCount(*testState.handCount, tempCount);
	if (retVal != 0){
		fail = -1;
	}
	//test coin count
	retVal = testCount(testState.coins, coinPre);
	if (retVal != 0){
		fail = -1;
	}	
	//State success
	if (fail == 0){
		printf("\tTest hand 2 SUCCESSFUL.\n");
	}
	else{
		printf("\tTest hand 2 FAIL.\n");
		f = -1;	//function fail
	}

	/*************************************************
 	* TEST HAND 3
 	*************************************************/ 	
	//coin value = 6 + 5 bonus
	testState.hand[currentPlayer][0] = copper;
	testState.hand[currentPlayer][1] = silver;
	testState.hand[currentPlayer][2] = gold;	
	testState.hand[currentPlayer][3] = village;
	testState.hand[currentPlayer][4] = estate;
	//coin total
	coinPre = 6 + bonusFive;

	r = updateCoins(currentPlayer, &testState, bonusFive);	
	if(r != 0){
		printf("CRITICAL FAILURE IN FUCNTION!");
	}

	//test hand count
	retVal = testCount(*testState.handCount, tempCount);
	if (retVal != 0){
		fail = -1;
	}
	//test coin count
	retVal = testCount(testState.coins, coinPre);
	if (retVal != 0){
		fail = -1;
	}	
	//State success
	if (fail == 0){
		printf("\tTest hand 3 SUCCESSFUL.\n");
	}
	else{
		printf("\tTest hand 3 FAIL.\n");
		f = -1;
	}	

	/*************************************************
 	* TEST HAND 4 - NO GOLD, NO BONUS
 	*************************************************/
	printf("   TESTING LOWER LIMIT - 0 coins.\n"); 	
	//coin value = 0 + no bonus
	testState.hand[currentPlayer][0] = smithy;
	testState.hand[currentPlayer][1] = village;
	testState.hand[currentPlayer][2] = estate;	
	testState.hand[currentPlayer][3] = village;
	testState.hand[currentPlayer][4] = estate;

	//coin total
	coinPre = 0 + bonusNone;

	r = updateCoins(currentPlayer, &testState, bonusNone);	
	if(r != 0){
		printf("CRITICAL FAILURE IN FUCNTION!");
	}
	//test hand count
	retVal = testCount(*testState.handCount, tempCount);
	if (retVal != 0){
		fail = -1;
	}
	//test coin count
	retVal = testCount(testState.coins, coinPre);
	if (retVal != 0){
		fail = -1;
	}	
	//State success
	if (fail == 0){
		printf("\tTest hand 4 SUCCESSFUL.\n");
	}
	else{
		printf("\tTest hand 4 FAIL.\n");
		f = -1;
	}
	
	/*************************************************
 	* TEST HAND 5 - UPPER LIMIT
 	*************************************************/
	printf("   TESTING UPPER LIMIT - 20 coins.\n"); 	
	//coin value = 15 + 5 bonus
	testState.hand[currentPlayer][0] = gold;
	testState.hand[currentPlayer][1] = gold;
	testState.hand[currentPlayer][2] = gold;	
	testState.hand[currentPlayer][3] = gold;
	testState.hand[currentPlayer][4] = gold;
	//coin total
	coinPre = 15 + bonusFive;

	r = updateCoins(currentPlayer, &testState, bonusFive);	
	if(r != 0){
		printf("CRITICAL FAILURE IN FUCNTION!");
	}

	//test hand count
	retVal = testCount(*testState.handCount, tempCount);
	if (retVal != 0){
		fail = -1;
	}
	//test coin count
	retVal = testCount(testState.coins, coinPre);
	if (retVal != 0){
		fail = -1;
	}	
	//State success
	if (fail == 0){
		printf("\tTest hand 5 SUCCESSFUL.\n");
	}
	else{
		printf("\tTest hand 5 FAIL.\n");
		f = -1;
	}

	if(f == 0){
		printf("-----TEST SUCCESSFULLY COMPLETED-----\n");
	}
	else{
		printf("-----TEST FAILED-----\n");
	}	
	//End
	return 0;
}

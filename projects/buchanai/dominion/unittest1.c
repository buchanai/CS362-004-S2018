/**************************************************************
 * Created by: Ian Buchanan
 * Course: CS362-400
 * Description: Unit Test Suite - unit test 1 program.
 *	Tests the endturn function in dominion.c implementation
**************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/**************************************************************
 * Test Functions
**************************************************************/
int testHand(struct gameState *st, int currentPlayer){
//Did the function change the hand value for each  to -1?
	int i;
	//Loop through the current player's array of cards and check value.
	for(i = 0; i < st->handCount[currentPlayer]; i++){
		//if the hand is not completely set to -1 return a bad test val.
		if(st->hand[currentPlayer][i] != -1){
			return -1;
		}
	}
	return 0;
}

int testHandCount(struct gameState *st){	
//Did the function set the current player's handCount to 0?
	if(*st->handCount != 0){
		return -1;
	}
	else{
		return 0;
	}
}
 
int testDeterminePlayer(struct gameState *st, int currentPlayer){
//Did the function select the correct player?
//Current player should be set to 1 after endTurn call.

	//printf("currentPlayer variable set to: %i\n", currentPlayer);
	if(st->whoseTurn != 1){
		return -1;
	} 
	else{
		return 0;
	}
}

int testStateVariables(struct gameState *st, int currentPlayer){

	if(st->outpostPlayed != 0){
		printf("outpostPlayed variable incorrect.\n");
		return -1;
	}
	else if(st->phase != 0){
		printf("phase variable incorrect.\n");
		return -1;
	}
	else if(st->numActions != 1){
		printf("numActions variable incorrect.\n");
		return -1;
	}
	//else if(st->coins != 0){	//do not test coins - update coins function called at end of endturn() for next player.
	//	printf("coins variable incorrect.\n");
	//	return -1;
	//}
	else if(st->numBuys != 1){
		printf("numBuys variable inccorrect.\n");
		return -1;
	}
	else if(st->playedCardCount != 0){
		printf("playedCardCount variable incorrect.\n");
		return -1;
	}
	else if(st->handCount[currentPlayer] != 0){
		printf("handCount variable incorrect.\n");
		return -1;
	}
	else{
		return 0;
	}	
}

/*
drawCard() and updateCoins() are functions called within endTurn()
which seperately alter the state of the game. These two functions
are not included in this unit test. 
*/

/**************************************************************
 * Main
**************************************************************/

int main(){

	//set necessary variables to test endTurn()
	struct gameState testState;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};	
	int seed = 30;
	int currentPlayer = 0;
	//int tempHand = 5;
	int tempCount = 5;
	//int i;
	int res = 0;

	//initialize game
	initializeGame(2, k, seed, &testState);

	//set temp hand
	testState.hand[currentPlayer][0] = copper;
	testState.hand[currentPlayer][1] = estate;
	testState.hand[currentPlayer][2] = village;
	testState.hand[currentPlayer][3] = steward;
	testState.hand[currentPlayer][4] = adventurer;

	//set beginning values
	//testState.hand[currentPlayer][i] = tempHand;
	testState.handCount[currentPlayer] = tempCount;
	testState.whoseTurn = currentPlayer;
	testState.outpostPlayed = 1;
	testState.phase = 2;	
	testState.numActions = 2;
	testState.coins = 3;
	testState.numBuys = 0;
	testState.playedCardCount = 2;

	//Call function being tested.
	endTurn(&testState);

	//Run Tests
	printf("-----UNIT TEST 1-----\n");
	printf("Testing the endTurn() fucntion.\n");	
	printf("\nCalling endturn with values set to: \n");
	printf("testState->hand[currentPlayer][i] = 5 \ntestState->handCount[currentPlayer] = 5\n");
	printf("testState->whoseTurn = currentPlayer \ntestState->outpostPlayed = 1 \ntestState->phase = 2\n");	
	printf("testState->numActions = 2\ntestState->numBuys = 0\ntestState->playedCardCount = 2\n\n");

	res = testHand(&testState, currentPlayer);
	if(res != 0){
		printf("Current Player's hand was not properly set to -1.\n");
		printf("TEST FAILED");
	}
	res = testHandCount(&testState);
	if(res !=0){
		printf("Hand Count incorrect.\n");
		printf("TEST FAILED");
	}
	res = testDeterminePlayer(&testState, currentPlayer);	
	if(res !=0){
		printf("The wrong player was assigned in the fucntion.\n");
		printf("TEST FAILED");
	}
	res = testStateVariables(&testState, currentPlayer);
	if(res != 0){
		printf("An inappropriate variable was assigned.\n");
		printf("TEST FAILED");
	}

	//If res reamins 0 = test pass
	
	if(res == 0){
		printf("TEST SUCCESSFULLY COMPLETED!\n");
		printf("-----UNIT TEST 1 COMPLETE-----\n\n");
	}
	return 0;
}
//end

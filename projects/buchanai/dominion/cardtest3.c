/*************************************************************************
 * Created By: Ian Buchanan
 * Course: CS362-400
 * Description: Card test 3 - tests the village card for errors in code.
*************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define CARD "village"  //Card being tested!

/************************************************************************
 * Helper test function - tests the pre conditions of other player to
 * 	Ensure no change occured from card effect (unless intended)
************************************************************************/
int checkOtherPlayer(struct gameState *pre, struct gameState *post, int otherP){
	//Check the other player's pre and post function call conditions for unintended changes.
	
	if(pre->handCount[otherP] != post->handCount[otherP]){
		return -1;
	}
	else if(pre->deckCount[otherP] != post->deckCount[otherP]){
		return -1;
	}
	else{
		return 0;
	}
}

/************************************************************************
 * Main
************************************************************************/
int main(){
	//Standard cardtest variables
	int k[10] = {village, gardens, embargo, smithy, minion, mine, cutpurse, sea_hag, tribute, adventurer};
	struct gameState testState, preState;
	int seed = 30;
	int currentPlayer = 0;
	int otherPlayer = 1;
	int handPos = 0;
	int bonus = 0;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int fail = 0;

	//card unique testing variables
	int t[3] = {copper, silver, gold};	
	int expectedCardCount = 5;
	int expectedActions = 3;
	int f = 0;
	int r = 0;

	//Initialize Game
	initializeGame(2, k, seed, &testState);

	printf("\n-----THIRD CARD TEST-----\n");
	printf("    Testing %s card:\n", CARD);

	//adventuer only has one choice - draw cards from your deck until you find two treasure cards
	
	//setting a test hand to ensure treasure cards are added.	
	printf("    Setting a test hand for current player.\n"); //Which include smithy card to play.
	testState.hand[currentPlayer][0] = k[0];	//card being tested always in this position.
	testState.hand[currentPlayer][1] = k[3];
	testState.hand[currentPlayer][2] = t[0];
	testState.hand[currentPlayer][3] = k[1];
	testState.hand[currentPlayer][4] = k[4];

	//copy game set
	memcpy(&preState, &testState, sizeof(struct gameState));

	/*************************************************
 	*Test 1 - check that one card was added.
 	*************************************************/
	printf("    Test 1 - check total card count - should be 5.\n");
	printf("\t--Pre game state test conditions--\n");
	printf("\tCurrent Player Hand Count: %d\n", preState.handCount[currentPlayer]);
	
 	cardEffect(k[0], choice1, choice2, choice3, &testState, handPos, &bonus);

	printf("\t--Post CardEffect--\n");
	if(testState.handCount[currentPlayer] != expectedCardCount){
		printf("\tHand Count Test 1 FAIL.\n");
		printf("\tExpected %i - received %d\n", expectedCardCount, testState.handCount[currentPlayer]);
		fail = -1;
	}
	else{
		printf("\tExpected %i - received %d\n", expectedCardCount, testState.handCount[currentPlayer]);
		printf("\tOne card remvoed (village), and one card added (from deck) succesffully.");
		printf("\tHand Count Test 1 PASS.\n");
	}	
	/*************************************************
 	*Test 2 - check that number of actions was incremented appropriatly.
 	*************************************************/
	printf("    Test 2 - check that two actions were added to the current player's turn.\n");
 	printf("\t--Pre CardEffect Condition--\n");
	printf("\tCurrent Player's number of actions prior to card effect function call: %d\n", preState.numActions); 
		
 	printf("\t--Post CardEffect--\n");
	printf("\tCurrent Player's post condition number of actions: %d\n", testState.numActions); 

	if(testState.numActions != expectedActions){
		f = -1;
	}

	if(f == 0){
		printf("\tNumber of actions added test PASS.\n");
	}
	else{
		fail = -1;
		printf("\tNumber of actions added test FAIL.\n");
	}
	
	/*********************************************************
 	* Test 3 - check the other player's status to ensure no change.
	*********************************************************/
	printf("    Test 3 - check the other Player's state for no change from card function call.\n");
	printf("\t--Pre card effect test conditions--\n");
	printf("\tOther Player Hand Count: %d\n", preState.handCount[otherPlayer]);
	printf("\tOther Player Deck Count: %d\n", preState.deckCount[otherPlayer]);

	r = checkOtherPlayer(&preState, &testState, otherPlayer);

	if(r != 0){
		printf("   Other player state test FAIL.\n");
		fail = -1;
	}
	else{
		printf("   Other player state test PASS.\n");		
	}

	/*********************************************************
	* End Test
	*********************************************************/ 
	if(fail != 0){
		printf("--CARD 3 TEST FAILED!--\n");
	}
	else{
		printf("--CARD 3 TEST SUCCESSFULLY PASSED--\n");
	}

	return 0;
}


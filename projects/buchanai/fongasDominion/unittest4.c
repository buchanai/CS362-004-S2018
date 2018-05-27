/**********************************************************
 * Created by: Ian Buchanan
 * Course: CS362-400
 * Description: Unit Test 4 - tests the discard card function
 *	in the dominion.c implementation.
**********************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**********************************************************
 * Test helper function - checks the other players card count
 * 	and deck count to ensure it was not improperly changed.
**********************************************************/
int checkOtherPlayer(struct gameState *pre, struct gameState *post, int otherP){
	//check the other player's pre and post cond.
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

/*********************************************************
 * Main
*********************************************************/
int main(){
	//variables
	struct gameState testState, preState;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int seed = 30;
	int currentPlayer = 0;
	int otherPlayer = 1;
	int handPos = 0;
	int trashFlag = 0;
	int f = 0;
	int fail =0;
	int r = 0;

	int expectedCardCount = 4;	

	initializeGame(2, k, seed, &testState);

	printf("-----UNIT TEST 4-----\n");
	printf("    Testing the discardCard() function.\n");

	//Test hand
	testState.hand[currentPlayer][0] = adventurer;
	testState.hand[currentPlayer][1] = gardens;
	testState.hand[currentPlayer][2] = embargo;
	testState.hand[currentPlayer][3] = copper;
	testState.hand[currentPlayer][4] = copper;

	//copy the state of the game.
	memcpy(&preState, &testState, sizeof(struct gameState));

	//set hand position for card being played
	handPos = 0;
	
	/*************************************************
 	*Test 1 - check that one card was added.
 	*************************************************/
	printf("    Test 1 - check that hand count was lowered to 5.\n");
	printf("\t--Pre game state test conditions--\n");
	printf("\tCurrent Player Hand Count: %d\n", preState.handCount[currentPlayer]);
	
 	discardCard(handPos, currentPlayer, &testState, trashFlag); //call the function!

	printf("\t--Post CardEffect--\n");
	if(testState.handCount[currentPlayer] != expectedCardCount){
		printf("\tHand Count Test FAIL.\n");
		printf("\tExpected %i - received %d\n", expectedCardCount, testState.handCount[currentPlayer]);
		fail = -1;
	}
	else{
		printf("\tExpected %i - received %d\n", expectedCardCount, testState.handCount[currentPlayer]);
		printf("\tOne card remvoed from hand succesffully.\n");
		printf("\tHand Count Test PASS.\n");
	}	
	/*************************************************
 	*Test 2 - Played card count incremented appropriately
 	*************************************************/
	printf("    Test 2 - check that played cards count was incremented appropriately.\n");
 	printf("\t--Pre CardEffect Condition--\n");
	printf("\tCurrent Player's number of played cards prior to discardCard function call: %d\n", preState.playedCardCount); 
		
 	printf("\t--Post CardEffect--\n");
	printf("\tCurrent Player's post condition number of played cards: %d\n", testState.playedCardCount); 

	int expectedPlay = preState.playedCardCount+1;	//increment the expected plays

	if(testState.playedCardCount != expectedPlay){
		f = -1;
	}

	if(f == 0){
		printf("\tNumber of played cards incremented correctly. Test PASS.\n");
	}
	else{
		fail = -1;
		printf("\tNumber of played cards incorrect, test FAIL.\n");
	}
	/*************************************************
 	*Test 3 - Played card set to -1
 	*************************************************/
	printf("    Test 3 - check that played card was removed from hand.\n");
 	printf("\t--Pre CardEffect Condition--\n");
	printf("\tCurrent Player's card prior to discardCard function call: %d\n", preState.hand[currentPlayer][handPos]); 
		
 	printf("\t--Post CardEffect--\n");
	printf("\tCurrent Player's post condition card: %d\n", testState.hand[currentPlayer][4]); //now last card in hand

	int expectedCardNum = -1;	//flaged for removal

	if(testState.hand[currentPlayer][4] == expectedCardNum){
		printf("\tCard was properly removed from hand. Test PASS.\n");
	}
	else{
		fail = -1;
		printf("\tCard was not remvoed from hand. Test FAIL.\n");
	}
	/*************************************************
 	*Test 4 - trash flag set
 	*************************************************/
	printf("    Test 4 - check that trash flag is set and card card count does not increment.\n");
	printf("\t--Pre game state test conditions--\n");
	printf("\tCurrent Player Hand Count: %d\n", testState.handCount[currentPlayer]);
	
	trashFlag = 1; //set trashflag
	int playedC = testState.playedCardCount;//get pre test condition!	

 	discardCard(handPos, currentPlayer, &testState, trashFlag); //call the function!

	printf("\t--Post CardEffect--\n");
	if(testState.playedCardCount != playedC){	//expectedCardCount remains 4
		printf("\tTrash Flag played card count test FAIL.\n");
		printf("\tExpected %i - received %d\n", playedC, testState.playedCardCount);
		fail = -1;
	}
	else{
		printf("\tExpected %i - received %d\n", playedC, testState.playedCardCount);
		printf("\tTrash Flag set test was succesfful. Test Pass\n");
	}
	/*********************************************************
 	* Test 5 - no change to other player deck and hand count.
	*********************************************************/
	printf("    Test 5 - check the other Player's state for no change from card function call.\n"); //TODO: update!
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
		printf("--UNIT TEST 4 FAILED!--\n");
	}
	else{
		printf("--UNIT TEST 4 SUCCESSFULLY PASSED--\n");
	}

	//End
	return 0;
}

/**********************************************************
 * Created by: Ian Buchanan
 * Course: CS362-400
 * Description: Unit Test 3 - tests the shuffle function
 *	in the dominion.c implementation.
**********************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
/**********************************************************
 * Test helper functions
**********************************************************/
int randomDeck(struct gameState *st, int currentPlayer){
	//card arrays
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int g[3] = {copper, silver, gold};
	int v[3] = {estate, duchy, province};
	int i;
	srand(time(0));
	int cardType;
	int randomNum;
	
	//assign a random deck
	for(i = 0; i < st->deckCount[currentPlayer]; i++){
	 	cardType = rand() % 3;				//select a random card type
		if(cardType == 0){
			randomNum = rand() % 3;				//select a random card
			st->deck[currentPlayer][i] = g[randomNum];
		}
		if(cardType == 1){
			randomNum = rand() % 3;
			st->deck[currentPlayer][i] = v[randomNum];
		}
		if(cardType == 2){
			randomNum = rand() % 10;
			st->deck[currentPlayer][i] = k[randomNum];
		}
	}
	return 0;
}
int compareCount(struct gameState *post, struct gameState *pre, int currentPlayer){
	if(post->deckCount[currentPlayer] == pre->deckCount[currentPlayer]){
		return 0;
	}
	else{
		return -1;
	}
}

int compareDecks(struct gameState *post, struct gameState *pre, int currentPlayer){
	int i; 
	
	for(i = 0; i < post->deckCount[currentPlayer]; i++){
		if(post->deck[currentPlayer][i] != pre->deck[currentPlayer][i]){	//compare each deck
			return 0;							//if one card is not equal return 0
		}
	}
	return -1;
}

/*********************************************************
 * Main
*********************************************************/
int main(){
	//variables
	struct gameState testState, preSt;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int seed = 30;
	int currentPlayer = 0;		
	int r = 0;
	int deckSize = 13;
	int testFail = 0;
	int fail = 0;

	initializeGame(2, k, seed, &testState);

	//Set game state testing variables
	testState.deckCount[currentPlayer] = deckSize;

	printf("-----UNIT TEST 3-----\n");
	printf("Unit test three tests the shuffle function in dominion.c\n");

	/*********************************************************************
 	* Test 1 - normal deck size - 13
 	*********************************************************************/ 
	printf("    Test normal deck size of 13:\n");

	//Set a random hand for current player
	r = randomDeck(&testState, currentPlayer);
	if(r != 0){
		printf("Something went wrong with randomHand helper function!");
		fail = -1;
	}
	//Copy the current state of the test game.
	memcpy(&preSt, &testState, sizeof(struct gameState));

	//Run shuffle function
	r = shuffle(currentPlayer, &testState);
	if(r != 0){
		printf("Something went wrong with shuffle function!");
		fail = -1;
 	}

	//Compare the results - note: there is a small statistical chance of the shuffle resulting in the same deck.	
	r = compareCount(&testState, &preSt, currentPlayer);
	if(r != 0){
		printf("\tDeck count test unsuccessful.\n");
		testFail = -1;
	}
	else{
		printf("\tDeck count test successful - appropriate amount of cards in returned deck.\n");
	}
	r = compareDecks(&testState, &preSt, currentPlayer);
	if(r != 0){
		printf("\tCompare Decks test unsuccessful.\n");
		testFail = -1;
	}
	else{
		printf("\tCompare Decks test successful - the cards are not in the same positions.\n");
	}
	if(testFail != 0){
		fail = -1;
		printf("--Test 1 failure!--\n");
	}
	else{
		printf("    Test 1 success.\n");
	}
	testFail = 0;

	/*********************************************************************
 	* Test 2 - low  deck count
 	*********************************************************************/ 
	printf("    Test low deck size of 5:\n");
	testState.deckCount[currentPlayer] = 5;

	//Set a random hand for current player
	r = randomDeck(&testState, currentPlayer);
	if(r != 0){
		printf("Something went wrong with randomHand helper function!");
		fail = -1;
	}
	//Copy the current state of the test game.
	memcpy(&preSt, &testState, sizeof(struct gameState));

	//Run shuffle function
	r = shuffle(currentPlayer, &testState);
	if(r != 0){
		printf("Something went wrong with shuffle function!");
		fail = -1;
 	}

	//Compare the results - note: there is a small statistical chance of the shuffle resulting in the same deck.	
	r = compareCount(&testState, &preSt, currentPlayer);
	if(r != 0){
		printf("\tDeck count test unsuccessful.\n");
		testFail = -1;
	}
	else{
		printf("\tDeck count test successful - appropriate amount of cards in returned deck.\n");
	}
	r = compareDecks(&testState, &preSt, currentPlayer);
	if(r != 0){
		printf("\tCompare Decks test unsuccessful.\n");
		printf("NOTE - STATISTICALLY SIGNIFICANT CHANCE THAT CARD ORDER COULD BE SAME WITH PROPER EXECUTION OF SHUFFLE.--\n");
		testFail = -1;
	}
	else{
		printf("\tCompare Decks test successful - the cards are not in the same positions.\n");
	}
	if(testFail != 0){
		fail = -1;
		printf("--Test 2 failure!--\n");
	}
	else{
		printf("    Test 2 success.\n");
	}
	testFail = 0;
	
	/*********************************************************************
 	* Test 3 - moderately high deck count
 	*********************************************************************/ 
	printf("    Test moderately high deck size of 50:\n");
	testState.deckCount[currentPlayer] = 50;

	//Set a random hand for current player
	r = randomDeck(&testState, currentPlayer);
	if(r != 0){
		printf("Something went wrong with randomHand helper function!");
		fail = -1;
	}
	//Copy the current state of the test game.
	memcpy(&preSt, &testState, sizeof(struct gameState));

	//Run shuffle function
	r = shuffle(currentPlayer, &testState);
	if(r != 0){
		printf("Something went wrong with shuffle function!");
		fail = -1;
 	}

	//Compare the results - note: there is a small statistical chance of the shuffle resulting in the same deck.	
	r = compareCount(&testState, &preSt, currentPlayer);
	if(r != 0){
		printf("\tDeck count test unsuccessful.\n");
		testFail = -1;
	}
	else{
		printf("\tDeck count test successful - appropriate amount of cards in returned deck.\n");
	}
	r = compareDecks(&testState, &preSt, currentPlayer);
	if(r != 0){
		printf("\tCompare Decks test unsuccessful.\n");
		testFail = -1;
	}
	else{
		printf("\tCompare Decks test successful - the cards are not in the same positions.\n");
	}
	if(testFail != 0){
		fail = -1;
		printf("--Test 3 failure!--\n");
	}
	else{
		printf("    Test 3 success.\n");
	}
	testFail = 0;

	/*********************************************************************
 	* Test 4 - high deck count
 	*********************************************************************/ 
	printf("    Test high deck size of 300:\n");
	testState.deckCount[currentPlayer] = 300;

	//Set a random hand for current player
	r = randomDeck(&testState, currentPlayer);
	if(r != 0){
		printf("Something went wrong with randomHand helper function!");
		fail = -1;
	}
	//Copy the current state of the test game.
	memcpy(&preSt, &testState, sizeof(struct gameState));

	//Run shuffle function
	r = shuffle(currentPlayer, &testState);
	if(r != 0){
		printf("Something went wrong with shuffle function!");
		fail = -1;
 	}

	//Compare the results - note: there is a small statistical chance of the shuffle resulting in the same deck.	
	r = compareCount(&testState, &preSt, currentPlayer);
	if(r != 0){
		printf("\tDeck count test unsuccessful.\n");
		testFail = -1;
	}
	else{
		printf("\tDeck count test successful - appropriate amount of cards in returned deck.\n");
	}
	r = compareDecks(&testState, &preSt, currentPlayer);
	if(r != 0){
		printf("\tCompare Decks test unsuccessful.\n");
		testFail = -1;
	}
	else{
		printf("\tCompare Decks test successful - the cards are not in the same positions.\n");
	}
	if(testFail != 0){
		fail = -1;
		printf("--Test 4 failure!--\n");
	}
	else{
		printf("    Test 4 success.\n");
	}
	testFail = 0;

	/*********************************************************************
 	* Test 5 - boundary test of deck count - 500
 	*********************************************************************/ 
	printf("    Boundary test of deck size - 500:\n");
	testState.deckCount[currentPlayer] = 500;

	//Set a random hand for current player
	r = randomDeck(&testState, currentPlayer);
	if(r != 0){
		printf("Something went wrong with randomHand helper function!");
		fail = -1;
	}
	//Copy the current state of the test game.
	memcpy(&preSt, &testState, sizeof(struct gameState));

	//Run shuffle function
	r = shuffle(currentPlayer, &testState);
	if(r != 0){
		printf("Something went wrong with shuffle function!");
		fail = -1;
 	}

	//Compare the results - note: there is a small statistical chance of the shuffle resulting in the same deck.	
	r = compareCount(&testState, &preSt, currentPlayer);
	if(r != 0){
		printf("\tDeck count test unsuccessful.\n");
		testFail = -1;
	}
	else{
		printf("\tDeck count test successful - appropriate amount of cards in returned deck.\n");
	}
	r = compareDecks(&testState, &preSt, currentPlayer);
	if(r != 0){
		printf("\tCompare Decks test unsuccessful.\n");
		testFail = -1;
	}
	else{
		printf("\tCompare Decks test successful - the cards are not in the same positions.\n");
	}
	if(testFail != 0){
		fail = -1;
		printf("--Test 5 failure!--\n");
	}
	else{
		printf("    Test 5 success.\n");
	}
	testFail = 0;

	/***********************************************
 	*END TEST
 	***********************************************/ 
	if(fail != 0){
		printf("-----TEST FAILED-----\n");
	}
	else{
		printf("-----TEST SUCCESSFULLY COMPLETED-----\n");
	}
 
	//End
	return 0;
}


/**********************************************************
 * Created by: Ian Buchanan
 * Course: CS362-400
 * Description: Random Test Card 2 - villageCard function
 *   Tests the villageCard function in dominion.c
**********************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>
/**********************************************************
 * Test Card Function
**********************************************************
int testCard(struct gameState* st, struct gameState* pre, int currentPlayer, int handPos){
	int ret = 0;
	//int fail = 0;

	//Call the village card function
	ret = villageCard(st, currentPlayer, handPos);

	if(ret != 0){  //if the adventurer card does not return 0, fatal error occured in card.
		//printf("Error occured in testCard function, return value from card call !=0.\n");
		//error("ERROR: adventurer card call crashed in testCard function.\n");
		return -1;
	}
	else{
		//printf("  First test successful -- function call did not fail with random values assigned.\n");
		return 0;
	}
}

	printf("  Testing against prestate conditionals to ensure correct behavior.\n");
	State pre card function call conditions for visual confirmations of testing the random test program.
	printf("  Pre card call conditions: \n\tPlayer: %d\n\tHand Count: %d\n\tDeck Count: %d\n\tNumber of Actions: %d\n",
		currentPlayer, pre->handCount[currentPlayer], pre->deckCount[currentPlayer], pre->numActions);
	
	printf("  Post card call conditions: \n\tPlayer: %d\n\tHand Count: %d\n\tDeck Count: %d\n\tNumber of ACtions: %d\n",
		currentPlayer, st->handCount[currentPlayer], st->deckCount[currentPlayer], pre->numActions);  

 	MOVED TESTS OUTSIDE OF FUNCTION FOR TRACKING PURPOSES
	
	//Test that the deck has decremented by 1.
	if(st->deckCount[currentPlayer] == pre->deckCount[currentPlayer]-1){
		printf("  Deck Count Test SUCCESSFUL.\n");
	}
	else{
		printf("  Deck Count Test FAILURE.\n");
		fail = -1;
	}

	//Test that the number of actions has increased by 2.
	if(st->numActions == pre->numActions + 2){
		printf("  Number of Actions Test SUCCESSFUL.\n");
	}
	else{
		printf("  Number of Actions Test FAILURE.\n");
		printf("\tExpected: %d Received: %d\n", pre->numActions+2, st->numActions);
		fail = -1;
	}

	//Test that hand count remained equal.
	if(st->handCount[currentPlayer] == pre->handCount[currentPlayer]){
		printf("  Hand Count Test SUCCESSFUL.\n");
	}
	else{
		printf("  Number of Actions Test FAILURE.\n");
		printf("\tExpected: %d Received: %d\n", pre->handCount[currentPlayer], st->handCount[currentPlayer]);
		fail = -1;
	}

	//send confirmation ret val
	if(fail != 0){
		return -1;
	}
	else{
		return 0;
	}
}
*/

/**********************************************************
 * Main
**********************************************************/
int main(){
	//Define the game state variables.
	struct gameState testState, preState;
	srand(time(0));	

	//Set the gold, village, and kingdom card stacks.
	int k[10] = {adventurer, council_room, feast, gardens, mine, smithy, 
		village, baron,	great_hall, tribute};
	int g[3] = {copper, silver, gold};
	int v[3] = {estate, duchy, province};

	//In leiu of rand(), use random generator provided with dominion implementation
	int seed;
	int i, m;
	int currentPlayer;
	//int r = 0;
	int simRand;
	int handPos, cardType, randoNum;
	int fail = 0;
	//Tracking failures through iterations.	
	int trackDeck = 0;
	int trackActs = 0;
	int trackHand = 0;
	int its = 5000;
	int card = village;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int bonus = 0;

	printf("-----PREPARING TO RUN RANDOM TESTS ON VILLAGE CARD-----\n");
	printf("  Randomizing game conditions and performing %i random tests.\n", its);

	//Run 5000 random tests.
	for(i = 0; i < its; i++){	//TODO: update number of tests!
		//printf("  -- RANDOMIZING GAME CONDITIONS -- \n");	
		//printf("\tIteration %i\n", i+1);	
		/************************************************
 		* Fill the game variables with random values
 		* Reference: addapted from testDrawCard.c provided 
 		* 	in course dominion folder.
		************************************************/
		//Set seed value to generate random initialization values.
		simRand = rand() % 100 + 1; //get a random value from time for each run of prog
		SelectStream(1);
		PutSeed(simRand); //seed with pseudo random val
		seed = floor(Random() * 100000);	//run once to get things rolling
	
		//printf("  Seed is: %i\n", seed);
		//Initialize game with random seed.
		initializeGame(2, k, seed, &testState); 		//initialize game

		//randly select the current player
		currentPlayer = floor(Random() * 2);			//random current player selection
		
		//radnsomly set the deck count
		testState.deckCount[currentPlayer] = floor(Random() * MAX_DECK);	
		
		//randomly set the hand count
		testState.handCount[currentPlayer] = floor(Random() * MAX_HAND);  
		
		//randomly assign a number of actions
		testState.numActions = floor(Random() * 5); //TODO: action number

		//Fill the player being tested hand with random cards
		for(m = 0; m < testState.handCount[currentPlayer]; m++){
			cardType = floor(Random() * 3);
			if(cardType == 0){
				randoNum = floor(Random() * 3);
				testState.hand[currentPlayer][m] = g[randoNum];  //assign random gold card
			}
			if(cardType == 1){
				randoNum = floor(Random() * 3);
				testState.hand[currentPlayer][m] = v[randoNum];  //assign random village card
			}
			if(cardType == 2){
				randoNum = floor(Random() * 10);
				testState.hand[currentPlayer][m] = k[randoNum];  //assign random kingdom card
			}
		}
		//NOTE: Actual existance of card in hand not necessary to test function of card.
		//Randomly assign a hard position for the "Smihy" card.
		handPos = floor(Random() * testState.handCount[currentPlayer]); //random value between 0 and random handcount

		//Copy the random state of the game.
		memcpy(&preState, &testState, sizeof(struct gameState));

		/*DIRECT CARD CALL - Test the card!
		r = testCard(&testState, &preState, currentPlayer, handPos);

		if(r != 0){
			printf("Failure in the call to the card function.\n");
		}

		****************************************************
 		* Change from direct call to card to cardEffect function call
 		* to expand coverage area of test.
		****************************************************/
		cardEffect(card, choice1, choice2, choice3, &testState, handPos, &bonus);

		/****************************************************
 		* Perform and track tests.
 		*   Tests moved outside of function to track and display better.
		****************************************************/

		//Test that the deck has decremented by 1.
		if(testState.deckCount[currentPlayer] == preState.deckCount[currentPlayer]-1){
			//printf("  Deck Count Test SUCCESSFUL.\n");
		}
		else{
			//printf("  Deck Count Test FAILURE.\n");
			//fail = -1;
			trackDeck++;
		}

		//Test that the number of actions has increased by 2.
		if(testState.numActions == preState.numActions + 2){
			//printf("  Number of Actions Test SUCCESSFUL.\n");
		}
		else{
			//printf("  Number of Actions Test FAILURE.\n");
			//printf("\tExpected: %d Received: %d\n", pre->numActions+2, st->numActions);
			//fail = -1;
			trackActs++;
		}
	
		//Test that hand count remained equal.
		if(testState.handCount[currentPlayer] == preState.handCount[currentPlayer]){
			//printf("  Hand Count Test SUCCESSFUL.\n");
		}
		else{
			//printf("  Number of Actions Test FAILURE.\n");
			//printf("\tExpected: %d Received: %d\n", pre->handCount[currentPlayer], st->handCount[currentPlayer]);
			//fail = -1;
			trackHand++;
		}

	//end iterations
	}

	if(trackDeck == 0){
		printf("  Deck Size Tests were SUCCESSFUL.\n");
	}
	else{
		printf("  Deck Size Tests FAILED.\n");
		printf("\tNumber of tests failed: %i\n", trackDeck);
		fail = -1;
	}
	if(trackActs == 0){
		printf("  Number of Actions Tests were SUCCESSFUL.\n");
	}
	else{
		printf("  Number of Actions Tests FAILED.\n");
		printf("\tNumber of tests failed: %i\n", trackActs);
		fail = -1;
	}
	if(trackHand == 0){
		printf("  Hand Size Tests were SUCCESSFUL.\n");
	}
	else{
		printf("  Hand Size Tests FAILED.\n");
		printf("\tNumber of tests failed: %i\n", trackHand);
		fail = -1;
	}

	if(fail != 0){
		printf("-----TEST FAILED-----\n");
	}
	else{
		printf("-----TEST SUCCESSFULLY PASSED-----\n");
	}

	return 0;
} //Fini

/**********************************************************
 * Created by: Ian Buchanan
 * Course: CS362-400
 * Description: Random Test Card 1 - smithyCard function
 *   Tests the smithyCard function in dominion.c
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
int testSmithyCard(struct gameState* st, struct gameState *pre, int currentPlayer, int handPos){
	int ret = 0;
	//int fail = 0;
	ret = smithyCard(st, currentPlayer, handPos);

	if(ret != 0){  //if the adventurer card does not return 0, fatal error occured in card.
		printf("Error occured in testCard function, return value from card call !=0.\n");
		//error("ERROR: adventurer card call crashed in testCard function.\n");
		return -1;
	}
	else{
		//printf("  First test pass - card did not fail with random values assigned.\n");
		return 0;
	}
}

*	MOVED ALL TESTS TO MAIN TO TRACK FOR DISPLAY AND OUTPUT WHEN TEST ITERATIONS ARE HIGH
	printf("  Testing against prestate conditionals to ensure correct behavior.\n");
	printf("  Pre card call conditions: \n\tPlayer: %d\n\tHand Count: %d\n\tDeck Count: %d\n",
		currentPlayer, pre->handCount[currentPlayer], pre->deckCount[currentPlayer]);
	printf("  Post card call conditions: \n\tPlayer: %d\n\tHand Count: %d\n\tDeck Count: %d\n",
		currentPlayer, st->handCount[currentPlayer], st->deckCount[currentPlayer]);  

	//Test the pre and post conditionals against expected behavior
	if(st->handCount[currentPlayer] != pre->handCount[currentPlayer]+2){ //Net increase should be +2 cards in hand (draw 3, discard 1)
		printf("  Error in hand count test- expected: %d\treceived: %d\n", pre->handCount[currentPlayer]+2, st->handCount[currentPlayer]);
		fail = -1;
	}
	else if(st->deckCount[currentPlayer] != pre->deckCount[currentPlayer] - 3){
		printf("  Error in deck count test- expected: %d\treceived: %d\n", pre->deckCount[currentPlayer]+2, st->deckCount[currentPlayer]);
		fail = -1;
	}
	else{
		printf("  Conditional tests successful.\n");
	}

	//send confirmation ret val
	if(fail != 0){
		return -1;
	}
	else{
		return 0;
	}
}*/

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
	int trackHand = 0;
	int trackDeck = 0;
	int its = 5000;

	//additional variables for card effect call
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int bonus = 0;
	int card = smithy;

	/*use simple random number generator to get different values each run.
	simRand = rand() % 100; //get a random value from time for each run of prog
	SelectStream(1);
	PutSeed(simRand); //seed with pseudo random val
	seed = floor(Random() * 1000);	//run once to get things rolling
	*/

	printf("-----PREPARING TO RUN RANDOM TESTS ON SMITHY CARD-----\n");
	printf("  Assigning random values and performing %i iterations.\n", its);
	//Run 5000 random tests.
	for(i = 0; i < its; i++){
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

		/*Test the card!
		r = testSmithyCard(&testState, &preState, currentPlayer, handPos);
		
		if(r != 0){
			printf("Test Failure with exit of card function -- FAILURE.\n");
			fail = -1;
		}
		
		************************************************
		* Card Effect - testing to expand code coverage
		************************************************/
		//TODO: evaluation section
		
		cardEffect(card, choice1, choice2, choice3, &testState, handPos, &bonus);

		/************************************************
 		* Test against pre conditions.
 		************************************************/
		//Test the pre and post conditionals against expected behavior
		if(testState.handCount[currentPlayer] != preState.handCount[currentPlayer]+2){ //Net increase should be +2 cards in hand (draw 3, discard 1)
			//printf("  Error in hand count test- expected: %d\treceived: %d\n", pre->handCount[currentPlayer]+2, st->handCount[currentPlayer]);
			//fail = -1;
			trackHand++;
		}
		if(testState.deckCount[currentPlayer] != preState.deckCount[currentPlayer]-3){
			//printf("  Error in deck count test- expected: %d\treceived: %d\n", pre->deckCount[currentPlayer]+2, st->deckCount[currentPlayer]);
			//fail = -1;
			trackDeck++;
		}
	}

	//Print out end results
	if(trackHand == 0){
		printf("Hand Count Test SUCCESSFUL.\n");
	}
	else{
		printf("Hand Count Test FAILURE.\n");
		printf("  Number of tests failed: %i\n", trackHand);
		fail = -1;
	}

	if(trackDeck == 0){
		printf("Deck Count Test SUCCESSFUL.\n");
	}
	else{
		printf("Deck Count Test FAILURE.\n");
		printf("  Number of tests failed: %i\n", trackDeck);
		fail = -1;
	}

	//tests complete
	if(fail != 0){
		printf("-----TEST FAILED-----\n");
	}
	else{
		printf("-----TEST SUCCESSFULLY PASSED-----\n");
	}

	return 0;
} //Fini

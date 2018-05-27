/**********************************************************
 * Created by: Ian Buchanan
 * Course: CS362-400
 * Description: Randomly Test the adventurer card - 
 *   Tests the adventurer function in dominion.c
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
**********************************************************/
int testCard(struct gameState* st, struct gameState *pre, int currentPlayer){
	int ret = 0;

	int temphand[MAX_HAND];  //holds the discarded cards - no need to input random data

	//call the adventurer card.
	ret = adventurerCard(st, temphand, currentPlayer);

	//Test that the card call function did not encounter a fatal error.
	if(ret != 0){  
		printf("Error occured in testCard function, return value from card call !=0.\n");
		return -1;
	}
	else{
		return 0;
	}
}

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
	int i, m, n;
	int currentPlayer;
	int r = 0;
	int simRand;
	int cardType, randoNum;
	int fail = 0;	
	int trackDeck = 0;
	int trackCount = 0;
	int trackHand = 0;
	int its = 5000;
	//use simple random number generator to get different values each run.
	simRand = rand() % 100; //get a random value from time for each run of prog
	SelectStream(1);
	PutSeed(simRand); //seed with pseudo random val
	seed = floor(Random() * 1000);	//run once to get things rolling

	printf("-----PREPARING TO RUN RANDOM TESTS ON ADVENTURER CARD-----\n");
	printf("  Randomizing the game conditions and running %i tests.\n", its);
	printf("  Running tests directly on the refactored adventurerCard function.\n");

	//Run 5000 random tests.
	for(i = 0; i < its; i++){	//TODO: update number of tests!

		//printf("  \n -- RANDOMIZING GAME CONDITIONS -- \n");
		//printf("\tIteration: %i\n", i+1);
		/************************************************
 		* Fill the game variables with random values
 		* Reference: addapted from testDrawCard.c provided 
 		* 	in course dominion folder.
		************************************************/
		simRand = rand() % 100+1; //get a random value from time for each run of prog
		SelectStream(1);
		PutSeed(simRand); //seed with pseudo random val
		seed = floor(Random() * 100000);	//run once to get things rolling
	
		//printf("  Seed is: %i\n", seed);
		//Initialize game with random seed.
		initializeGame(2, k, seed, &testState); 	
	
		//randomly select a current player to test
		currentPlayer = floor(Random() * 2);	

		//set random deck count
		testState.deckCount[currentPlayer] = floor(Random() * MAX_DECK);

		//random hand count that is equal to or less than deck count.
		testState.handCount[currentPlayer] = floor(Random() * testState.deckCount[currentPlayer]);  	

		//Randomly fill the player's deck with randomly selected cards.
		for(m = 0; m < testState.deckCount[currentPlayer]; m++){
			cardType = floor(Random() * 3);
			if(cardType == 0){
				randoNum = floor(Random() * 3);
				testState.deck[currentPlayer][m] = g[randoNum];  //assign random gold card
			}
			if(cardType == 1){
				randoNum = floor(Random() * 3);
				testState.deck[currentPlayer][m] = v[randoNum];  //assign random village card
			}
			if(cardType == 2){
				randoNum = floor(Random() * 10);
				testState.deck[currentPlayer][m] = k[randoNum];  //assign random kingdom card
			}
		}

		//Randomly fill the player's hands with cards from the player's deck.
		for(n = 0; n < testState.handCount[currentPlayer]; n++){
			cardType = floor(Random() * 3);
			if(cardType == 0){
				randoNum = floor(Random() * 3);
				testState.hand[currentPlayer][n] = g[randoNum];  //assign random gold card
			}
			if(cardType == 1){
				randoNum = floor(Random() * 3);
				testState.hand[currentPlayer][n] = v[randoNum];  //assign random village card
			}
			if(cardType == 2){
				randoNum = floor(Random() * 10);
				testState.hand[currentPlayer][n] = k[randoNum];  //assign random kingdom card
			}
		}
		
		//Copy the random state of the game.
		memcpy(&preState, &testState, sizeof(struct gameState));

		//printf("  -- Running tests --\n");
		//Test the card!
		r = testCard(&testState, &preState, currentPlayer);
		
		if(r != 0){
			fail = -1;
		}
		
		/*******************************************************
 		* Moved all tests from function to here.
 		*   Makes it easier to track and display total failures.
		*******************************************************/

		//test deckCount to see if the deck has decreased by at least two
		if(testState.deckCount[currentPlayer] <= preState.deckCount[currentPlayer]-2){
			//printf("    Deck count test passed successfully.\n"); 
		}
		else{
			//printf("    --Error in deck count test-- expected: %d or less - received: %d\n", pre->deckCount[currentPlayer]-2, st->deckCount[currentPlayer]);
			//fail = -1;
			trackDeck++;
		}

		//test handCount to ensure that the count has increased by two
		if(testState.handCount[currentPlayer] != preState.handCount[currentPlayer]+2){ //Net increase should be +2 cards in hand (draw 3, discard 1)
			//printf("    Error in hand count test- expected: %d\treceived: %d\n", pre->handCount[currentPlayer]+2, st->handCount[currentPlayer]);
			//fail = -1;
			trackCount++;
		}

		//NOTE: adventurer card implimentation does not discard cards drawn but are not treasure cards.
		//	It only increments down the hand count variable.
		//printf("    Drawn Cards were:\n\tCard 1: %d\n\tCard 2: %d\n", 
		//	st->hand[currentPlayer][st->handCount[currentPlayer]-1],
		//	st->hand[currentPlayer][st->handCount[currentPlayer]-2]);
		
		//Test HAND to see that there are two new treasure cards.
		//Check the last card in the hand to ensure it is a treasure card.
		if(testState.hand[currentPlayer][testState.handCount[currentPlayer]-1] == g[0] ||
			testState.hand[currentPlayer][testState.handCount[currentPlayer]-1] == g[1] ||
			testState.hand[currentPlayer][testState.handCount[currentPlayer]-1] == g[2]){
			//printf("    First card drawn was a treasure card\n");
		}
		else{
			//printf("    --Error: First card drawn was not a treasure card--\n");
			//printf("    --New cards is: %d -- should be a 4, 5, or 6 --\n", st->hand[currentPlayer][st->handCount[currentPlayer]-1]);
			//fail = -1;
			trackHand++;
		}
		//Test the second to last card in the current player's hand to ensure treasure card added.
		if(testState.hand[currentPlayer][testState.handCount[currentPlayer]-2] == g[0] ||
			testState.hand[currentPlayer][testState.handCount[currentPlayer]-2] == g[1] ||
			testState.hand[currentPlayer][testState.handCount[currentPlayer]-2] == g[2]){
			//printf("    Second card drawn was a treasure card.\n");
		}
		else{
			//printf("    --Error: Second card drawn was not a treasure card--\n");
			//printf("    New cards is: %d\n -- should be a 4, 5, or 6 --\n", st->hand[currentPlayer][st->handCount[currentPlayer]-2]);
			//fail = -1;
			trackHand++;
		}

	}

	printf("\n--Direct Adventurer Card Function Results--\n");
	if(trackDeck == 0){
		printf("  Track Deck Tests SUCCESSFUL.\n");
	}
	else{
		printf("  Track Deck Tests FAILED.\n");
		printf("\tNumber of test failures: %i\n", trackDeck);
		fail = -1;
	}
	if(trackCount == 0){
		printf("  Track Count Tests SUCCESSFUL.\n");
	}
	else{
		printf("  Track Count Tests FAILED.\n");
		printf("\tNumber of test failures: %i\n", trackCount);
		fail = -1;
	}
	if(trackHand == 0){
		printf("  Hand Count Tests SUCCESSFUL.\n");
	}
	else{
		printf("  Hand Count Tests FAILED.\n");
		printf("\tNumber of test failures: %i\n", trackHand);
		fail = -1;
	}

	/*********************************************
 	* Performing tests using cardEffect call
 	*  Expanded coverage yeilds errors
	*********************************************/

	//adding cardEffect variables here
	int handPos = 0;
	int bonus = 0;	
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;

	printf("Running tests on the refactored adventurerCard function by calling through the cardEffect function.\n\n");

	//Run 5000 random tests.
	for(i = 0; i < its; i++){	//TODO: update number of tests!

		//printf("  \n -- RANDOMIZING GAME CONDITIONS -- \n");
		//printf("\tIteration: %i\n", i+1);
		/************************************************
 		* Fill the game variables with random values
 		* Reference: addapted from testDrawCard.c provided 
 		* 	in course dominion folder.
		************************************************/
		simRand = rand() % 100+1; //get a random value from time for each run of prog
		SelectStream(1);
		PutSeed(simRand); //seed with pseudo random val
		seed = floor(Random() * 100000);	//run once to get things rolling
	
		//printf("  Seed is: %i\n", seed);
		//Initialize game with random seed.
		initializeGame(2, k, seed, &testState); 	
	
		//randomly select a current player to test
		currentPlayer = floor(Random() * 2);	

		//set random deck count
		testState.deckCount[currentPlayer] = floor(Random() * MAX_DECK);

		//random hand count that is equal to or less than deck count.
		testState.handCount[currentPlayer] = floor(Random() * testState.deckCount[currentPlayer]);  	

		//Randomly fill the player's deck with randomly selected cards.
		for(m = 0; m < testState.deckCount[currentPlayer]; m++){
			cardType = floor(Random() * 3);
			if(cardType == 0){
				randoNum = floor(Random() * 3);
				testState.deck[currentPlayer][m] = g[randoNum];  //assign random gold card
			}
			if(cardType == 1){
				randoNum = floor(Random() * 3);
				testState.deck[currentPlayer][m] = v[randoNum];  //assign random village card
			}
			if(cardType == 2){
				randoNum = floor(Random() * 10);
				testState.deck[currentPlayer][m] = k[randoNum];  //assign random kingdom card
			}
		}

		//Randomly fill the player's hands with cards from the player's deck.
		for(n = 0; n < testState.handCount[currentPlayer]; n++){
			cardType = floor(Random() * 3);
			if(cardType == 0){
				randoNum = floor(Random() * 3);
				testState.hand[currentPlayer][n] = g[randoNum];  //assign random gold card
			}
			if(cardType == 1){
				randoNum = floor(Random() * 3);
				testState.hand[currentPlayer][n] = v[randoNum];  //assign random village card
			}
			if(cardType == 2){
				randoNum = floor(Random() * 10);
				testState.hand[currentPlayer][n] = k[randoNum];  //assign random kingdom card
			}
		}
		
		//Copy the random state of the game.
		memcpy(&preState, &testState, sizeof(struct gameState));

		//printf("  -- Running tests --\n");
		//Test the card!
		cardEffect(adventurer, choice1, choice2, choice3, &testState, handPos, &bonus); 
		
		/*******************************************************
 		* Moved all tests from function to here.
 		*   Makes it easier to track and display total failures.
		*******************************************************/

		//test deckCount to see if the deck has decreased by at least two
		if(testState.deckCount[currentPlayer] <= preState.deckCount[currentPlayer]-2){
			//printf("    Deck count test passed successfully.\n"); 
		}
		else{
			//printf("    --Error in deck count test-- expected: %d or less - received: %d\n", pre->deckCount[currentPlayer]-2, st->deckCount[currentPlayer]);
			//fail = -1;
			trackDeck++;
		}

		//test handCount to ensure that the count has increased by two
		if(testState.handCount[currentPlayer] != preState.handCount[currentPlayer]+2){ //Net increase should be +2 cards in hand (draw 3, discard 1)
			//printf("    Error in hand count test- expected: %d\treceived: %d\n", pre->handCount[currentPlayer]+2, st->handCount[currentPlayer]);
			//fail = -1;
			trackCount++;
		}

		//NOTE: adventurer card implimentation does not discard cards drawn but are not treasure cards.
		//	It only increments down the hand count variable.
		//printf("    Drawn Cards were:\n\tCard 1: %d\n\tCard 2: %d\n", 
		//	st->hand[currentPlayer][st->handCount[currentPlayer]-1],
		//	st->hand[currentPlayer][st->handCount[currentPlayer]-2]);
		
		//Test HAND to see that there are two new treasure cards.
		//Check the last card in the hand to ensure it is a treasure card.
		if(testState.hand[currentPlayer][testState.handCount[currentPlayer]-1] == g[0] ||
			testState.hand[currentPlayer][testState.handCount[currentPlayer]-1] == g[1] ||
			testState.hand[currentPlayer][testState.handCount[currentPlayer]-1] == g[2]){
			//printf("    First card drawn was a treasure card\n");
		}
		else{
			//printf("    --Error: First card drawn was not a treasure card--\n");
			//printf("    --New cards is: %d -- should be a 4, 5, or 6 --\n", st->hand[currentPlayer][st->handCount[currentPlayer]-1]);
			//fail = -1;
			trackHand++;
		}
		//Test the second to last card in the current player's hand to ensure treasure card added.
		if(testState.hand[currentPlayer][testState.handCount[currentPlayer]-2] == g[0] ||
			testState.hand[currentPlayer][testState.handCount[currentPlayer]-2] == g[1] ||
			testState.hand[currentPlayer][testState.handCount[currentPlayer]-2] == g[2]){
			//printf("    Second card drawn was a treasure card.\n");
		}
		else{
			//printf("    --Error: Second card drawn was not a treasure card--\n");
			//printf("    New cards is: %d\n -- should be a 4, 5, or 6 --\n", st->hand[currentPlayer][st->handCount[currentPlayer]-2]);
			//fail = -1;
			trackHand++;
		}

	}

	printf("--Card Effect Call Results--\n");
	if(trackDeck == 0){
		printf("  Track Deck Tests SUCCESSFUL.\n");
	}
	else{
		printf("  Track Deck Tests FAILED.\n");
		printf("\tNumber of test failures: %i\n", trackDeck);
		fail = -1;
	}
	if(trackCount == 0){
		printf("  Track Count Tests SUCCESSFUL.\n");
	}
	else{
		printf("  Track Count Tests FAILED.\n");
		printf("\tNumber of test failures: %i\n", trackCount);
		fail = -1;
	}
	if(trackHand == 0){
		printf("  Hand Count Tests SUCCESSFUL.\n");
	}
	else{
		printf("  Hand Count Tests FAILED.\n");
		printf("\tNumber of test failures: %i\n", trackHand);
		fail = -1;
	}



	//Tests finished
	if(fail != 0){
		printf("-----TEST FAILED-----\n");
	}
	else{
		printf("-----TEST SUCCESSFULLY PASSED-----\n");
	}

	return 0;
} //Fini

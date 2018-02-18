#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "assertEquals.c"
#include<time.h>

#define NUM_ITERATIONS 10000

int randomCard (int *kingdom) {
	int randCardNum = rand()%17;
	int randCard;
	switch (randCardNum) {
		case 0: randCard = copper; break;
		case 1: randCard = silver; break;
		case 2: randCard = gold; break;
		case 3: randCard = estate; break;
		case 4: randCard = duchy; break;
		case 5: randCard = province; break;
		case 6: randCard = curse; break;
		default: randCard = kingdom[randCardNum-7];
	}
	return randCard;
}

int numCardsInArray(int *array, int size, int card) {
	int numberFound = 0;
	int i;
	for (i = 0; i < size; i++) {
		if (array[i] == card) numberFound++;
	}
	return numberFound;
}


int main() {
	printf("---- STARTING RANDOM TEST ON ADVENTURER ----\n");

	srand(time(NULL));
	
	int numPlayers = 2;
	int player = 0;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int seed = 1;
	int bonus = 0;
	struct gameState G, testG;
	
	initializeGame(numPlayers, k, seed, &G);
	G.whoseTurn = player;
	
	int totalFailures = 0;
	int iteration;
	for (iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
		// Random deck size
		int deckSize = rand()%41; // deck size 0 to 40
		G.deckCount[player] = deckSize;
		
		// Fill deck with random cards
		// There are 17 possible cards - 3 treasures, 3 victory, 1 curse, and 10 kingdom
		int i;
		for (i = 0; i < deckSize; i++) {
			G.deck[player][i] = randomCard(k);
		}
		
		// Random hand size
		int handSize = rand()%10 + 1;
		G.handCount[player] = handSize;
		G.hand[player][0] = adventurer; // First card Adventurer
		
		// Fill hand with random cards
		for (i = 1; i < handSize; i++) {
			G.hand[player][i] = randomCard(k);
		}
		
		// Copy G to testG
		memcpy(&testG, &G, sizeof(struct gameState));
		
		
		// Get expected results
		int coppersDrawn = 0;
		int silversDrawn = 0;
		int goldsDrawn = 0;
		int cardsDrawn = 0;
		
		int numDiscarded = 0;
		int deckPosition = deckSize;
		while (cardsDrawn == 0) {
			deckPosition--;
			if (deckPosition < 0) break;
			int cardAtPosition = G.deck[player][deckPosition];
			
			switch(cardAtPosition) {
				case copper: 
					coppersDrawn++; 
					cardsDrawn++;
					break;
				case silver: 
					silversDrawn++; 
					cardsDrawn++;
					break;
				case gold: 
					goldsDrawn++; 
					cardsDrawn++;
					break;
				default: numDiscarded++;
			}
		}
		while (cardsDrawn == 1) {
			deckPosition--;
			if (deckPosition < 0) break;
			int cardAtPosition = G.deck[player][deckPosition];
			
			switch(cardAtPosition) {
				case copper: 
					coppersDrawn++; 
					cardsDrawn++;
					break;
				case silver: 
					silversDrawn++; 
					cardsDrawn++;
					break;
				case gold: 
					goldsDrawn++; 
					cardsDrawn++;
					break;
				default: numDiscarded++;
			}
		}
		
		int numCardsInDeck = deckPosition;
		if (numCardsInDeck < 0) numCardsInDeck = 0;
		
		printf("STARTING TEST NUMBER %d\n", iteration);
		printf("Initial deck count: %d, hand count: %d\n\n", deckSize, handSize);

		// Invoke method (play Adventurer)
		cardEffect(adventurer, 0, 0, 0, &testG, 0, &bonus);
		
		int numFailures = 0;
		// Verify results
		// Deck
		numFailures += assertEquals("Deck count", testG.deckCount[player], numCardsInDeck);
		
		// Hand
		numFailures += assertEquals("Hand count", testG.handCount[player], handSize + cardsDrawn);
		numFailures += assertEquals("Copper count", numCardsInArray(testG.hand[player], testG.handCount[player], copper), numCardsInArray(G.hand[player], G.handCount[player], copper) + coppersDrawn);
		numFailures += assertEquals("Silver count", numCardsInArray(testG.hand[player], testG.handCount[player], silver), numCardsInArray(G.hand[player], G.handCount[player], silver) + silversDrawn);
		numFailures += assertEquals("Gold count", numCardsInArray(testG.hand[player], testG.handCount[player], gold), numCardsInArray(G.hand[player], G.handCount[player], gold) + goldsDrawn);
		
		// Discard
		numFailures += assertEquals("Discard count", testG.discardCount[player], numDiscarded);
		
		if (numFailures == 0) {
			printf("TEST SUCCESSFULLY COMPLETED\n");
		}
		else {
			printf("TEST FAILED\n");
			totalFailures++;
		}
		printf("\n");
	}
	
	printf("End Adventurer card test\nTotal runs: %d\nTotal passed: %d\nTotal failed: %d\n\n", NUM_ITERATIONS, NUM_ITERATIONS - totalFailures, totalFailures);
	return 0;
}




















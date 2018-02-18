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
	printf("---- STARTING RANDOM TEST ON SMITHY ----\n");

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
		G.hand[player][0] = smithy; // First card Smithy
		
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
		int estatesDrawn = 0;
		int duchysDrawn = 0;
		int provincesDrawn = 0;
		int cursesDrawn = 0;
		int adventurersDrawn = 0;
		int embargosDrawn = 0;
		int villagesDrawn = 0;
		int minionsDrawn = 0;
		int minesDrawn = 0;
		int cutpursesDrawn = 0;
		int seaHagsDrawn = 0;
		int tributesDrawn = 0;
		int smithysDrawn = 0;
		int councilRoomsDrawn = 0;
		int cardsDrawn = 0;
		
		int deckPosition = deckSize;
		deckPosition--;
		if (deckPosition >= 0) {
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
				case estate: 
					estatesDrawn++; 
					cardsDrawn++;
					break;
				case duchy: 
					duchysDrawn++; 
					cardsDrawn++;
					break;
				case province: 
					provincesDrawn++; 
					cardsDrawn++;
					break;
				case curse: 
					cursesDrawn++; 
					cardsDrawn++;
					break;
				case adventurer: 
					adventurersDrawn++; 
					cardsDrawn++;
					break;
				case embargo: 
					embargosDrawn++; 
					cardsDrawn++;
					break;
				case village: 
					villagesDrawn++; 
					cardsDrawn++;
					break;
				case minion: 
					minionsDrawn++; 
					cardsDrawn++;
					break;
				case mine: 
					minesDrawn++; 
					cardsDrawn++;
					break;
				case cutpurse: 
					cutpursesDrawn++; 
					cardsDrawn++;
					break;
				case sea_hag: 
					seaHagsDrawn++; 
					cardsDrawn++;
					break;
				case tribute: 
					tributesDrawn++; 
					cardsDrawn++;
					break;
				case smithy: 
					smithysDrawn++; 
					cardsDrawn++;
					break;
				case council_room: 
					councilRoomsDrawn++; 
					cardsDrawn++;
					break;
			}
		}
		deckPosition--;
		if (deckPosition >= 0) {
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
				case estate: 
					estatesDrawn++; 
					cardsDrawn++;
					break;
				case duchy: 
					duchysDrawn++; 
					cardsDrawn++;
					break;
				case province: 
					provincesDrawn++; 
					cardsDrawn++;
					break;
				case curse: 
					cursesDrawn++; 
					cardsDrawn++;
					break;
				case adventurer: 
					adventurersDrawn++; 
					cardsDrawn++;
					break;
				case embargo: 
					embargosDrawn++; 
					cardsDrawn++;
					break;
				case village: 
					villagesDrawn++; 
					cardsDrawn++;
					break;
				case minion: 
					minionsDrawn++; 
					cardsDrawn++;
					break;
				case mine: 
					minesDrawn++; 
					cardsDrawn++;
					break;
				case cutpurse: 
					cutpursesDrawn++; 
					cardsDrawn++;
					break;
				case sea_hag: 
					seaHagsDrawn++; 
					cardsDrawn++;
					break;
				case tribute: 
					tributesDrawn++; 
					cardsDrawn++;
					break;
				case smithy: 
					smithysDrawn++; 
					cardsDrawn++;
					break;
				case council_room: 
					councilRoomsDrawn++; 
					cardsDrawn++;
					break;
			}
		}
		
		deckPosition--;
		if (deckPosition >= 0) {
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
				case estate: 
					estatesDrawn++; 
					cardsDrawn++;
					break;
				case duchy: 
					duchysDrawn++; 
					cardsDrawn++;
					break;
				case province: 
					provincesDrawn++; 
					cardsDrawn++;
					break;
				case curse: 
					cursesDrawn++; 
					cardsDrawn++;
					break;
				case adventurer: 
					adventurersDrawn++; 
					cardsDrawn++;
					break;
				case embargo: 
					embargosDrawn++; 
					cardsDrawn++;
					break;
				case village: 
					villagesDrawn++; 
					cardsDrawn++;
					break;
				case minion: 
					minionsDrawn++; 
					cardsDrawn++;
					break;
				case mine: 
					minesDrawn++; 
					cardsDrawn++;
					break;
				case cutpurse: 
					cutpursesDrawn++; 
					cardsDrawn++;
					break;
				case sea_hag: 
					seaHagsDrawn++; 
					cardsDrawn++;
					break;
				case tribute: 
					tributesDrawn++; 
					cardsDrawn++;
					break;
				case smithy: 
					smithysDrawn++; 
					cardsDrawn++;
					break;
				case council_room: 
					councilRoomsDrawn++; 
					cardsDrawn++;
					break;
			}
		}
		
		int numCardsInDeck = deckPosition;
		if (numCardsInDeck < 0) numCardsInDeck = 0;
		
		printf("STARTING TEST NUMBER %d\n", iteration);
		printf("Initial deck count: %d, hand count: %d\n\n", deckSize, handSize);

		// Invoke method (play Smithy)
		cardEffect(smithy, 0, 0, 0, &testG, 0, &bonus);
		
		int numFailures = 0;
		// Verify results
		// Deck
		numFailures += assertEquals("Deck count", testG.deckCount[player], numCardsInDeck);
		
		// Hand
		numFailures += assertEquals("Hand count", testG.handCount[player], handSize + cardsDrawn - 1);
		numFailures += assertEquals("Copper count", numCardsInArray(testG.hand[player], testG.handCount[player], copper), numCardsInArray(G.hand[player], G.handCount[player], copper) + coppersDrawn);
		numFailures += assertEquals("Silver count", numCardsInArray(testG.hand[player], testG.handCount[player], silver), numCardsInArray(G.hand[player], G.handCount[player], silver) + silversDrawn);
		numFailures += assertEquals("Gold count", numCardsInArray(testG.hand[player], testG.handCount[player], gold), numCardsInArray(G.hand[player], G.handCount[player], gold) + goldsDrawn);
		numFailures += assertEquals("Estate count", numCardsInArray(testG.hand[player], testG.handCount[player], estate), numCardsInArray(G.hand[player], G.handCount[player], estate) + estatesDrawn);
		numFailures += assertEquals("Duchy count", numCardsInArray(testG.hand[player], testG.handCount[player], duchy), numCardsInArray(G.hand[player], G.handCount[player], duchy) + duchysDrawn);
		numFailures += assertEquals("Province count", numCardsInArray(testG.hand[player], testG.handCount[player], province), numCardsInArray(G.hand[player], G.handCount[player], province) + provincesDrawn);
		numFailures += assertEquals("Curse count", numCardsInArray(testG.hand[player], testG.handCount[player], curse), numCardsInArray(G.hand[player], G.handCount[player], curse) + cursesDrawn);
		numFailures += assertEquals("Adventurer count", numCardsInArray(testG.hand[player], testG.handCount[player], adventurer), numCardsInArray(G.hand[player], G.handCount[player], adventurer) + adventurersDrawn);
		numFailures += assertEquals("Embargo count", numCardsInArray(testG.hand[player], testG.handCount[player], embargo), numCardsInArray(G.hand[player], G.handCount[player], embargo) + embargosDrawn);
		numFailures += assertEquals("Village count", numCardsInArray(testG.hand[player], testG.handCount[player], village), numCardsInArray(G.hand[player], G.handCount[player], village) + villagesDrawn);
		numFailures += assertEquals("Minion count", numCardsInArray(testG.hand[player], testG.handCount[player], minion), numCardsInArray(G.hand[player], G.handCount[player], minion) + minionsDrawn);
		numFailures += assertEquals("Mine count", numCardsInArray(testG.hand[player], testG.handCount[player], mine), numCardsInArray(G.hand[player], G.handCount[player], mine) + minesDrawn);
		numFailures += assertEquals("Cutpurse count", numCardsInArray(testG.hand[player], testG.handCount[player], cutpurse), numCardsInArray(G.hand[player], G.handCount[player], cutpurse) + cutpursesDrawn);
		numFailures += assertEquals("Sea hag count", numCardsInArray(testG.hand[player], testG.handCount[player], sea_hag), numCardsInArray(G.hand[player], G.handCount[player], sea_hag) + seaHagsDrawn);
		numFailures += assertEquals("Tribute count", numCardsInArray(testG.hand[player], testG.handCount[player], tribute), numCardsInArray(G.hand[player], G.handCount[player], tribute) + tributesDrawn);
		numFailures += assertEquals("Smithy count", numCardsInArray(testG.hand[player], testG.handCount[player], smithy), numCardsInArray(G.hand[player], G.handCount[player], smithy) + smithysDrawn - 1);
		numFailures += assertEquals("Council room count", numCardsInArray(testG.hand[player], testG.handCount[player], council_room), numCardsInArray(G.hand[player], G.handCount[player], council_room) + councilRoomsDrawn);
		
		
		// Discard
		numFailures += assertEquals("Discard count", testG.discardCount[player], 0);
		
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

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
	printf("---- STARTING RANDOM TEST ON MINE ----\n");
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
		// Random supply sizes for treasures
		G.supplyCount[copper] = rand()%47; // 2 player game starts with 46
		G.supplyCount[silver] = rand()%41; // starts with 40
		G.supplyCount[gold] = rand()%31; // starts with 30
		
		// Random hand size
		int handSize = rand()%10 + 1;
		G.handCount[player] = handSize;
		G.hand[player][0] = mine; // First card Mine
		
		// Fill hand with random cards
		int i;
		for (i = 1; i < handSize; i++) {
			G.hand[player][i] = randomCard(k);
		}
		
		// Pick random hand position and card to gain
		int choice1 = rand()%handSize;
		int choice2 = randomCard(k);
		
		// Copy G to testG
		memcpy(&testG, &G, sizeof(struct gameState));
		
		
		// Get expected results		
		int copperGained = 0;
		int copperLost = 0;
		int silverGained = 0;
		int silverLost = 0;
		int goldGained = 0;
		int goldLost = 0;
		
		if (G.hand[player][choice1] == copper) {
			copperLost = 1;
			if (choice2 == copper && G.supplyCount[copper] > 0) {
				copperGained = 1;
			} else if (choice2 == silver && G.supplyCount[silver] > 0) {
				silverGained = 1;
			}
		} else if (G.hand[player][choice1] == silver) {
			silverLost = 1;
			if (choice2 == copper && G.supplyCount[copper] > 0) {
				copperGained = 1;
			} else if (choice2 == silver && G.supplyCount[silver] > 0) {
				silverGained = 1;
			} else if (choice2 == gold && G.supplyCount[gold] > 0) {
				goldGained = 1;
			}
		} else if (G.hand[player][choice1] == gold) {
			goldLost = 1;
			if (choice2 == copper && G.supplyCount[copper] > 0) {
				copperGained = 1;
			} else if (choice2 == silver && G.supplyCount[silver] > 0) {
				silverGained = 1;
			} else if (choice2 == gold && G.supplyCount[gold] > 0) {
				goldGained = 1;
			}
		}
		
		printf("STARTING TEST NUMBER %d\n", iteration);
		printf("Supply pile counts\n");
		printf("Copper: %d, Silver: %d, Gold %d\n", G.supplyCount[copper], G.supplyCount[silver], G.supplyCount[gold]);
		printf("Initial hand contents\n");
		printf("Copper: %d, Silver: %d, Gold %d\n", numCardsInArray(G.hand[player], G.handCount[player], copper), numCardsInArray(G.hand[player], G.handCount[player], silver), numCardsInArray(G.hand[player], G.handCount[player], gold));
		printf("Trashing card %d, gaining card %d\n", G.hand[player][choice1], choice2);

		// Invoke method (play Mine)
		cardEffect(mine, choice1, choice2, 0, &testG, 0, &bonus);
		
		int numFailures = 0;
		// Verify results
		
		// Hand
		numFailures += assertEquals("Copper count", numCardsInArray(testG.hand[player], testG.handCount[player], copper), numCardsInArray(G.hand[player], G.handCount[player], copper) + copperGained - copperLost);
		numFailures += assertEquals("Silver count", numCardsInArray(testG.hand[player], testG.handCount[player], silver), numCardsInArray(G.hand[player], G.handCount[player], silver) + silverGained - silverLost);
		numFailures += assertEquals("Gold count", numCardsInArray(testG.hand[player], testG.handCount[player], gold), numCardsInArray(G.hand[player], G.handCount[player], gold) + goldGained - goldLost);
		
		// Supply piles
		numFailures += assertEquals("Copper supply pile", testG.supplyCount[copper], G.supplyCount[copper] - copperGained);
		numFailures += assertEquals("Silver supply pile", testG.supplyCount[silver], G.supplyCount[silver] - silverGained);
		numFailures += assertEquals("Gold supply pile", testG.supplyCount[gold], G.supplyCount[gold] - goldGained);
	
		
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
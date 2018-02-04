/*
	buyCard
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "assertEquals.c"

int main() {
	int numFailures = 0;
	
	int numPlayers = 2;
	int player = 0;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int seed = 1;
	struct gameState G, testG;
	
	initializeGame(numPlayers, k, seed, &G);
	G.whoseTurn = player;
	
	// start with 8 coins and 2 buys
	G.coins = 8;
	G.numBuys = 2;
	
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf(" ----- Starting test: buyCard() -----\n");
	
	// buy village (3 coins)
	printf(" - Buy village -\n");
	buyCard(village, &testG);
	numFailures += assertEquals("Buy village coins",testG.coins, G.coins - 3);
	numFailures += assertEquals("Buy village discard count",testG.discardCount[player], G.discardCount[player] + 1);
	numFailures += assertEquals("Buy village num buys remaining",testG.numBuys, G.numBuys - 1);
	numFailures += assertEquals("Buy village supply count",testG.supplyCount[village], G.supplyCount[village] - 1);
	
	// buy mine (5 coins)
	printf(" - Buy mine -\n");
	buyCard(mine, &testG);
	numFailures += assertEquals("Buy mine coins",testG.coins, G.coins - 8);
	numFailures += assertEquals("Buy mine discard count",testG.discardCount[player], G.discardCount[player] + 2);
	numFailures += assertEquals("Buy mine num buys remaining",testG.numBuys, G.numBuys - 2);
	numFailures += assertEquals("Buy mine supply count",testG.supplyCount[mine], G.supplyCount[mine] - 1);

	// Failure - not enough coins
	printf(" - Not enough coins -\n");
	G.coins = 4;
	G.numBuys = 1;
	memcpy(&testG, &G, sizeof(struct gameState));
	buyCard(mine, &testG);
	numFailures += assertEquals("Coins",testG.coins, G.coins);
	numFailures += assertEquals("Discard count",testG.discardCount[player], G.discardCount[player]);
	numFailures += assertEquals("Buys remaining",testG.numBuys, G.numBuys);
	numFailures += assertEquals("Supply count",testG.supplyCount[mine], G.supplyCount[mine]);
	
	// Failure - out of buys
	printf(" - Out of buys -\n");
	G.coins = 5;
	G.numBuys = 0;
	memcpy(&testG, &G, sizeof(struct gameState));
	buyCard(mine, &testG);
	numFailures += assertEquals("Coins",testG.coins, G.coins);
	numFailures += assertEquals("Discard count",testG.discardCount[player], G.discardCount[player]);
	numFailures += assertEquals("Buys remaining",testG.numBuys, G.numBuys);
	numFailures += assertEquals("Supply count",testG.supplyCount[mine], G.supplyCount[mine]);
	
	if (numFailures == 0) printf("TEST SUCCESSFULLY COMPLETED\n");
	else printf("TEST FAILED\n");
	printf("\n");
	
	return 0;
}
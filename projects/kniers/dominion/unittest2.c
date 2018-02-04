/*
	updateCoins
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
	int bonus = 0;
	struct gameState G, testG;
	
	initializeGame(numPlayers, k, seed, &G);
	G.whoseTurn = player;
		
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf(" ----- Starting test: updateCoins() -----\n");
	
	// Add a copper
	printf(" - Add a copper -\n");
	testG.handCount[player]++;
	testG.hand[player][testG.handCount[player]-1] = copper;
	updateCoins(player, &testG, bonus);
	updateCoins(player, &G, bonus);
	numFailures += assertEquals("Coins",testG.coins, G.coins + 1);
	
	// Add a silver
	printf(" - Add a silver -\n");
	testG.hand[player][testG.handCount[player]-1] = silver;
	updateCoins(player, &testG, bonus);
	updateCoins(player, &G, bonus);
	numFailures += assertEquals("Coins",testG.coins, G.coins + 2);
	
	// Add a gold
	printf(" - Add a gold -\n");
	testG.hand[player][testG.handCount[player]-1] = gold;
	updateCoins(player, &testG, bonus);
	updateCoins(player, &G, bonus);
	numFailures += assertEquals("Coins",testG.coins, G.coins + 3);
	
	// Add bonus
	printf(" - Add a bonus -\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	updateCoins(player, &G, bonus);
	bonus += 2;
	updateCoins(player, &testG, bonus);
	numFailures += assertEquals("Coins",testG.coins, G.coins + 2);
	
	if (numFailures == 0) printf("TEST SUCCESSFULLY COMPLETED\n");
	else printf("TEST FAILED\n");
	printf("\n");
	
	return 0;
}
	
/*	
	isGameOver
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
	
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf(" ----- Starting test: isGameOver() -----\n");
	
	// No changes
	printf(" - New game -\n");
	numFailures += assertEquals("Game over state",isGameOver(&testG), 0);
	
	// Province pile empty
	printf(" - Province pile empty -\n");
	testG.supplyCount[province] = 0;
	numFailures += assertEquals("Game over state",isGameOver(&testG), 1);
	
	// 3 piles empty ends game
	printf(" - 3 supply piles empty -\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.supplyCount[copper] = 0;
	testG.supplyCount[estate] = 0;
	testG.supplyCount[mine] = 0;
	numFailures += assertEquals("Game over state",isGameOver(&testG), 1);
	
	// 2 pile empty, game not over
	printf(" - 2 supply piles empty -\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.supplyCount[copper] = 0;
	testG.supplyCount[estate] = 0;
	numFailures += assertEquals("Game over state",isGameOver(&testG), 0);
		
	if (numFailures == 0) printf("TEST SUCCESSFULLY COMPLETED\n");
	else printf("TEST FAILED\n");
	printf("\n");
	
	return 0;
}
		
		
/*	
	Embargo card test
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
	
	G.hand[player][0] = embargo;
	G.hand[player][1] = embargo;
	
	printf(" ----- Starting test: embargo card -----\n");
	
	// Play embargo on copper
	printf(" - Play embargo on copper -\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(embargo, copper, 0, 0, &testG, 0, &bonus);
	numFailures += assertEquals("Tokens on copper",testG.embargoTokens[copper], G.embargoTokens[copper] + 1);
	numFailures += assertEquals("Coins",testG.coins, G.coins + 2);
	
	// Play embargo on copper with an embargo token already on copper
	printf(" - Play embargo on copper with a token already on copper -\n");
	G.embargoTokens[copper] = 1;
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(embargo, copper, 0, 0, &testG, 0, &bonus);
	numFailures += assertEquals("Tokens on copper",testG.embargoTokens[copper], G.embargoTokens[copper] + 1);
	numFailures += assertEquals("Coins",testG.coins, G.coins + 2);
	
	// Play embargo on village with an embargo token on copper already
	printf(" - Play embargo on village with a token already on copper -\n");
	G.embargoTokens[copper] = 1;
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(embargo, village, 0, 0, &testG, 0, &bonus);
	numFailures += assertEquals("Tokens on copper",testG.embargoTokens[copper], G.embargoTokens[copper]);
	numFailures += assertEquals("Tokens on village",testG.embargoTokens[village], G.embargoTokens[village] + 1);
	numFailures += assertEquals("Coins",testG.coins, G.coins + 2);
	
	if (numFailures == 0) printf("TEST SUCCESSFULLY COMPLETED\n");
	else printf("TEST FAILED\n");
	printf("\n");
	
	return 0;
}
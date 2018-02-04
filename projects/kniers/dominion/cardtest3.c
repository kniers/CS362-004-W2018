/*	
	Village card test
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
	
	G.hand[player][0] = village;
	
	printf(" ----- Starting test: village card -----\n");
	
	// Play village
	printf(" - Play village -\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(village, 0, 0, 0, &testG, 0, &bonus);
	numFailures += assertEquals("Actions",testG.numActions, G.numActions + 1);
	numFailures += assertEquals("Hand count",testG.handCount[player], G.handCount[player]);
	numFailures += assertEquals("Deck count",testG.deckCount[player], G.deckCount[player]-1);
	numFailures += assertEquals("Played card count",testG.playedCardCount, G.playedCardCount + 1);
	
	if (numFailures == 0) printf("TEST SUCCESSFULLY COMPLETED\n");
	else printf("TEST FAILED\n");
	printf("\n");
	
	return 0;
}
		
		
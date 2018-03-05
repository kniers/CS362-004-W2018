/*	
	Smithy card test
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
	
	G.hand[player][0] = smithy;
	memcpy(&testG, &G, sizeof(struct gameState));

	printf(" ----- Starting test: Smithy card -----\n");
	
	// Play smithy
	printf(" - Play smithy -\n");
	cardEffect(smithy, 0, 0, 0, &testG, 0, &bonus);
	printf("hand count: %d, expected: %d\n", testG.handCount[player], G.handCount[player]+2);
	numFailures += assertEquals("Hand count",testG.handCount[player], G.handCount[player] + 2);
	printf("played count: %d, expected: %d\n", testG.playedCardCount, G.playedCardCount+1);
	numFailures += assertEquals("Played card count",testG.playedCardCount, G.playedCardCount + 1);
	printf("deck count: %d, expected: %d\n", testG.deckCount[player], G.deckCount[player]-3);
	numFailures += assertEquals("Deck count",testG.deckCount[player], G.deckCount[player] - 3);
	
	// Play smithy with 1 more card in hand
	printf(" - Play smithy with additional card in hand -\n");
	G.handCount[player] += 1;
	G.hand[player][G.handCount[player]-1] = smithy;
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, 0, 0, 0, &testG, 0, &bonus);
	printf("hand count: %d, expected: %d\n", testG.handCount[player], G.handCount[player]+2);
	numFailures += assertEquals("Hand count",testG.handCount[player], G.handCount[player] + 2);
	printf("played count: %d, expected: %d\n", testG.playedCardCount, G.playedCardCount+1);
	numFailures += assertEquals("Played card count",testG.playedCardCount, G.playedCardCount + 1);
	printf("deck count: %d, expected: %d\n", testG.deckCount[player], G.deckCount[player]-3);
	numFailures += assertEquals("Deck count",testG.deckCount[player], G.deckCount[player] - 3);
	
	if (numFailures == 0) printf("TEST SUCCESSFULLY COMPLETED\n");
	else printf("TEST FAILED\n");
	printf("\n");
	
	return 0;
}
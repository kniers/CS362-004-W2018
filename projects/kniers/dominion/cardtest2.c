/*	
	Adventurer card test
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
	
	G.hand[player][0] = adventurer;
	
	printf(" ----- Starting test: adventurer card -----\n");
	
	// Top of deck is 2 coppers
	printf(" - Top of deck is 2 coppers -\n");
	G.deck[player][G.deckCount[player]-1] = copper;
	G.deck[player][G.deckCount[player]-2] = copper;
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, 0, 0, 0, &testG, 0, &bonus);
	numFailures += assertEquals("Hand count",testG.handCount[player], G.handCount[player] + 2);
	numFailures += assertEquals("Deck count",testG.deckCount[player], G.deckCount[player] - 2);
	numFailures += assertEquals("Discard count",testG.discardCount[player], G.discardCount[player]);
	
	// Top of deck is 2 silvers
	printf(" - Top of deck is 2 silvers -\n");
	G.deck[player][G.deckCount[player]-1] = silver;
	G.deck[player][G.deckCount[player]-2] = silver;
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, 0, 0, 0, &testG, 0, &bonus);
	numFailures += assertEquals("Hand count",testG.handCount[player], G.handCount[player] + 2);
	numFailures += assertEquals("Deck count",testG.deckCount[player], G.deckCount[player] - 2);
	numFailures += assertEquals("Discard count",testG.discardCount[player], G.discardCount[player]);

	// Top of deck is 2 golds
	printf(" - Top of deck is 2 gold -\n");
	G.deck[player][G.deckCount[player]-1] = gold;
	G.deck[player][G.deckCount[player]-2] = gold;
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, 0, 0, 0, &testG, 0, &bonus);
	numFailures += assertEquals("Hand count",testG.handCount[player], G.handCount[player] + 2);
	numFailures += assertEquals("Deck count",testG.deckCount[player], G.deckCount[player] - 2);
	numFailures += assertEquals("Discard count",testG.discardCount[player], G.discardCount[player]);
	
	// Top of deck is copper, estate, village, and silver
	printf(" - Top of deck is copper, estate, village, and silver -\n");
	G.deck[player][G.deckCount[player]-1] = copper;
	G.deck[player][G.deckCount[player]-2] = estate;
	G.deck[player][G.deckCount[player]-3] = village;
	G.deck[player][G.deckCount[player]-4] = silver;
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, 0, 0, 0, &testG, 0, &bonus);
	numFailures += assertEquals("Hand count",testG.handCount[player], G.handCount[player] + 2);
	numFailures += assertEquals("Deck count",testG.deckCount[player], G.deckCount[player] - 4);
	numFailures += assertEquals("Discard count",testG.discardCount[player], G.discardCount[player] + 2);
	
	if (numFailures == 0) printf("TEST SUCCESSFULLY COMPLETED\n");
	else printf("TEST FAILED\n");
	printf("\n");
	
	return 0;
}
	
	
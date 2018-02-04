/*	
	numHandCards
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
	printf(" ----- Starting test: numHandCards() -----\n");

	// Add card
	printf(" - Add a card -\n");
	testG.handCount[player] += 1;
	numFailures += assertEquals("Cards in hand",numHandCards(&testG), numHandCards(&G) + 1);
	
	// Remove a card
	printf(" - Remove a card -\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.handCount[player] -= 1;
	numFailures += assertEquals("Cards in hand",numHandCards(&testG), numHandCards(&G) - 1);
	
	// Change player
	printf(" - Change players -\n");
	int player2 = 1;
	G.whoseTurn = player2;
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.handCount[player2] += 1;
	numFailures += assertEquals("Cards in hand",numHandCards(&testG), numHandCards(&G) + 1);
		
	if (numFailures == 0) printf("TEST SUCCESSFULLY COMPLETED\n");
	else printf("TEST FAILED\n");
	printf("\n");
	
	return 0;
}
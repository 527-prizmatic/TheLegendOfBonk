#include <stdlib.h>

#include "interact.h"

void interactTilePos(char _map[H_MAP_T][W_MAP_T]) {
	system("cls");
	chestCpt = 0;
	lampCpt = 0;
	int counterNpc = 0;
	char _txt[256] = "";

	for (int i = 0; i < H_MAP_T; i++) {
		for (int j = 0; j < W_MAP_T; j++) {
			switch (_map[i][j]) {
				// Sign
				case 81:
					lampArray[lampCpt].id = lampCpt;
					lampArray[lampCpt].lampPosition.y = TILE_PX * i;
					lampArray[lampCpt].lampPosition.x = TILE_PX * j;
					lampCpt++;
					break;
				case 90:
					pnjArray[counterNpc].id = counterNpc;
					if (counterNpc == 1) sprintf_s(_txt, 256, "Z-Q-S-D to move\nLeft Shift to sprint\nE to interact with the world\n...but you already knew that,\nof course.\nDon't lie to me, you couldn't\nbe reading this otherwise.");
					else {
						int r = rand() % 8;
						switch (r) {
							case 0: sprintf_s(_txt, 256, "Invest in dogecoin TODAY!!!\nSign up today and\nget 100 free dogecoin\n\n\"Much munies\"\n - Satisfied customer"); break;
							case 1: sprintf_s(_txt, 256, "Dogecoin exchange\n1 DOGE = 0.074 USD\n1 DOGE = 0.068 EUR\n1 DOGE = 0.059 GBP\n1 DOGE = 11.06 JPY"); break;
							case 2: sprintf_s(_txt, 256, "@elonmusk on X -\nHonestly, I did it for the memes."); break;
							case 3: sprintf_s(_txt, 256, "Market collapses after\nElon Musk buys the USA\nWhat future for doge?"); break;
							case 4: sprintf_s(_txt, 256, "bonk"); break;
							case 5: sprintf_s(_txt, 256, "wow such sign very text"); break;
							case 6: sprintf_s(_txt, 256, "YOUR AD HERE\nCall 555-312-DOGE"); break;
							case 7: sprintf_s(_txt, 256, "SpaceX rocket launch fails,\ncrashes into Amazon HQ\nJeff Bezos claims it was\non purpose, WW3 imminent"); break;
						}
					}
					
					sprintf(pnjArray[counterNpc].txt, "%s", _txt);
					pnjArray[counterNpc].pnjPosition.y = TILE_PX * i;
					pnjArray[counterNpc].pnjPosition.x = TILE_PX * j;
					counterNpc++;
					break;
				// Chest
				case 91:
					chestArray[chestCpt].id = chestCpt;
					chestArray[chestCpt].chestPosition.y = TILE_PX * i;
					chestArray[chestCpt].chestPosition.x = TILE_PX * j;
					chestCpt++;
					break;
				default: break;
			}
		}
	}
}

int canInteract() {
    int playerRadius = 60;
    int interactRadius = 20;

    int sqrPosChestX = 0;
    int sqrPosChestY = 0;

	int sqrPosPnjX = 0;
	int sqrPosPnjY = 0;

	int sqrPosCageX = (playerPos.x - 3970.0f) * (playerPos.x - 3970.0f);
	int sqrPosCageY = (playerPos.y - 70.0f) * (playerPos.y - 70.0f);

    int sqrRadius = (playerRadius + interactRadius) * (playerRadius + interactRadius);

	for (int i = 0; i < 5; i++) {
		sqrPosChestX = (playerPos.x - chestArray[i].chestPosition.x) * (playerPos.x - chestArray[i].chestPosition.x);
		sqrPosChestY = (playerPos.y - chestArray[i].chestPosition.y) * (playerPos.y - chestArray[i].chestPosition.y);
		if (sqrPosChestX + sqrPosChestY < sqrRadius) return chestArray[i].id;
	}
	for (int j = 0; j < 10; j++) {
		sqrPosPnjX = (playerPos.x - pnjArray[j].pnjPosition.x) * (playerPos.x - pnjArray[j].pnjPosition.x);
		sqrPosPnjY = (playerPos.y - pnjArray[j].pnjPosition.y) * (playerPos.y - pnjArray[j].pnjPosition.y);
		if (sqrPosPnjX + sqrPosPnjY < sqrRadius) return pnjArray[j].id + 20;
	}

	if (sqrPosCageX + sqrPosCageY < sqrRadius) return 100;

	return -1;
}
#include <stdlib.h>

#include "SFML/Audio.h"
#include "interact.h"
#include "textures.h"
#include "save.h"

#pragma warning (disable: 4244)

void interactTilePos(char _map[H_MAP_T][W_MAP_T], char _props[H_MAP_T][W_MAP_T], sfMusic* _m) {
	system("cls");
	chestCpt = 0;
	lampCpt = 0;
	int counterNpc = 0;
	char _txt[256] = "";

	for (int i = 0; i < H_MAP_T; i++) {
		for (int j = 0; j < W_MAP_T; j++) {
			int invTemp[4];
			switch (_props[i][j]) {
				// Sign
				case 90:
					npcArray[counterNpc].id = counterNpc;
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
					
					sprintf(npcArray[counterNpc].txt, "%s", _txt);
					npcArray[counterNpc].pnjPosition.y = TILE_PX * i;
					npcArray[counterNpc].pnjPosition.x = TILE_PX * j;
					counterNpc++;
					break;
				// Chest
				case 91:
					chestArray[chestCpt].id = chestCpt;
					chestArray[chestCpt].spriteId = 0;
					chestArray[chestCpt].chestPosition.y = TILE_PX * i;
					chestArray[chestCpt].chestPosition.x = TILE_PX * j;
					chestArray[chestCpt].flagOpen = 0;
					chestCpt++;
					break;
				case 115:
					load_map(_map, _props, &playerPos, invTemp, _m);
					playerPos.y = i * TILE_PX;
					playerPos.x = j * TILE_PX;
					save_map(_map, _props, playerPos, invTemp, _m);
					break;
				default: break;
			}
		}
	}
}

int canInteract() {
    float playerRadius = 60.f;
	float interactRadius = 20.f;

	float sqrPosChestX = 0.f;
	float sqrPosChestY = 0.f;

	float sqrPosNpcX = 0.f;
	float sqrPosNpcY = 0.f;

	float sqrPosCageX = (playerPos.x - 3970.0f) * (playerPos.x - 3970.0f);
	float sqrPosCageY = (playerPos.y - 70.0f) * (playerPos.y - 70.0f);

	float sqrPosCheeseX = (playerPos.x - 1655.0f) * (playerPos.x - 1655.0f);
	float sqrPosCheeseY = (playerPos.y - 2085.0f) * (playerPos.y - 2085.0f);

	float sqrRadius = (playerRadius + interactRadius) * (playerRadius + interactRadius);

	for (int i = 0; i < 5; i++) {
		sqrPosChestX = (playerPos.x - chestArray[i].chestPosition.x) * (playerPos.x - chestArray[i].chestPosition.x);
		sqrPosChestY = (playerPos.y - chestArray[i].chestPosition.y) * (playerPos.y - chestArray[i].chestPosition.y);
		if (sqrPosChestX + sqrPosChestY < sqrRadius) return chestArray[i].id;
	}
	for (int j = 0; j < 10; j++) {
		sqrPosNpcX = (playerPos.x - npcArray[j].pnjPosition.x) * (playerPos.x - npcArray[j].pnjPosition.x);
		sqrPosNpcY = (playerPos.y - npcArray[j].pnjPosition.y) * (playerPos.y - npcArray[j].pnjPosition.y);
		if (sqrPosNpcX + sqrPosNpcY < sqrRadius) return npcArray[j].id + 20;
	}

	if (sqrPosCageX + sqrPosCageY < sqrRadius) return 100;
	if (sqrPosCheeseX + sqrPosCheeseY < sqrRadius) return 200;

	return -1;
}
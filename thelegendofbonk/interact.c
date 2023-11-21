#include "interact.h"


void interactTilePos(char _map[H_MAP_T][W_MAP_T])
{
	system("cls");
	chestCpt = 0;
	pnjCpt = 0;
	char _txt[100] = "";

	for (int i = 0; i < H_MAP_T; i++)
	{
		for (int j = 0; j < W_MAP_T; j++)
		{
			switch (_map[i][j])
			{
				// Sign
				case 90:
					pnjArray[pnjCpt].id = pnjCpt;
					sprintf_s(_txt, 25, "Je suis le pnj n %d", pnjCpt);
					pnjArray[pnjCpt].txt = _txt;
					pnjArray[pnjCpt].pnjPosition.y = TILE_PX * i;
					pnjArray[pnjCpt].pnjPosition.x = TILE_PX * j;
					printf("PNJ : Position Y : %f, Position X : %f \n", pnjArray[pnjCpt].pnjPosition.y, pnjArray[pnjCpt].pnjPosition.x);
					pnjCpt++;
					break;
				// Chest
				case 91:
					chestArray[chestCpt].id = chestCpt;
					chestArray[chestCpt].chestPosition.y = TILE_PX * i;
					chestArray[chestCpt].chestPosition.x = TILE_PX * j;
					printf("CHEST : Position Y : %f, Position X : %f\n", chestArray[chestCpt].chestPosition.y, chestArray[chestCpt].chestPosition.x);
					chestCpt++;
					break;
				default:
					break;
			}
		}
	}
	printf("Nb chest : %d\nNb pnj : %d\n", chestCpt, pnjCpt);
}

int canInteract() {
    int playerRadius = 60;
    int interactRadius = 20;
    int sqrPosChestX = 0;
    int sqrPosChestY = 0;
	int sqrPosPnjX = 0;
	int sqrPosPnjY = 0;
    int sqrRadius = (playerRadius + interactRadius) * (playerRadius + interactRadius);

	for (int i = 0; i < 5; i++)
	{
		sqrPosChestX = (playerPos.x - chestArray[i].chestPosition.x) * (playerPos.x - chestArray[i].chestPosition.x);
		sqrPosChestY = (playerPos.y - chestArray[i].chestPosition.y) * (playerPos.y - chestArray[i].chestPosition.y);
		if (sqrPosChestX + sqrPosChestY < sqrRadius) return chestArray[i].id;
	}
	for (int j = 0; j < 10; j++)
	{
		sqrPosPnjX = (playerPos.x - pnjArray[j].pnjPosition.x) * (playerPos.x - pnjArray[j].pnjPosition.x);
		sqrPosPnjY = (playerPos.y - pnjArray[j].pnjPosition.y) * (playerPos.y - pnjArray[j].pnjPosition.y);
		if (sqrPosPnjX + sqrPosPnjY < sqrRadius) return pnjArray[j].id + 20;
	}
	return -1;
}
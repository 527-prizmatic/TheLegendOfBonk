#include "interact.h"

void interactTilePos(char _map[H_MAP_T][W_MAP_T])
{
	system("cls");
	int chestCpt = 0;

	for (int i = 0; i < H_MAP_T; i++)
	{
		for (int j = 0; j < W_MAP_T; j++)
		{
			switch (_map[i][j])
			{
				case 91:
					chestArray[chestCpt].id = chestCpt;
					chestArray[chestCpt].chestPosition.y = TILE_PX * i;
					chestArray[chestCpt].chestPosition.x = TILE_PX * j;
					printf("Position Y : %f, Position X : %f\n", chestArray[chestCpt].chestPosition.y, chestArray[chestCpt].chestPosition.x);
					chestCpt++;
					break;
				default:
					break;
			}
		}
	}
	printf("Nb chest : %d\n", chestCpt);
}

int canInteract() {
    int playerRadius = 60;
    int interactRadius = 20;
    int sqrPosX = 0;
    int sqrPosY = 0;
    int sqrRadius = (playerRadius + interactRadius) * (playerRadius + interactRadius);

	for (int i = 0; i < 5; i++)
	{
		sqrPosX = (playerPos.x - chestArray[i].chestPosition.x) * (playerPos.x - chestArray[i].chestPosition.x);
		sqrPosY = (playerPos.y - chestArray[i].chestPosition.y) * (playerPos.y - chestArray[i].chestPosition.y);
		if (sqrPosX + sqrPosY < sqrRadius)
		{
			return chestArray[i].id;
		}
	}
	return -1;
}
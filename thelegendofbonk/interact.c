#include "interact.h"

void interactTilePos(char _map[H_MAP_T][W_MAP_T])
{
	int chestCpt = 0;

	for (int i = 0; i < H_MAP_T; i++)
	{
		for (int j = 0; j < W_MAP_T; j++)
		{
			switch (_map[i][j])
			{
				case 5:
					chestArray[chestCpt].id = chestArray;
					chestArray[chestCpt].chestPosition.y = 48 * i;
					chestArray[chestCpt].chestPosition.x = 48 * j;
					chestCpt++;
					break;
				default:
					break;
			}
		}
	}
	printf("Nb chest : %d", chestCpt);
}

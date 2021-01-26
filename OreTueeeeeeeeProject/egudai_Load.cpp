#include "egudai_Load.h"
#include <DxLib.h>

int LoadCSV(int map[Map::Size::height][Map::Size::width], const char *FilePath)
{
	if (map == nullptr)
	{
		return -1;
	}

	int fileHandle;
	char string[256];
	fileHandle = FileRead_open(FilePath);

	for (int y = 0; y < Map::Size::height; y++)
	{
		FileRead_gets(string, 256, fileHandle);
		for (int x = 0, j = 0; x < sizeof(map[0]) / sizeof(map[0][0]); j++)
		{
			if (string[j] == '\0' || ispunct(string[j]))
			{
				x++;
			}
			else
			{
				map[y][x] *= 10;
				map[y][x] += string[j] - '0';
			}
		}
	}
	FileRead_close(fileHandle);

	return 0;
}

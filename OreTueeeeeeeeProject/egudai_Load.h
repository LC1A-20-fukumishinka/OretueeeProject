#pragma once
#include "Map.h"

//map�F�ǂݍ��񂾃}�b�v�̕ۑ���i��d�z��̗v�f����Map�N���X��enum�Ɉˑ��j
//FilePath�FCSV�t�@�C���̃p�X
int LoadCSV(int map[Map::Size::height][Map::Size::width], const char *FilePath);
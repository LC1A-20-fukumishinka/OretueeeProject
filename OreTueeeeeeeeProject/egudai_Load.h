#pragma once
#include "Map.h"

//map：読み込んだマップの保存先（二重配列の要素数はMapクラスのenumに依存）
//FilePath：CSVファイルのパス
int LoadCSV(int map[Map::Size::height][Map::Size::width], const char *FilePath);
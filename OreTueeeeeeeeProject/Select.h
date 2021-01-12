#pragma once
class Select
{
public:
	Select();
	void Init();
	void Update();
	void Draw();
	bool ChangeGameScene();
	int SetStageNum();
private:
	int joypadX;
	int joypadY;
	bool isSelectFlag;
	int stageNum;
	int stageMaxNum;
	bool isOKFlag;
};
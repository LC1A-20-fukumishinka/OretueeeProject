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
	int oldpadX;
	int joypadY;
	int oldpadY;
	bool isSelectFlag;
	int stageNum;
	int stageMaxNum;
	bool isOKFlag;
};
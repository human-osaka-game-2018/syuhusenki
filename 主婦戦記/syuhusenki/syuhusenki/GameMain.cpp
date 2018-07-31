#include "Main.h"

enum GAMESCENE {
	FLOAMOVE,
	PUSHENEMY,
	TAKEGOODS
};

int gameScene = FLOAMOVE;

RECT testText = { 100,600,1100,1000 };
void gameControl();
void gameRender();



void gameMain() {
	switch (gameScene) {
	case FLOAMOVE:
		gameControl();
		gameRender();
		WriteWord("フロア移動", testText, DT_CENTER, RED, FONT);
		break;
	case PUSHENEMY:
		gameControl();
		gameRender();
		WriteWord("モブ主婦排除", testText, DT_CENTER, RED, FONT);
		break;
	case TAKEGOODS:
		gameControl();
		gameRender();
		WriteWord("セール品入手", testText, DT_CENTER, RED, FONT);
		break;
	
	}
}
void gameControl() {
	GetControl(0);
	BottonCheck();
	CheckKeyState(DIK_RETURN);

	if (KeyState[DIK_RETURN] == KeyRelease)// ←キーを押してる
	{
		soundManager.Play("Sound/Buppigan2.wav", false);

		switch (gameScene) {
		case FLOAMOVE:
			gameScene = PUSHENEMY;
			break;
		case PUSHENEMY:
			gameScene = TAKEGOODS;
			break;
		case TAKEGOODS:
			g_scene = SCENE_RESULT;
			gameScene = FLOAMOVE;
			break;
		}
	}
	if (PadState[ButtonA] == KeyRelease)// ←キーを押してる
	{
		soundManager.Play("Sound/Buppigan2.wav", false);

		switch (gameScene) {
		case FLOAMOVE:
			gameScene = PUSHENEMY;
			break;
		case PUSHENEMY:
			gameScene = TAKEGOODS;
			break;
		case TAKEGOODS:
			g_scene = SCENE_RESULT;
			gameScene = FLOAMOVE;
			break;
		}
	}
}

void gameRender() {
	BeginSetTexture();
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BLANK);

	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, YASUKO_TEX);

		WriteWord("メインゲーム", testWord, DT_CENTER, RED, FONT);


	switch (gameScene) {
	case FLOAMOVE:
		WriteWord("フロア移動", testText, DT_CENTER, RED, FONT);
		break;
	case PUSHENEMY:
		WriteWord("モブ主婦排除", testText, DT_CENTER, RED, FONT);
		break;
	case TAKEGOODS:
		WriteWord("セール品入手", testText, DT_CENTER, RED, FONT);
		break;

	}

	EndSetTexture();
}
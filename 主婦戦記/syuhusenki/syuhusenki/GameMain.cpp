#include "Main.h"

#define PLAYERSCALE 100
#define MOVE_MILEAGE 8



enum GAMESCENE {
	FLOAMOVE,
	PUSHENEMY,
	PICKGOODS
};

enum FLOA {
	FOOD,
	CLOTH
};

int gameScene = FLOAMOVE;
int seletFloa = FOOD;

RECT testText = { 100,600,1100,1000 };
CUSTOMVERTEX player[4];
CENTRAL_STATE playerCentral = {800,800,PLAYERSCALE,PLAYERSCALE };

void gameControl();
void gameRender();
void floaMove();
void floaMoveControl();
void floaMoveRender();
void KeyControl(CENTRAL_STATE* central);

void gameMain() {
	switch (gameScene) {
	case FLOAMOVE:
		floaMove();
		//WriteWord("フロア移動", testText, DT_CENTER, RED, FONT);
		break;
	case PUSHENEMY:
		gameControl();
		gameRender();
		WriteWord("モブ主婦排除", testText, DT_CENTER, RED, FONT);
		break;
	case PICKGOODS:
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
		//case FLOAMOVE:
		//	gameScene = PUSHENEMY;
		//	break;
		case PUSHENEMY:
			gameScene = PICKGOODS;
			break;
		case PICKGOODS:
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
			gameScene = PICKGOODS;
			break;
		case PICKGOODS:
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
	//case FLOAMOVE:
	//	WriteWord("フロア移動", testText, DT_CENTER, RED, FONT);
	//	break;
	case PUSHENEMY:
		WriteWord("モブ主婦排除", testText, DT_CENTER, RED, FONT);
		break;
	case PICKGOODS:
		WriteWord("セール品入手", testText, DT_CENTER, RED, FONT);
		break;

	}

	EndSetTexture();
}

void floaMove() {
	static bool isFirst = true;
	if (isFirst) {
		ReadInTexture("Texture/testFrame.png", FRAME_TEX);
		ReadInTexture("Texture/FoodSection.png", FOOD_STAGE_TEX);
		ReadInTexture("Texture/ClothingOrnament.png", CLOTH_STAGE_TEX);
		isFirst = false;
	}
	floaMoveControl();
	floaMoveRender();
}

void floaMoveControl() {
	CreateSquareVertex(player, playerCentral);
	GetControl(0);
	BottonCheck();
	CheckKeyState(DIK_RETURN);

	KeyControl(&playerCentral);

	if (KeyState[DIK_RETURN] == KeyRelease)// ←キーを押してる
	{
		soundManager.Play("Sound/Buppigan2.wav", false);

			gameScene = PUSHENEMY;
	}
	if (PadState[ButtonA] == KeyRelease)// ←キーを押してる
	{
		soundManager.Play("Sound/Buppigan2.wav", false);

			gameScene = PUSHENEMY;
	}
	MoveInToErea(&playerCentral, 20, 20, 1420, 1000);

}

void floaMoveRender() {
	BeginSetTexture();
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BLANK);
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, FRAME_TEX);
	switch (seletFloa) {
	case FOOD:
		EasyCreateSquareVertex(20, 20, 1420, 1000, FOOD_STAGE_TEX);
		break;
	case CLOTH:
		EasyCreateSquareVertex(20, 20, 1420, 1000, CLOTH_STAGE_TEX);
		break;
	}
	SetUpTexture(player, YASUKO_TEX);

	WriteWord("フロア移動", testText, DT_CENTER, RED, FONT);

	EndSetTexture();
}

void KeyControl(CENTRAL_STATE* central) {
	CheckKeyState(DIK_LEFT);
	CheckKeyState(DIK_RIGHT);
	CheckKeyState(DIK_UP);
	CheckKeyState(DIK_DOWN);
	if (KeyState[DIK_LEFT])// →キーを押してる
	{
		central->x -= MOVE_MILEAGE;
	}
	if (KeyState[DIK_RIGHT])// ←キーを押してる
	{
		central->x += MOVE_MILEAGE;
	}
	if (KeyState[DIK_UP])// ↑キーを押してる
	{
		central->y -= MOVE_MILEAGE;
	}
	if (KeyState[DIK_DOWN])// ↓キーを押してる
	{
		central->y += MOVE_MILEAGE;
	}
	//XInputデバイス操作
	GetControl(0);
	BottonCheck();
	if (GetAnalogL(ANALOGRIGHT))
	{
		for (int i = 0; i < 4; i++)
		{
			central->x += MOVE_MILEAGE;
		}
	}

	if (GetAnalogL(ANALOGLEFT))
	{
		for (int i = 0; i < 4; i++)
		{
			central->x -= MOVE_MILEAGE;
		}
	}
	if (!GetAnalogL(ANALOGDOWN))
	{
		for (int i = 0; i < 4; i++)
		{
			central->y -= MOVE_MILEAGE;
		}
	}
	if (!GetAnalogL(ANALOGUP))
	{
		for (int i = 0; i < 4; i++)
		{
			central->y += MOVE_MILEAGE;
		}
	}

}

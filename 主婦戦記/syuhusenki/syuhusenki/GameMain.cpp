#include "Main.h"

#define PLAYER_FLOA_SCALE 100
#define PLAYER_BLOWOFF_SCALE 250
#define MOVE_MILEAGE 8
#define MOVE_MILEAGE_STICK 2

enum MOBDIRECTION {
	NORTH,
	SOUTH,
	EAST,
	WEST
};

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
static bool isBlowOff = false;
static bool isFirst = true;
static int effectCount = 0;
static int fallCount = 0;


RECT testText = { 100,600,1100,1000 };
//プレイヤーの画像頂点
CUSTOMVERTEX playerFloa[4];
CENTRAL_STATE playerCentralFloa = {800,800,PLAYER_FLOA_SCALE,PLAYER_FLOA_SCALE };


//モブの画像頂点
CUSTOMVERTEX mobFloa[4];
CENTRAL_STATE mobCentralFloa = { 500,500 ,PLAYER_FLOA_SCALE,PLAYER_FLOA_SCALE };

CENTRAL_STATE mobCentralBlowOff[5]{
//{ 900,800 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE },
//{ 1100,800 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE},
//{ 1300,800 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE},
//{ 1500,800 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE},
//{ 1700,800 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE}
};

//エフェクト
CUSTOMVERTEX effectExplosion[4];
CENTRAL_STATE effectExplosionCentral = {1000,800,300,300};



void gameControl();
void gameRender();
void floaMove();
void floaMoveControl();
void floaMoveRender();
void keyControl(CENTRAL_STATE* central);
void mobMoving(CENTRAL_STATE* mob);

void blowOff();
void blowOffControl();
void blowOffRender();
void blowOffDeviseControl();
void madamBlowOff();

void gameMain() {
	srand((unsigned int)time(NULL));
	switch (gameScene) {
	case FLOAMOVE:
		floaMove();
		break;
	case PUSHENEMY:
		blowOff();		
		break;
	case PICKGOODS:
		gameControl();
		gameRender();
		effectCount = 0;
		fallCount = 0;

		isFirst = true;

		WriteWord("セール品入手", testText, DT_CENTER, RED, FONT);
		break;
	
	}
}
void gameControl() {
	GetControl(0);
	BottonCheck();
	CheckKeyState(DIK_RETURN);

	if (KeyState[DIK_RETURN] == KeyRelease)
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
	if (PadState[ButtonA] == KeyRelease)
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

void gameRender() 
{
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
//フロア移動場面
void floaMove() {
	
	if (isFirst) {

		ReadInTexture("Texture/testFrame.png", FRAME_TEX);
		ReadInTexture("Texture/FoodSection.png", FOOD_STAGE_TEX);
		ReadInTexture("Texture/ClothingOrnament.png", CLOTH_STAGE_TEX);
		ReadInTexture("Texture/supermarket.jpg", BG_BLOWOFF_TEX);
		ReadInTexture("Texture/bakuhuhathu.png", EXPLOSION_TEX);
		
		mobCentralBlowOff[0] = { 900,800 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };
		mobCentralBlowOff[1] = { 1100,800 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };
		mobCentralBlowOff[2] = { 1300,800 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };
		mobCentralBlowOff[3] = { 1500,800 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };
		mobCentralBlowOff[4] = { 1700,800 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };

		effectExplosionCentral = { 1000,800,300,300 };

		isBlowOff = false;
		isFirst = false;
	}
	floaMoveControl();
	floaMoveRender();
}

void floaMoveControl() {
	CreateSquareVertex(playerFloa, playerCentralFloa);
	CreateSquareVertex(mobFloa,mobCentralFloa);

	BottonCheck();
	CheckKeyState(DIK_RETURN);

	keyControl(&playerCentralFloa);

	if (KeyState[DIK_RETURN] == KeyRelease)
	{
		soundManager.Play("Sound/Buppigan2.wav", false);

			gameScene = PUSHENEMY;
	}

	GetControl(0);
	if (PadState[ButtonA] == KeyRelease)
	{
		soundManager.Play("Sound/Buppigan2.wav", false);

			gameScene = PUSHENEMY;
	}
	mobMoving(&mobCentralFloa);
	MoveInToErea(&playerCentralFloa, 20, 20, 1520, 1000);
	MoveInToErea(&mobCentralFloa, 20, 20, 1520, 1000);
}

void floaMoveRender() {
	BeginSetTexture();
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BLANK);
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, FRAME_TEX);
	switch (seletFloa) {
	case FOOD:
		EasyCreateSquareVertex(20, 20, 1520, 1000, FOOD_STAGE_TEX);
		break;
	case CLOTH:
		EasyCreateSquareVertex(20, 20, 1520, 1000, CLOTH_STAGE_TEX);
		break;
	}
	SetUpTexture(mobFloa, MOB_TEX);
	SetUpTexture(playerFloa, YASUKO_TEX);

	WriteWord("フロア移動", testText, DT_CENTER, RED, FONT);

	EndSetTexture();
}

void keyControl(CENTRAL_STATE* central) {
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
			central->x += MOVE_MILEAGE_STICK;
		}
	}

	if (GetAnalogL(ANALOGLEFT))
	{
		for (int i = 0; i < 4; i++)
		{
			central->x -= MOVE_MILEAGE_STICK;
		}
	}
	if (!GetAnalogL(ANALOGDOWN))
	{
		for (int i = 0; i < 4; i++)
		{
			central->y -= MOVE_MILEAGE_STICK;
		}
	}
	if (!GetAnalogL(ANALOGUP))
	{
		for (int i = 0; i < 4; i++)
		{
			central->y += MOVE_MILEAGE_STICK;
		}
	}
	if (PadState[ButtonLEFT])// →キーを押してる
	{
		central->x += MOVE_MILEAGE;
	}
	if (PadState[ButtonRIGHT])// ←キーを押してる
	{
		central->x -= MOVE_MILEAGE;
	}
	if (PadState[ButtonUP])// ↑キーを押してる
	{
		central->y += MOVE_MILEAGE;
	}
	if (PadState[ButtonDOWN])// ↓キーを押してる
	{
		central->y -= MOVE_MILEAGE;
	}

}

void mobMoving(CENTRAL_STATE* mob) {
	static int mobDirection = EAST;
	static int mobTurnCount = 0;
	mobTurnCount++;
	if (mobTurnCount > 10) {
		mobDirection = rand() % 4;
		mobTurnCount = 0;
	}
	switch (mobDirection) {
	case NORTH:
		mob->y -= MOVE_MILEAGE;
		break;

	case SOUTH:	
		mob->y += MOVE_MILEAGE;
		break;

	case EAST:
		mob->x += MOVE_MILEAGE;
		break;

	case WEST:
		mob->x -= MOVE_MILEAGE;
		break;
	}
}


//コマンド入力場面

void blowOff() {
	blowOffControl();
	blowOffRender();
}
void blowOffControl() {
	CreateSquareVertex(effectExplosion, effectExplosionCentral);
	blowOffDeviseControl();
	if (isBlowOff) {
		madamBlowOff();
		effectExplosionCentral.scaleX++;
		effectExplosionCentral.scaleY++;
		if (effectCount > 270) {
			gameScene = PICKGOODS;
		}
	}
}
void blowOffRender() {
	
	effectCount++;
	BeginSetTexture();

	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BG_BLOWOFF_TEX);
	for (int i = 0; i < 5; i++) {
		CreateSquareVertexEx(mobFloa, mobCentralBlowOff[i], 1, 0, -1, 1);
		if(isBlowOff){

			static float Rad = 0;
			Rad += 0.9;

			if (Rad < 0)
			{
				Rad = Rad * -1;
			}
			if (i % 2)
			{
				Rad = Rad * -1;
			}
			RevolveZ(mobFloa, Rad, mobCentralBlowOff[i]);
		}
		SetUpTexture(mobFloa, MOB_TEX);
	}
	if ((effectCount < 20) || isBlowOff) {
		SetUpTexture(effectExplosion, EXPLOSION_TEX);
	}
	//SetUpTexture(playerFloa, YASUKO_TEX);

	WriteWord("モブ主婦排除", testText, DT_CENTER, RED, FONT);
	EndSetTexture();
}

void blowOffDeviseControl() {
	BottonCheck();
	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_A);
	CheckKeyState(DIK_D);
	CheckKeyState(DIK_W);
	CheckKeyState(DIK_S);

	if (KeyState[DIK_RETURN] == KeyRelease)
	{
		gameScene = PICKGOODS;
		soundManager.Play("Sound/Buppigan2.wav", false);

	}

	if (KeyState[DIK_A])
	{
		isBlowOff = true;
	}
	if (KeyState[DIK_D])
	{

	}
	if (KeyState[DIK_W])
	{

	}
	if (KeyState[DIK_S])
	{

	}
	//XInputデバイス操作
	GetControl(0);
	BottonCheck();

	if (PadState[ButtonA] == KeyRelease)
	{
		gameScene = PICKGOODS;
		soundManager.Play("Sound/Buppigan2.wav", false);


	}
	if (PadState[ButtonB] == KeyRelease)
	{

	}
	if (PadState[ButtonX] == KeyRelease)
	{
		isBlowOff = true;
	}
	if (PadState[ButtonY] == KeyRelease)
	{

	}

}

void madamBlowOff() {
	fallCount++;

	mobCentralBlowOff[0].x -= rand() % 15;
	mobCentralBlowOff[0].y -= rand() % 5;

	mobCentralBlowOff[1].x += rand() % 10;
	mobCentralBlowOff[1].y -= rand() % 10;

	mobCentralBlowOff[2].x += rand() % 3;
	mobCentralBlowOff[2].y -= rand() % 10;

	mobCentralBlowOff[3].x -= rand() % 8;
	mobCentralBlowOff[3].y -= rand() % 10;

	mobCentralBlowOff[4].x += rand() % 25;
	mobCentralBlowOff[4].y -= rand() % 30;

	if (fallCount > 120) {
		for (int i = 0; i < 5; i++) {
			mobCentralBlowOff[i].y += 35;
		}
	}

}
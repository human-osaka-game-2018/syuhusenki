#include "Main.h"

#define PLAYER_FLOA_SCALE 100
#define PLAYER_BLOWOFF_SCALE 150
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

//int gameScene = FLOAMOVE;
int gameScene = PUSHENEMY;
//int gameScene = PICKGOODS;
int seletFloa = FOOD;
static bool isBlowOff = false;
static bool isFirst = true;
static int effectCount = 0;
//static int fallCount = 0;
static bool isTake[2] = {false,false};
static float goodsScale[2] = { 50,50 };

RECT testText = { 100,200,900,500 };


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

CUSTOMVERTEX goodsA[4];
CUSTOMVERTEX goodsB[4];

CENTRAL_STATE goodsCentral[2]{
	{500,500,goodsScale[0],goodsScale[0]},
	{500,500,goodsScale[1],goodsScale[1]}
};


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
void blowOffDeviseControl(int* i,int comand[]);
void madamBlowOff();
bool comandCheck(int comand[], int inputComand[]);


void pickGoods();
void pickGoodsControl();
void pickGoodsRender();
void pickGoodsDeviseControl();

void gameMain() {
	srand((unsigned int)time(NULL));
	if (isFirst) {

		ReadInTexture("Texture/testFrame.png", FRAME_TEX);
		ReadInTexture("Texture/FoodSection.png", FOOD_STAGE_TEX);
		ReadInTexture("Texture/ClothingOrnament.png", CLOTH_STAGE_TEX);
		ReadInTexture("Texture/supermarket.jpg", BG_BLOWOFF_TEX);
		ReadInTexture("Texture/bakuhuhathu.png", EXPLOSION_TEX);
		ReadInTexture("Texture/wagonsele.jpg", BG_PICKGGOODS_TEX);
		ReadInTexture("Texture/beef.png", BEEF_TEX);
		ReadInTexture("Texture/chicken.png", CHICKEN_TEX);
		ReadInTexture("Texture/pork.png", PORK_TEX);

		mobCentralBlowOff[0] = { 850,650 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };
		mobCentralBlowOff[1] = { 900,650 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };
		mobCentralBlowOff[2] = { 950,650 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };
		mobCentralBlowOff[3] = { 1000,650 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };
		mobCentralBlowOff[4] = { 1050,650 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };

		effectExplosionCentral = { 900,750,300,300 };

		isBlowOff = false;
		isFirst = false;
	}
	switch (gameScene) {
	case FLOAMOVE:
		floaMove();
		break;
	case PUSHENEMY:
		blowOff();		
		break;
	case PICKGOODS:
		pickGoods();
		effectCount = 0;
		
		isFirst = true;
		break;
	
	}
}
void gameControl() {
	GetControl(0);
	BottonCheck();
	CheckKeyState(DIK_RETURN);

	if (KeyState[DIK_RETURN] == KeyRelease)
	{

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

		WriteWord("メインゲーム", testWord, DT_CENTER, RED, HOGE_FONT);
	switch (gameScene) {
	//case FLOAMOVE:
	//	WriteWord("フロア移動", testText, DT_CENTER, RED, FONT);
	//	break;
	case PUSHENEMY:
		WriteWord("モブ主婦排除", testText, DT_CENTER, RED, HOGE_FONT);
		break;
	case PICKGOODS:
		WriteWord("セール品入手", testText, DT_CENTER, RED, HOGE_FONT);
		break;

	}

	EndSetTexture();
}
//フロア移動場面
void floaMove() {
	
	
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

			gameScene = PUSHENEMY;
	}

	GetControl(0);
	if (PadState[ButtonA] == KeyRelease)
	{

			gameScene = PUSHENEMY;
	}
	mobMoving(&mobCentralFloa);
	MoveInToErea(&playerCentralFloa, 10, 60, 1000, 680);
	MoveInToErea(&mobCentralFloa, 10, 60, 1000, 680);
}

void floaMoveRender() {
	BeginSetTexture();
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BLANK);
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, FRAME_TEX);
	switch (seletFloa) {
	case FOOD:
		EasyCreateSquareVertex(10, 15, 1000, 680, FOOD_STAGE_TEX);
		break;
	case CLOTH:
		EasyCreateSquareVertex(10, 15, 1000, 680, CLOTH_STAGE_TEX);
		break;
	}
	SetUpTexture(mobFloa, MOB_TEX);
	SetUpTexture(playerFloa, YASUKO_TEX);

	WriteWord("フロア移動", testText, DT_CENTER, RED, HOGE_FONT);

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
int comandInput[5] = { 10,10,10,10,10 };
int comandPresentment[5] = { rand() % 5,rand() % 5 ,rand() % 5 ,rand() % 5 ,rand() % 5 };
int comandCount = 0;
void blowOff() {
	blowOffControl();
	blowOffRender();
}
void blowOffControl() 
{
	CreateSquareVertex(effectExplosion, effectExplosionCentral);

	if (comandCount < 5) 
	{
		blowOffDeviseControl(&comandCount,comandInput);
	}
	else
	{
		if (comandCheck(comandPresentment, comandInput)) 
		{
			SoundSuccess = soundsManager.Start("SUCCESS", false) && SoundSuccess;
			isBlowOff = true;
			comandCount = 0;
		}
		else {
			SoundSuccess = soundsManager.Start("MISS", false) && SoundSuccess;
			comandCount = 0;
		}
	}
	if (isBlowOff) {
		madamBlowOff();
		effectExplosionCentral.scaleX++;
		effectExplosionCentral.scaleY++;
		if (effectCount >= 600) {
			gameScene = PICKGOODS;
		}
	}
}
void blowOffRender() {
	BeginSetTexture();
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BLANK);
	for (int i = 0; i < 5; i++) {
		CreateSquareVertexEx(mobFloa, mobCentralBlowOff[i], 1, 0, -1, 1);
		if(isBlowOff){
		effectCount++;

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
	if ((effectCount > 20) && isBlowOff) {
		SetUpTexture(effectExplosion, EXPLOSION_TEX);
	}
	//SetUpTexture(playerFloa, YASUKO_TEX);

	WriteWord("モブ主婦排除", testText, DT_CENTER, RED, HOGE_FONT);
#ifdef _DEBUG
	char debugComandInput[10];
	char debugComandOutput[10];
	char DebugCounter[10];
	for (int i = 0; i < 5; i++)
	{
		sprintf_s(debugComandInput, 10, "%d", comandInput[i]);

		RECT DEBUGText = { 100+(i*50),500,900,600 };
		WriteWord(debugComandInput, DEBUGText, DT_LEFT, 0xff0000ff, DEBUG_FONT);
	}	
	for (int i = 0; i < 5; i++)
	{
		sprintf_s(debugComandOutput, 10, "%d", comandPresentment[i]);

		RECT DEBUGText = { 100 + (i * 50),450,900,600 };
		WriteWord(debugComandOutput, DEBUGText, DT_LEFT, 0xff0000ff, DEBUG_FONT);
	}

	sprintf_s(DebugCounter, 10, "%d", comandCount);
	RECT DEBUGText = { 100 ,550,900,600 };
	WriteWord(DebugCounter, DEBUGText, DT_LEFT, 0xff00ffff, DEBUG_FONT);
#endif

	EndSetTexture();
}
bool comandCheck(int comand[], int inputComand[])
{
	for (int i = 0; i < 5; i++)
	{
		if (comand[i] != inputComand[i]) {
			return false;
		}
	}
	return true;
}
void blowOffDeviseControl(int* i,int comand[])
{
	BottonCheck();
	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_A);
	CheckKeyState(DIK_D);
	CheckKeyState(DIK_W);
	CheckKeyState(DIK_S);

	if (KeyState[DIK_RETURN] == KeyRelease)
	{
		gameScene = PICKGOODS;

	}

	if (KeyState[DIK_A] == KeyRelease)
	{
		comand[*i] = ButtonA;
	}
	if (KeyState[DIK_D] == KeyRelease)
	{

	}
	if (KeyState[DIK_W] == KeyRelease)
	{

	}
	if (KeyState[DIK_S] == KeyRelease)
	{

	}
	//XInputデバイス操作
	GetControl(0);
	BottonCheck();
	if (PadState[ButtonStart] == KeyRelease)
	{
		gameScene = PICKGOODS;
	}

	if (PadState[ButtonA] == KeyRelease)
	{
		comand[*i] = ButtonA;
		*i+=1;
		SoundSuccess = soundsManager.Start("BOTTUN", false) && SoundSuccess;
	}
	if (PadState[ButtonB] == KeyRelease)
	{
		comand[*i] = ButtonB;
		*i+=1;
		SoundSuccess = soundsManager.Start("BOTTUN", false) && SoundSuccess;

	}
	if (PadState[ButtonX] == KeyRelease)
	{
		comand[*i] = ButtonX;
		*i+=1;
		SoundSuccess = soundsManager.Start("BOTTUN", false) && SoundSuccess;

	}
	if (PadState[ButtonY] == KeyRelease)
	{
		comand[*i] = ButtonY;
		*i+=1;
		SoundSuccess = soundsManager.Start("BOTTUN", false) && SoundSuccess;

	}
	if (PadState[ButtonRB] == KeyRelease)
	{
		comand[*i] = ButtonRB;
		*i+=1;
		SoundSuccess = soundsManager.Start("BOTTUN", false) && SoundSuccess;

	}
	if (PadState[ButtonLB] == KeyRelease)
	{
		comand[*i] = ButtonLB;
		*i+=1;
		SoundSuccess = soundsManager.Start("BOTTUN", false) && SoundSuccess;

	}

}

void madamBlowOff() {
	

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

	if (effectCount > 500) {
		for (int i = 0; i < 5; i++) {
			mobCentralBlowOff[i].y += 35;
		}
	}

}



//商品取得場面

void pickGoods() {
	pickGoodsControl();
	pickGoodsRender();
}

void pickGoodsControl() {
	CreateSquareVertex(goodsA, goodsCentral[0]);
	CreateSquareVertex(goodsB, goodsCentral[1]);
	if (goodsCentral[0].x >= 650) {
		goodsScale[0] -= 5;
	}						
	if (goodsCentral[1].x >= 650) {
		goodsScale[1] -= 5;
	}

	if (isTake[0]) {
		goodsCentral[0].x += 5;
		goodsCentral[0].y += 2;
	}
	if (isTake[1]) {
		goodsCentral[1].x += 5;
		goodsCentral[1].y += 2;
	}

	if (!goodsScale[0]) {
		goodsScale[0] = 50;
		goodsCentral[0] = { 500,500,goodsScale[0],goodsScale[0] };
		isTake[0] = false;
	}
	if (!goodsScale[1]) {
		goodsScale[1] = 50;
		goodsCentral[1] = { 500,500,goodsScale[1],goodsScale[1] };
		isTake[1] = false;
	}

	pickGoodsDeviseControl();

}

void pickGoodsRender() {

	BeginSetTexture();

	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BG_PICKGGOODS_TEX);

	EasyCreateSquareVertex(500, 300, 900, HEIGHT, YASUKO_TEX);

	if (isTake[0]) {
		SetUpTexture(goodsA, BEEF_TEX);
	}
	if (isTake[1]) {
		SetUpTexture(goodsB, PORK_TEX);
	}

	

	WriteWord("セール品入手", testText, DT_CENTER, RED, HOGE_FONT);


	EndSetTexture();
}

void pickGoodsDeviseControl() {
	BottonCheck();
	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_A);
	CheckKeyState(DIK_D);
	CheckKeyState(DIK_W);
	CheckKeyState(DIK_S);

	if (KeyState[DIK_RETURN] == KeyRelease)
	{

		g_scene = SCENE_RESULT;
		gameScene = FLOAMOVE;
	}

	if (KeyState[DIK_A])
	{
		isTake[0] = true;
	}
	if (KeyState[DIK_D])
	{
		isTake[1] = true;
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

		g_scene = SCENE_RESULT;
		gameScene = FLOAMOVE;
	}
	if (PadState[ButtonB] == KeyRelease)
	{
		isTake[1] = true;
	}
	if (PadState[ButtonX] == KeyRelease)
	{
		isTake[0] = true;
	}
	if (PadState[ButtonY] == KeyRelease)
	{

	}

}

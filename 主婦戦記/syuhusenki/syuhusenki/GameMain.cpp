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
static bool isTakeA[2] = {false,false};
static bool isTakeB[2] = { false,false };

static float goodsScale[4] = { 50,50,50,50 };

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
CUSTOMVERTEX goodsA2[4];
CUSTOMVERTEX goodsB2[4];


CENTRAL_STATE goodsCentral[4]{
	{ 500,500,goodsScale[0],goodsScale[0]},
	{ 500,500,goodsScale[1],goodsScale[1]},
	{ 500,500,goodsScale[2],goodsScale[2] },
	{ 500,500,goodsScale[3],goodsScale[3] }
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
int comandCheck(int comand[], int inputComand[], int count);
void comandMake();
char comandButton(int comand);

void pickGoods();
void pickGoodsControl();
void pickGoodsRender();
void pickGoodsDeviseControl();

void gameMain() {
	srand((unsigned int)time(NULL));
	if (isFirst) {
		static bool canRead = true;
		if (canRead) {
			ReadInTexture("Texture/testFrame.png", FRAME_TEX);
			ReadInTexture("Texture/FoodSection.png", FOOD_STAGE_TEX);
			ReadInTexture("Texture/ClothingOrnament.png", CLOTH_STAGE_TEX);
			ReadInTexture("Texture/supermarket.jpg", BG_BLOWOFF_TEX);
			ReadInTexture("Texture/bakuhuhathu.png", EXPLOSION_TEX);
			ReadInTexture("Texture/wagonsele.jpg", BG_PICKGGOODS_TEX);
			ReadInTexture("Texture/beef.png", BEEF_TEX);
			ReadInTexture("Texture/chicken.png", CHICKEN_TEX);
			ReadInTexture("Texture/pork.png", PORK_TEX);
			canRead = false;
		}
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
		break;
	
	}
}
void gameControl() {
	GetControl(0);
	BottonCheck();
	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_NUMPADENTER);
	if (KeyState[DIK_RETURN] == KeyRelease || KeyState[DIK_NUMPADENTER] == KeyRelease)
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
	CheckKeyState(DIK_NUMPADENTER);

	keyControl(&playerCentralFloa);

	if (KeyState[DIK_RETURN] == KeyRelease|| KeyState[DIK_NUMPADENTER] == KeyRelease)
	{
		comandMake();
			gameScene = PUSHENEMY;
	}

	GetControl(0);
	if (PadState[ButtonA] == KeyRelease)
	{
		comandMake();
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
int comandPresentment[5];
int comandCount = 0;
int checkedComand = 2;
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
		checkedComand = comandCheck(comandPresentment, comandInput, comandCount);
		if (1 == checkedComand)
		{
			SoundSuccess = soundsManager.Start("SUCCESS", false) && SoundSuccess;
			checkedComand = 2;
		}
		if (!checkedComand)
		{
			checkedComand = 2;
			SoundSuccess = soundsManager.Start("MISS", false) && SoundSuccess;
			if (comandButton) {
				comandCount -= 1;
			}
		}
	}
	else
	{
		checkedComand = comandCheck(comandPresentment, comandInput, comandCount);
		if (1 == checkedComand)
		{
			SoundSuccess = soundsManager.Start("SUCCESS", false) && SoundSuccess;
			isBlowOff = true;
			checkedComand = 2;
			comandCount = 0;
		}
		if (!checkedComand)
		{
			SoundSuccess = soundsManager.Start("MISS", false) && SoundSuccess;
			checkedComand = 2;
			comandCount = 0;
		}
	}
	if (isBlowOff) {
		madamBlowOff();
		effectExplosionCentral.scaleX++;
		effectExplosionCentral.scaleY++;
		if (effectCount >= 600) {
			gameScene = PICKGOODS;
			isBlowOff = false;
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
	char debugComandInput[10];
	char debugComandOutput[10];
	char DebugCounter[10];
	for (int i = 0; i < 5; i++)
	{
		sprintf_s(debugComandInput, 10, "%c", comandButton(comandInput[i]));

		RECT DEBUGText = { 100+(i*50),500,900,600 };
		WriteWord(debugComandInput, DEBUGText, DT_LEFT, 0xff0000ff, DEBUG_FONT);
	}	
	for (int i = 0; i < 5; i++)
	{
		sprintf_s(debugComandOutput, 10, "%c", comandButton(comandPresentment[i]));

		RECT DEBUGText = { 100 + (i * 50),450,900,600 };
		WriteWord(debugComandOutput, DEBUGText, DT_LEFT, 0xff0000ff, DEBUG_FONT);
	}

#ifdef _DEBUG
	sprintf_s(DebugCounter, 10, "%d", comandCount);
	RECT DEBUGText = { 100 ,550,900,600 };
	WriteWord(DebugCounter, DEBUGText, DT_LEFT, 0xff00ffff, DEBUG_FONT);
#endif

	EndSetTexture();
}
int comandCheck(int comand[], int inputComand[],int count)
{
	for (int i = 0; i < count; i++) {
		if (inputComand[i] == 10) {
			return 2;
		}
		if (comand[i] == inputComand[i]) {
			if (i == count - 1) {
				return 1;
			}
		}
		if (comand[i] != inputComand[i]) {
			if (i == count - 1) {
				return 0;
			}
		}
	}
	return 2;
}
void comandMake() {
	comandPresentment[0] = rand() % 6;
	comandPresentment[1]= rand() % 6;
	comandPresentment[2]= rand() % 6;
	comandPresentment[3]= rand() % 6;
	comandPresentment[4]= rand() % 6;
}

char comandButton(int comand)
{
	switch (comand) {
	case ButtonA:
		return 'A';
	case ButtonB:
		return 'B';
	case ButtonX:
		return 'X';
	case ButtonY:
		return 'Y';
	case ButtonRB:
		return 'R';
	case ButtonLB:
		return 'L';
	}

}

void blowOffDeviseControl(int* i,int comand[])
{
	BottonCheck();
	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_NUMPADENTER);
	CheckKeyState(DIK_A);
	CheckKeyState(DIK_B);
	CheckKeyState(DIK_X);
	CheckKeyState(DIK_Y);
	CheckKeyState(DIK_R);
	CheckKeyState(DIK_L);

	if (KeyState[DIK_RETURN]||KeyState[DIK_NUMPADENTER] == KeyRelease)
	{
		gameScene = PICKGOODS;

	}

	if (KeyState[DIK_A] == KeyRelease)
	{
		comand[*i] = ButtonA;
		*i += 1;
		SoundSuccess = soundsManager.Start("BOTTUN", false) && SoundSuccess;

	}
	if (KeyState[DIK_B] == KeyRelease)
	{
		comand[*i] = ButtonB;
		*i += 1;
		SoundSuccess = soundsManager.Start("BOTTUN", false) && SoundSuccess;

	}
	if (KeyState[DIK_X] == KeyRelease)
	{
		comand[*i] = ButtonX;
		*i += 1;
		SoundSuccess = soundsManager.Start("BOTTUN", false) && SoundSuccess;

	}
	if (KeyState[DIK_Y] == KeyRelease)
	{
		comand[*i] = ButtonY;
		*i += 1;
		SoundSuccess = soundsManager.Start("BOTTUN", false) && SoundSuccess;

	}
	if (KeyState[DIK_R] == KeyRelease)
	{
		comand[*i] = ButtonRB;
		*i += 1;
		SoundSuccess = soundsManager.Start("BOTTUN", false) && SoundSuccess;

	}
	if (KeyState[DIK_L] == KeyRelease)
	{
		comand[*i] = ButtonLB;
		*i += 1;
		SoundSuccess = soundsManager.Start("BOTTUN", false) && SoundSuccess;

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
	CreateSquareVertex(goodsA2, goodsCentral[2]);
	CreateSquareVertex(goodsB2, goodsCentral[3]);

	if (goodsCentral[0].x >= 650) {
		goodsScale[0] -= 5;
	}						
	if (goodsCentral[1].x >= 650) {
		goodsScale[1] -= 5;
	}
	if (goodsCentral[2].x >= 650) {
		goodsScale[2] -= 5;
	}
	if (goodsCentral[3].x >= 650) {
		goodsScale[3] -= 5;
	}

	if (isTakeA[0]) {
		goodsCentral[0].x += 5;
		goodsCentral[0].y += 2;
	}
	if (isTakeB[0]) {
		goodsCentral[1].x += 5;
		goodsCentral[1].y += 2;
	}
	if (isTakeA[1]) {
		goodsCentral[2].x += 5;
		goodsCentral[2].y += 2;
	}
	if (isTakeB[1]) {
		goodsCentral[3].x += 5;
		goodsCentral[3].y += 2;
	}

	if (!goodsScale[0]) {
		goodsScale[0] = 50;
		goodsCentral[0] = { 500,500,goodsScale[0],goodsScale[0] };
		isTakeA[0] = false;
	}
	if (!goodsScale[1]) {
		goodsScale[1] = 50;
		goodsCentral[1] = { 500,500,goodsScale[1],goodsScale[1] };
		isTakeB[0] = false;
	}
	if (!goodsScale[2]) {
		goodsScale[2] = 50;
		goodsCentral[2] = { 500,500,goodsScale[2],goodsScale[2] };
		isTakeA[1] = false;
	}
	if (!goodsScale[3]) {
		goodsScale[3] = 50;
		goodsCentral[3] = { 500,500,goodsScale[3],goodsScale[3] };
		isTakeB[1] = false;
	}

	pickGoodsDeviseControl();

}

void pickGoodsRender() {

	BeginSetTexture();

	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BG_PICKGGOODS_TEX);

	EasyCreateSquareVertex(500, 300, 900, HEIGHT, YASUKO_TEX);

	if (isTakeA[0]) {
		SetUpTexture(goodsA, BEEF_TEX);
		if (isTakeA[1]) {
			SetUpTexture(goodsA2, BEEF_TEX);
		}
	}
	if (isTakeB[0]) {
		SetUpTexture(goodsB, PORK_TEX);
		if (isTakeB[1]) {
			SetUpTexture(goodsB2, PORK_TEX);
		}
	}

	

	WriteWord("セール品入手", testText, DT_CENTER, RED, HOGE_FONT);


	EndSetTexture();
}

void pickGoodsDeviseControl() {
	BottonCheck();
	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_NUMPADENTER);

	CheckKeyState(DIK_A);
	CheckKeyState(DIK_D);
	CheckKeyState(DIK_W);
	CheckKeyState(DIK_S);

	if (KeyState[DIK_RETURN] == KeyRelease|| KeyState[DIK_NUMPADENTER] == KeyRelease)
	{
		isFirst = true;
		g_scene = SCENE_RESULT;
		gameScene = FLOAMOVE;
	}

	if (KeyState[DIK_A] == KeyRelease)
	{
		if (isTakeA[0]) {
			isTakeA[1] = true;
		}
		else isTakeA[0] = true;
	}
	if (KeyState[DIK_D] == KeyRelease)
	{
		if (isTakeB[0]) {
			isTakeB[1] = true;
		}

		else isTakeB[0] = true;
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

	if (PadState[ButtonA] == PadRelease)
	{
		isFirst = true;
		g_scene = SCENE_RESULT;
		gameScene = FLOAMOVE;
	}
	if (PadState[ButtonB] == PadRelease)
	{
		if (isTakeB[0]) {
			isTakeB[1] = true;
		}

		isTakeB[0] = true;
	}
	if (PadState[ButtonX] == PadRelease)
	{
		if (isTakeA[0]) {
			isTakeA[1] = true;
		}

		isTakeA[0] = true;
	}
	if (PadState[ButtonY] == PadRelease)
	{

	}

}

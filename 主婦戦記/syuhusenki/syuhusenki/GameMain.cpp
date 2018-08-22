#include "Main.h"
#include "FloaMove.h"
#include "GameMain.h"

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


int g_gameScene = FLOAMOVE;
//int g_gameScene = PUSHENEMY;
//int g_gameScene = PICKGOODS;
int g_selectFloa = FOOD;
//int g_selectFloa = CLOTH;

static bool g_isBlowOff = false;
static bool g_isFirst = true;
static int g_effectCount = 0;
//static int fallCount = 0;
static bool g_isTakeA[8] = { false,false,false,false,false,false,false,false };
static bool g_isTakeB[8] = { false,false,false,false,false,false,false,false };
SoundEffect Button{ "BUTTON1","BUTTON2","BUTTON3" };
SoundEffect Pick{ "PICK1", "PICK2","PICK3", "PICK4","PICK5", "PICK6" , "PICK7" };
static float g_goodsScaleA[8] = { 60,60,60,60,60,60,60,60 };
static float g_goodsScaleB[8] = { 60,60,60,60,60,60,60,60 };
RECT testText = { 100,200,900,500 };
static int g_goodsTakenNumA = 0;
static int g_goodsTakenNumB = 0;

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


CUSTOMVERTEX playerHit[4];
CENTRAL_STATE playerCentralHit = {200,350,300,250};

CUSTOMVERTEX goodsA[4];
CUSTOMVERTEX goodsB[4];
CUSTOMVERTEX goodsA2[4];
CUSTOMVERTEX goodsB2[4];
CUSTOMVERTEX goodsA3[4];
CUSTOMVERTEX goodsB3[4]; 
CUSTOMVERTEX goodsA4[4];
CUSTOMVERTEX goodsB4[4];
CUSTOMVERTEX goodsA5[4];
CUSTOMVERTEX goodsB5[4];
CUSTOMVERTEX goodsA6[4];
CUSTOMVERTEX goodsB6[4];
CUSTOMVERTEX goodsA7[4];
CUSTOMVERTEX goodsB7[4];
CUSTOMVERTEX goodsA8[4];
CUSTOMVERTEX goodsB8[4];

CENTRAL_STATE goodsCentralA[8]{
	{ 600,550,g_goodsScaleA[0],g_goodsScaleA[0]},
	{ 600,550,g_goodsScaleA[1],g_goodsScaleA[1]},
	{ 600,550,g_goodsScaleA[2],g_goodsScaleA[2] },
	{ 600,550,g_goodsScaleA[3],g_goodsScaleA[3] },
	{ 600,550,g_goodsScaleA[4],g_goodsScaleA[4] },
	{ 600,550,g_goodsScaleA[5],g_goodsScaleA[5] },
	{ 600,550,g_goodsScaleA[6],g_goodsScaleA[6] },
	{ 600,550,g_goodsScaleA[7],g_goodsScaleA[7] }
};

CENTRAL_STATE goodsCentralB[8]{
	{ 500,500,g_goodsScaleB[0],g_goodsScaleB[0] },
	{ 500,500,g_goodsScaleB[1],g_goodsScaleB[1] },
	{ 500,500,g_goodsScaleB[2],g_goodsScaleB[2] },
	{ 500,500,g_goodsScaleB[3],g_goodsScaleB[3] },
	{ 600,550,g_goodsScaleB[4],g_goodsScaleB[4] },
	{ 600,550,g_goodsScaleB[5],g_goodsScaleB[5] },
	{ 600,550,g_goodsScaleB[6],g_goodsScaleB[6] },
	{ 600,550,g_goodsScaleB[7],g_goodsScaleB[7] }

};

CENTRAL_STATE durabilityPointCentral = { 900,75 ,15,40};
void gameControl();
void gameRender();
void floaMove();
//void floaMoveControl();
//void floaMoveRender();
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
void takeingGoods(bool take[], int size);
void goodsMoving(CUSTOMVERTEX vertex[], float goodsScale[], bool take[], CENTRAL_STATE goodsCentral[], float deleatPosX, int arreyNum);
void goodsRender(CUSTOMVERTEX vertex[], bool take[], int arreyNum, int texNum);

void clothRush();
void clothRushControl();
void clothRushRender();
void clothRushInit();
/////////////////////////////////////
void gameMain() {
	srand((unsigned int)time(NULL));
	if (g_isFirst) {
		static bool canRead = true;
		if (canRead) {
			ReadInTexture("Texture/testFrame.png", FRAME_TEX);
			ReadInTexture("Texture/FoodSection.png", FOOD_STAGE_TEX);
			ReadInTexture("Texture/ClothingOrnament.png", CLOTH_STAGE_TEX);
			//ReadInTexture("Texture/", BG_BLOWOFF_TEX);
			ReadInTexture("Texture/bakuhuhathu.png", EXPLOSION_TEX);
			//ReadInTexture("Texture/", BG_PICKGGOODS_TEX);
			ReadInTexture("Texture/beef.png", BEEF_TEX);
			ReadInTexture("Texture/chicken.png", CHICKEN_TEX);
			ReadInTexture("Texture/pork.png", PORK_TEX);
			ReadInTexture("Texture/cardboard.png", BOX_TEX);
			ReadInTexture("Texture/durabilityBar.jpg", DURABILITY_TEX);
			ReadInTexture("Texture/ClothBattle.png", CLOTH_BG_TEX);
			ReadInTexture("Texture/smoke.png", SMOKE_TEX);

			ReadInTexture("Texture/cardboard.png", TIMER_FRAME_TEX);
			ReadInTexture("Texture/cardboard.png", TIMER_HAND_TEX);
			ReadInTexture("Texture/startCount3.png", STARTCOUNT_3_TEX);
			ReadInTexture("Texture/startCount2.png", STARTCOUNT_2_TEX);
			ReadInTexture("Texture/startCount1.png", STARTCOUNT_1_TEX);
			ReadInTexture("Texture/kariStart.png", START_TEX);
			ReadInTexture("Texture/pauseMenu.png", PAUSE_TEX);
			ReadInTexture("Texture/cardboard.png", TIMEUP_TEX);
			//ReadInTexture("Texture/cardboard.png", PC_TEX);
			ReadInTexture("Texture/cardboard.png", GAME_BG_TEX);
			canRead = false;
		}
		mobCentralBlowOff[0] = { 850,650 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };
		mobCentralBlowOff[1] = { 900,650 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };
		mobCentralBlowOff[2] = { 950,650 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };
		mobCentralBlowOff[3] = { 1000,650 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };
		mobCentralBlowOff[4] = { 1050,650 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };

		effectExplosionCentral = { 900,750,300,300 };

		g_isBlowOff = false;
		g_isFirst = false;
	}
	CheckKeyState(DIK_F1);
	if (KeyState[DIK_F1] == KeyRelease)
	{
		g_selectFloa = FOOD;
	}
	CheckKeyState(DIK_F2);
	if (KeyState[DIK_F2] == KeyRelease)
	{
		g_selectFloa = CLOTH;
	}

	switch (g_gameScene) {
	case FLOAMOVE:
		floaMove();
		break;
	case PUSHENEMY:
		blowOff();		
		break;
	case PICKGOODS:
		pickGoods();
		g_effectCount = 0;
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

		switch (g_gameScene) {
		//case FLOAMOVE:
		//	gameScene = PUSHENEMY;
		//	break;
		case PUSHENEMY:
			g_gameScene = PICKGOODS;
			break;
		case PICKGOODS:
			g_scene = SCENE_RESULT;
			g_gameScene = FLOAMOVE;
			break;
		}
	}
	if (PadState[ButtonA] == KeyRelease)
	{

		switch (g_gameScene) {
		case FLOAMOVE:
			g_gameScene = PUSHENEMY;
			break;
		case PUSHENEMY:
			g_gameScene = PICKGOODS;
			break;
		case PICKGOODS:
			g_scene = SCENE_RESULT;
			g_gameScene = FLOAMOVE;
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
	switch (g_gameScene) {
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
////////////////////////////////////////////////
//フロア移動場面
void floaMove() {
	
	
	floaMoveControl();
	floaMoveRender();
}

//void floaMoveControl() {
//	CreateSquareVertex(playerFloa, playerCentralFloa);
//	CreateSquareVertex(mobFloa,mobCentralFloa);
//
//	BottonCheck();
//	CheckKeyState(DIK_RETURN);
//	CheckKeyState(DIK_NUMPADENTER);
//
//	keyControl(&playerCentralFloa);
//
//	if (KeyState[DIK_RETURN] == KeyRelease|| KeyState[DIK_NUMPADENTER] == KeyRelease)
//	{
//		comandMake();
//			g_gameScene = PUSHENEMY;
//	}
//
//	GetControl(0);
//	if (PadState[ButtonA] == KeyRelease)
//	{
//		comandMake();
//			g_gameScene = PUSHENEMY;
//	}
//	mobMoving(&mobCentralFloa);
//	MoveInToErea(&playerCentralFloa, 10, 60, 1000, 680);
//	MoveInToErea(&mobCentralFloa, 10, 60, 1000, 680);
//}
//
//void floaMoveRender() {
//	BeginSetTexture();
//	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BLANK);
//	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, FRAME_TEX);
//	switch (g_selectFloa) {
//	case FOOD:
//		EasyCreateSquareVertex(10, 15, 1000, 680, FOOD_STAGE_TEX);
//		break;
//	case CLOTH:
//		EasyCreateSquareVertex(10, 15, 1000, 680, CLOTH_STAGE_TEX);
//		break;
//	}
//	SetUpTexture(mobFloa, MOB_TEX);
//	SetUpTexture(playerFloa, YASUKO_TEX);
//
//	WriteWord("フロア移動", testText, DT_CENTER, RED, HOGE_FONT);
//
//	EndSetTexture();
//}

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

////////////////////////////////////////////
//コマンド入力場面
int comandInput[5] = { 10,10,10,10,10 };
int comandPresentment[5];
int comandCount = 0;
int checkedComand = 2;
void blowOff() {
	switch (g_selectFloa) {
	case FOOD:
	blowOffControl();
	blowOffRender();
	break;
	case CLOTH:
		g_gameScene = PICKGOODS;
		break;
	}

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
			g_SoundSuccess = soundsManager.Start("SUCCESS", false) && g_SoundSuccess;
			checkedComand = 2;
		}
		if (!checkedComand)
		{
			checkedComand = 2;
			g_SoundSuccess = soundsManager.Start("MISS", false) && g_SoundSuccess;
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
			g_SoundSuccess = soundsManager.Start("ATTACK", false) && g_SoundSuccess;
			g_isBlowOff = true;
			checkedComand = 2;
			comandCount = 0;
		}
		if (!checkedComand)
		{
			g_SoundSuccess = soundsManager.Start("MISS", false) && g_SoundSuccess;
			checkedComand = 2;
			comandCount = 0;
		}
	}
	if (g_isBlowOff) {
		madamBlowOff();
		effectExplosionCentral.scaleX++;
		effectExplosionCentral.scaleY++;
		if (g_effectCount >= 600) {
			g_gameScene = PICKGOODS;
			g_isBlowOff = false;
		}
	}
}
void blowOffRender() 
{

	CreateSquareVertex(playerHit, playerCentralHit);

	BeginSetTexture();
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BLANK);

	EasyCreateSquareVertex(490, 300, 890, 760, BOX_TEX);
	EasyCreateSquareVertex(560, 300, 960, 760, BOX_TEX);

	for (int i = 0; i < 5; i++) {
		CreateSquareVertexEx(mobFloa, mobCentralBlowOff[i], 1, 0, -1, 1);
		if(g_isBlowOff){
		g_effectCount++;

			static float Rad = 0;//5:4 400:360
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
	if ((g_effectCount > 20) && g_isBlowOff) {
		SetUpTexture(effectExplosion, EXPLOSION_TEX);
	}
	SetUpTexture(playerHit, texturePC);

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
	static int buttonKeyID = 0;
	static int prevbuttonKeyID = 1;
	BottonCheck();
	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_NUMPADENTER);
	CheckKeyState(DIK_A);
	CheckKeyState(DIK_B);
	CheckKeyState(DIK_X);
	CheckKeyState(DIK_Y);
	CheckKeyState(DIK_R);
	CheckKeyState(DIK_L);

	if (KeyState[DIK_RETURN] == KeyRelease ||KeyState[DIK_NUMPADENTER] == KeyRelease)
	{
		g_gameScene = PICKGOODS;

	}

	if (KeyState[DIK_A] == KeyRelease)
	{
		comand[*i] = ButtonA;
		*i += 1;

		buttonSE(Button, 3);
	}
	if (KeyState[DIK_B] == KeyRelease)
	{
		comand[*i] = ButtonB;
		*i += 1;
		buttonSE(Button, 3);
	}
	if (KeyState[DIK_X] == KeyRelease)
	{
		comand[*i] = ButtonX;
		*i += 1;
		buttonSE(Button, 3);
	}
	if (KeyState[DIK_Y] == KeyRelease)
	{
		comand[*i] = ButtonY;
		*i += 1;
		buttonSE(Button, 3);
	}
	if (KeyState[DIK_R] == KeyRelease)
	{
		comand[*i] = ButtonRB;
		*i += 1;
		buttonSE(Button, 3);
	}
	if (KeyState[DIK_L] == KeyRelease)
	{
		comand[*i] = ButtonLB;
		*i += 1;
		buttonSE(Button, 3);
	}
	//XInputデバイス操作
	GetControl(0);
	BottonCheck();
	if (PadState[ButtonStart] == KeyRelease)
	{
		g_gameScene = PICKGOODS;
	}

	if (PadState[ButtonA] == KeyRelease)
	{
		comand[*i] = ButtonA;
		*i+=1;
		buttonSE(Button, 3);
	}
	if (PadState[ButtonB] == KeyRelease)
	{
		comand[*i] = ButtonB;
		*i+=1;
		buttonSE(Button, 3);
	}
	if (PadState[ButtonX] == KeyRelease)
	{
		comand[*i] = ButtonX;
		*i+=1;
		buttonSE(Button, 3);
	}
	if (PadState[ButtonY] == KeyRelease)
	{
		comand[*i] = ButtonY;
		*i+=1;
		buttonSE(Button, 3);
	}
	if (PadState[ButtonRB] == KeyRelease)
	{
		comand[*i] = ButtonRB;
		*i+=1;
		buttonSE(Button, 3);
	}
	if (PadState[ButtonLB] == KeyRelease)
	{
		comand[*i] = ButtonLB;
		*i+=1;
		buttonSE(Button, 3);
	}

}

void buttonSE(SoundEffect Button,int SoundNumber) {
	static int buttonKeyID = 0;
	static int prevbuttonKeyID = 1;
	if (buttonKeyID >= SoundNumber) {
		buttonKeyID = 0;
	}

	switch (buttonKeyID) {
	case 6:
		if (buttonKeyID == 6 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE7) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE7, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 0;
			break;
		}
	case 5:
		if (buttonKeyID == 5 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE6) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE6, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 6;
			break;
		}

	case 4:
		if (buttonKeyID == 4 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE5) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE5, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 5;
			break;
		}
	case 3:
		if (buttonKeyID == 3 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE4) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE4, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 4;
			break;
		}
	case 2:
		if (buttonKeyID == 2 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE3) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE3, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 3;
			break;
		}
	case 1:
		if (buttonKeyID == 1 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE2) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE2, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 2;
			break;
		}
	case 0:
		if (buttonKeyID == 0 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE1) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE1, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 1;
			break;
		}
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

	if (g_effectCount > 500) {
		for (int i = 0; i < 5; i++) {
			mobCentralBlowOff[i].y += 35;
		}
	}

}

////////////////////////////////////////////////////
//商品取得場面

void pickGoods() {
	switch (g_selectFloa) {
	case FOOD:
		pickGoodsControl();
		pickGoodsRender();
		break;
	case CLOTH:
		clothRush();
		break;
	}
}

void pickGoodsControl() {
	float deleatPosX = 250;

	CreateSquareVertex(goodsA, goodsCentralA[0]);
	CreateSquareVertex(goodsB, goodsCentralB[0]);
	CreateSquareVertex(goodsA2, goodsCentralA[1]);
	CreateSquareVertex(goodsB2, goodsCentralB[1]);
	CreateSquareVertex(goodsA3, goodsCentralA[2]);
	CreateSquareVertex(goodsB3, goodsCentralB[2]); 
	CreateSquareVertex(goodsA4, goodsCentralA[3]);
	CreateSquareVertex(goodsB4, goodsCentralB[3]);
	CreateSquareVertex(goodsA5, goodsCentralA[4]);
	CreateSquareVertex(goodsB5, goodsCentralB[4]);
	CreateSquareVertex(goodsA6, goodsCentralA[5]);
	CreateSquareVertex(goodsB6, goodsCentralB[5]);
	CreateSquareVertex(goodsA7, goodsCentralA[6]);
	CreateSquareVertex(goodsB7, goodsCentralB[6]);
	CreateSquareVertex(goodsA8, goodsCentralA[7]);
	CreateSquareVertex(goodsB8, goodsCentralB[7]);

	goodsMoving(goodsA, g_goodsScaleA, g_isTakeA, goodsCentralA, deleatPosX, 0);
	goodsMoving(goodsA2, g_goodsScaleA, g_isTakeA, goodsCentralA, deleatPosX, 1);
	goodsMoving(goodsA3, g_goodsScaleA, g_isTakeA, goodsCentralA, deleatPosX, 2);
	goodsMoving(goodsA4, g_goodsScaleA, g_isTakeA, goodsCentralA, deleatPosX, 3);
	goodsMoving(goodsA5, g_goodsScaleA, g_isTakeA, goodsCentralA, deleatPosX, 4);
	goodsMoving(goodsA6, g_goodsScaleA, g_isTakeA, goodsCentralA, deleatPosX, 5);
	goodsMoving(goodsA7, g_goodsScaleA, g_isTakeA, goodsCentralA, deleatPosX, 6);
	goodsMoving(goodsA8, g_goodsScaleA, g_isTakeA, goodsCentralA, deleatPosX, 7);

	goodsMoving(goodsB, g_goodsScaleB, g_isTakeB, goodsCentralB, deleatPosX, 0);
	goodsMoving(goodsB2, g_goodsScaleB, g_isTakeB, goodsCentralB, deleatPosX, 1);
	goodsMoving(goodsB3, g_goodsScaleB, g_isTakeB, goodsCentralB, deleatPosX, 2);
	goodsMoving(goodsB4, g_goodsScaleB, g_isTakeB, goodsCentralB, deleatPosX, 3);
	goodsMoving(goodsB5, g_goodsScaleB, g_isTakeB, goodsCentralB, deleatPosX, 4);
	goodsMoving(goodsB6, g_goodsScaleB, g_isTakeB, goodsCentralB, deleatPosX, 5);
	goodsMoving(goodsB7, g_goodsScaleB, g_isTakeB, goodsCentralB, deleatPosX, 6);
	goodsMoving(goodsB8, g_goodsScaleB, g_isTakeB, goodsCentralB, deleatPosX, 7);

	pickGoodsDeviseControl();

}

void pickGoodsRender() {
	CreateSquareVertex(playerHit, playerCentralHit);

	BeginSetTexture();

	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BLANK);
	EasyCreateSquareVertex(490, 300, 890, 760, BOX_TEX);
	EasyCreateSquareVertex(560, 300, 960, 760, BOX_TEX);

	SetUpTexture(playerHit, texturePC);

	goodsRender(goodsA, g_isTakeA, 0, BEEF_TEX);
	goodsRender(goodsA2, g_isTakeA, 1, BEEF_TEX);
	goodsRender(goodsA3, g_isTakeA, 2, BEEF_TEX);
	goodsRender(goodsA4, g_isTakeA, 3, BEEF_TEX);
	goodsRender(goodsA5, g_isTakeA, 4, BEEF_TEX);
	goodsRender(goodsA6, g_isTakeA, 5, BEEF_TEX);
	goodsRender(goodsA7, g_isTakeA, 6, BEEF_TEX);
	goodsRender(goodsA8, g_isTakeA, 7, BEEF_TEX);

	goodsRender(goodsB, g_isTakeB, 0, PORK_TEX);
	goodsRender(goodsB2, g_isTakeB, 1, PORK_TEX);
	goodsRender(goodsB3, g_isTakeB, 2, PORK_TEX);
	goodsRender(goodsB4, g_isTakeB, 3, PORK_TEX);
	goodsRender(goodsB5, g_isTakeB, 4, PORK_TEX);
	goodsRender(goodsB6, g_isTakeB, 5, PORK_TEX);
	goodsRender(goodsB7, g_isTakeB, 6, PORK_TEX);
	goodsRender(goodsB8, g_isTakeB, 7, PORK_TEX);


	WriteWord("セール品入手", testText, DT_CENTER, RED, HOGE_FONT);
#ifdef _DEBUG
	char goodsNumA[10];
	char goodsNumB[10];
	char DebugTakeBoolA[10];
	char DebugTakeBoolB[10];

	sprintf_s(goodsNumA, 10, "%d ", g_goodsTakenNumA);
	RECT DEBUGGoodsA = { 100 ,200,900,600 };
	WriteWord(goodsNumA, DEBUGGoodsA, DT_LEFT, 0xff00ffff, DEBUG_FONT);
	sprintf_s(goodsNumB, 10, "%d ", g_goodsTakenNumB);
	RECT DEBUGGoodsB = { 100 ,250,900,600 };
	WriteWord(goodsNumB, DEBUGGoodsB, DT_LEFT, 0xff00ffff, DEBUG_FONT);

	for (int i = 0; i < 8; i++) {
		sprintf_s(DebugTakeBoolA, 10, "%d ", g_isTakeA[i]);
		RECT DEBUGTextA = { 100 + i * 50 ,500,900,600 };
		WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xff00ffff, DEBUG_FONT);
		sprintf_s(DebugTakeBoolB, 10, "%d ", g_isTakeB[i]);
		RECT DEBUGTextB = { 100 + i * 50 ,550,900,600 };
		WriteWord(DebugTakeBoolB, DEBUGTextB, DT_LEFT, 0xff00ffff, DEBUG_FONT);
	}

	SoundLib::PlayingStatus status = soundsManager.GetStatus("PICK1");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	RECT DEBUGTextA = { 100 ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);
	status = soundsManager.GetStatus("PICK2");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 150  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);
	status = soundsManager.GetStatus("PICK3");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 200  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);
	status = soundsManager.GetStatus("PICK4");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 250  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);
	status = soundsManager.GetStatus("PICK5");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 300  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);
	status = soundsManager.GetStatus("PICK6");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 350  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);
	status = soundsManager.GetStatus("PICK7");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 400  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);

#endif
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
		g_isFirst = true;
		g_scene = SCENE_RESULT;
		g_gameScene = FLOAMOVE;
	}

	if (KeyState[DIK_A] == KeyRelease)
	{
		g_goodsTakenNumA++;
		takeingGoods(g_isTakeA, 8);
		buttonSE(Pick,7);
	}
	if (KeyState[DIK_D] == KeyRelease)
	{
		g_goodsTakenNumB++;
		takeingGoods(g_isTakeB, 8);
		buttonSE(Pick, 7);
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
		g_isFirst = true;
		g_scene = SCENE_RESULT;
		g_gameScene = FLOAMOVE;
	}
	if (PadState[ButtonB] == PadRelease)
	{
		g_goodsTakenNumB++;
		takeingGoods(g_isTakeB, 8);
		g_SoundSuccess = soundsManager.Start("PICK1", false) && g_SoundSuccess;
	}
	if (PadState[ButtonX] == PadRelease)
	{
		g_goodsTakenNumA++;
		takeingGoods(g_isTakeA, 8);
		g_SoundSuccess = soundsManager.Start("PICK1", false) && g_SoundSuccess;
	}
	if (PadState[ButtonY] == PadRelease)
	{

	}

}

void takeingGoods(bool take[],int size) {
	switch (size)
	{
	case 8:
		if (take[6])
		{
			take[7] = true;
		}
	case 7:
		if (take[5])
		{
			take[6] = true;
		}
	case 6:
		if (take[4])
		{
			take[5] = true;
		}
	case 5:
		if (take[3])
		{
			take[4] = true;
		}
	case 4:
		if (take[2])
		{
			take[3] = true;
		}
	case 3:
		if (take[1])
		{
			take[2] = true;
		}
	case 2:
		if (take[0])
		{
			take[1] = true;
		}
	case 1:
		take[0] = true;
	}
	
}

void goodsMoving(CUSTOMVERTEX vertex[],float goodsScale[],bool take[],CENTRAL_STATE goodsCentral[], float deleatPosX, int arreyNum) {

	if (take[arreyNum]) {
		goodsCentral[arreyNum].x -= 4;
		goodsCentral[arreyNum].y -= 1;
	}
	if (goodsCentral[arreyNum].x <= deleatPosX) {
		goodsScale[arreyNum] = 60;
		goodsCentral[arreyNum] = { 600,550,goodsScale[arreyNum],goodsScale[arreyNum] };
		take[arreyNum] = false;
	}
}

void goodsRender(CUSTOMVERTEX vertex[], bool take[], int arreyNum,int texNum) {
	if (take[arreyNum])
	{
		SetUpTexture(vertex, texNum);
	}
}

/////////////////////////////////////
int texturePC = YASUKO_TEX;
static int clothHP = 1000;
static int mobHP = 50;
static bool clothBreak = false;
static bool clothStolen = false;
static bool getCloth = false;
static int openCount = 0;
static float Rad;
CENTRAL_STATE clothMobCentral = {900,500,200,300};
CENTRAL_STATE clothPCCentral = { 300,500,200,300};
CUSTOMVERTEX clothSmoke[4];
CENTRAL_STATE clothSmokeCentral[6] = 
{
	{800,550,200,200},
	{700,450,200,200},
	{600,500,230,230},
	{650,600,200,200},
	{450,500,230,230},
	{500,400,200,200}
};



void clothRush() 
{
	clothRushControl();
	clothRushRender();
}

void clothRushControl() 
{
	openCount++;
	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_NUMPADENTER);
	CheckKeyState(DIK_A);
	if (KeyState[DIK_RETURN] == KeyRelease || KeyState[DIK_NUMPADENTER] == KeyRelease)
	{
		g_scene = SCENE_RESULT;
		g_gameScene = FLOAMOVE;
	}
	if (openCount > 20)
	{
		if (durabilityPointCentral.x <= 600 || !clothHP)
		{
			clothBreak = true;
		}
		if (durabilityPointCentral.x >= 1200)
		{
			clothStolen = true;
		}
		if (durabilityPointCentral.x >= 600 && durabilityPointCentral.x <= 1200)
		{
			if (KeyState[DIK_A] == KeyRelease) {
				durabilityPointCentral.x -= 10;
				mobHP--;
			}
		}
		if (durabilityPointCentral.x <= 805 && clothHP)
		{
			clothHP--;
		}
		if (!mobHP)
		{
			getCloth = true;
		}
		else if (durabilityPointCentral.x <= 1200 && !clothStolen)
		{
			durabilityPointCentral.x += 1;
		}


		if (clothBreak)
		{
			soundsManager.Start("BREAK", false);
			clothBreak = false;
			clothRushInit();
		}
		if (clothStolen)
		{
			soundsManager.Start("LOSE", false);
			clothStolen = false;
			clothRushInit();
		}
		if (getCloth && durabilityPointCentral.x <= 1000 && durabilityPointCentral.x >= 805)
		{
			soundsManager.Start("WIN", false);
			getCloth = false;
			clothRushInit();
		}
		else if (getCloth && durabilityPointCentral.x >= 1000)
		{
			soundsManager.Start("LOSE", false);
			getCloth = false;
			clothRushInit();
		}
		else if (getCloth && durabilityPointCentral.x <= 805)
		{
			soundsManager.Start("BREAK", false);
			getCloth = false;
			clothRushInit();
		}
		if (Rad < 0.2) {
			Rad -= 0.05;
		}
		if (Rad > 0) {
			Rad += 0.05;
		}
		static int clothCount = 0;
		clothCount++;
		static bool smokeVary = false;
		static bool charMove = false;
		if (clothPCCentral.x >= 350) {
			charMove = true;
		}
		if (clothPCCentral.x <= 250) {
			charMove = false;
		}
		if (!charMove) {
		clothPCCentral.x += 1;
		clothMobCentral.x += 1;
		}
		if (charMove) {
			clothPCCentral.x -= 1;
			clothMobCentral.x -= 1;
		}
		if (clothCount <= 50) {
			for (int i = 0; i < 6; i++)
			{
				clothSmokeCentral[i].scaleX += rand() % 4;
				clothSmokeCentral[i].scaleY += rand() % 4;

			}
		}
		if (clothCount > 50) {
			smokeVary = true;
			for (int i = 0; i < 6; i++)
			{
				clothSmokeCentral[i].scaleX -= rand() % 4;
				clothSmokeCentral[i].scaleY -= rand() % 4;

			}
			smokeVary = false;
		}
		if (clothCount > 100) {
			clothCount = 0;
		}
	}
}

void clothRushRender() 
{
	CUSTOMVERTEX durabilityPoint[4];
	CUSTOMVERTEX clothMob[4];
	CUSTOMVERTEX clothPC[4];

	CreateSquareVertex(clothMob, clothMobCentral);
	CreateSquareVertex(clothPC, clothPCCentral);
	CreateSquareVertexColor(durabilityPoint, durabilityPointCentral,0xff000000);


	BeginSetTexture();
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, CLOTH_BG_TEX);
	EasyCreateSquareVertex(600,50,1200,100,DURABILITY_TEX);

	
	SetUpTexture(durabilityPoint, BLANK);

	SetUpTexture(clothMob, MOB_TEX);
	SetUpTexture(clothPC, texturePC);
	for (int i = 0; i < 6; i++) 
	{
		RevolveZ(clothSmoke, Rad, clothSmokeCentral[i]);
		SetUpTexture(clothSmoke, SMOKE_TEX);
	}
	if (openCount < 20)
	{
		EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, START_TEX);
	}

#ifdef _DEBUG
	char debugcloth[10];
	sprintf_s(debugcloth, 10, "%.2f ", durabilityPointCentral.x);
	RECT DEBUGText = { 100 ,150,900,600 };
	WriteWord(debugcloth, DEBUGText, DT_LEFT, 0xffff0000, DEBUG_FONT);

	sprintf_s(debugcloth, 10, "%d ", clothHP);
	DEBUGText = { 100 ,200,900,600 };
	WriteWord(debugcloth, DEBUGText, DT_LEFT, 0xffff0000, DEBUG_FONT);

	sprintf_s(debugcloth, 10, "%d ", mobHP);
	DEBUGText = { 100 ,250,900,600 };
	WriteWord(debugcloth, DEBUGText, DT_LEFT, 0xffff0000, DEBUG_FONT);

#endif

	EndSetTexture();

}

void clothRushInit() 
{
	durabilityPointCentral.x = 900;
	clothHP = 1000;
	mobHP = 100;
	openCount = 0;

	clothSmokeCentral[0]={ 800,550,200,200 };
	clothSmokeCentral[1]={ 700,450,200,200 };
	clothSmokeCentral[2]={ 600,500,250,250 };
	clothSmokeCentral[3]={ 650,600,200,200 };
	clothSmokeCentral[4]={ 400,500,250,250 };
	clothSmokeCentral[5]={ 500,400,200,200 };

	g_gameScene = PUSHENEMY;
}
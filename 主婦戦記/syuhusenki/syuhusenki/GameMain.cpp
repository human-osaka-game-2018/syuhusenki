#include "Main.h"
#include "FloaMove.h"
#include "GameMain.h"
#include "Goods.h"
#include "Timer.h"


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

void testScene();

int g_gameScene = FLOAMOVE;
//int g_gameScene = CHOSEGOODS;
//int g_gameScene = PUSHENEMY;
//int g_gameScene = PICKGOODS;
int g_selectFloa = FOOD;
//int g_selectFloa = CLOTH;

int g_turn = 0;
int mobTexNum;
static bool g_isBlowOff = false;
bool g_isFirst = true;
static int g_effectCount = 0;
static float mobRad = 0;//5:4 400:360

static int comandInput[5] = { 10,10,10,10,10 };
static int comandPresentment[5];
static int comandCount = 0;
static int checkedComand = 2;
static int rushButtonShow;
//static int fallCount = 0;
static bool g_isTakeA[8] = { false,false,false,false,false,false,false,false };
static bool g_isTakeB[8] = { false,false,false,false,false,false,false,false };
SoundEffect Button{ "BUTTON1","BUTTON2","BUTTON3" };
SoundEffect Pick{ "PICK1", "PICK2","PICK3", "PICK4","PICK5", "PICK6" , "PICK7" ,"PICK8","PICK9","PICK10" };
static float g_goodsScaleA[8] = { 60,60,60,60,60,60,60,60 };
static float g_goodsScaleB[8] = { 60,60,60,60,60,60,60,60 };
RECT testText = { 100,200,900,500 };
static int g_goodsTakenNum = 0;
//static int g_goodsTakenNum = 0;

CENTRAL_STATE playerCutinCentral = { 1200,350,300,250 };

//モブの画像頂点
CUSTOMVERTEX mobFloa[4];
CENTRAL_STATE mobCentralFloa = { 500,500 ,PLAYER_FLOA_SCALE,PLAYER_FLOA_SCALE };

CENTRAL_STATE mobCentralBlowOff[5];

//エフェクト
CUSTOMVERTEX effectExplosion[4];
CENTRAL_STATE effectExplosionCentral = {1000,800,300,300};


CUSTOMVERTEX playerHit[4];
CENTRAL_STATE playerCentralHit = {200,350,300,250};


CENTRAL_STATE durabilityPointCentral = { 900,75 ,15,40};

void floaMove();
//void floaMoveControl();
//void floaMoveRender();
//void keyControl(CENTRAL_STATE* central);
//void mobMoving(CENTRAL_STATE* mob);

int texturePC = YASUKO_TEX;

void choseGoods();
void choseGoodsControl();
void choseGoodsReader();


void blowOff();
void blowOffControl();
void blowOffRender();
void blowOffDeviseControl(int* i,int comand[]);
void madamBlowOff();
int comandCheck(int comand[], int inputComand[], int count);
void comandMake();
char comandButton(int comand);
int comandButtonTexture(int comand);


void pickGoods();
void pickGoodsControl();
void pickGoodsRender();
void pickGoodsDeviseControl(int* rushInput);
void rushButtonCheck(int rushInput, int rushShow);

void takeingGoods(bool take[], int size);
void goodsMoving(CUSTOMVERTEX vertex[], float goodsScale[], bool take[], CENTRAL_STATE goodsCentral[], float deleatPosX, int arreyNum);
void goodsRender(CUSTOMVERTEX vertex[], bool take[], int arreyNum, int texNum);
int priceEdit(GOODSPARAMETER foodGoods[], int goodsselector, int nomalOrSale);
int editMerchandise(int selesChoice, int arrayNum);
int salesChoice;
//void clothRush();
//void clothRushControl();
//void clothRushRender();
//void clothRushInit();
/////////////////////////////////////
void gameMain() {
	srand((unsigned int)time(NULL));
	if (g_isFirst) 
	{
		static bool canRead = true;
		if (canRead) 
		{
			setNowLoading();

			ReadInTexture("Texture/frame_goods.png", FRAME_TEX);
			ReadInTexture("Texture/FoodSection.png", FOOD_STAGE_TEX);
			ReadInTexture("Texture/maxresdefault.png", CUTIN_TEX);
			ReadInTexture("Texture/bakuhuhathu.png", EXPLOSION_TEX);
			////ReadInTexture("Texture/", BG_PICKGGOODS_TEX);
			ReadInTexture("Texture/cardboard.png", BOX_TEX);
			ReadInTexture("Texture/durabilityBar.jpg", DURABILITY_TEX);
			ReadInTexture("Texture/ClothBattle.png", CLOTH_BG_TEX);
			ReadInTexture("Texture/smoke.png", SMOKE_TEX);

			ReadInTexture("Texture/timerFrame.png", TIMER_FRAME_TEX);
			ReadInTexture("Texture/timerHand.png", TIMER_HAND_TEX);
			ReadInTexture("Texture/startCount3.png", STARTCOUNT_3_TEX);
			ReadInTexture("Texture/startCount2.png", STARTCOUNT_2_TEX);
			ReadInTexture("Texture/startCount1.png", STARTCOUNT_1_TEX);
			ReadInTexture("Texture/kariStart.png", START_TEX);
			ReadInTexture("Texture/pauseMenu.png", PAUSE_TEX);
			ReadInTexture("Texture/end.png", TIMEUP_TEX);
			ReadInTexture("Texture/stage.png", FLOAMOVE_BG_TEX);

			ReadInTexture("Texture/scoretext/50.png", FIFTY_TEX );
			ReadInTexture("Texture/scoretext/60.png", SIXTY_TEX );
			ReadInTexture("Texture/scoretext/65.png", SIXTYFIVE_TEX );
			ReadInTexture("Texture/scoretext/100.png", HUNDRED_TEX );
			ReadInTexture("Texture/scoretext/150.png", HUNDREDFIFTY_TEX);
			ReadInTexture("Texture/scoretext/200.png", TWEHANDRED_TEX );
			ReadInTexture("Texture/scoretext/250.png", TWEHANDREDFIFTY_TEX );
			ReadInTexture("Texture/scoretext/300.png", THREEHANDRED_TEX );
			ReadInTexture("Texture/scoretext/s30.png", S_THRTY_TEX );
			ReadInTexture("Texture/scoretext/s40.png", S_FOURTY_TEX );
			ReadInTexture("Texture/scoretext/s50.png", S_FIFTY_TEX );
			ReadInTexture("Texture/scoretext/s60.png", S_SIXTY_TEX );
			ReadInTexture("Texture/scoretext/s70.png", S_SEVENTY_TEX );
			ReadInTexture("Texture/scoretext/s80.png", S_EIGHTY_TEX);
			ReadInTexture("Texture/scoretext/s100.png", S_HUNDRED_TEX );
			ReadInTexture("Texture/scoretext/s150.png", S_HUNDREDFIFTY_TEX );
			ReadInTexture("Texture/scoretext/s180.png", S_HUNDREDEIGHTY_TEX);
			ReadInTexture("Texture/scoretext/s200.png", S_TWEHUNDRED_TEX );

			ReadInTexture("Texture/button/a.png", A_TEX);
			ReadInTexture("Texture/button/b.png", B_TEX);
			ReadInTexture("Texture/button/x.png", X_TEX);
			ReadInTexture("Texture/button/y.png", Y_TEX);
			ReadInTexture("Texture/button/r.png", R_TEX);
			ReadInTexture("Texture/button/l.png", L_TEX);
			ReadInTexture("Texture/button/button.png", NULL_BUTTON_TEX);

			ReadInTexture("Texture/merchandise/beef.png", BEEF_TEX);
			ReadInTexture("Texture/merchandise/chicken.png", CHICKEN_TEX);
			ReadInTexture("Texture/merchandise/pork.png", PORK_TEX);
			ReadInTexture("Texture/merchandise/wiener.png", VIENNESE_TEX);
			ReadInTexture("Texture/merchandise/mince.png", MINCE_TEX);

			ReadInTexture("Texture/merchandise/shrimp.png", SHRIMP_TEX);
			ReadInTexture("Texture/merchandise/octopus.png", OCTOPUS_TEX);
			ReadInTexture("Texture/merchandise/squid.png", INKFISH_TEX);
			ReadInTexture("Texture/merchandise/fish.png", FISH_TEX);

			ReadInTexture("Texture/merchandise/carrot.png", GINESENG_TEX);
			ReadInTexture("Texture/merchandise/onion.png", ONION_TEX);
			ReadInTexture("Texture/merchandise/potato.png", POTATO_TEX);
			ReadInTexture("Texture/merchandise/tomato.png", TOMATO_TEX);
			ReadInTexture("Texture/merchandise/radish.png", RADISH_TEX);

			ReadInTexture("Texture/merchandise/snack.png", POTATOCHIPS_TEX);
			ReadInTexture("Texture/merchandise/choco.png", CHOCOLATE_TEX);
			ReadInTexture("Texture/merchandise/ice.png", ICE_TEX);
			ReadInTexture("Texture/merchandise/ricecracker.png", RICECRACKER_TEX);

			ReadInTexture("Texture/merchandise/apple.png", APPLE_TEX);
			ReadInTexture("Texture/merchandise/orenge.png", ORANGE_TEX);
			ReadInTexture("Texture/merchandise/banana.png", BANANA_TEX);

			ReadInTexture("Texture/merchandise/tea.png", TEA_TEX);
			ReadInTexture("Texture/merchandise/juice.png", JUICE_TEX);
			ReadInTexture("Texture/merchandise/beer.png", BEER_TEX);


			g_SoundSuccess = soundsManager.Start("LOAD", false) && g_SoundSuccess;

			g_SoundSuccess = soundsManager.Stop("SELECT_BGM") && g_SoundSuccess;

			canRead = false;
		}

		for (int i = 0; i < 3; i++)
		{
			popSales[i].goodsSorting = rand() % 6;//フロア移動で決めたものを入れる
		}
		selectGoods(&popSales[0]);
		selectGoods(&popSales[1]);
		selectGoods(&popSales[2]);

		comandMake();

		g_isBlowOff = false;
		g_isFirst = false;
	}
#ifdef _DEBUG
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
	CheckKeyState(DIK_F3);
	if (KeyState[DIK_F3] == KeyRelease)
	{
		g_gameScene = TESTSCENE;
	}

#endif
	switch (g_gameScene) 
	{
	case FLOAMOVE:
	{
		for (int i = 0; i < 5; i++)
		{
			comandInput[i] = 10;
		}
		g_isBlowOff = false;

		floaMove();
		
		CheckKeyState(DIK_0);
		if (KeyState[DIK_0] == KeyRelease)
		{
			for (int i = 0; i < 3; i++)
			{
				popSales[i].goodsSorting = rand() % 6;//フロア移動で決めたものを入れる
			}
			selectGoods(&popSales[0]);
			selectGoods(&popSales[1]);
			selectGoods(&popSales[2]);
		}
		CheckKeyState(DIK_1);
		if (KeyState[DIK_1] == KeyRelease)
		{
			salesChoice = 0;
		}
		CheckKeyState(DIK_2);
		if (KeyState[DIK_2] == KeyRelease)
		{
			salesChoice = 1;
		}
		CheckKeyState(DIK_3);
		if (KeyState[DIK_3] == KeyRelease)
		{
			salesChoice = 2;
		}
		break;
	}
	case CHOSEGOODS:
		switch (g_turn)
		{
		case 0:
			mobTexNum = ISOKO_TEX;
			break;
		case 1:
			mobTexNum = MOB_TEX;
			break;
		case 2:
			mobTexNum = MITUKO_TEX;
			break;
		}

		choseGoods();
		break;
	case PUSHENEMY:
		if (!g_isBlowOff) 
		{

			mobCentralBlowOff[0] = { 450,550 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };
			mobCentralBlowOff[1] = { 600,550 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };
			mobCentralBlowOff[2] = { 750,550 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };
			mobCentralBlowOff[3] = { 900,550 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };
			mobCentralBlowOff[4] = { 1050,550 ,PLAYER_BLOWOFF_SCALE,PLAYER_BLOWOFF_SCALE };

			effectExplosionCentral = { 900,750,300,300 };
			g_effectCount = 0;
			playerCutinCentral.x = 1200;
		}
		blowOff();		
		break;
	case PICKGOODS:
		pickGoods();
		comandMake();
		for (int i = 0; i < 5; i++)
		{
			comandInput[i] = 10;
		}
		break;
#ifdef _DEBUG
	case TESTSCENE:
		testScene();
		break;
#endif
	}
}

////////////////////////////////////////////////
//フロア移動場面
void floaMove() {
	
	floaMoveControl();
	floaMoveRender();
}

void choseGoods() {

	choseGoodsControl();
	choseGoodsReader();
}
void choseGoodsControl() {

	timerControl();

	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_NUMPADENTER);
	CheckKeyState(DIK_A);
	CheckKeyState(DIK_D);

	if (KeyState[DIK_RETURN] == KeyRelease || KeyState[DIK_NUMPADENTER] == KeyRelease)
	{
		g_gameScene = PUSHENEMY;
	}
	if (KeyState[DIK_A] == KeyRelease)
	{
		selectedGoods[g_turn] = popSales[salesChoice].merchandise[0];
		g_gameScene = PUSHENEMY;
	}
	if (KeyState[DIK_D] == KeyRelease)
	{
		selectedGoods[g_turn] = popSales[salesChoice].merchandise[1];
		g_gameScene = PUSHENEMY;
	}

	GetControl(0);
	BottonCheck();

	if (PadState[ButtonStart] == PadRelease)
	{
		g_gameScene = PUSHENEMY;
	}
	if (PadState[ButtonA] == PadRelease)
	{

	}
	if (PadState[ButtonB] == PadRelease)
	{
		selectedGoods[g_turn] = popSales[salesChoice].merchandise[1];
		g_gameScene = PUSHENEMY;
	}
	if (PadState[ButtonX] == PadRelease)
	{
		selectedGoods[g_turn] = popSales[salesChoice].merchandise[0];
		g_gameScene = PUSHENEMY;
	}

}
void choseGoodsReader() {

	BeginSetTexture();
	CreateSquareVertex(playerHit, playerCentralHit);
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, FLOAMOVE_BG_TEX);

	EasyCreateSquareVertexColor(0, 0, WIDTH, HEIGHT, HARFCLEAR,BLANK);

	EasyCreateSquareVertex(490, 300, 890, 760, BOX_TEX);
	EasyCreateSquareVertex(560, 300, 960, 760, BOX_TEX);


	for (int i = 0; i < 5; i++) {
		CreateSquareVertexEx(mobFloa, mobCentralBlowOff[i], 1, 0, -1, 1);
		SetUpTexture(mobFloa, mobTexNum);
	}
	SetUpTexture(playerHit, texturePC);
	EasyCreateSquareVertex(350, 150, 600, 400, foodGoods[popSales[salesChoice].merchandise[0]].textureID);
	EasyCreateSquareVertex(660, 150, 910, 400, foodGoods[popSales[salesChoice].merchandise[1]].textureID);
	EasyCreateSquareVertex(350, 350, 600, 500, X_TEX);
	EasyCreateSquareVertex(660, 350, 910, 500, B_TEX);

	goodsScoreShow();
	timerRender();
	EndSetTexture();

}

void blowOff() {
	switch (g_selectFloa) {
	case FOOD:
	blowOffControl();
	blowOffRender();
	rushButtonShow = rand() % 6;
	break;
	case CLOTH:
		g_gameScene = PICKGOODS;
		break;
	}

}
void blowOffControl() 
{
	timerControl();
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
		if (g_effectCount >= 180) {
			g_gameScene = PICKGOODS;
			comandCount = 0;
		}
	}

}
void blowOffRender() 
{

	CreateSquareVertex(playerHit, playerCentralHit);

	BeginSetTexture();
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, FLOAMOVE_BG_TEX);

	EasyCreateSquareVertexColor(0, 0, WIDTH, HEIGHT, HARFCLEAR, BLANK);

	EasyCreateSquareVertex(490, 300, 890, 760, BOX_TEX);
	EasyCreateSquareVertex(560, 300, 960, 760, BOX_TEX);
	for (int i = 0; i < 5; i++) {
		CreateSquareVertex(mobFloa, mobCentralBlowOff[i]);
		if(g_isBlowOff){
		g_effectCount++;

			mobRad += 0.9f;

			if (mobRad < 0)
			{
				mobRad = mobRad * -1;
			}
			if (i % 2)
			{
				mobRad = mobRad * -1;
			}
			RevolveZ(mobFloa, mobRad, mobCentralBlowOff[i]);
		}
		SetUpTexture(mobFloa, mobTexNum);
	}
	if ((g_effectCount > 20) && g_isBlowOff) {
		SetUpTexture(effectExplosion, EXPLOSION_TEX);
	}
	SetUpTexture(playerHit, texturePC);

	char debugComandInput[10];
	char debugComandOutput[10];
	char DebugCounter[10];
	for (int i = 0; i < 5; i++)
	{
		RECT DEBUGText = { 300 + (i * 100),200,450 + (i * 100),300 };
		EasyCreateRECTVertex(DEBUGText, comandButtonTexture(comandPresentment[i]));
	}
	for (int i = 0; i < 5; i++)
	{
		RECT DEBUGText = { 300 + (i * 100),300,450 + (i * 100),400 };
		EasyCreateRECTVertex( DEBUGText, comandButtonTexture(comandInput[i]));
	}
#ifdef _DEBUG

	for (int i = 0; i < 5; i++)
	{
		sprintf_s(debugComandInput, 10, "%c", comandButton(comandInput[i]));

		RECT DEBUGText = { 100 + (i * 50),500,900,600 };
		WriteWord(debugComandInput, DEBUGText, DT_LEFT, 0xff0000ff, DEBUG_FONT);
	}	
	for (int i = 0; i < 5; i++)
	{
		sprintf_s(debugComandOutput, 10, "%c", comandButton(comandPresentment[i]));

		RECT DEBUGText = { 100 + (i * 50),450,900,600 };
		WriteWord(debugComandOutput, DEBUGText, DT_LEFT, 0xff0000ff, DEBUG_FONT);
	}

	sprintf_s(DebugCounter, 10, "%d", comandCount);
	RECT DEBUGText = { 100 ,550,900,600 };
	WriteWord(DebugCounter, DEBUGText, DT_LEFT, 0xff00ffff, DEBUG_FONT);
#endif

	goodsScoreShow();
	timerRender();
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
	srand((unsigned int)time(NULL));
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
int comandButtonTexture(int comand)
{
	switch (comand) {
	case ButtonA:
		return A_TEX;
	case ButtonB:
		return B_TEX;
	case ButtonX:
		return X_TEX;
	case ButtonY:
		return Y_TEX;
	case ButtonRB:
		return R_TEX;
	case ButtonLB:
		return L_TEX;
	default:
		return NULL_BUTTON_TEX;
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
	case 9:
		if (buttonKeyID == 9 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE10) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE10, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 0;
			break;
		}
	case 8:
		if (buttonKeyID == 8 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE9) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE9, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 9;
			break;
		}

	case 7:
		if (buttonKeyID == 7 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE8) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE8, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 8;
			break;
		}
	case 6:
		if (buttonKeyID == 6 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE7) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE7, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 7;
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
		//clothRush();
		break;
	}
}

void pickGoodsControl() {
	timerControl();
	float deleatPosX = 250;
	int rushInput = 10;
	playerCutinCentral.x -= 5;
	if (playerCutinCentral.x < 50)
	{
		g_isBlowOff = false;
		g_gameScene = PUSHENEMY;
	}
	pickGoodsDeviseControl(&rushInput);
	if (g_isBlowOff) {
		madamBlowOff();
	}

}

void pickGoodsRender() {
	CUSTOMVERTEX playerCutin[4];
	CreateSquareVertex(playerHit, playerCentralHit);
	CreateSquareVertexEx(playerCutin, playerCutinCentral,0,0,1,0.5f);

	BeginSetTexture();
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, FLOAMOVE_BG_TEX);

	EasyCreateSquareVertexColor(0, 0, WIDTH, HEIGHT, HARFCLEAR, BLANK);
	EasyCreateSquareVertex(490, 300, 890, 760, BOX_TEX);
	EasyCreateSquareVertex(560, 300, 960, 760, BOX_TEX);

	for (int i = 0; i < 5; i++) {
		CreateSquareVertex(mobFloa, mobCentralBlowOff[i]);
		if (g_isBlowOff) {
			g_effectCount++;

			mobRad += 0.9f;

			if (mobRad < 0)
			{
				mobRad = mobRad * -1;
			}
			if (i % 2)
			{
				mobRad = mobRad * -1;
			}
			RevolveZ(mobFloa, mobRad, mobCentralBlowOff[i]);
		}
		SetUpTexture(mobFloa, mobTexNum);
	}


	SetUpTexture(playerHit, texturePC);

	
	EasyCreateSquareVertex(0, 150, WIDTH, 550, CUTIN_TEX);

	SetUpTexture(playerCutin, texturePC);

	//char rushButton[10];
	RECT rushButtonAppear = {470,200,810,550};
	EasyCreateRECTVertex(rushButtonAppear, comandButtonTexture(rushButtonShow));

	//sprintf_s(rushButton, 10, "%c", comandButton(rushButtonShow));
	//WriteWord(rushButton, rushButtonAppear, DT_CENTER, RED, RUSH_FONT);
#ifdef _DEBUG
	char goodsNumA[10];
	char DebugTakeBoolA[10];

	sprintf_s(goodsNumA, 10, "%d ", foodGoods[selectedGoods[g_turn]].haveValue);
	RECT DEBUGGoodsA = { 100 ,200,900,600 };
	WriteWord(goodsNumA, DEBUGGoodsA, DT_LEFT, 0xff00ffff, DEBUG_FONT);

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
	status = soundsManager.GetStatus("PICK8");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 450  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);
	status = soundsManager.GetStatus("PICK9");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 500  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);
	status = soundsManager.GetStatus("PICK10");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 550  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);

#endif

	goodsScoreShow();
	timerRender();
	EndSetTexture();
}

void pickGoodsDeviseControl(int* rushInput) {
	BottonCheck();
	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_NUMPADENTER);

	CheckKeyState(DIK_A);
	CheckKeyState(DIK_B);
	CheckKeyState(DIK_X);
	CheckKeyState(DIK_Y);
	CheckKeyState(DIK_R);
	CheckKeyState(DIK_L);

	if (KeyState[DIK_RETURN] == KeyRelease|| KeyState[DIK_NUMPADENTER] == KeyRelease)
	{
		g_isFirst = true;
		g_scene = SCENE_RESULT;
		g_gameScene = FLOAMOVE;
	}
	if (KeyState[DIK_A] == KeyRelease)
	{
		*rushInput = ButtonA;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (KeyState[DIK_B] == KeyRelease)
	{
		*rushInput = ButtonB;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (KeyState[DIK_X] == KeyRelease)
	{
		*rushInput = ButtonX;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (KeyState[DIK_Y] == KeyRelease)
	{
		*rushInput = ButtonY;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (KeyState[DIK_R] == KeyRelease)
	{
		*rushInput = ButtonRB;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (KeyState[DIK_L] == KeyRelease)
	{
		*rushInput = ButtonLB;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}

	//XInputデバイス操作
	GetControl(0);
	BottonCheck();

	if (PadState[ButtonStart] == PadRelease)
	{
		g_isFirst = true;
		g_scene = SCENE_RESULT;
		g_gameScene = FLOAMOVE;
	}
	if (PadState[ButtonA] == PadRelease)
	{
		*rushInput = ButtonA;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (PadState[ButtonB] == PadRelease)
	{
		*rushInput = ButtonB;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (PadState[ButtonX] == PadRelease)
	{
		*rushInput = ButtonX;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (PadState[ButtonY] == PadRelease)
	{
		*rushInput = ButtonY;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (PadState[ButtonRB] == PadRelease)
	{
		*rushInput = ButtonRB;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (PadState[ButtonLB] == PadRelease)
	{
		*rushInput = ButtonLB;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}

}
void rushButtonCheck(int rushInput, int rushShow)
{
	if (rushInput == rushShow) 
	{
		foodGoods[selectedGoods[g_turn]].haveValue++;

	}
	else g_SoundSuccess = soundsManager.Start("MISS", false) && g_SoundSuccess;

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
//int texturePC = YASUKO_TEX;
//static int clothMAXHP = 1000;
//static int mobMAXHP = 50;
//static int clothHP = clothMAXHP;
//static int mobHP = mobMAXHP;
//
//static bool clothBreak = false;
//static bool clothStolen = false;
//static bool getCloth = false;
//static int openCount = 0;
//static float mobRad;
//CENTRAL_STATE clothMobCentral = {900,500,200,300};
//CENTRAL_STATE clothPCCentral = { 300,500,200,300};
//CUSTOMVERTEX clothSmoke[4];
//CENTRAL_STATE clothSmokeCentral[6] = 
//{
//	{800,550,200,200},
//	{700,450,200,200},
//	{600,500,230,230},
//	{650,600,200,200},
//	{450,500,230,230},
//	{500,400,200,200}
//};
//
//
//
//void clothRush() 
//{
//	clothRushControl();
//	clothRushRender();
//}
//
//void clothRushControl() 
//{
//	openCount++;
//	CheckKeyState(DIK_RETURN);
//	CheckKeyState(DIK_NUMPADENTER);
//	CheckKeyState(DIK_A);
//	if (KeyState[DIK_RETURN] == KeyRelease || KeyState[DIK_NUMPADENTER] == KeyRelease)
//	{
//		g_scene = SCENE_RESULT;
//		g_gameScene = FLOAMOVE;
//	}
//	if (openCount > 20)
//	{
//		if (durabilityPointCentral.x <= 600 || !clothHP)
//		{
//			clothBreak = true;
//		}
//		if (durabilityPointCentral.x >= 1200)
//		{
//			clothStolen = true;
//		}
//		if (durabilityPointCentral.x >= 600 && durabilityPointCentral.x <= 1200)
//		{
//			if (KeyState[DIK_A] == KeyRelease) {
//				durabilityPointCentral.x -= 10;
//				mobHP--;
//			}
//		}
//		if (durabilityPointCentral.x <= 805 && clothHP)
//		{
//			clothHP--;
//		}
//		if (!mobHP)
//		{
//			getCloth = true;
//		}
//		else if (durabilityPointCentral.x <= 1200 && !clothStolen)
//		{
//			durabilityPointCentral.x += 1;
//		}
//
//
//		if (clothBreak)
//		{
//			soundsManager.Start("BREAK", false);
//			clothBreak = false;
//			clothRushInit();
//		}
//		if (clothStolen)
//		{
//			soundsManager.Start("LOSE", false);
//			clothStolen = false;
//			clothRushInit();
//		}
//		if (getCloth && durabilityPointCentral.x <= 1000 && durabilityPointCentral.x >= 805)
//		{
//			soundsManager.Start("WIN", false);
//			getCloth = false;
//			clothRushInit();
//		}
//		else if (getCloth && durabilityPointCentral.x >= 1000)
//		{
//			soundsManager.Start("LOSE", false);
//			getCloth = false;
//			clothRushInit();
//		}
//		else if (getCloth && durabilityPointCentral.x <= 805)
//		{
//			soundsManager.Start("BREAK", false);
//			getCloth = false;
//			clothRushInit();
//		}
//		if (mobRad < 0.2) {
//			mobRad -= 0.05;
//		}
//		if (mobRad > 0) {
//			mobRad += 0.05;
//		}
//		static int clothCount = 0;
//		clothCount++;
//		static bool smokeVary = false;
//		static bool charMove = false;
//		if (clothPCCentral.x >= 350) {
//			charMove = true;
//		}
//		if (clothPCCentral.x <= 250) {
//			charMove = false;
//		}
//		if (!charMove) {
//		clothPCCentral.x += 1;
//		clothMobCentral.x += 1;
//		}
//		if (charMove) {
//			clothPCCentral.x -= 1;
//			clothMobCentral.x -= 1;
//		}
//		if (clothCount <= 50) {
//			for (int i = 0; i < 6; i++)
//			{
//				clothSmokeCentral[i].scaleX += rand() % 4;
//				clothSmokeCentral[i].scaleY += rand() % 4;
//
//			}
//		}
//		if (clothCount > 50) {
//			smokeVary = true;
//			for (int i = 0; i < 6; i++)
//			{
//				clothSmokeCentral[i].scaleX -= rand() % 4;
//				clothSmokeCentral[i].scaleY -= rand() % 4;
//
//			}
//			smokeVary = false;
//		}
//		if (clothCount > 100) {
//			clothCount = 0;
//		}
//	}
//}
//
//void clothRushRender() 
//{
//	CUSTOMVERTEX durabilityPoint[4];
//	CUSTOMVERTEX clothMob[4];
//	CUSTOMVERTEX clothPC[4];
//
//	CreateSquareVertex(clothMob, clothMobCentral);
//	CreateSquareVertex(clothPC, clothPCCentral);
//	CreateSquareVertexColor(durabilityPoint, durabilityPointCentral,0xff000000);
//
//
//	BeginSetTexture();
//	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, CLOTH_BG_TEX);
//	EasyCreateSquareVertex(600,50,1200,100,DURABILITY_TEX);
//															  
//	SetUpTexture(durabilityPoint, BLANK);
//
//	SetUpTexture(clothMob, MOB_TEX);
//	SetUpTexture(clothPC, texturePC);
//	for (int i = 0; i < 6; i++) 
//	{
//		RevolveZ(clothSmoke, mobRad, clothSmokeCentral[i]);
//		SetUpTexture(clothSmoke, SMOKE_TEX);
//	}
//	EasyCreateSquareVertexColor(800, 600, 1200, 650,  0xff000000, BLANK);
//	EasyCreateSquareVertexColor(800, 600, 800 - (((800-1200)/ mobMAXHP)*(mobHP)), 650, 0xff00ff00, BLANK);
//
//	if (openCount < 20)
//	{
//		EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, START_TEX);
//	}
//
//#ifdef _DEBUG
//	char debugcloth[10];
//	sprintf_s(debugcloth, 10, "%.2f ", durabilityPointCentral.x);
//	RECT DEBUGText = { 100 ,150,900,600 };
//	WriteWord(debugcloth, DEBUGText, DT_LEFT, 0xffff0000, DEBUG_FONT);
//
//	sprintf_s(debugcloth, 10, "%d ", clothHP);
//	DEBUGText = { 100 ,200,900,600 };
//	WriteWord(debugcloth, DEBUGText, DT_LEFT, 0xffff0000, DEBUG_FONT);
//
//	sprintf_s(debugcloth, 10, "%d ", mobHP);
//	DEBUGText = { 100 ,250,900,600 };
//	WriteWord(debugcloth, DEBUGText, DT_LEFT, 0xffff0000, DEBUG_FONT);
//
//#endif
//
//	EndSetTexture();
//
//}
//
//void clothRushInit() 
//{
//	durabilityPointCentral.x = 900;
//	clothHP = clothMAXHP;
//	mobHP = mobMAXHP;
//	openCount = 0;
//	clothSmokeCentral[0]={ 800,550,200,200 };
//	clothSmokeCentral[1]={ 700,450,200,200 };
//	clothSmokeCentral[2]={ 600,500,250,250 };
//	clothSmokeCentral[3]={ 650,600,200,200 };
//	clothSmokeCentral[4]={ 400,500,250,250 };
//	clothSmokeCentral[5]={ 500,400,200,200 };
//
//	g_gameScene = PUSHENEMY;
//}
//


void testScene() 
{
	for (int i = 0; i < GOODS_MAX; i++) {
		foodGoods[i].haveValue = 10;
	}
	BeginSetTexture();
	static int takegoods[3]{ ICE ,ORANGE ,JUICE };
	comboCheck(takegoods[0], takegoods[1], takegoods[2]);

	for (int i = 0; i < COMBOMAX; i++)
	{
		char test[10];
		sprintf_s(test, 10, "%d", foodCombo[i].comboSucceed);
		RECT DEBUGText = { 100+i*50 ,150,900,600 };
		WriteWord(test, DEBUGText, DT_LEFT, 0xffff0000, DEBUG_FONT);
	}
	EndSetTexture();
}

void goodsScoreShow()
{
	static int goodsInfoShowing;
	static int goodsInfoCount = 0;

	char goodsNumBuff[10];
	EasyCreateSquareVertex(10, 0, 1260, 90, FRAME_TEX);
	switch (g_gameScene)
	{
	case FLOAMOVE:
	
		goodsInfoCount++;
		if (goodsInfoCount > 60)
		{
			switch (goodsInfoShowing)
			{
			case 0:
				goodsInfoShowing = 1;
				break;
			case 1:
				goodsInfoShowing = 2;
				break;
			case 2:
				goodsInfoShowing = 0;
				break;
			}
			goodsInfoCount = 0;
		}
		EasyCreateSquareVertex(100, 10, 200, 80, foodGoods[editMerchandise(goodsInfoShowing, 0)].textureID);
		EasyCreateSquareVertex(200, 10, 300, 80, priceEdit(foodGoods, editMerchandise(goodsInfoShowing, 0), 0));
		EasyCreateSquareVertex(300, 10, 400, 80, priceEdit(foodGoods, editMerchandise(goodsInfoShowing, 0), 1));

		EasyCreateSquareVertex(800, 10, 900, 80, foodGoods[editMerchandise(goodsInfoShowing, 1)].textureID);
		EasyCreateSquareVertex(900, 10, 1000, 80, priceEdit(foodGoods, editMerchandise(goodsInfoShowing, 1), 0));
		EasyCreateSquareVertex(1000, 10, 1100, 80, priceEdit(foodGoods, editMerchandise(goodsInfoShowing, 1), 1));

		break;
	
	case CHOSEGOODS:
		EasyCreateSquareVertex(100, 10, 200, 80, foodGoods[editMerchandise(salesChoice, 0)].textureID);
		EasyCreateSquareVertex(200, 10, 300, 80, priceEdit(foodGoods, editMerchandise(salesChoice,0), 0));
		EasyCreateSquareVertex(300, 10, 400, 80, priceEdit(foodGoods, editMerchandise(salesChoice,0), 1));

		EasyCreateSquareVertex(800, 10, 900, 80, foodGoods[editMerchandise(salesChoice, 1)].textureID);
		EasyCreateSquareVertex(900, 10, 1000, 80, priceEdit(foodGoods, editMerchandise(salesChoice, 1), 0));
		EasyCreateSquareVertex(1000, 10, 1100, 80, priceEdit(foodGoods, editMerchandise(salesChoice, 1), 1));

		break;
	case PUSHENEMY:
	{
		EasyCreateSquareVertex(310, 10, 400, 80, foodGoods[selectedGoods[g_turn]].textureID);
		EasyCreateSquareVertex(450, 10, 600, 80, priceEdit(foodGoods, selectedGoods[g_turn], 0));

		EasyCreateSquareVertex(650, 10, 800, 80, priceEdit(foodGoods, selectedGoods[g_turn], 1));

		sprintf_s(goodsNumBuff, 10, "%d ", foodGoods[selectedGoods[g_turn]].haveValue);
		RECT GoodsNUM = { 900 ,10,1100,80 };
		WriteWord(goodsNumBuff, GoodsNUM, DT_LEFT, BLACK, HAVEGOODS_FONT);

		break;
	}
	case PICKGOODS:
	{
		EasyCreateSquareVertex(310, 10, 400, 80, foodGoods[selectedGoods[g_turn]].textureID);
		EasyCreateSquareVertex(450, 10, 600, 80, priceEdit(foodGoods, selectedGoods[g_turn], 0));

		EasyCreateSquareVertex(650, 10, 800, 80, priceEdit(foodGoods, selectedGoods[g_turn], 1));
		sprintf_s(goodsNumBuff, 10, "%d ", foodGoods[selectedGoods[g_turn]].haveValue);
		RECT GoodsNUM = { 900 ,10,1100,80 };
		WriteWord(goodsNumBuff, GoodsNUM, DT_LEFT, BLACK, HAVEGOODS_FONT);

		break;
	}
	}
}


int priceEdit(GOODSPARAMETER foodGoods[],int goodsselector,int nomalOrSale)
{
	if (!nomalOrSale)
	{
		switch (foodGoods[goodsselector].nominalCost)
		{
		case 300:
			return THREEHANDRED_TEX;
		case 250:
			return TWEHANDREDFIFTY_TEX;
		case 200:
			return TWEHANDRED_TEX;
		case 150:
			return HUNDREDFIFTY_TEX;
		case 100:
			return HUNDRED_TEX;
		case 65:
			return SIXTYFIVE_TEX;
		case 60:
			return SIXTY_TEX;
		case 50:
			return FIFTY_TEX;
		}
	}
	if (nomalOrSale)
	{
		switch (foodGoods[goodsselector].selePrice)
		{
		case 200:
			return S_TWEHUNDRED_TEX;
		case 180:
			return S_HUNDREDEIGHTY_TEX;
		case 150:
			return S_HUNDREDFIFTY_TEX;
		case 100:
			return S_HUNDRED_TEX;
		case 80:
			return S_EIGHTY_TEX;
		case 70:
			return S_SEVENTY_TEX;
		case 60:
			return S_SIXTY_TEX;
		case 50:
			return S_FIFTY_TEX;
		case 40:
			return S_FOURTY_TEX;
		case 30:
			return S_THRTY_TEX;
		}
	return BLANK;
}
	}

int editMerchandise(int seleChoice,int arrayNum)
{
	return popSales[seleChoice].merchandise[arrayNum];
}
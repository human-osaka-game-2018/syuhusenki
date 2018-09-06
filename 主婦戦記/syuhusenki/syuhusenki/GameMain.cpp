#include "Main.h"
#include "FloaMove.h"
#include "GameMain.h"
#include "Goods.h"
#include "Timer.h"
#include "ChoseGoods.h"
#include "BlowOff.h"
#include "PickGoods.h"


#define PLAYER_FLOA_SCALE 50
#define PLAYER_BLOWOFF_SCALE 150
#define MOVE_MILEAGE 8
#define MOVE_MILEAGE_STICK 2
#define YASUKO_TU (325.f/2048.f)
#define YASUKO_TV (675.f/2048.f)
#define ANIMETIONTIME 20


void floaMoveControlM();
void floaMoveRenderM();
void floaMoveRenderStaM();
void collisionM(CENTRAL_STATE* charctor, CENTRAL_STATE prevcentral);
void playerControl(int* onceSound);
bool leachGondola[SORT_MAX];
void leachedGondolaCheck(int* leschgondola, SALESMAN popSales[], int whergondola);
bool MoveOutToErea(CENTRAL_STATE* central, CENTRAL_STATE prevcentral, float Left, float Top, float Right, float Bottom);
void salesmanPoping(SALESMAN popSales[]);
int salesmanToPCCollision(CENTRAL_STATE central, SALESMAN popSales[]);
int PCtu = 0;
int PCtv = 0;
CUSTOMVERTEX PC[4];
void mobControler(CENTRAL_STATE mobCentralFloa[], CENTRAL_STATE prevcentral[]);
bool mobMovedRight[3];
void mobToPCContact(CENTRAL_STATE* charctor, CENTRAL_STATE mobCentralFloa[]);
enum SALESPOSITION
{
	POS_MEET,
	POS_VEGETABLE1,
	POS_VEGETABLE2,
	POS_SEAFOOD1,
	POS_SEAFOOD2,
	POS_SWEET1,
	POS_SWEET2,
	POS_SWEET3,
	POS_DRINK1,
	POS_DRINK2,
	POS_FRUIT1,
	POS_FRUIT2,
	POS_FRUIT3,
	POS_NOTING
};

enum MOBDIRECTION {
	NORTH,
	SOUTH,
	EAST,
	WEST
};

bool g_pause = false;
bool g_isGameStart = false;
bool g_isTimeUp = false;
int g_inCount = 0;

int g_gameScene = FLOAMOVE;

int g_turn = 0;
int mobTexNum;

bool g_isFirst = true;
int g_effectCount = 0;
float mobRad = 0;

 int comandInput[5] = { 10,10,10,10,10 };
 int comandPresentment[5];
 int comandCount = 0;
 int checkedComand = 2;
 int rushButtonShow;
SoundEffect Button{ "BUTTON1","BUTTON2","BUTTON3" };
SoundEffect Pick{ "PICK1", "PICK2","PICK3", "PICK4","PICK5", "PICK6" , "PICK7" ,"PICK8","PICK9","PICK10" };


//モブの画像頂点
CUSTOMVERTEX mobFloa[4];
CENTRAL_STATE mobCentralFloa[3]
{ 
	{ 1200,500 ,PLAYER_FLOA_SCALE,PLAYER_FLOA_SCALE } ,
	{ 600,300 ,PLAYER_FLOA_SCALE,PLAYER_FLOA_SCALE },
	{ 120,500 ,PLAYER_FLOA_SCALE,PLAYER_FLOA_SCALE }
};
CENTRAL_STATE prevMobCentralFloa[3];
CENTRAL_STATE mobCentralBlowOff[5];



CUSTOMVERTEX playerHit[4];
CENTRAL_STATE playerCentralHit = {200,350,300,250};


CENTRAL_STATE durabilityPointCentral = { 900,75 ,15,40};

void floaMove();
//void floaMoveControl();
//void floaMoveRender();
//void keyControl(CENTRAL_STATE* central);
//void mobMoving(CENTRAL_STATE* mob);

int texturePC = YASUKO_TEX;


int priceEdit(GOODSPARAMETER foodGoods[], int goodsselector, int nomalOrSale);
int editMerchandise(int selesChoice, int arrayNum);

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

			ReadInTexture("Texture/UI/frame_goods.png", FRAME_TEX);
			ReadInTexture("Texture/FoodSection.png", FOOD_STAGE_TEX);
			ReadInTexture("Texture/maxresdefault.png", CUTIN_TEX);
			ReadInTexture("Texture/bakuhuhathu.png", EXPLOSION_TEX);
			ReadInTexture("Texture/ヤスコ統合ファイル.png", COMBINED_YASUKO_TEX);
			ReadInTexture("Texture/cardboard.png", BOX_TEX);
			ReadInTexture("Texture/UI/durabilityBar.jpg", DURABILITY_TEX);
			ReadInTexture("Texture/ClothBattle.png", CLOTH_BG_TEX);
			ReadInTexture("Texture/smoke.png", SMOKE_TEX);
			ReadInTexture("Texture/boy.png", BOY_TEX);
			ReadInTexture("Texture/salesclerk.png", SALESMAN_TEX);

			ReadInTexture("Texture/UI/timerFrame.png", TIMER_FRAME_TEX);
			ReadInTexture("Texture/UI/timerHand.png", TIMER_HAND_TEX);
			ReadInTexture("Texture/UI/startCount3.png", STARTCOUNT_3_TEX);
			ReadInTexture("Texture/UI/startCount2.png", STARTCOUNT_2_TEX);
			ReadInTexture("Texture/UI/startCount1.png", STARTCOUNT_1_TEX);
			ReadInTexture("Texture/UI/salerogo.png", START_TEX);
			ReadInTexture("Texture/pauseMenu.png", PAUSE_TEX);
			ReadInTexture("Texture/UI/end.png", TIMEUP_TEX);
			ReadInTexture("Texture/stage.png", FLOAMOVE_BG_TEX);

			ReadInTexture("Texture/scoretext/s50e.png", FIFTY_TEX );
			ReadInTexture("Texture/scoretext/s60e.png", SIXTY_TEX );
			ReadInTexture("Texture/scoretext/s65e.png", SIXTYFIVE_TEX );
			ReadInTexture("Texture/scoretext/s100e.png", HUNDRED_TEX );
			ReadInTexture("Texture/scoretext/s150e.png", HUNDREDFIFTY_TEX);
			ReadInTexture("Texture/scoretext/s200e.png", TWEHANDRED_TEX );
			ReadInTexture("Texture/scoretext/s250e.png", TWEHANDREDFIFTY_TEX );
			ReadInTexture("Texture/scoretext/s300e.png", THREEHANDRED_TEX );
			ReadInTexture("Texture/scoretext/ss30e.png", S_THRTY_TEX );
			ReadInTexture("Texture/scoretext/ss40e.png", S_FOURTY_TEX );
			ReadInTexture("Texture/scoretext/ss50e.png", S_FIFTY_TEX );
			ReadInTexture("Texture/scoretext/ss60e.png", S_SIXTY_TEX );
			ReadInTexture("Texture/scoretext/ss70e.png", S_SEVENTY_TEX );
			ReadInTexture("Texture/scoretext/ss80e.png", S_EIGHTY_TEX);
			ReadInTexture("Texture/scoretext/ss100e.png", S_HUNDRED_TEX );
			ReadInTexture("Texture/scoretext/ss150e.png", S_HUNDREDFIFTY_TEX );
			ReadInTexture("Texture/scoretext/ss180e.png", S_HUNDREDEIGHTY_TEX);
			ReadInTexture("Texture/scoretext/ss200e.png", S_TWEHUNDRED_TEX );

			ReadInTexture("Texture/scoretext/t1.png", T_1);
			ReadInTexture("Texture/scoretext/t2.png", T_2);
			ReadInTexture("Texture/scoretext/t3.png", T_3);
			ReadInTexture("Texture/scoretext/t4.png", T_4);
			ReadInTexture("Texture/scoretext/t5.png", T_5);

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
			ReadInTexture("Texture/merchandise/orange.png", ORANGE_TEX);
			ReadInTexture("Texture/merchandise/banana.png", BANANA_TEX);

			ReadInTexture("Texture/merchandise/tea.png", TEA_TEX);
			ReadInTexture("Texture/merchandise/juice.png", JUICE_TEX);
			ReadInTexture("Texture/merchandise/beer.png", BEER_TEX);


			g_SoundSuccess = soundsManager.Start("LOAD", false) && g_SoundSuccess;

			g_SoundSuccess = soundsManager.Stop("SELECT_BGM") && g_SoundSuccess;

			canRead = false;
		}

		popSales[0].goodsSorting = rand() % 6;//フロア移動で決めたものを入れる
		while (popSales[0].goodsSorting == popSales[1].goodsSorting) {
			popSales[1].goodsSorting = rand() % 6;
		}
		while ((popSales[0].goodsSorting == popSales[2].goodsSorting) || (popSales[1].goodsSorting == popSales[2].goodsSorting)) {

			popSales[2].goodsSorting = rand() % 6;
		}
		selectGoods(&popSales[0]);
		selectGoods(&popSales[1]);
		selectGoods(&popSales[2]);

		comandMake();

		g_isBlowOff = false;
		g_isFirst = false;
	}
#ifdef _DEBUG
	//CheckKeyState(DIK_F1);
	//if (KeyState[DIK_F1] == KeyRelease)
	//{
	//}
	//CheckKeyState(DIK_F2);
	//if (KeyState[DIK_F2] == KeyRelease)
	//{
	//}
	//CheckKeyState(DIK_F3);
	//if (KeyState[DIK_F3] == KeyRelease)
	//{
	//}

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
	}
}

////////////////////////////////////////////////
//フロア移動場面
void floaMove() {
	
	floaMoveControlM();
	floaMoveRenderM();
}

void goodsScoreShow()
{
	static int goodsInfoShowing;
	static int goodsInfoCount = 0;

	char goodsNumBuff[10];
	EasyCreateSquareVertex(10, 0, 1260, 90, FRAME_TEX);
	if (!g_timeDeadline && g_isGameStart) 
	{
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
			EasyCreateSquareVertex(200, 10, 300, 80, priceEdit(foodGoods, editMerchandise(salesChoice, 0), 0));
			EasyCreateSquareVertex(300, 10, 400, 80, priceEdit(foodGoods, editMerchandise(salesChoice, 0), 1));

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
	if (g_timeDeadline)
	{
		float scaleTimmer = 0;
		float posYTimmer = 0;
		int timmerTexture = 0;

		switch (timeShow())
		{
		case 0:
			posYTimmer = 200;
			scaleTimmer = 200;
			timmerTexture = T_1;
			break;
		case 1:
			posYTimmer = 200;
			scaleTimmer = 150;
			timmerTexture = T_2;
			break;
		case 2:
			posYTimmer = 150;
			scaleTimmer = 100;
			timmerTexture = T_3;
			break;
		case 3:
			posYTimmer = 100;
			scaleTimmer = 75;
			timmerTexture = T_4;
			break;
		case 4:
			posYTimmer = 50;
			scaleTimmer = 40;
			timmerTexture = T_5;
			break;
		}
		CUSTOMVERTEX timeLimitShow[4];
		CENTRAL_STATE timeLimitShowCentral = { 640,posYTimmer,scaleTimmer,scaleTimmer };
		CreateSquareVertex(timeLimitShow, timeLimitShowCentral);
		SetUpTexture(timeLimitShow, timmerTexture);

		//char timeText[10];
		//sprintf_s(timeText, 10, "%d ", timeShow() + 1);
		//RECT timeLimit = { 200 ,10,1000,80 };
		//WriteWord(timeText, timeLimit, DT_CENTER, RED, HAVEGOODS_FONT);

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


////////////////////////////////////////////////////
//商品取得場面


CENTRAL_STATE g_PCSta = { 900.f, 580.f, 32.f, 53.f };
CENTRAL_STATE g_prevPCSta;

CENTRAL_STATE g_startCountSta = { WIDTH / 2, HEIGHT / 2, 150.f, 150.f };
CENTRAL_STATE g_startSta = { WIDTH / 2, HEIGHT / 2, 200.f, 96.25f };

FLOAT g_PCSpeed = 2.f;

static bool isRight = false;
//ゲーム制御処理
void floaMoveControlM()
{
	static int onceSound = 0;
	
	timerControl();
	if (g_timerCount < THREE_SECOND)
	{
		salesmanPoping(popSales);
	}
	if (g_isTimeUp)
	{
		for (onceSound; onceSound < 2; onceSound++)
		{
			soundsManager.Start("GONG", false);
		}
	}

	if (g_isGameStart)
	{
		playerControl(&onceSound);
		mobControler(mobCentralFloa, prevMobCentralFloa);
		for (int i = 0; i < 3; i++)
		{
			collisionM(&mobCentralFloa[i], prevMobCentralFloa[i]);
			prevMobCentralFloa[i] = mobCentralFloa[i];
		}
		CheckKeyState(DIK_SPACE);
		if (KeyState[DIK_SPACE] == KeyRelease)
		{
			g_gameScene = CHOSEGOODS;
			onceSound = 0;
		}
	}
	if (isRight)
	{
		CreateSquareVertexEx(PC, g_PCSta,PCtu*YASUKO_TU, PCtv*YASUKO_TV, -1*YASUKO_TU, YASUKO_TV);
	}
	else CreateSquareVertexEx(PC, g_PCSta, PCtu*YASUKO_TU, PCtv*YASUKO_TV, YASUKO_TU, YASUKO_TV);

}
void playerControl(int* onceSound)
{
	GetControl(0);
	BottonCheck();

	static int animeCount = 0;
	animeCount++;
	for (*onceSound; *onceSound < 1; *onceSound++)
	{
		soundsManager.SetVolume("FOOD", 25);
		soundsManager.Start("FOOD", true);
	}

	if (g_Xinput.Gamepad.wButtons == 0)
	{
		g_inCount = 0;
	}
	else if (g_inCount)
	{
		g_inCount++;
	}

	if (InputKEY(DIK_RETURN) || (PadState[ButtonA] == PadRelease) && !(g_inCount))
	{
		//if (g_pause && !g_isTimeUp)
		//{
		//	*onceSound = 0;
		//	PostQuitMessage(0);
		//	g_inCount++;
		//}

		//if (g_isTimeUp)
		//{
		//	*onceSound = 0;
		//	PostQuitMessage(0);
		//	g_inCount++;
		//}
		leachedGondolaCheck(&salesChoice, popSales, salesmanToPCCollision(g_PCSta, popSales));
	}
	if ((GetAnalogLValue(ANALOG_Y) && !GetAnalogLValue(ANALOG_X))|| (!GetAnalogLValue(ANALOG_Y) && GetAnalogLValue(ANALOG_X)) 
		|| (!GetAnalogLValue(ANALOG_Y) && !GetAnalogLValue(ANALOG_X)))
	{
		if (InputKEY(DIK_W) || 0 < GetAnalogLValue(ANALOG_Y))
		{
			isRight = false;
			if (!g_pause && !g_isTimeUp)
			{
				if (GetAnalogLValue(ANALOG_Y) >= 6000 && GetAnalogLValue(ANALOG_Y) <= 10000)
				{
					g_PCSta.y -= g_PCSpeed / 4;
				}
				else if (GetAnalogLValue(ANALOG_Y) >= 10000 && GetAnalogLValue(ANALOG_Y) <= 18000)
				{
					g_PCSta.y -= g_PCSpeed / 2;
				}
				else if (GetAnalogLValue(ANALOG_Y) >= 18000)
				{
					g_PCSta.y -= g_PCSpeed;
				}
				else if (InputKEY(DIK_W))g_PCSta.y -= g_PCSpeed;
				if (animeCount >= ANIMETIONTIME)
				{
					PCtu++;
					animeCount = 0;
				}
				if (PCtu >= 3)
				{
					PCtu = 1;
				}
				PCtv = 1;

			}
		}

		if (InputKEY(DIK_S) || 0 > GetAnalogLValue(ANALOG_Y))
		{
			isRight = false;
			if (!g_pause && !g_isTimeUp)
			{
				if (GetAnalogLValue(ANALOG_Y) <= -6000 && GetAnalogLValue(ANALOG_Y) >= -10000)
				{
					g_PCSta.y += g_PCSpeed / 4;
				}
				else if (GetAnalogLValue(ANALOG_Y) <= -10000 && GetAnalogLValue(ANALOG_Y) >= -18000)
				{
					g_PCSta.y += g_PCSpeed / 2;
				}
				else if (GetAnalogLValue(ANALOG_Y) <= -18000)
				{
					g_PCSta.y += g_PCSpeed;
				}
				else if (InputKEY(DIK_S))g_PCSta.y += g_PCSpeed;
				if (animeCount >= ANIMETIONTIME)
				{
					PCtu++;
					animeCount = 0;
				}
				if (PCtu >= 3)
				{
					PCtu = 1;
				}
				PCtv = 0;

			}
		}

		if (InputKEY(DIK_D) || 0 < GetAnalogLValue(ANALOG_X))
		{
			isRight = true;
			if (!g_pause && !g_isTimeUp)
			{
				if (GetAnalogLValue(ANALOG_X) >= 6000 && GetAnalogLValue(ANALOG_X) <= 10000)
				{
					g_PCSta.x += g_PCSpeed / 4;
				}
				else if (GetAnalogLValue(ANALOG_X) >= 10000 && GetAnalogLValue(ANALOG_X) <= 18000)
				{
					g_PCSta.x += g_PCSpeed / 2;
				}
				else if (GetAnalogLValue(ANALOG_X) >= 18000)
				{
					g_PCSta.x += g_PCSpeed;
				}
				else if (InputKEY(DIK_D))g_PCSta.x += g_PCSpeed;

				if (PCtu == 0)
				{
					PCtu = 1;
				}
				if (animeCount >= ANIMETIONTIME)
				{
					PCtu++;
					animeCount = 0;
				}
				if (PCtu >= 4)
				{
					PCtu = 2;
				}
				PCtv = 2;
			}
		}


		if (InputKEY(DIK_A) || 0 > GetAnalogLValue(ANALOG_X))
		{
			isRight = false;
			if (!g_pause && !g_isTimeUp)
			{
				if (GetAnalogLValue(ANALOG_X) <= -6000 && GetAnalogLValue(ANALOG_X) >= -10000)
				{
					g_PCSta.x -= g_PCSpeed / 4;
				}
				else if (GetAnalogLValue(ANALOG_X) <= -10000 && GetAnalogLValue(ANALOG_X) >= -18000)
				{
					g_PCSta.x -= g_PCSpeed / 2;
				}
				else if (GetAnalogLValue(ANALOG_X) <= -18000)
				{
					g_PCSta.x -= g_PCSpeed;
				}
				else if (InputKEY(DIK_A))g_PCSta.x -= g_PCSpeed;

				if (animeCount >= ANIMETIONTIME)
				{
					PCtu++;
					animeCount = 0;
				}
				if (PCtu >= 3)
				{
					PCtu = 1;
				}
				PCtv = 2;
			}
		}
	}
	if (PadState[ButtonStart] == PadRelease && !(g_inCount))
	{
		if (g_pause && !g_isTimeUp)
		{
			buttonSE(Button, 3);
			g_pause = false;
			g_inCount++;
		}
		else if (!g_pause && !g_isTimeUp)
		{
			buttonSE(Button, 3);
			g_pause = true;
			g_inCount++;
		}
	}
	mobToPCContact(&g_PCSta, mobCentralFloa);
	collisionM(&g_PCSta, g_prevPCSta);
	g_prevPCSta = g_PCSta;
}

//当たり判定処理
void collisionM(CENTRAL_STATE* charctor, CENTRAL_STATE prevcentral)
{
	//壁
	if (charctor->x <= 50.f)
	{
		charctor->x = 50.f;
	}

	if (charctor->x >= 1230.f)
	{
		charctor->x = 1230.f;
	}

	if (charctor->y <= 145.f)
	{
		charctor->y = 145.f;
	}

	if (charctor->y >= 630.f)
	{
		charctor->y = 630.f;
	}

	//商品棚
	//ジュース1
	if (charctor->x <= 100.f && charctor->y <= 555.f&& charctor->y >= 185.f)
	{
		charctor->x = 100.f;
	}
	//肉
	if (charctor->x >= 125.f && charctor->x <= 640.f&& charctor->y <= 155.f)
	{
		charctor->y = 155.f;
	}
	//魚
	if (charctor->x <= 1230.f && charctor->x >= 640.f&& charctor->y <= 155.f)
	{
		charctor->y = 155.f;
	}
	//野菜1
	if (charctor->x >= 1200.f && charctor->y <= 615.f&& charctor->y >= 165.f)
	{
		charctor->x = 1200.f;
	}
	//果実2
	MoveOutToErea(charctor, prevcentral, 786, 420, 1016, 575);
	//野菜2
	MoveOutToErea(charctor, prevcentral, 1035, 213, 1152, 565);
	//ジュース2
	MoveOutToErea(charctor, prevcentral, 640, 170, 1152, 250);
	//ジュース3
	MoveOutToErea(charctor, prevcentral, 682, 260, 1016, 405);
	//果実1
	MoveOutToErea(charctor, prevcentral, 442, 429, 770, 590);
	//おやつ1
	MoveOutToErea(charctor, prevcentral, 270, 170, 595, 290);
	//おやつ2-1
	MoveOutToErea(charctor, prevcentral, 135, 170, 250, 320);
	//おやつ2-2
	MoveOutToErea(charctor, prevcentral, 135, 320, 600, 400);
	//おやつ3
	MoveOutToErea(charctor, prevcentral, 135, 430, 420, 590);

}
void leachedGondolaCheck(int* leschgondola,SALESMAN popSales[], int whergondola)
{
	for (int i = 0; i < 3; i++)
	{
		if (popSales[i].popPosition == whergondola)
		{
			*leschgondola = i;
			g_gameScene = CHOSEGOODS;
		}
	}
}
bool MoveOutToErea(CENTRAL_STATE* central, CENTRAL_STATE prevcentral, float Left, float Top, float Right, float Bottom)
{
	static float posBuff = 0;
	posBuff = central->y;
	if ((Left <= central->x) && (central->x <= Right)
		&&( Top <= central->y) && (central->y <= Bottom) )
	{
		if ((Left <= prevcentral.x) && (prevcentral.x <= Right)&&(central->x!= prevcentral.x))
		{
		if ((Left <= central->x) && (central->x <= Right))
			{
				if ((Left + (Right - Left) / 2) >= central->x) {
					central->x = Left-1;
					return true;
				}
				if (central->x >= (Right - (Right - Left) / 2)) {
					central->x = Right+1;
					return true;
				}
			}
		}
		if ((Top <= prevcentral.y) && (prevcentral.y <= Bottom) && (central->y != prevcentral.y))
			{
		if ((Top <= central->y) && (central->y <= Bottom))
			{
				if ((Top + (Bottom - Top) / 2) >= central->y) {
					central->y = Top-1;
					return true;
				}
				if (central->y >= (Bottom - (Bottom - Top) / 2)) {
					central->y = Bottom+1;
					return true;
				}
			}
		}
		
	}
	else return false;
}
int salesmanToPCCollision(CENTRAL_STATE central, SALESMAN popSales[])
{
	for (int i = 0; i < 3; i++)
	{
		if (BtoBContact(&central, &popSales[i].popPositionCentral))
		{
			return popSales[i].popPosition;
		}
	}
	return POS_NOTING;
}
//ゲーム描画処理
void floaMoveRenderM()
{
	BeginSetTexture();

	//ゲーム画面のテクスチャの設定
	floaMoveRenderStaM();
#ifdef _DEBUG
	char debugPC[10];
	sprintf_s(debugPC, 10, "%.2f", g_PCSta.x);
	RECT DEBUGTextA = { 100 ,500,900,600 };
	WriteWord(debugPC, DEBUGTextA, DT_LEFT, 0xff000000, DEBUG_FONT);
	sprintf_s(debugPC, 10, "%.2f", g_PCSta.y);
	DEBUGTextA = { 100 ,550,900,600 };
	WriteWord(debugPC, DEBUGTextA, DT_LEFT, 0xff000000, DEBUG_FONT);

#endif

	EndSetTexture();
}
void floaMoveRenderStaM()
{
	EasyCreateSquareVertex(0, 100, WIDTH, 680, FLOAMOVE_BG_TEX);

	CUSTOMVERTEX startCount[4];
	CUSTOMVERTEX start[4];
	CUSTOMVERTEX salesmans[4];

	CreateSquareVertex(startCount, g_startCountSta);
	CreateSquareVertex(start, g_startSta);
	for (int i = 0; i < 3; i++)
	{
		if (!mobMovedRight[i])
		{
			CreateSquareVertexEx(salesmans, mobCentralFloa[i], 1, 0, -1, 1);
		}
		else CreateSquareVertexEx(salesmans, mobCentralFloa[i], 0, 0, 1, 1);

		if (i == 2) {
			SetUpTexture(salesmans, MOB_TEX);
		}
		else SetUpTexture(salesmans, BOY_TEX);
	}


	if (g_isGameStart)
	{
		for (int i = 0; i < 3; i++)
		{
			CreateSquareVertex/*Color*/(salesmans, popSales[i].popPositionCentral/*,0xaf999999*/);
			SetUpTexture(salesmans, SALESMAN_TEX/*BLANK*/);
		}
	}
	//プレイヤーキャラクターのテクスチャの描画
	SetUpTexture(PC, COMBINED_YASUKO_TEX);
	goodsScoreShow();
	timerRender();

	if ((g_timerCount > ZERO_SECOND) && (g_timerCount <= ONE_SECOND))
	{
		//スタートカウントのテクスチャの描画
		SetUpTexture(startCount, STARTCOUNT_3_TEX);
	}
	else if ((g_timerCount > ONE_SECOND) && (g_timerCount <= TWO_SECOND))
	{
		//スタートカウントのテクスチャの描画
		SetUpTexture(startCount, STARTCOUNT_2_TEX);
	}
	else if ((g_timerCount > TWO_SECOND) && (g_timerCount <= THREE_SECOND))
	{
		//スタートカウントのテクスチャの描画
		SetUpTexture(startCount, STARTCOUNT_1_TEX);
	}
	else if ((g_timerCount > THREE_SECOND) && (g_timerCount <= FOUR_SECOND))
	{
		//スタートカウントのテクスチャの描画
		SetUpTexture(start, START_TEX);
	}

	if (g_pause && !(g_isTimeUp))
	{
		EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, PAUSE_TEX);
	}
}

//ゲーム画面のテクスチャ
void salesmanPoping(SALESMAN popSales[])
{
	for (int i = 0; i < 3; i++)
	{
		switch (popSales[i].goodsSorting)
		{
		case MEET_SORT:
			popSales[i].popPositionCentral = { 285,120,75,75 };
			popSales[i].popPosition = POS_MEET;
			break;
		case VEGETABLE_SORT:
			switch (i)
			{
			case 0:
				popSales[i].popPositionCentral = { 1190,360,75,75 };
				popSales[i].popPosition = POS_VEGETABLE1;
				break;
			case 1:
				popSales[i].popPositionCentral = { 1095,400,90,75 };
				popSales[i].popPosition = POS_VEGETABLE2;
				break;
			case 2:
				if (rand() % 2)
				{
					popSales[i].popPositionCentral = { 1095,400,90,75 };
					popSales[i].popPosition = POS_VEGETABLE2;
				}
				else
				{
					popSales[i].popPositionCentral = { 1190,360,75,75 };
					popSales[i].popPosition = POS_VEGETABLE1;
				}
				break;
			}
			continue;
		case SEAFOOD_SORT:
			switch (i)
			{
			case 0:
				popSales[i].popPositionCentral = { 800,120,75,75 };
				popSales[i].popPosition = POS_SEAFOOD1;
				break;
			case 1:
				popSales[i].popPositionCentral = { 875,210,75,75 };
				popSales[i].popPosition = POS_SEAFOOD2;
				break;
			case 2:
				if (rand() % 2)
				{
					popSales[i].popPositionCentral = { 875,210,75,75 };
					popSales[i].popPosition = POS_SEAFOOD2;
				}
				else
				{
					popSales[i].popPositionCentral = { 800,120,75,75 };
					popSales[i].popPosition = POS_SEAFOOD1;
				}
				break;
			}
			continue;
		case SWEET_SORT:
			switch (i)
			{
			case 0:
				popSales[i].popPositionCentral = { 410,230,75,90 };
				popSales[i].popPosition = POS_SWEET1;
				break;
			case 1:
				popSales[i].popPositionCentral = { 270,330,50,50 };
				popSales[i].popPosition = POS_SWEET2;
				break;
			case 2:
				popSales[i].popPositionCentral = { 270,550,100,100 };
				popSales[i].popPosition = POS_SWEET3;
				break;
			}
			continue;
		case FRUIT_SORT:
			switch (i)
			{
			case 0:
				popSales[i].popPositionCentral = { 610,540,170,80 };
				popSales[i].popPosition = POS_FRUIT1;
				break;
			case 1:
				popSales[i].popPositionCentral = { 917,512,100,100 };
				popSales[i].popPosition = POS_FRUIT2;
				break;
			case 2:
				if (rand() % 2) {
					popSales[i].popPositionCentral = { 917,512,100,100 };
					popSales[i].popPosition = POS_FRUIT2;
				}
				else
				{
					popSales[i].popPositionCentral = { 610,540,170,80 };
					popSales[i].popPosition = POS_FRUIT1;
				}
				break;
			}
			continue;
		case DRINK_SORT:
			switch (i)
			{
			case 0:
				popSales[i].popPositionCentral = { 65,450,75,100 };
				popSales[i].popPosition = POS_DRINK1;
				break;
			case 1:
				popSales[i].popPositionCentral = { 820,360,100,100 };
				popSales[i].popPosition = POS_DRINK2;
				break;
			case 2:
				if (rand() % 2) {
					popSales[i].popPositionCentral = { 820,360,100,100 };
					popSales[i].popPosition = POS_DRINK2;
				}
				else
				{
					popSales[i].popPositionCentral = { 70,450,75,75 };
					popSales[i].popPosition = POS_DRINK1;
				}
				break;
			}
			continue;
		}
	}
}
void mobControler(CENTRAL_STATE mobCentralFloa[], CENTRAL_STATE prevcentral[])
{
	static int collisionCount[3] = { 0,0,0 };
	if (!BtoBContact(&mobCentralFloa[0], &g_PCSta))
	{
		if (mobCentralFloa[0].x <= 100)
		{
			mobCentralFloa[0].y -= 3;
			mobMovedRight[0] = false;

		}
		if (mobCentralFloa[0].x >= 1200)
		{
			mobCentralFloa[0].y += 3;
			mobMovedRight[0] = true;
		}
		if (mobCentralFloa[0].y >= 630)
		{
			mobCentralFloa[0].x -= 4;
			mobMovedRight[0] = true;

		}
		if (mobCentralFloa[0].y <= 165)
		{
			mobCentralFloa[0].x += 4;
			mobMovedRight[0] = false;

		}
	}
	else
	{
		collisionCount[0]++;
		if (collisionCount[0] > 30)
		{
			if (mobCentralFloa[0].x <= 100)
			{
				mobCentralFloa[0].y += 5;
				mobMovedRight[0] = false;

			}
			if (mobCentralFloa[0].x >= 1200)
			{
				mobCentralFloa[0].y -= 5;
				mobMovedRight[0] = true;
			}
			if (mobCentralFloa[0].y >= 630)
			{
				mobCentralFloa[0].x += 6;
				mobMovedRight[0] = true;

			}
			if (mobCentralFloa[0].y <= 165)
			{
				mobCentralFloa[0].x -= 6;
				mobMovedRight[0] = false;
			}
			collisionCount[0] = 0;
		}
	}
	if (!BtoBContact(&mobCentralFloa[1], &g_PCSta))
	{
		switch (rand() % 4)
		{
		case NORTH:
			mobCentralFloa[1].y -= 3;
			mobMovedRight[1] = true;
			break;
		case SOUTH:
			mobCentralFloa[1].y += 3;
			mobMovedRight[1] = false;
			break;
		case EAST:
			mobCentralFloa[1].x -= 3;
			mobMovedRight[1] = true;
			break;
		case WEST:
			mobCentralFloa[1].x += 3;
			mobMovedRight[1] = false;
			break;
		}
	}
	else
	{
		collisionCount[1]++;
		if (collisionCount[1] > 30)
		{
			mobCentralFloa[1].y += 5;
			mobCentralFloa[1].x += 5;

		collisionCount[1] = 0;
		}
	}
	if (!BtoBContact(&mobCentralFloa[2], &g_PCSta))
	{
		switch (rand() % 5)
		{
		case NORTH:
			mobCentralFloa[2].y -= 1.5f;
			mobMovedRight[2] = true;
			break;
		case SOUTH:
			mobCentralFloa[2].y += 1.5f;
			mobMovedRight[2] = false;
			break;
		case EAST:
			mobCentralFloa[2].x -= 2;
			mobMovedRight[2] = true;
			break;
		case WEST:
			mobCentralFloa[2].x += 2;
			mobMovedRight[2] = false;
			break;
		default:
			break;
		}
	}
	else
	{
		collisionCount[2]++;
		if (collisionCount[2] > 30)
		{
			mobCentralFloa[2].y += 5;
			mobCentralFloa[2].x += 5;
			collisionCount[2] = 0;
		}
	}
	collisionM(&mobCentralFloa[1], prevcentral[1]);
	collisionM(&mobCentralFloa[2], prevcentral[2]);
}

void mobToPCContact(CENTRAL_STATE* charctor, CENTRAL_STATE mobCentralFloa[])
{
	for (int i = 0; i < 3; i++)
	{
		if ((charctor->x <= mobCentralFloa[i].x + mobCentralFloa[i].scaleX) && (mobCentralFloa[i].x <= charctor->x + charctor->scaleX)
			&& (charctor->y <= mobCentralFloa[i].y + mobCentralFloa[i].scaleY) && (mobCentralFloa[i].y <= charctor->y + charctor->scaleY)) {

			if ((charctor->x <= mobCentralFloa[i].x + mobCentralFloa[i].scaleX))
			{
				charctor->x = mobCentralFloa[i].x + mobCentralFloa[i].scaleX;
			}
			if ((charctor->x >= mobCentralFloa[i].x - mobCentralFloa[i].scaleX))
			{
				charctor->x = mobCentralFloa[i].x - mobCentralFloa[i].scaleX;
			}
			if ((charctor->y <= mobCentralFloa[i].y + mobCentralFloa[i].scaleY))
			{
				charctor->y = mobCentralFloa[i].y + mobCentralFloa[i].scaleY;
			}
			if ((charctor->y >= mobCentralFloa[i].y - mobCentralFloa[i].scaleY))
			{
				charctor->y = mobCentralFloa[i].y - mobCentralFloa[i].scaleY;
			}
		}
	}
}
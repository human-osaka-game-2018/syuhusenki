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
CENTRAL_STATE mobCentralBlowOff[5];

CUSTOMVERTEX playerHit[4];
CENTRAL_STATE playerCentralHit = {200,350,300,250};

CENTRAL_STATE durabilityPointCentral = { 900,75 ,15,40};

int texturePC = YASUKO_TEX;
int priceEdit(GOODSPARAMETER foodGoods[], int goodsselector, int nomalOrSale);
int editMerchandise(int selesChoice, int arrayNum);

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
			ReadInTexture("Texture/UI/durabilityBar.jpg", DURABILITY_TEX);
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


void showPressA()
{
	CUSTOMVERTEX showA[4];
	CENTRAL_STATE centralAButton = {1150,600,50,50};
	CreateSquareVertexColor(showA, centralAButton,g_cursolColor);
	SetUpTexture(showA, A_TEX);
}
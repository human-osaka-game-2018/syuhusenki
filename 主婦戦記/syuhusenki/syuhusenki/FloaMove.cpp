#include "Main.h"
#include "GameMain.h"
#include "FloaMove.h"
#include "Timer.h"
#include "Goods.h"
#include "ChoseGoods.h"

#define ANIMETIONTIME 20
//モブの動く方向
enum MOBDIRECTION {
	NORTH,
	SOUTH,
	EAST,
	WEST
};

CENTRAL_STATE mobCentralFloa[4]
{
	{ 1200,500 ,PLAYER_FLOA_SCALE,PLAYER_FLOA_SCALE },
	{ 600,300 ,PLAYER_FLOA_SCALE,PLAYER_FLOA_SCALE },
	{ 120,500 ,PLAYER_FLOA_SCALE,PLAYER_FLOA_SCALE },
	{ 1030,230 ,PLAYER_FLOA_SCALE,PLAYER_FLOA_SCALE }

};
CENTRAL_STATE prevMobCentralFloa[4];
CUSTOMVERTEX PC[4];

static bool mobMovedRight[4];
static bool isRight = false;

static int PCtu = 0;
static int PCtv = 0;
static int mobtu[4] = {0,0,0,0};
static int mobtv[4] = {0,0,0,0};


void playerControl(int* onceSound);
void leachedGondolaCheck(int* leschgondola, SALESMAN popSales[], int whergondola);
bool MoveOutToErea(CENTRAL_STATE* central, CENTRAL_STATE prevcentral, float Left, float Top, float Right, float Bottom);
void salesmanPoping(SALESMAN popSales[]);
int salesmanToPCCollision(CENTRAL_STATE central, SALESMAN popSales[]);
void floaMoveControl();
void floaMoveRender();
void floaMoveRenderSta();
void collision(CENTRAL_STATE* charctor, CENTRAL_STATE prevcentral);
void mobControler(CENTRAL_STATE mobCentralFloa[], CENTRAL_STATE prevcentral[]);
void mobToPCContact(CENTRAL_STATE* charctor, CENTRAL_STATE mobCentralFloa[]);


CENTRAL_STATE g_PCSta = { 900.f, 580.f, 32.f, 53.f };
CENTRAL_STATE g_prevPCSta;

CENTRAL_STATE g_startCountSta = { WIDTH / 2, HEIGHT / 2, 150.f, 150.f };
CENTRAL_STATE g_startSta = { WIDTH / 2, HEIGHT / 2, 200.f, 96.25f };

FLOAT g_PCSpeed = 2.f;

void floaMove() {

	floaMoveControl();
	floaMoveRender();
}

//ゲーム制御処理
void floaMoveControl()
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
		for (int i = 0; i < 4; i++)
		{
			collision(&mobCentralFloa[i], prevMobCentralFloa[i]);
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
		CreateSquareVertexEx(PC, g_PCSta, PCtu*YASUKO_TU, PCtv*YASUKO_TV, -1 * YASUKO_TU, YASUKO_TV);
	}
	else CreateSquareVertexEx(PC, g_PCSta, PCtu*YASUKO_TU, PCtv*YASUKO_TV, YASUKO_TU, YASUKO_TV);

}
void playerControl(int* onceSound)
{
	GetControl(0);
	BottonCheck();

	static int animeCount = 0;
	animeCount++;

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
		leachedGondolaCheck(&salesChoice, popSales, salesmanToPCCollision(g_PCSta, popSales));
	}
	if ((GetAnalogLValue(ANALOG_Y) && !GetAnalogLValue(ANALOG_X)) || (!GetAnalogLValue(ANALOG_Y) && GetAnalogLValue(ANALOG_X))
		|| (!GetAnalogLValue(ANALOG_Y) && !GetAnalogLValue(ANALOG_X)))
	{
		if (InputKEY(DIK_W) || 0 < GetAnalogLValue(ANALOG_Y)|| (PadState[ButtonUP] == PadOn))
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
				else if (InputKEY(DIK_W) || (PadState[ButtonUP] == PadOn))g_PCSta.y -= g_PCSpeed;
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

		if (InputKEY(DIK_S) || 0 > GetAnalogLValue(ANALOG_Y) || (PadState[ButtonDOWN] == PadOn))
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
				else if (InputKEY(DIK_S) || (PadState[ButtonDOWN] == PadOn))g_PCSta.y += g_PCSpeed;
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

		if (InputKEY(DIK_D) || 0 < GetAnalogLValue(ANALOG_X) || (PadState[ButtonRIGHT] == PadOn))
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
				else if (InputKEY(DIK_D) || (PadState[ButtonRIGHT] == PadOn))g_PCSta.x += g_PCSpeed;

				if (PCtu == 0)
				{
					PCtu = 1;
				}
				if (animeCount >= ANIMETIONTIME)
				{
					PCtu++;
					animeCount = 0;
				}
				if (PCtu > 4)
				{
					PCtu = 1;
				}
				PCtv = 2;
			}
		}


		if (InputKEY(DIK_A) || 0 > GetAnalogLValue(ANALOG_X) || (PadState[ButtonLEFT] == PadOn))
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
				else if (InputKEY(DIK_A) || (PadState[ButtonLEFT] == PadOn))g_PCSta.x -= g_PCSpeed;

				if (animeCount >= ANIMETIONTIME)
				{
					PCtu++;
					animeCount = 0;
				}
				if (PCtu > 3)
				{
					PCtu = 0;
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
	collision(&g_PCSta, g_prevPCSta);
	g_prevPCSta = g_PCSta;
}

//当たり判定処理
void collision(CENTRAL_STATE* charctor, CENTRAL_STATE prevcentral)
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
void leachedGondolaCheck(int* leschgondola, SALESMAN popSales[], int whergondola)
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
		&& (Top <= central->y) && (central->y <= Bottom))
	{
		if ((Left <= prevcentral.x) && (prevcentral.x <= Right) && (central->x != prevcentral.x))
		{
			if ((Left <= central->x) && (central->x <= Right))
			{
				if ((Left + (Right - Left) / 2) >= central->x) {
					central->x = Left - 1;
					return true;
				}
				if (central->x >= (Right - (Right - Left) / 2)) {
					central->x = Right + 1;
					return true;
				}
			}
		}
		if ((Top <= prevcentral.y) && (prevcentral.y <= Bottom) && (central->y != prevcentral.y))
		{
			if ((Top <= central->y) && (central->y <= Bottom))
			{
				if ((Top + (Bottom - Top) / 2) >= central->y) {
					central->y = Top - 1;
					return true;
				}
				if (central->y >= (Bottom - (Bottom - Top) / 2)) {
					central->y = Bottom + 1;
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
void floaMoveRender()
{
	BeginSetTexture();

	//ゲーム画面のテクスチャの設定
	floaMoveRenderSta();
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

//ゲーム画面のテクスチャ
void floaMoveRenderSta()
{
	EasyCreateSquareVertex(0, 100, WIDTH, 680, FLOAMOVE_BG_TEX);

	CUSTOMVERTEX startCount[4];
	CUSTOMVERTEX start[4];
	CUSTOMVERTEX salesmans[4];

	CreateSquareVertex(startCount, g_startCountSta);
	CreateSquareVertex(start, g_startSta);
	for (int i = 0; i < 4; i++)
	{
		if (i == 0 || i == 1)
		{
			if (mobMovedRight[i])
			{
				CreateSquareVertexEx(salesmans, mobCentralFloa[i], mobtu[i] * BOY_TU, mobtv[i] * BOY_TV, -BOY_TU, BOY_TV);
			}
			else CreateSquareVertexEx(salesmans, mobCentralFloa[i], mobtu[i] * BOY_TU, mobtv[i] * BOY_TV, BOY_TU, BOY_TV);
		}
		else {
			if (mobMovedRight[i])
			{
				CreateSquareVertexEx(salesmans, mobCentralFloa[i], MOB_TU, mobtv[i] * MOB_TV, -MOB_TU, MOB_TV);
			}
			else CreateSquareVertexEx(salesmans, mobCentralFloa[i], 0, mobtv[i] * MOB_TV, MOB_TU, MOB_TV);
		}
		if (i >= 2)
		{
			SetUpTexture(salesmans, mobTexNum);
		}
		else SetUpTexture(salesmans, BOY_TEX);
	}


	goodsScoreShow();
	if (g_isGameStart)
	{
		static int saleAnimeCount = 0;
		int saleAnimeTv;
		static bool saleAnimeChainger = false;
		saleAnimeCount++;
		if (saleAnimeCount > ANIMETIONTIME && !saleAnimeChainger)
		{
			saleAnimeCount = 0;
			saleAnimeChainger = true;
		}
		if(saleAnimeCount > ANIMETIONTIME && saleAnimeChainger)
		{
			saleAnimeCount = 0;
			saleAnimeChainger = false;
		}
		if (saleAnimeChainger)
		{
			saleAnimeTv = 1;
		}
		else saleAnimeTv = 0;
		for (int i = 0; i < 3; i++)
		{
			CreateSquareVertexEx(salesmans, popSales[i].popPositionCentral, 0, saleAnimeTv * SALE_TV, SALE_TU, SALE_TV);
			SetUpTexture(salesmans, SALESMAN_TEX);
		}
	}
	//プレイヤーキャラクターのテクスチャの描画
	SetUpTexture(PC, YASUKO_TEX);

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
				popSales[i].popPositionCentral = { 270,360,60,60 };
				popSales[i].popPosition = POS_SWEET2;
				break;
			case 2:
				popSales[i].popPositionCentral = { 270,530,100,100 };
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
	static int collisionCount[4] = { 0,0,0,0};
	static int mobAnimeCount[4] = { 0,0,0,0 };
	if (!BtoBContact(&mobCentralFloa[0], &g_PCSta))
	{
		if (mobCentralFloa[0].x <= 100)
		{
			mobCentralFloa[0].y -= 3;
			mobMovedRight[0] = false;
			mobtv[0] = 1;

		}
		if (mobCentralFloa[0].x >= 1200)
		{
			mobCentralFloa[0].y += 3;
			mobMovedRight[0] = false;
			mobtv[0] = 0;
		}
		if (mobCentralFloa[0].y >= 630)
		{
			mobCentralFloa[0].x -= 4;
			mobMovedRight[0] = false;
			mobtv[0] = 2;

		}
		if (mobCentralFloa[0].y <= 165)
		{
			mobCentralFloa[0].x += 4;
			mobMovedRight[0] = true;
			mobtv[0] = 2;

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
				mobtv[0] = 0;

			}
			if (mobCentralFloa[0].x >= 1200)
			{
				mobCentralFloa[0].y -= 5;
				mobMovedRight[0] = false;
				mobtv[0] = 1;
			}
			if (mobCentralFloa[0].y >= 630)
			{
				mobCentralFloa[0].x += 6;
				mobMovedRight[0] = true;
				mobtv[0] = 2;


			}
			if (mobCentralFloa[0].y <= 165)
			{
				mobCentralFloa[0].x -= 6;
				mobMovedRight[0] = false;
				mobtv[0] = 2;

			}
			collisionCount[0] = 0;
		}
	}
	mobAnimeCount[0]++;
	if (mobAnimeCount[0] >= ANIMETIONTIME)
	{
		mobtu[0]++;
		mobAnimeCount[0] = 0;
	}
	if (mobtu[0] > 1 && !mobMovedRight[0])
	{
		mobtu[0] = 0;
	}
	if (mobtu[0] > 2 && mobMovedRight[0])
	{
		mobtu[0] = 1;
	}


	if (!BtoBContact(&mobCentralFloa[1], &g_PCSta))
	{
		switch (rand() % 4)
		{
		case NORTH:
			mobCentralFloa[1].y -= 3;
			mobMovedRight[1] = false;
			mobtv[1] = 1;
			break;
		case SOUTH:
			mobCentralFloa[1].y += 3;
			mobMovedRight[1] = false;
			mobtv[1] = 0;
			break;
		case EAST:
			mobCentralFloa[1].x -= 3;
			mobMovedRight[1] = false;
			mobtv[1] = 2;
			break;
		case WEST:
			mobCentralFloa[1].x += 3;
			mobMovedRight[1] = true;
			mobtv[1] = 2;
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
	mobAnimeCount[1]++;
	if (mobAnimeCount[1] >= ANIMETIONTIME)
	{
		mobtu[1]++;
		mobAnimeCount[1] = 0;
	}
	if (mobtu[1] > 1 && !mobMovedRight[1])
	{
		mobtu[1] = 0;
	}
	if (mobtu[1] > 2 && mobMovedRight[1])
	{
		mobtu[1] = 1;
	}

	if (!BtoBContact(&mobCentralFloa[2], &g_PCSta))
	{
		switch (rand() % 5)
		{
		case NORTH:
			mobCentralFloa[2].y -= 1.5f;
			mobMovedRight[2] = false;
			mobtv[2] = 1;
			break;
		case SOUTH:
			mobCentralFloa[2].y += 1.5f;
			mobMovedRight[2] = false;
			mobtv[2] = 0;
			break;
		case EAST:
			mobCentralFloa[2].x -= 2;
			mobMovedRight[2] = false;
			mobtv[2] = 2;
			break;
		case WEST:
			mobCentralFloa[2].x += 2;
			mobMovedRight[2] = true;
			mobtv[2] = 2;
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
	if (!BtoBContact(&mobCentralFloa[3], &g_PCSta))
	{
		switch (rand() % 5)
		{
		case NORTH:
			mobCentralFloa[3].y -= 1.5f;
			mobMovedRight[3] = false;
			mobtv[3] = 1;
			break;
		case SOUTH:
			mobCentralFloa[3].y += 1.5f;
			mobMovedRight[3] = false;
			mobtv[3] = 0;
			break;
		case EAST:
			mobCentralFloa[3].x -= 2;
			mobMovedRight[3] = false;
			mobtv[3] = 2;
			break;
		case WEST:
			mobCentralFloa[3].x += 2;
			mobMovedRight[3] = true;
			mobtv[3] = 2;
			break;
		default:
			break;
		}
	}
	else
	{
		collisionCount[3]++;
		if (collisionCount[3] > 30)
		{
			mobCentralFloa[3].y += 5;
			mobCentralFloa[3].x += 5;
			collisionCount[3] = 0;
		}
	}

	collision(&mobCentralFloa[1], prevcentral[1]);
	collision(&mobCentralFloa[2], prevcentral[2]);
	collision(&mobCentralFloa[3], prevcentral[3]);

}

void mobToPCContact(CENTRAL_STATE* charctor, CENTRAL_STATE mobCentralFloa[])
{
	for (int i = 0; i < 4; i++)
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

#include "Main.h"
#include "FloaMove.h"
#include "GameMain.h"
#include "Timer.h"

//ヤス子のステータス
CHARACTER_STATE g_yasukoSta = { 1, 1.5f, 1 };

//ミツ子のステータス
CHARACTER_STATE g_mitukoSta = { 2, 1.5f, 1.25 };

//イソ子のステータス
CHARACTER_STATE g_isokoSta = { 2, 2.f, 1 };

CENTRAL_STATE g_PCSta = { 900.f, 580.f, 32.f, 53.f };
CENTRAL_STATE g_startCountSta = { 520.f, 350.f, 150.f, 150.f };
CENTRAL_STATE g_startSta = { 520.f, 350.f, 200.f, 96.25f };

FLOAT g_PCSpeed = 0.f;

//ゲーム制御処理
VOID floaMoveControl(VOID)
{
	static int onceSound = 0;

	timerControl();

	if (g_isTimeUp)
	{
		for (onceSound; onceSound < 2; onceSound++)
		{
			soundsManager.Start("GONG", false);
		}
	}

	if (g_isGameStart)
	{
		GetControl(0);
		BottonCheck();

		for (onceSound; onceSound < 1; onceSound++)
		{
			soundsManager.SetVolume("FOOD", 25);
			soundsManager.Start("FOOD", true);
			soundsManager.Start("WHISYLE", false);
		}

	if (g_Xinput.Gamepad.wButtons == 0)
	{
		g_inCount = 0;
	}
	else if (g_inCount)
	{
		g_inCount++;
	}

	if (InputKEY(DIK_RETURN) || (PadState[ButtonA] == PadRelease )&& !(g_inCount))
	{
		if (g_pause && !g_isTimeUp)
		{
			onceSound = 0;
			PostQuitMessage(0);
			g_inCount++;
		}

		if (g_isTimeUp)
		{
			onceSound = 0;
			PostQuitMessage(0);
			g_inCount++;
		}
	}

	if (InputKEY(DIK_W)|| GetAnalogLValue(ANALOG_Y))
			{
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
				}
			}

	if (InputKEY(DIK_S)|| GetAnalogLValue(ANALOG_Y))
			{
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
				}
			}

	if (InputKEY(DIK_D)|| GetAnalogLValue(ANALOG_X))
			{
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
				}
			}

	if (InputKEY(DIK_A)|| GetAnalogLValue(ANALOG_X))
			{
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
		collision();
	}
	CheckKeyState(DIK_SPACE);
	if (KeyState[DIK_SPACE] == KeyRelease)
	{
		g_gameScene = PUSHENEMY;
	}

}

//当たり判定処理
VOID collision(VOID)
{
	if (g_PCSta.x <= 40.f)
	{
		g_PCSta.x = 40.f;
	}

	if (g_PCSta.x >= 1230.f)
	{
		g_PCSta.x = 1230.f;
	}

	if (g_PCSta.y <= 165.f)
	{
		g_PCSta.y = 165.f;
	}

	if (g_PCSta.y >= 645.f)
	{
		g_PCSta.y = 645.f;
	}
}

//ゲーム描画処理
VOID floaMoveRender(VOID)
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
VOID floaMoveRenderSta(VOID)
{
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, FLOAMOVE_BG_TEX);

	CUSTOMVERTEX PC[4];
	CUSTOMVERTEX startCount[4];
	CUSTOMVERTEX start[4];

	CreateSquareVertex(PC,g_PCSta);
	CreateSquareVertex(startCount,g_startCountSta);
	CreateSquareVertex(start, g_startSta);

	//プレイヤーキャラクターのテクスチャの描画
	SetUpTexture(PC, texturePC);

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

	timerRender();
}
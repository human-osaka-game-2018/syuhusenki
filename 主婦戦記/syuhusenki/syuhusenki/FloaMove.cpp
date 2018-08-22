#include "Main.h"
#include "FloaMove.h"
#include "GameMain.h"

//ヤス子のステータス
CHARACTER_STATE g_yasukoSta = { 1.f, 3.f, 1.f };

//ミツ子のステータス
CHARACTER_STATE g_mitukoSta = { 2.f, 3.f, 1.25 };

//イソ子のステータス
CHARACTER_STATE g_isokoSta = { 2.f, 4.f, 1.f };

CENTRAL_STATE g_PCSta = { 1400.f, 900.f, 80.f, 80.f };
CENTRAL_STATE g_timerSta = { 1710.f, 815.f, 200.f, 200.f };
CENTRAL_STATE g_startCountSta = { 750.f, 500.f, 300.f, 300.f };
CENTRAL_STATE g_startSta = { 750.f, 500.f, 400.f, 192.5 };
CENTRAL_STATE g_timeUpSta = { 750.f, 500.f, 520.f, 200.f };

FLOAT g_PCSpeed = 0.f;

int g_gameCount = 0;

//ゲーム制御処理
VOID floaMoveControl(VOID)
{
	static int onceSound = 0;

	if (g_gameCount < 10980)
	{
		g_gameCount++;
	}

	if (g_gameCount == 180)
	{
		g_isGameStart = true;
	}

	if (g_gameCount == 10980)
	{soundsManager.SetVolume("FOOD", 25);
		soundsManager.Stop("FOOD");
		g_isTimeUp = true;
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
		GetControl(0);
		BottonCheck();
		


		//XInputGetState(0, &g_Xinput);

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

	if (InputKEY(DIK_W)|| g_Xinput.Gamepad.sThumbLY)
			{
				if (!g_pause && !g_isTimeUp)
				{
					if (g_Xinput.Gamepad.sThumbLY >= 6000 && g_Xinput.Gamepad.sThumbLY <= 10000)
					{
						g_PCSta.y -= g_PCSpeed / 4;
					}
					else if (g_Xinput.Gamepad.sThumbLY >= 10000 && g_Xinput.Gamepad.sThumbLY <= 18000)
					{
						g_PCSta.y -= g_PCSpeed / 2;
					}
					else if (g_Xinput.Gamepad.sThumbLY >= 18000)
					{
						g_PCSta.y -= g_PCSpeed;
					}
				}
			}

	if (InputKEY(DIK_S)|| g_Xinput.Gamepad.sThumbLY)
			{
				if (!g_pause && !g_isTimeUp)
				{
					if (g_Xinput.Gamepad.sThumbLY <= -6000 && g_Xinput.Gamepad.sThumbLY >= -10000)
					{
						g_PCSta.y += g_PCSpeed / 4;
					}
					else if (g_Xinput.Gamepad.sThumbLY <= -10000 && g_Xinput.Gamepad.sThumbLY >= -18000)
					{
						g_PCSta.y += g_PCSpeed / 2;
					}
					else if (g_Xinput.Gamepad.sThumbLY <= -18000)
					{
						g_PCSta.y += g_PCSpeed;
					}
				}
			}

	if (InputKEY(DIK_D)|| g_Xinput.Gamepad.sThumbLX)
			{
				if (!g_pause && !g_isTimeUp)
				{
					if (g_Xinput.Gamepad.sThumbLX >= 6000 && g_Xinput.Gamepad.sThumbLX <= 10000)
					{
						g_PCSta.x += g_PCSpeed / 4;
					}
					else if (g_Xinput.Gamepad.sThumbLX >= 10000 && g_Xinput.Gamepad.sThumbLX <= 18000)
					{
						g_PCSta.x += g_PCSpeed / 2;
					}
					else if (g_Xinput.Gamepad.sThumbLX >= 18000)
					{
						g_PCSta.x += g_PCSpeed;
					}
				}
			}

	if (InputKEY(DIK_A)|| g_Xinput.Gamepad.sThumbLX)
			{
				if (!g_pause && !g_isTimeUp)
				{
					if (g_Xinput.Gamepad.sThumbLX <= -6000 && g_Xinput.Gamepad.sThumbLX >= -10000)
					{
						g_PCSta.x -= g_PCSpeed / 4;
					}
					else if (g_Xinput.Gamepad.sThumbLX <= -10000 && g_Xinput.Gamepad.sThumbLX >= -18000)
					{
						g_PCSta.x -= g_PCSpeed / 2;
					}
					else if (g_Xinput.Gamepad.sThumbLX <= -18000)
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
	if (g_PCSta.x <= 80)
	{
		g_PCSta.x = 80;
	}

	if (g_PCSta.x >= 1455)
	{
		g_PCSta.x = 1455;
	}

	if (g_PCSta.y <= 130)
	{
		g_PCSta.y = 130;
	}

	if (g_PCSta.y >= 900)
	{
		g_PCSta.y = 900;
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
	WriteWord(debugPC, DEBUGTextA, DT_LEFT, 0xffffff00, DEBUG_FONT);
	sprintf_s(debugPC, 10, "%.2f", g_PCSta.y);
	DEBUGTextA = { 100 ,550,900,600 };
	WriteWord(debugPC, DEBUGTextA, DT_LEFT, 0xffffff00, DEBUG_FONT);

#endif

	EndSetTexture();
}

//ゲーム画面のテクスチャ
VOID floaMoveRenderSta(VOID)
{
	static float timerRotation = 0.f;
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, GAME_BG_TEX);

	CUSTOMVERTEX timer[4];
	CUSTOMVERTEX timerHand[4];
	CUSTOMVERTEX PC[4];
	CUSTOMVERTEX startCount[4];
	CUSTOMVERTEX start[4];
	CUSTOMVERTEX timeUp[4];

	CreateSquareVertex(timer,g_timerSta);
	CreateSquareVertex(timerHand,g_timerSta);
	CreateSquareVertex(PC,g_PCSta);
	CreateSquareVertex(startCount,g_startCountSta);
	CreateSquareVertex(start, g_startSta);
	CreateSquareVertex(timeUp, g_timeUpSta);

	//回転
	RevolveZ(timerHand, timerRotation, g_timerSta);


	//タイマーのテクスチャの描画
	SetUpTexture(timer, TIMER_FRAME_TEX);

	//タイマーのテクスチャの描画
	SetUpTexture(timerHand, TIMER_HAND_TEX);

	//プレイヤーキャラクターのテクスチャの描画
	SetUpTexture(PC, PC_TEX);

	if ((g_gameCount > 0) && (g_gameCount <= 60))
	{
		//スタートカウントのテクスチャの描画
		SetUpTexture(startCount, STARTCOUNT_3_TEX);
	}
	else if ((g_gameCount > 60) && (g_gameCount <= 120))
	{
		//スタートカウントのテクスチャの描画
		SetUpTexture(startCount, STARTCOUNT_2_TEX);
	}
	else if ((g_gameCount > 120) && (g_gameCount <= 180))
	{
		//スタートカウントのテクスチャの描画
		SetUpTexture(startCount, STARTCOUNT_1_TEX);
	}
	else if ((g_gameCount > 180) && (g_gameCount <= 240))
	{
		//スタートカウントのテクスチャの描画
		SetUpTexture(start, START_TEX);
	}

	if (g_gameCount >= 180 && !g_isTimeUp)
	{
		timerRotation += -0.001744;
	}

	if (g_pause && !(g_isTimeUp))
	{
		EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, PAUSE_TEX);
	}

	if (g_isTimeUp)
	{
		//タイムアップのテクスチャの描画
		SetUpTexture(timeUp, TIMEUP_TEX);
	}

}
#include "Main.h"
#include "FloaMove.h"

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
	{
		soundsManager.Stop("Sound/gameBGM.wav");
		g_isTimeUp = true;
	}

	if (g_isTimeUp)
	{
		for (onceSound; onceSound < 2; onceSound++)
		{
			soundsManager.Start("Sound/gong.wav", false);
		}
	}

	if (g_isGameStart)
	{

		HRESULT hr;

		XInputGetState(0, &g_Xinput);

		for (onceSound; onceSound < 1; onceSound++)
		{
			soundsManager.Start("Sound/gameBGM.wav", true);
			soundsManager.Start("Sound/gameStartSE.wav", false);
		}

		hr = g_pKeyDevice->Acquire();

		if ((hr == DI_OK) || (hr == S_FALSE))
		{
			BYTE diks[256];
			g_pKeyDevice->GetDeviceState(sizeof(diks), &diks);

			if (g_Xinput.Gamepad.wButtons == 0)
			{
				g_inCount = 0;
			}
			else if (g_inCount)
			{
				g_inCount++;
			}

			if (diks[DIK_RETURN] & 0x80 || g_Xinput.Gamepad.wButtons == A_BUTTON && !(g_inCount))
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

			if (diks[DIK_W] & 0x80 || g_Xinput.Gamepad.sThumbLY)
			{
				if (!g_pause && !g_isTimeUp)
				{
					if (g_Xinput.Gamepad.sThumbLY >= 6000 && g_Xinput.Gamepad.sThumbLY <= 10000)
					{
						g_PCSta.y -= g_yasukoSta.speed / 4;
					}
					else if (g_Xinput.Gamepad.sThumbLY >= 10000 && g_Xinput.Gamepad.sThumbLY <= 18000)
					{
						g_PCSta.y -= g_yasukoSta.speed / 2;
					}
					else if (g_Xinput.Gamepad.sThumbLY >= 18000)
					{
						g_PCSta.y -= g_yasukoSta.speed;
					}
				}
			}

			if (diks[DIK_S] & 0x80 || g_Xinput.Gamepad.sThumbLY)
			{
				if (!g_pause && !g_isTimeUp)
				{
					if (g_Xinput.Gamepad.sThumbLY <= -6000 && g_Xinput.Gamepad.sThumbLY >= -10000)
					{
						g_PCSta.y += g_yasukoSta.speed / 4;
					}
					else if (g_Xinput.Gamepad.sThumbLY <= -10000 && g_Xinput.Gamepad.sThumbLY >= -18000)
					{
						g_PCSta.y += g_yasukoSta.speed / 2;
					}
					else if (g_Xinput.Gamepad.sThumbLY <= -18000)
					{
						g_PCSta.y += g_yasukoSta.speed;
					}
				}
			}

			if (diks[DIK_D] & 0x80 || g_Xinput.Gamepad.sThumbLX)
			{
				if (!g_pause && !g_isTimeUp)
				{
					if (g_Xinput.Gamepad.sThumbLX >= 6000 && g_Xinput.Gamepad.sThumbLX <= 10000)
					{
						g_PCSta.x += g_yasukoSta.speed / 4;
					}
					else if (g_Xinput.Gamepad.sThumbLX >= 10000 && g_Xinput.Gamepad.sThumbLX <= 18000)
					{
						g_PCSta.x += g_yasukoSta.speed / 2;
					}
					else if (g_Xinput.Gamepad.sThumbLX >= 18000)
					{
						g_PCSta.x += g_yasukoSta.speed;
					}
				}
			}

			if (diks[DIK_A] & 0x80 || g_Xinput.Gamepad.sThumbLX)
			{
				if (!g_pause && !g_isTimeUp)
				{
					if (g_Xinput.Gamepad.sThumbLX <= -6000 && g_Xinput.Gamepad.sThumbLX >= -10000)
					{
						g_PCSta.x -= g_yasukoSta.speed / 4;
					}
					else if (g_Xinput.Gamepad.sThumbLX <= -10000 && g_Xinput.Gamepad.sThumbLX >= -18000)
					{
						g_PCSta.x -= g_yasukoSta.speed / 2;
					}
					else if (g_Xinput.Gamepad.sThumbLX <= -18000)
					{
						g_PCSta.x -= g_yasukoSta.speed;
					}
				}
			}

			if (diks[DIK_ESCAPE] & 0x80 || g_Xinput.Gamepad.wButtons == START_BUTTOM && !(g_inCount))
			{
				if (g_pause && !g_isTimeUp)
				{
					soundsManager.Start("Sound/button.wav", false);
					g_pause = false;
					g_inCount++;
				}
				else if (!g_pause && !g_isTimeUp)
				{
					soundsManager.Start("Sound/button.wav", false);
					g_pause = true;
					g_inCount++;
				}
			}
		}
		collision();
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
VOID gameRender(VOID)
{
	//画面の消去
	g_pD3Device->Clear(0, NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0x00, 0x00, 0x00),
		1.0f, 0);

	//描画の開始
	g_pD3Device->BeginScene();

	//ゲーム画面のテクスチャの設定
	floaMoveRenderSta();

	//描画の終了
	g_pD3Device->EndScene();

	//表示
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}

//ゲーム画面のテクスチャ
VOID gameRenderSta(VOID)
{
	static float timerRotation = 0.f;

	//頂点情報の設定
	CUSTOMVERTEX gameBG[4]
	{
		{ 0.f,    0.f, 1.f, 1.f, 0xFFFFFFF, 0.f, 0.f },
	{ 1920.f,    0.f, 1.f, 1.f, 0xFFFFFFF, 1.f, 0.f },
	{ 1920.f, 1080.f, 1.f, 1.f, 0xFFFFFFF, 1.f, 1.f },
	{ 0.f, 1080.f, 1.f, 1.f, 0xFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX timer[4]
	{
		{ g_timerSta.x - g_timerSta.scaleX, g_timerSta.y - g_timerSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_timerSta.x + g_timerSta.scaleX, g_timerSta.y - g_timerSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_timerSta.x + g_timerSta.scaleX, g_timerSta.y + g_timerSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_timerSta.x - g_timerSta.scaleX, g_timerSta.y + g_timerSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX timerHand[4]
	{
		{ g_timerSta.x - g_timerSta.scaleX, g_timerSta.y - g_timerSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_timerSta.x + g_timerSta.scaleX, g_timerSta.y - g_timerSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_timerSta.x + g_timerSta.scaleX, g_timerSta.y + g_timerSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_timerSta.x - g_timerSta.scaleX, g_timerSta.y + g_timerSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX PC[4]
	{
		{ g_PCSta.x - g_PCSta.scaleX, g_PCSta.y - g_PCSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_PCSta.x + g_PCSta.scaleX, g_PCSta.y - g_PCSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_PCSta.x + g_PCSta.scaleX, g_PCSta.y + g_PCSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_PCSta.x - g_PCSta.scaleX, g_PCSta.y + g_PCSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX startCount[4]
	{
		{ g_startCountSta.x - g_startCountSta.scaleX, g_startCountSta.y - g_startCountSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_startCountSta.x + g_startCountSta.scaleX, g_startCountSta.y - g_startCountSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_startCountSta.x + g_startCountSta.scaleX, g_startCountSta.y + g_startCountSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_startCountSta.x - g_startCountSta.scaleX, g_startCountSta.y + g_startCountSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX start[4]
	{
		{ g_startSta.x - g_startSta.scaleX, g_startSta.y - g_startSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_startSta.x + g_startSta.scaleX, g_startSta.y - g_startSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_startSta.x + g_startSta.scaleX, g_startSta.y + g_startSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_startSta.x - g_startSta.scaleX, g_startSta.y + g_startSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX pauseMenu[4]
	{
		{ 0.f,    0.f, 1.f, 1.f, 0xFFFFFFF, 0.f, 0.f },
	{ 1920.f,    0.f, 1.f, 1.f, 0xFFFFFFF, 1.f, 0.f },
	{ 1920.f, 1080.f, 1.f, 1.f, 0xFFFFFFF, 1.f, 1.f },
	{ 0.f, 1080.f, 1.f, 1.f, 0xFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX timeUp[4]
	{
		{ g_timeUpSta.x - g_timeUpSta.scaleX, g_timeUpSta.y - g_timeUpSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_timeUpSta.x + g_timeUpSta.scaleX, g_timeUpSta.y - g_timeUpSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_timeUpSta.x + g_timeUpSta.scaleX, g_timeUpSta.y + g_timeUpSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_timeUpSta.x - g_timeUpSta.scaleX, g_timeUpSta.y + g_timeUpSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	//回転
	RevolveZ(timerHand, timerRotation, g_timerSta);

	//ゲーム背景のテクスチャの描画
	g_pD3Device->SetTexture(0, g_pTexture[GAME_BG_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, gameBG, sizeof(CUSTOMVERTEX));

	//タイマーのテクスチャの描画
	g_pD3Device->SetTexture(0, g_pTexture[TIMER_FRAME_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, timer, sizeof(CUSTOMVERTEX));

	//タイマーのテクスチャの描画
	g_pD3Device->SetTexture(0, g_pTexture[TIMER_HAND_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, timerHand, sizeof(CUSTOMVERTEX));

	//プレイヤーキャラクターのテクスチャの描画
	g_pD3Device->SetTexture(0, g_pTexture[PC_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, PC, sizeof(CUSTOMVERTEX));

	if ((g_gameCount > 0) && (g_gameCount <= 60))
	{
		//スタートカウントのテクスチャの描画
		g_pD3Device->SetTexture(0, g_pTexture[STARTCOUNT_3_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, startCount, sizeof(CUSTOMVERTEX));
	}
	else if ((g_gameCount > 60) && (g_gameCount <= 120))
	{
		//スタートカウントのテクスチャの描画
		g_pD3Device->SetTexture(0, g_pTexture[STARTCOUNT_2_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, startCount, sizeof(CUSTOMVERTEX));
	}
	else if ((g_gameCount > 120) && (g_gameCount <= 180))
	{
		//スタートカウントのテクスチャの描画
		g_pD3Device->SetTexture(0, g_pTexture[STARTCOUNT_1_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, startCount, sizeof(CUSTOMVERTEX));
	}
	else if ((g_gameCount > 180) && (g_gameCount <= 240))
	{
		//スタートカウントのテクスチャの描画
		g_pD3Device->SetTexture(0, g_pTexture[START_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, start, sizeof(CUSTOMVERTEX));
	}

	if (g_gameCount >= 180 && !g_isTimeUp)
	{
		timerRotation += -0.001744;
	}

	if (g_pause && !(g_isTimeUp))
	{
		//ポーズ画面のテクスチャの描画
		g_pD3Device->SetTexture(0, g_pTexture[PAUSE_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, pauseMenu, sizeof(CUSTOMVERTEX));
	}

	if (g_isTimeUp)
	{
		//タイムアップのテクスチャの描画
		g_pD3Device->SetTexture(0, g_pTexture[TIMEUP_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, timeUp, sizeof(CUSTOMVERTEX));
	}
}
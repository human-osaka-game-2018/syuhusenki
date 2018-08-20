#include "Main.h"
#include "Select.h"

XINPUT_STATE g_Xinput;

CENTRAL_STATE g_yasukoSta = { 237.f, 270.f, 120.f, 120.f };
CENTRAL_STATE g_mitukoSta = { 525.f, 264.f, 120.f, 120.f };
CENTRAL_STATE g_isokoSta = { 817.f, 264.f, 120.f, 120.f };
CENTRAL_STATE g_charSelectFrameSta = { 235.f, 265.f, 140.f, 140.f };
CENTRAL_STATE g_stageSelectFrameSta = { 299.f,866.f,200.f,180.f };
CENTRAL_STATE g_selectCharSta = { 1562.5, 430.f, 400.f, 400.f };
CENTRAL_STATE g_lastCheckSta = { 770.f, 590.f,30.f,30.f };

int g_inCount = 0;
int g_gameCount = 0;

bool g_pause = false;
bool g_isGameStart = false;
bool g_isTimeUp = false;
bool g_isNextSelect = false;
bool g_isLastCheck = false;

//セレクト制御処理
VOID selectControl(VOID)
{
	HRESULT hr;

	XInputGetState(0, &g_Xinput);

	hr = g_pKeyDevice->Acquire();

	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		g_pKeyDevice->GetDeviceState(sizeof(diks), &diks);

		if (g_Xinput.Gamepad.wButtons == 0 && g_Xinput.Gamepad.sThumbLX <= 6000 && g_Xinput.Gamepad.sThumbLX >= -6000)
		{
			g_inCount = 0;
		}
		else if (g_inCount)
		{
			g_inCount++;
		}

		if (g_Xinput.Gamepad.wButtons == A_BUTTON && !(g_inCount))
		{
			if (g_isNextSelect && g_isLastCheck && g_lastCheckSta.y == 490.f)
			{
				soundsManager.Start("Sound/button.wav", false);
				g_isNextSelect = false;
				g_isLastCheck = false;
				g_scene = SCENE_MAIN;
			}
			else if (g_isNextSelect && g_isLastCheck && g_lastCheckSta.y == 590.f)
			{
				soundsManager.Start("Sound/button.wav", false);
				g_isNextSelect = false;
				g_isLastCheck = false;
				g_inCount++;
			}

			else if (g_stageSelectFrameSta.x == 299.f && g_isNextSelect && !(g_isLastCheck))
			{
				soundsManager.Start("Sound/button.wav", false);
				soundsManager.Stop("Sound/selectBGM.wav");
				g_isLastCheck = true;
				g_inCount++;
			}
			else if (g_stageSelectFrameSta.x == 745.f && g_isNextSelect && !(g_isLastCheck))
			{
				soundsManager.Start("Sound/missTake.wav", false);
				g_inCount++;
			}

			else if (g_charSelectFrameSta.x == 235.f && !(g_isNextSelect) && !(g_isLastCheck))
			{
				soundsManager.Start("Sound/button.wav", false);
				g_isNextSelect = true;
				g_inCount++;
			}
			else if (g_charSelectFrameSta.x == 525.f && !(g_isNextSelect) && !(g_isLastCheck))
			{
				soundsManager.Start("Sound/missTake.wav", false);
				g_inCount++;
			}
			else if (g_charSelectFrameSta.x == 817.f && !(g_isNextSelect) && !(g_isLastCheck))
			{
				soundsManager.Start("Sound/missTake.wav", false);
				g_inCount++;
			}
		}

		if (g_Xinput.Gamepad.wButtons == B_BUTTON && !(g_inCount))
		{
			if (!(g_isNextSelect) && !(g_isLastCheck))
			{
				soundsManager.Stop("Sound/selectBGM.wav");
				soundsManager.Start("Sound/button.wav", false);
				g_scene = SCENE_TITLE;
				g_inCount++;
			}
			if (g_isNextSelect && !(g_isLastCheck))
			{
				soundsManager.Start("Sound/button.wav", false);
				g_isNextSelect = false;
				g_inCount++;
			}
		}

		if (g_Xinput.Gamepad.wButtons == UP_BUTTON && !(g_inCount) || g_Xinput.Gamepad.sThumbLY >= 6000 && !(g_inCount))
		{
			if (g_lastCheckSta.y == 590.f && g_isNextSelect && g_isLastCheck)
			{
				g_lastCheckSta.y = 490.f;
			}
		}

		if (g_Xinput.Gamepad.wButtons == DOWN_BUTTON && !(g_inCount) || g_Xinput.Gamepad.sThumbLY <= -6000 && !(g_inCount))
		{
			if (g_lastCheckSta.y == 490.f && g_isNextSelect && g_isLastCheck)
			{
				g_lastCheckSta.y = 590.f;
			}
		}

		if (g_Xinput.Gamepad.wButtons == RIGHT_BUTTON && !(g_inCount) || g_Xinput.Gamepad.sThumbLX >= 6000 && !(g_inCount))
		{
			if (g_charSelectFrameSta.x == 525.f && !(g_isNextSelect) && !(g_isLastCheck))
			{
				soundsManager.Start("Sound/cursorMove.wav", false);
				g_charSelectFrameSta.x = 817.f;
				g_inCount++;
			}
			else if (g_charSelectFrameSta.x == 235.f && !(g_isNextSelect) && !(g_isLastCheck))
			{
				soundsManager.Start("Sound/cursorMove.wav", false);
				g_charSelectFrameSta.x = 525.f;
				g_inCount++;
			}

			if (g_stageSelectFrameSta.x == 299.f && g_isNextSelect && !(g_isLastCheck))
			{
				soundsManager.Start("Sound/cursorMove.wav", false);
				g_stageSelectFrameSta.x = 745.f;
				g_inCount++;
			}
		}
		else if (g_Xinput.Gamepad.wButtons == LEFT_BUTTON && !(g_inCount) || g_Xinput.Gamepad.sThumbLX <= -6000 && !(g_inCount))
		{
			if (g_charSelectFrameSta.x == 817.f && !(g_isNextSelect) && !(g_isLastCheck))
			{
				soundsManager.Start("Sound/cursorMove.wav", false);
				g_charSelectFrameSta.x = 525.f;
				g_inCount++;
			}
			else if (g_charSelectFrameSta.x == 525.f && !(g_isNextSelect) && !(g_isLastCheck))
			{
				soundsManager.Start("Sound/cursorMove.wav", false);
				g_charSelectFrameSta.x = 235.f;
				g_inCount++;
			}

			if (g_stageSelectFrameSta.x == 745.f && g_isNextSelect && !(g_isLastCheck))
			{
				soundsManager.Start("Sound/cursorMove.wav", false);
				g_stageSelectFrameSta.x = 299.f;
				g_inCount++;
			}
		}
	}
}

//セレクト描画処理
VOID selectRender(VOID)
{
	//画面の消去
	g_pD3Device->Clear(0, NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0x00, 0x00, 0x00),
		1.0f, 0);

	//描画の開始
	g_pD3Device->BeginScene();

	//セレクト画面のテクスチャの設定
	selectRenderSta();

	//描画の終了
	g_pD3Device->EndScene();

	//表示
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}

//セレクト画面のテクスチャ
VOID selectRenderSta(VOID)
{
	//頂点情報の設定
	CUSTOMVERTEX selectBG[4]
	{
		{ 0.f,    0.f, 1.f, 1.f, 0xFFFFFFF, 0.f, 0.f },
	{ 1920.f,    0.f, 1.f, 1.f, 0xFFFFFFF, 1.f, 0.f },
	{ 1920.f, 1080.f, 1.f, 1.f, 0xFFFFFFF, 1.f, 1.f },
	{ 0.f, 1080.f, 1.f, 1.f, 0xFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX yasuko[4]
	{
		{ g_yasukoSta.x - g_yasukoSta.scaleX, g_yasukoSta.y - g_yasukoSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_yasukoSta.x + g_yasukoSta.scaleX, g_yasukoSta.y - g_yasukoSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_yasukoSta.x + g_yasukoSta.scaleX, g_yasukoSta.y + g_yasukoSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_yasukoSta.x - g_yasukoSta.scaleX, g_yasukoSta.y + g_yasukoSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX mituko[4]
	{
		{ g_mitukoSta.x - g_mitukoSta.scaleX, g_mitukoSta.y - g_mitukoSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_mitukoSta.x + g_mitukoSta.scaleX, g_mitukoSta.y - g_mitukoSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_mitukoSta.x + g_mitukoSta.scaleX, g_mitukoSta.y + g_mitukoSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_mitukoSta.x - g_mitukoSta.scaleX, g_mitukoSta.y + g_mitukoSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX isoko[4]
	{
		{ g_isokoSta.x - g_isokoSta.scaleX, g_isokoSta.y - g_isokoSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_isokoSta.x + g_isokoSta.scaleX, g_isokoSta.y - g_isokoSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_isokoSta.x + g_isokoSta.scaleX, g_isokoSta.y + g_isokoSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_isokoSta.x - g_isokoSta.scaleX, g_isokoSta.y + g_isokoSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX frame[4]
	{
		{ g_charSelectFrameSta.x - g_charSelectFrameSta.scaleX, g_charSelectFrameSta.y - g_charSelectFrameSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_charSelectFrameSta.x + g_charSelectFrameSta.scaleX, g_charSelectFrameSta.y - g_charSelectFrameSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_charSelectFrameSta.x + g_charSelectFrameSta.scaleX, g_charSelectFrameSta.y + g_charSelectFrameSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_charSelectFrameSta.x - g_charSelectFrameSta.scaleX, g_charSelectFrameSta.y + g_charSelectFrameSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX selectChar[4]
	{
		{ g_selectCharSta.x - g_selectCharSta.scaleX, g_selectCharSta.y - g_selectCharSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_selectCharSta.x + g_selectCharSta.scaleX, g_selectCharSta.y - g_selectCharSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_selectCharSta.x + g_selectCharSta.scaleX, g_selectCharSta.y + g_selectCharSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_selectCharSta.x - g_selectCharSta.scaleX, g_selectCharSta.y + g_selectCharSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX selectStage[4]
	{
		{ g_stageSelectFrameSta.x - g_stageSelectFrameSta.scaleX, g_stageSelectFrameSta.y - g_stageSelectFrameSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_stageSelectFrameSta.x + g_stageSelectFrameSta.scaleX, g_stageSelectFrameSta.y - g_stageSelectFrameSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_stageSelectFrameSta.x + g_stageSelectFrameSta.scaleX, g_stageSelectFrameSta.y + g_stageSelectFrameSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_stageSelectFrameSta.x - g_stageSelectFrameSta.scaleX, g_stageSelectFrameSta.y + g_stageSelectFrameSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX lastCheck[4]
	{
		{ g_lastCheckSta.x - g_lastCheckSta.scaleX, g_lastCheckSta.y - g_lastCheckSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_lastCheckSta.x + g_lastCheckSta.scaleX, g_lastCheckSta.y - g_lastCheckSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_lastCheckSta.x + g_lastCheckSta.scaleX, g_lastCheckSta.y + g_lastCheckSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_lastCheckSta.x - g_lastCheckSta.scaleX, g_lastCheckSta.y + g_lastCheckSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	//セレクト背景のテクスチャの描画
	g_pD3Device->SetTexture(0, g_pTexture[SELECT_BG_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, selectBG, sizeof(CUSTOMVERTEX));

	//ヤス子のテクスチャの描画
	g_pD3Device->SetTexture(0, g_pTexture[SELECT_YASUKO_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, yasuko, sizeof(CUSTOMVERTEX));

	//ミツ子のテクスチャの描画
	g_pD3Device->SetTexture(0, g_pTexture[SELECT_MITUKO_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, mituko, sizeof(CUSTOMVERTEX));

	//イソ子のテクスチャの描画
	g_pD3Device->SetTexture(0, g_pTexture[SELECT_ISOKO_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, isoko, sizeof(CUSTOMVERTEX));

	//選択の枠のテクスチャの描画
	g_pD3Device->SetTexture(0, g_pTexture[SELECTFRAME_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, frame, sizeof(CUSTOMVERTEX));

	if (g_charSelectFrameSta.x == 235.f)
	{
		g_pD3Device->SetTexture(0, g_pTexture[SELECT_YASUKO_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, selectChar, sizeof(CUSTOMVERTEX));
	}
	else if (g_charSelectFrameSta.x == 525.f)
	{
		g_pD3Device->SetTexture(0, g_pTexture[SELECT_MITUKO_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, selectChar, sizeof(CUSTOMVERTEX));
	}
	else if (g_charSelectFrameSta.x == 817.f)
	{
		g_pD3Device->SetTexture(0, g_pTexture[SELECT_ISOKO_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, selectChar, sizeof(CUSTOMVERTEX));
	}

	//選択の枠のテクスチャの描画
	g_pD3Device->SetTexture(0, g_pTexture[SELECTFRAME_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, selectStage, sizeof(CUSTOMVERTEX));

	if (g_isLastCheck)
	{
		//最終確認画面のテクスチャの描画
		g_pD3Device->SetTexture(0, g_pTexture[SELECTLASTCHECK_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, selectBG, sizeof(CUSTOMVERTEX));

		//最終確認画面の矢印テクスチャの描画
		g_pD3Device->SetTexture(0, g_pTexture[TITLEICON_TEX]);
		g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, lastCheck, sizeof(CUSTOMVERTEX));
	}
}
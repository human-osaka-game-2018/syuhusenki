#include "Main.h"
#include "Title.h"
#include "Select.h"

CENTRAL_STATE g_selectArrowSta = { 500.f, 900.f, 20.f, 20.f };

//タイトル制御処理
VOID titleControl(VOID)
{
	static int BGM = 0;

	HRESULT hr;

	XInputGetState(0, &g_Xinput);

	for (BGM; BGM < 1; BGM++)
	{
		soundsManager.Start("Sound/titleBGM.wav", true);
	}

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

		if (diks[DIK_ESCAPE] & 0x80 && !(g_inCount))
		{
			PostQuitMessage(0);
			g_inCount++;
		}

		if (diks[DIK_A] & 0x80 || g_Xinput.Gamepad.wButtons == LEFT_BUTTON && !(g_inCount) || g_Xinput.Gamepad.sThumbLX <= -6000 && !(g_inCount))
		{
			soundsManager.Start("Sound/cursorMove.wav", false);
			g_selectArrowSta.x = 500;
			g_inCount++;
		}

		if (diks[DIK_D] & 0x80 || g_Xinput.Gamepad.wButtons == RIGHT_BUTTON && !(g_inCount) || g_Xinput.Gamepad.sThumbLX >= 6000 && !(g_inCount))
		{
			soundsManager.Start("Sound/cursorMove.wav", false);
			g_selectArrowSta.x = 1150;
			g_inCount++;
		}

		if (diks[DIK_RETURN] & 0x80 && g_selectArrowSta.x == 500 || g_Xinput.Gamepad.wButtons == A_BUTTON && !(g_inCount) && g_selectArrowSta.x == 500)
		{
			soundsManager.Start("Sound/button.wav", false);
			soundsManager.Stop("Sound/titleBGM.wav");
			soundsManager.Start("Sound/selectBGM.wav", true);
			BGM = 0;
			g_scene = SCENE_SERECTCHARANDSTAGE;
			g_inCount++;
		}

		if (diks[DIK_RETURN] & 0x80 && g_selectArrowSta.x == 1150 || g_Xinput.Gamepad.wButtons == A_BUTTON && g_selectArrowSta.x == 1150)
		{
			PostQuitMessage(0);
		}
	}
}

//タイトル描画処理
VOID titleRender(VOID)
{
	//画面の消去
	g_pD3Device->Clear(0, NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0x00, 0x00, 0x00),
		1.0f, 0);

	//描画の開始
	g_pD3Device->BeginScene();

	//タイトル画面のテクスチャの設定
	titleRenderSta();

	//描画の終了
	g_pD3Device->EndScene();

	//表示
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}

//タイトル画面のテクスチャ
VOID titleRenderSta(VOID)
{
	//頂点情報の設定
	CUSTOMVERTEX titleBG[4]
	{
		{ 0.f,    0.f, 1.f, 1.f, 0xFFFFFFF, 0.f, 0.f },
	{ 1920.f,    0.f, 1.f, 1.f, 0xFFFFFFF, 1.f, 0.f },
	{ 1920.f, 1080.f, 1.f, 1.f, 0xFFFFFFF, 1.f, 1.f },
	{ 0.f, 1080.f, 1.f, 1.f, 0xFFFFFFF, 0.f, 1.f }
	};

	CUSTOMVERTEX selectArrow[4]
	{
		{ g_selectArrowSta.x - g_selectArrowSta.scaleX, g_selectArrowSta.y - g_selectArrowSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ g_selectArrowSta.x + g_selectArrowSta.scaleX, g_selectArrowSta.y - g_selectArrowSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ g_selectArrowSta.x + g_selectArrowSta.scaleX, g_selectArrowSta.y + g_selectArrowSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ g_selectArrowSta.x - g_selectArrowSta.scaleX, g_selectArrowSta.y + g_selectArrowSta.scaleY, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	//タイトル背景のテクスチャの描画
	g_pD3Device->SetTexture(0, g_pTexture[TITLE_BG_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, titleBG, sizeof(CUSTOMVERTEX));

	//タイトル矢印テクスチャの生成
	g_pD3Device->SetTexture(0, g_pTexture[TITLEICON_TEX]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, selectArrow, sizeof(CUSTOMVERTEX));
}
#include "Main.h"
#include "Title.h"

CENTRAL_STATE g_selectArrowSta = { 500.f, 900.f, 20.f, 20.f };

//タイトル制御処理
VOID titleControl(VOID)
{
	static int BGM = 0;

	GetControl(0);
	BottonCheck();

	

	for (BGM; BGM < 1; BGM++)
	{
		soundsManager.Start("OP_BGM", true);
	}



		if (g_Xinput.Gamepad.wButtons == 0 && g_Xinput.Gamepad.sThumbLX <= 6000 && g_Xinput.Gamepad.sThumbLX >= -6000)
		{
			g_inCount = 0;
		}
		else if (g_inCount)
		{
			g_inCount++;
		}

		if (InputKEY(DIK_ESCAPE) && !(g_inCount))
		{
			PostQuitMessage(0);
			g_inCount++;
		}

		if (InputKEY(DIK_A)||PadState[ButtonLEFT] && !(g_inCount) || g_Xinput.Gamepad.sThumbLX <= -6000 && !(g_inCount))
		{
			soundsManager.Start("CURSOR", false);
			g_selectArrowSta.x = 500;
			g_inCount++;
		}

		if (InputKEY(DIK_D)||PadState[ButtonRIGHT]&& !(g_inCount) || g_Xinput.Gamepad.sThumbLX >= 6000 && !(g_inCount))
		{
			soundsManager.Start("CURSOR", false);
			g_selectArrowSta.x = 1150;
			g_inCount++;
		}

		if (InputKEY(DIK_RETURN)&& g_selectArrowSta.x == 500 ||PadState[ButtonA] && !(g_inCount) && g_selectArrowSta.x == 500)
		{
			soundsManager.Start("BUTTON1", false);
			soundsManager.Stop("OP_BGM");
			soundsManager.Start("SELECT_BGM", true);
			BGM = 0;
			g_scene = SCENE_SERECTCHARANDSTAGE;
			g_inCount++;
		}

		if (InputKEY(DIK_RETURN)&& g_selectArrowSta.x == 1150 ||PadState[ButtonA]&& g_selectArrowSta.x == 1150)
		{
			PostQuitMessage(0);
		}
}

//タイトル描画処理
VOID titleRender(VOID)
{
	BeginSetTexture();

	//タイトル画面のテクスチャの設定
	titleRenderSta();

	EndSetTexture();
}

//タイトル画面のテクスチャ
VOID titleRenderSta(VOID)
{
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, TITLE_BG_TEX);

	CUSTOMVERTEX selectArrow[4];
	CreateSquareVertex(selectArrow, g_selectArrowSta);

	//タイトル矢印テクスチャの生成
	SetUpTexture(selectArrow, TITLEICON_TEX);
}
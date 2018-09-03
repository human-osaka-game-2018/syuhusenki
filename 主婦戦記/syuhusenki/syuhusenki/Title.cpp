#include "Main.h"
#include "Title.h"

CENTRAL_STATE g_selectArrowSta = { 330.f, 600.f, 20.f, 20.f };

//タイトル制御処理
VOID titleControl(VOID)
{
	static int sceneSuccession = 0;
	static int BGM = 0;
	GetControl(0);
	BottonCheck();
	static bool entry[2] = { false,false };

	for (BGM; BGM < 1; BGM++)
	{
		g_SoundSuccess = soundsManager.SetVolume("OP_BGM", 50) && g_SoundSuccess;
		g_SoundSuccess = soundsManager.Start("OP_BGM", true) && g_SoundSuccess;
	}

	if (g_Xinput.Gamepad.wButtons == 0 && GetAnalogLValue(ANALOG_X) <= 6000 && GetAnalogLValue(ANALOG_X) >= -6000)
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

	if (InputKEY(DIK_A) || PadState[ButtonLEFT] == PadOn && !(g_inCount) || GetAnalogLValue(ANALOG_X) <= -6000 && !(g_inCount))
	{
		g_SoundSuccess = soundsManager.Start("CURSOR", false) && g_SoundSuccess;
		g_selectArrowSta.x = ARROWRIGHT;
		g_inCount++;
	}

	if (InputKEY(DIK_D) || PadState[ButtonRIGHT] == PadOn && !(g_inCount) || GetAnalogLValue(ANALOG_X) >= 6000 && !(g_inCount))
	{
		g_SoundSuccess = soundsManager.Start("CURSOR", false) && g_SoundSuccess;
		g_selectArrowSta.x = ARROWLEFT;
		g_inCount++;
	}
	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_NUMPADENTER);

	if ((KeyState[DIK_RETURN] == KeyRelease || KeyState[DIK_NUMPADENTER] == KeyRelease) && g_selectArrowSta.x == ARROWRIGHT ||PadState[ButtonA] == PadOn && !(g_inCount) && g_selectArrowSta.x == ARROWRIGHT &&(!entry[0]))
	{
		g_SoundSuccess = soundsManager.Start("GREETING", false) && g_SoundSuccess;
		g_SoundSuccess = soundsManager.Start("BUTTON1", false) && g_SoundSuccess;
		g_SoundSuccess = soundsManager.Stop("OP_BGM") && g_SoundSuccess;
		BGM = 0;
		entry[0] = true;
		//g_scene = SCENE_SERECTCHARANDSTAGE;
		g_inCount++;

	}

	if ((KeyState[DIK_RETURN] == KeyRelease || KeyState[DIK_NUMPADENTER] == KeyRelease) && g_selectArrowSta.x == ARROWLEFT ||PadState[ButtonA] == PadOn && g_selectArrowSta.x == ARROWLEFT)
	{
		g_SoundSuccess = soundsManager.Start("BOW", false) && g_SoundSuccess;
		entry[1] = true;
	}

	if (entry[0])
	{
		sceneSuccession++;
		if ((sceneSuccession >= 70) && entry[0])
		{
			//soundsManager.SetVolume("SELECT_BGM", 25);
			//soundsManager.Start("SELECT_BGM", true);
			g_scene = SCENE_MAIN;
			sceneSuccession = 0;
			entry[0] = false;
		}

	}
	if (entry[1])
	{
		sceneSuccession++;

		if ((sceneSuccession >= 170) && entry[1])
		{
			PostQuitMessage(0);
		}

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
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BG_TITLE_TEX);

	CUSTOMVERTEX selectArrow[4];
	CreateSquareVertex(selectArrow, g_selectArrowSta);

	//タイトル矢印テクスチャの生成
	SetUpTexture(selectArrow, TITLEICON_TEX);
}
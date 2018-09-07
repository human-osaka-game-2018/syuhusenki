#include "Main.h"
#include "Title.h"
#include "GameMain.h"

CENTRAL_STATE g_selectArrowSta = { 500.f, ARROWHIGH, 20.f, 20.f };
static int wisdomTex = WISDOM1_TEX;
//タイトル制御処理
void titleControl(void)
{
	static int sceneSuccession = 0;
	static int BGM = 0;
	GetControl(0);
	BottonCheck();
	static bool entry[2] = { false,false };
	CheckKeyState(DIK_W);
	CheckKeyState(DIK_S);

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

	if (KeyState[DIK_W] == KeyRelease || PadState[ButtonUP] == PadRelease && !(g_inCount) || GetAnalogLValue(ANALOG_Y) <= -6000 && !(g_inCount))
	{
		if (g_selectArrowSta.y == ARROWMIDLE)
		{

			g_SoundSuccess = soundsManager.Start("CURSOR", false) && g_SoundSuccess;
			g_selectArrowSta.y = ARROWHIGH;
			g_inCount++;
		}
		if (g_selectArrowSta.y == ARROWDOWN)
		{
			g_SoundSuccess = soundsManager.Start("CURSOR", false) && g_SoundSuccess;
			g_selectArrowSta.y = ARROWMIDLE;
			g_inCount++;
		}

	}

	if (KeyState[DIK_S] == KeyRelease || PadState[ButtonDOWN] == PadRelease && !(g_inCount) || GetAnalogLValue(ANALOG_Y) >= 6000 && !(g_inCount))
	{
		if (g_selectArrowSta.y == ARROWMIDLE)
		{
			g_SoundSuccess = soundsManager.Start("CURSOR", false) && g_SoundSuccess;
			g_selectArrowSta.y = ARROWDOWN;
			g_inCount++;
		}
		if (g_selectArrowSta.y == ARROWHIGH)
		{
			g_SoundSuccess = soundsManager.Start("CURSOR", false) && g_SoundSuccess;
			g_selectArrowSta.y = ARROWMIDLE;
			g_inCount++;
		}

	}
	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_NUMPADENTER);

	if ((KeyState[DIK_RETURN] == KeyRelease || KeyState[DIK_NUMPADENTER] == KeyRelease) && g_selectArrowSta.y == ARROWHIGH ||PadState[ButtonA] == PadOn && !(g_inCount) && g_selectArrowSta.y == ARROWHIGH &&(!entry[0]))
	{
		g_SoundSuccess = soundsManager.Start("GREETING", false) && g_SoundSuccess;
		g_SoundSuccess = soundsManager.Start("BUTTON1", false) && g_SoundSuccess;
		g_SoundSuccess = soundsManager.Stop("OP_BGM") && g_SoundSuccess;
		BGM = 0;
		entry[0] = true;
		//g_scene = SCENE_SERECTCHARANDSTAGE;
		g_inCount++;

	}

	if ((KeyState[DIK_RETURN] == KeyRelease || KeyState[DIK_NUMPADENTER] == KeyRelease) && g_selectArrowSta.y == ARROWMIDLE ||PadState[ButtonA] == PadOn && g_selectArrowSta.y == ARROWMIDLE)
	{
		g_SoundSuccess = soundsManager.Start("BOW", false) && g_SoundSuccess;
		entry[1] = true;
	}
	if ((KeyState[DIK_RETURN] == KeyRelease || KeyState[DIK_NUMPADENTER] == KeyRelease) && g_selectArrowSta.y == ARROWDOWN || PadState[ButtonA] == PadOn && g_selectArrowSta.y == ARROWDOWN)
	{
		g_titleScene = WISDOM;
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
void titleRender(void)
{
	BeginSetTexture();

	//タイトル画面のテクスチャの設定
	titleRenderSta();

	EndSetTexture();
}

//タイトル画面のテクスチャ
void titleRenderSta(void)
{
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BG_TITLE_TEX);

	CUSTOMVERTEX selectArrow[4];
	CreateSquareVertexColor(selectArrow, g_selectArrowSta, g_cursolColor);

	//タイトル矢印テクスチャの生成
	SetUpTexture(selectArrow, TITLEICON_TEX);
}

void wisdomControl()
{
	static int wisdomPage = PAGE1;
	GetControl(0);
	BottonCheck();

	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_NUMPADENTER);

	if (KeyState[DIK_RETURN] == KeyRelease || KeyState[DIK_NUMPADENTER] == KeyRelease|| PadState[ButtonA] == PadRelease)
	{
		switch (wisdomPage)
		{
		case PAGE1:
			wisdomTex = WISDOM2_TEX;
			wisdomPage = PAGE2;
			break;
		case PAGE2:
			wisdomTex = WISDOM3_TEX;
			wisdomPage = PAGE3;
			break;
		case PAGE3:
			wisdomTex = WISDOM1_TEX;
			wisdomPage = PAGE1;
			g_titleScene = TITLE;
			break;
		}

	}

}

void wisdomRender()
{
	BeginSetTexture();

	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, wisdomTex);

	showPressA();

	EndSetTexture();

}
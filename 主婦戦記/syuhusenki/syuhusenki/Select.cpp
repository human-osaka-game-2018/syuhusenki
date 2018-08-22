#include "Main.h"
#include "Select.h"

CENTRAL_STATE g_yasukoTexSta = { 226.4f, 177.f, 52.f, 73.f };
CENTRAL_STATE g_mitukoTexSta = { 419.5f, 180.f, 52.f, 73.f };
CENTRAL_STATE g_isokoTexSta = { 614.7f, 183.f, 52.f, 73.f };
CENTRAL_STATE g_charSelectFrameSta = { 226.4f, 177.f, 90.f, 90.f };
CENTRAL_STATE g_stageSelectFrameSta = { 269.f,480.f,140.f,120.f };
CENTRAL_STATE g_selectCharSta = { 1050.f, 270.f, 230.f, 230.f };
CENTRAL_STATE g_lastCheckSta = { 500.f, 390.f,20.f,20.f };

int g_inCount = 0;

bool g_pause = false;
bool g_isGameStart = false;
bool g_isTimeUp = false;
bool g_isNextSelect = false;
bool g_isLastCheck = false;

//セレクト制御処理
VOID selectControl(VOID)
{
	GetControl(0);
	BottonCheck();

	if (g_Xinput.Gamepad.wButtons == 0 && g_Xinput.Gamepad.sThumbLX <= 6000 && g_Xinput.Gamepad.sThumbLX >= -6000)
	{
		g_inCount = 0;
	}
	else if (g_inCount)
	{
		g_inCount++;
	}

	if (PadState[ButtonA] == PadOn && !(g_inCount))
	{
		//出撃確認の処理
		if (g_isNextSelect && g_isLastCheck && g_lastCheckSta.y == LASTCHECKTOP)
		{
			soundsManager.Start("BUTTON1", false);
			g_isNextSelect = false;
			g_isLastCheck = false;
			g_scene = SCENE_MAIN;
		}
		else if (g_isNextSelect && g_isLastCheck && g_lastCheckSta.y == LASTCHECKBOTTOM)
		{
			soundsManager.Start("BUTTON1", false);
			g_isNextSelect = false;
			g_isLastCheck = false;
			g_inCount++;
		}

		//ステージ選択の処理
		else if (g_stageSelectFrameSta.x == STAGESELECTLEFT && g_isNextSelect && !(g_isLastCheck))
		{
			soundsManager.Start("BUTTON1", false);
			soundsManager.Stop("SELECT");
			g_isLastCheck = true;
			g_inCount++;
		}
		else if (g_stageSelectFrameSta.x == STAGESELECTRIGHT && g_isNextSelect && !(g_isLastCheck))
		{
			soundsManager.Start("MISS", false);
			g_inCount++;
		}

		//キャラ選択の処理
		else if (g_charSelectFrameSta.x == CHARSELECTLEFT && !(g_isNextSelect) && !(g_isLastCheck))
		{
			g_PCSpeed = g_yasukoSta.speed;
			soundsManager.Start("BUTTON1", false);
			g_isNextSelect = true;
			g_inCount++;
		}
		else if (g_charSelectFrameSta.x == CHARSELECTCENTER && !(g_isNextSelect) && !(g_isLastCheck))
		{
			g_PCSpeed = g_mitukoSta.speed;
			soundsManager.Start("BUTTON1", false);
			g_isNextSelect = true;
			g_inCount++;
		}
		else if (g_charSelectFrameSta.x == CHARSELECTRIGHT && !(g_isNextSelect) && !(g_isLastCheck))
		{
			g_PCSpeed = g_isokoSta.speed;
			soundsManager.Start("BUTTON1", false);
			g_isNextSelect = true;
			g_inCount++;
		}
	}
	if (PadState[ButtonB] == PadOn && !(g_inCount))
	{
		//Bボタンを押すとタイトルに戻る処理
		if (!(g_isNextSelect) && !(g_isLastCheck))
		{
			soundsManager.Stop("SELECT");
			soundsManager.Start("BUTTON1", false);
			g_scene = SCENE_TITLE;
			g_inCount++;
		}

		//出撃の最終確認の時のBボタンの処理
		if (g_isNextSelect && !(g_isLastCheck))
		{
			soundsManager.Start("BUTTON1", false);
			g_isNextSelect = false;
			g_inCount++;
		}
	}
	if (PadState[ButtonUP] == PadOn && !(g_inCount))
	{
		if (g_lastCheckSta.y == LASTCHECKBOTTOM && g_isNextSelect && g_isLastCheck)
		{
			soundsManager.Start("CURSOR", false);
			g_lastCheckSta.y = LASTCHECKTOP;
		}
	}
	if (PadState[ButtonDOWN] == PadOn && !(g_inCount))
	{
		if (g_lastCheckSta.y == LASTCHECKTOP && g_isNextSelect && g_isLastCheck)
		{
			soundsManager.Start("CURSOR", false);
			g_lastCheckSta.y = LASTCHECKBOTTOM;
		}
	}
	if (PadState[ButtonRIGHT] == PadOn && !(g_inCount))
	{
		if (g_charSelectFrameSta.x == CHARSELECTCENTER && !(g_isNextSelect) && !(g_isLastCheck))
		{
			soundsManager.Start("CURSOR", false);
			g_charSelectFrameSta.x = CHARSELECTRIGHT;
			g_inCount++;
		}
		else if (g_charSelectFrameSta.x == CHARSELECTLEFT && !(g_isNextSelect) && !(g_isLastCheck))
		{
			soundsManager.Start("CURSOR", false);
			g_charSelectFrameSta.x = CHARSELECTCENTER;
			g_inCount++;
		}

		if (g_stageSelectFrameSta.x == STAGESELECTLEFT && g_isNextSelect && !(g_isLastCheck))
		{
			soundsManager.Start("CURSOR", false);
			g_stageSelectFrameSta.x = STAGESELECTRIGHT;
			g_inCount++;
		}
	}
	if (PadState[ButtonLEFT] == PadOn && !(g_inCount))
	{
		if (g_charSelectFrameSta.x == CHARSELECTRIGHT && !(g_isNextSelect) && !(g_isLastCheck))
		{
			soundsManager.Start("CURSOR", false);
			g_charSelectFrameSta.x = CHARSELECTCENTER;
			g_inCount++;
		}
		else if (g_charSelectFrameSta.x == CHARSELECTCENTER && !(g_isNextSelect) && !(g_isLastCheck))
		{
			soundsManager.Start("CURSOR", false);
			g_charSelectFrameSta.x = CHARSELECTLEFT;
			g_inCount++;
		}

		if (g_stageSelectFrameSta.x == STAGESELECTRIGHT && g_isNextSelect && !(g_isLastCheck))
		{
			soundsManager.Start("CURSOR", false);
			g_stageSelectFrameSta.x = STAGESELECTLEFT;
			g_inCount++;
		}
	}
	
	//左スティックを上に倒したときの処理
	if (g_Xinput.Gamepad.sThumbLY >= 6000 && !(g_inCount))
	{
		if (g_lastCheckSta.y == LASTCHECKBOTTOM && g_isNextSelect && g_isLastCheck)
		{
			soundsManager.Start("CURSOR", false);
			g_lastCheckSta.y = LASTCHECKTOP;
		}
	}

	//左スティックを下に倒したときの処理
	if (g_Xinput.Gamepad.sThumbLY <= -6000 && !(g_inCount))
	{
		if (g_lastCheckSta.y == LASTCHECKTOP && g_isNextSelect && g_isLastCheck)
		{
			soundsManager.Start("CURSOR", false);
			g_lastCheckSta.y = LASTCHECKBOTTOM;
		}
	}

	//左スティックを右に倒した時の処理
	if (g_Xinput.Gamepad.sThumbLX >= 6000 && !(g_inCount))
	{
		//キャラ選択のカーソル移動
		if (g_charSelectFrameSta.x == CHARSELECTCENTER && !(g_isNextSelect) && !(g_isLastCheck))
		{
			soundsManager.Start("CURSOR", false);
			g_charSelectFrameSta.x = CHARSELECTRIGHT;
			g_inCount++;
		}
		else if (g_charSelectFrameSta.x == CHARSELECTLEFT && !(g_isNextSelect) && !(g_isLastCheck))
		{
			soundsManager.Start("CURSOR", false);
			g_charSelectFrameSta.x = CHARSELECTCENTER;
			g_inCount++;
		}

		//ステージ選択のカーソル移動
		if (g_stageSelectFrameSta.x == STAGESELECTLEFT && g_isNextSelect && !(g_isLastCheck))
		{
			soundsManager.Start("CURSOR", false);
			g_stageSelectFrameSta.x = STAGESELECTRIGHT;
			g_inCount++;
		}
	}
	//左スティックを左に倒したときの処理
	else if (g_Xinput.Gamepad.sThumbLX <= -6000 && !(g_inCount))
	{
		//キャラ選択のカーソル移動
		if (g_charSelectFrameSta.x == CHARSELECTRIGHT && !(g_isNextSelect) && !(g_isLastCheck))
		{
			soundsManager.Start("CURSOR", false);
			g_charSelectFrameSta.x = CHARSELECTCENTER;
			g_inCount++;
		}
		else if (g_charSelectFrameSta.x == CHARSELECTCENTER && !(g_isNextSelect) && !(g_isLastCheck))
		{
			soundsManager.Start("CURSOR", false);
			g_charSelectFrameSta.x = CHARSELECTLEFT;
			g_inCount++;
		}

		//ステージ選択のカーソル移動
		if (g_stageSelectFrameSta.x == STAGESELECTRIGHT && g_isNextSelect && !(g_isLastCheck))
		{
			soundsManager.Start("CURSOR", false);
			g_stageSelectFrameSta.x = STAGESELECTLEFT;
			g_inCount++;
		}
	}
	
}

//セレクト描画処理
VOID selectRender(VOID)
{
	BeginSetTexture();

	//セレクト画面のテクスチャの設定
	selectRenderSta();

	EndSetTexture();
}

//セレクト画面のテクスチャ
VOID selectRenderSta(VOID)
{
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BLANK);
	CUSTOMVERTEX yasuko[4];
	CreateSquareVertex(yasuko, g_yasukoTexSta);
	CUSTOMVERTEX mituko[4];
	CreateSquareVertex(mituko, g_mitukoTexSta);
	CUSTOMVERTEX isoko[4];
	CreateSquareVertex(isoko, g_isokoTexSta);
	CUSTOMVERTEX frame[4];
	CreateSquareVertex(frame, g_charSelectFrameSta);
	CUSTOMVERTEX selectChar[4];
	CreateSquareVertex(selectChar, g_selectCharSta);
	CUSTOMVERTEX selectStage[4];
	CreateSquareVertex(selectStage, g_stageSelectFrameSta);
	CUSTOMVERTEX lastCheck[4];
	CreateSquareVertex(lastCheck, g_lastCheckSta);


	//ヤス子のテクスチャの描画
	SetUpTexture(yasuko, SELECT_YASUKO_TEX);
	//ミツ子のテクスチャの描画
	SetUpTexture(mituko, SELECT_MITUKO_TEX);
	//イソ子のテクスチャの描画
	SetUpTexture(isoko, SELECT_ISOKO_TEX);

	//選択の枠のテクスチャの描画
	SetUpTexture(frame, SELECTFRAME_TEX);

	if (g_charSelectFrameSta.x == CHARSELECTLEFT)
	{
		SetUpTexture(selectChar, SELECT_YASUKO_TEX);
	}
	else if (g_charSelectFrameSta.x == CHARSELECTCENTER)
	{
		SetUpTexture(selectChar, SELECT_MITUKO_TEX);
	}
	else if (g_charSelectFrameSta.x == CHARSELECTRIGHT)
	{
		SetUpTexture(selectChar, SELECT_ISOKO_TEX);
	}

	//選択の枠のテクスチャの描画
	SetUpTexture(selectStage, SELECTFRAME_TEX);

	if (g_isLastCheck)
	{
		EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, SELECTLASTCHECK_TEX);
		//最終確認画面の矢印テクスチャの描画
		SetUpTexture(lastCheck, TITLEICON_TEX);
	}
}
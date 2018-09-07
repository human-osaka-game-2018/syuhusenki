#include "Main.h"
#include "FloaMove.h"
#include "GameMain.h"
#include "Goods.h"
#include "Timer.h"
#include "BlowOff.h"
#include "PickGoods.h"



CENTRAL_STATE playerCutinCentral = { 1200,350,320,280 };
static float cutinAnime = 0.5f;
static float cutinAnimeCount = 0;
void pickGoods() {
	static bool canCutin = true;
	if (canCutin)
	{
		g_SoundSuccess = soundsManager.Start("CUTIN", false) && g_SoundSuccess;
		canCutin = false;
	}
	pickGoodsControl();
	pickGoodsRender();
}

void pickGoodsControl() {
	timerControl();
	float deleatPosX = 250;
	int rushInput = 10;
	playerCutinCentral.x -= 5;
	if (playerCutinCentral.x < 50)
	{
		g_isBlowOff = false;
		g_gameScene = PUSHENEMY;
	}
	if (g_isGameStart)
	{
		pickGoodsDeviseControl(&rushInput);
	}
	if (g_isBlowOff) {
		madamBlowOff();
	}

}

void pickGoodsRender() {
	CUSTOMVERTEX playerCutin[4];
	CreateSquareVertexEx(playerHit, playerCentralHit, 0, 0, YASUKO_TU, YASUKO_TV);
	CreateSquareVertexEx(playerCutin, playerCutinCentral,0, cutinAnimeCount, 0.8f, cutinAnime);

	BeginSetTexture();
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, FLOAMOVE_BG_TEX);

	EasyCreateSquareVertexColor(0, 0, WIDTH, HEIGHT, HARFCLEAR, BLANK);

	for (int i = 0; i < 5; i++) {
		CreateSquareVertex(mobFloa, mobCentralBlowOff[i]);
		if (g_isBlowOff) {
			g_effectCount++;

			mobRad += 0.9f;

			if (mobRad < 0)
			{
				mobRad = mobRad * -1;
			}
			if (i % 2)
			{
				mobRad = mobRad * -1;
			}
			RevolveZ(mobFloa, mobRad, mobCentralBlowOff[i]);
		}
		SetUpTexture(mobFloa, mobTexNum);
	}


	SetUpTexture(playerHit, texturePC);


	EasyCreateSquareVertex(0, 150, WIDTH, 550, CUTIN_TEX);

	SetUpTexture(playerCutin, CUTIN_YASUKO_TEX);

	//char rushButton[10];
	RECT rushButtonAppear = { 470,200,810,550 };
	EasyCreateRECTVertex(rushButtonAppear, comandButtonTexture(rushButtonShow));

	//sprintf_s(rushButton, 10, "%c", comandButton(rushButtonShow));
	//WriteWord(rushButton, rushButtonAppear, DT_CENTER, RED, RUSH_FONT);
#ifdef _DEBUG
	char goodsNumA[10];
	char DebugTakeBoolA[10];

	sprintf_s(goodsNumA, 10, "%d ", foodGoods[selectedGoods[g_turn]].haveValue);
	RECT DEBUGGoodsA = { 100 ,200,900,600 };
	WriteWord(goodsNumA, DEBUGGoodsA, DT_LEFT, 0xff00ffff, DEBUG_FONT);

	SoundLib::PlayingStatus status = soundsManager.GetStatus("PICK1");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	RECT DEBUGTextA = { 100 ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);
	status = soundsManager.GetStatus("PICK2");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 150  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);
	status = soundsManager.GetStatus("PICK3");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 200  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);
	status = soundsManager.GetStatus("PICK4");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 250  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);
	status = soundsManager.GetStatus("PICK5");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 300  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);
	status = soundsManager.GetStatus("PICK6");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 350  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);
	status = soundsManager.GetStatus("PICK7");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 400  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);
	status = soundsManager.GetStatus("PICK8");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 450  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);
	status = soundsManager.GetStatus("PICK9");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 500  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);
	status = soundsManager.GetStatus("PICK10");
	sprintf_s(DebugTakeBoolA, 10, "%d ", status);
	DEBUGTextA = { 550  ,150,900,600 };
	WriteWord(DebugTakeBoolA, DEBUGTextA, DT_LEFT, 0xfff0f00f, DEBUG_FONT);

#endif

	goodsScoreShow();
	timerRender();
	EndSetTexture();
}

void pickGoodsDeviseControl(int* rushInput) {
	BottonCheck();
	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_NUMPADENTER);

	CheckKeyState(DIK_A);
	CheckKeyState(DIK_B);
	CheckKeyState(DIK_X);
	CheckKeyState(DIK_Y);
	CheckKeyState(DIK_R);
	CheckKeyState(DIK_L);
#ifdef _DEBUG

	if (KeyState[DIK_RETURN] == KeyRelease || KeyState[DIK_NUMPADENTER] == KeyRelease)
	{
		g_isFirst = true;
		g_SoundSuccess = soundsManager.Stop("FOOD") && g_SoundSuccess;
		g_SoundSuccess = soundsManager.Stop("HURRY_UP") && g_SoundSuccess;
		g_SoundSuccess = soundsManager.SetVolume("HURRY_UP", 100) && g_SoundSuccess;

		g_SoundSuccess = soundsManager.Stop("FOOD") && g_SoundSuccess;

		g_SoundSuccess = soundsManager.Stop("TIME_LIMIT") && g_SoundSuccess;

		g_timeDeadline = false;

		g_scene = SCENE_RESULT;
		g_gameScene = FLOAMOVE;
	}
#endif
	if (KeyState[DIK_A] == KeyRelease)
	{
		*rushInput = ButtonA;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (KeyState[DIK_B] == KeyRelease)
	{
		*rushInput = ButtonB;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (KeyState[DIK_X] == KeyRelease)
	{
		*rushInput = ButtonX;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (KeyState[DIK_Y] == KeyRelease)
	{
		*rushInput = ButtonY;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (KeyState[DIK_R] == KeyRelease)
	{
		*rushInput = ButtonRB;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (KeyState[DIK_L] == KeyRelease)
	{
		*rushInput = ButtonLB;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}

	//XInputデバイス操作
	GetControl(0);
	BottonCheck();
#ifdef _DEBUG
	if (PadState[ButtonStart] == PadRelease)
	{
		g_isFirst = true;
		g_SoundSuccess = soundsManager.Stop("FOOD") && g_SoundSuccess;
		g_SoundSuccess = soundsManager.Stop("HURRY_UP") && g_SoundSuccess;
		g_SoundSuccess = soundsManager.SetVolume("HURRY_UP", 100) && g_SoundSuccess;

		g_SoundSuccess = soundsManager.Stop("FOOD") && g_SoundSuccess;

		g_SoundSuccess = soundsManager.Stop("TIME_LIMIT") && g_SoundSuccess;

		g_timeDeadline = false;

		g_scene = SCENE_RESULT;
		g_gameScene = FLOAMOVE;
	}
#endif
	if (PadState[ButtonA] == PadRelease)
	{
		*rushInput = ButtonA;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (PadState[ButtonB] == PadRelease)
	{
		*rushInput = ButtonB;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (PadState[ButtonX] == PadRelease)
	{
		*rushInput = ButtonX;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (PadState[ButtonY] == PadRelease)
	{
		*rushInput = ButtonY;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (PadState[ButtonRB] == PadRelease)
	{
		*rushInput = ButtonRB;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}
	if (PadState[ButtonLB] == PadRelease)
	{
		*rushInput = ButtonLB;
		rushButtonCheck(*rushInput, rushButtonShow);
		buttonSE(Pick, 10);
	}

}
void rushButtonCheck(int rushInput, int rushShow)
{
	if (rushInput == rushShow)
	{
		foodGoods[selectedGoods[g_turn]].haveValue++;
		cutinAnimeCount += 0.5f;
	}
	else g_SoundSuccess = soundsManager.Start("MISS", false) && g_SoundSuccess;

}

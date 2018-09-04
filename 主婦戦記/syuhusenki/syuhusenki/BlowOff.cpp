#include "Main.h"
#include "FloaMove.h"
#include "GameMain.h"
#include "Goods.h"
#include "Timer.h"
#include "BlowOff.h"

//エフェクト
CUSTOMVERTEX effectExplosion[4];
CENTRAL_STATE effectExplosionCentral = { 1000,800,300,300 };

bool g_isBlowOff = false;

static bool soundOnce = false;
void blowOff() {
	blowOffControl();
	blowOffRender();
	if (g_turn == 0)
	{
		rushButtonShow = rand() % 4;
	}
	else {
		rushButtonShow = rand() % 6;
	}

}
void blowOffControl()
{
	timerControl();
	CreateSquareVertex(effectExplosion, effectExplosionCentral);

	if (comandCount < 5)
	{
		if (g_isGameStart)
		{
			blowOffDeviseControl(&comandCount, comandInput);
		}
		checkedComand = comandCheck(comandPresentment, comandInput, comandCount);
		if (1 == checkedComand && soundOnce)
		{
			soundOnce = false;
			g_SoundSuccess = soundsManager.Start("SUCCESS", false) && g_SoundSuccess;
			checkedComand = 2;
		}
		if (!checkedComand&&soundOnce)
		{
			soundOnce = false;
			checkedComand = 2;
			g_SoundSuccess = soundsManager.Start("MISS", false) && g_SoundSuccess;
			if (comandButton) {
				comandCount -= 1;
			}
		}
	}
	else
	{
		checkedComand = comandCheck(comandPresentment, comandInput, comandCount);
		if (1 == checkedComand)
		{
			g_SoundSuccess = soundsManager.Start("ATTACK", false) && g_SoundSuccess;
			g_isBlowOff = true;
			checkedComand = 2;
			comandCount = 0;
		}
		if (!checkedComand)
		{
			g_SoundSuccess = soundsManager.Start("MISS", false) && g_SoundSuccess;
			checkedComand = 2;
			comandCount = 0;
		}
	}
	if (g_isBlowOff) {
		madamBlowOff();
		effectExplosionCentral.scaleX++;
		effectExplosionCentral.scaleY++;
		if (g_effectCount >= 180) {
			g_gameScene = PICKGOODS;
			comandCount = 0;
		}
	}

}
void blowOffRender()
{

	CreateSquareVertex(playerHit, playerCentralHit);

	BeginSetTexture();
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, FLOAMOVE_BG_TEX);

	EasyCreateSquareVertexColor(0, 0, WIDTH, HEIGHT, HARFCLEAR, BLANK);

	EasyCreateSquareVertex(490, 300, 890, 760, BOX_TEX);
	EasyCreateSquareVertex(560, 300, 960, 760, BOX_TEX);
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
	if ((g_effectCount > 20) && g_isBlowOff) {
		SetUpTexture(effectExplosion, EXPLOSION_TEX);
	}
	SetUpTexture(playerHit, texturePC);

	char debugComandInput[10];
	char debugComandOutput[10];
	char DebugCounter[10];
	for (int i = 0; i < 5; i++)
	{
		RECT DEBUGText = { 300 + (i * 100),200,450 + (i * 100),300 };
		EasyCreateRECTVertex(DEBUGText, comandButtonTexture(comandPresentment[i]));
	}
	for (int i = 0; i < 5; i++)
	{
		RECT DEBUGText = { 300 + (i * 100),300,450 + (i * 100),400 };
		EasyCreateRECTVertex(DEBUGText, comandButtonTexture(comandInput[i]));
	}
#ifdef _DEBUG

	for (int i = 0; i < 5; i++)
	{
		sprintf_s(debugComandInput, 10, "%c", comandButton(comandInput[i]));

		RECT DEBUGText = { 100 + (i * 50),500,900,600 };
		WriteWord(debugComandInput, DEBUGText, DT_LEFT, 0xff0000ff, DEBUG_FONT);
	}
	for (int i = 0; i < 5; i++)
	{
		sprintf_s(debugComandOutput, 10, "%c", comandButton(comandPresentment[i]));

		RECT DEBUGText = { 100 + (i * 50),450,900,600 };
		WriteWord(debugComandOutput, DEBUGText, DT_LEFT, 0xff0000ff, DEBUG_FONT);
	}

	sprintf_s(DebugCounter, 10, "%d", comandCount);
	RECT DEBUGText = { 100 ,550,900,600 };
	WriteWord(DebugCounter, DEBUGText, DT_LEFT, 0xff00ffff, DEBUG_FONT);
#endif

	goodsScoreShow();
	timerRender();
	EndSetTexture();
}
int comandCheck(int comand[], int inputComand[], int count)
{
	for (int i = 0; i < count; i++) {
		if (inputComand[i] == 10) {
			return 2;
		}
		if (comand[i] == inputComand[i]) {
			if (i == count - 1) {
				return 1;
			}
		}
		if (comand[i] != inputComand[i]) {
			if (i == count - 1) {
				return 0;
			}
		}
	}
	return 2;
}
void comandMake() {
	srand((unsigned int)time(NULL));
	if (g_turn == 0)
	{
		comandPresentment[0] = rand() % 4;
		comandPresentment[1] = rand() % 4;
		comandPresentment[2] = rand() % 4;
		comandPresentment[3] = rand() % 4;
		comandPresentment[4] = rand() % 4;

	}
	else {
		comandPresentment[0] = rand() % 6;
		comandPresentment[1] = rand() % 6;
		comandPresentment[2] = rand() % 6;
		comandPresentment[3] = rand() % 6;
		comandPresentment[4] = rand() % 6;
	}
}

char comandButton(int comand)
{
	switch (comand) {
	case ButtonA:
		return 'A';
	case ButtonB:
		return 'B';
	case ButtonX:
		return 'X';
	case ButtonY:
		return 'Y';
	case ButtonRB:
		return 'R';
	case ButtonLB:
		return 'L';
	}

}
int comandButtonTexture(int comand)
{
	switch (comand) {
	case ButtonA:
		return A_TEX;
	case ButtonB:
		return B_TEX;
	case ButtonX:
		return X_TEX;
	case ButtonY:
		return Y_TEX;
	case ButtonRB:
		return R_TEX;
	case ButtonLB:
		return L_TEX;
	default:
		return NULL_BUTTON_TEX;
	}

}

void blowOffDeviseControl(int* i, int comand[])
{
	static int buttonKeyID = 0;
	static int prevbuttonKeyID = 1;
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
		g_gameScene = PICKGOODS;

	}
#endif
	if (KeyState[DIK_A] == KeyRelease)
	{
		soundOnce = true;
		comand[*i] = ButtonA;
		*i += 1;

		buttonSE(Button, 3);
	}
	if (KeyState[DIK_B] == KeyRelease)
	{
		soundOnce = true;
		comand[*i] = ButtonB;
		*i += 1;
		buttonSE(Button, 3);
	}
	if (KeyState[DIK_X] == KeyRelease)
	{
		soundOnce = true;
		comand[*i] = ButtonX;
		*i += 1;
		buttonSE(Button, 3);
	}
	if (KeyState[DIK_Y] == KeyRelease)
	{
		soundOnce = true;
		comand[*i] = ButtonY;
		*i += 1;
		buttonSE(Button, 3);
	}
	if (KeyState[DIK_R] == KeyRelease)
	{
		soundOnce = true;
		comand[*i] = ButtonRB;
		*i += 1;
		buttonSE(Button, 3);
	}
	if (KeyState[DIK_L] == KeyRelease)
	{
		soundOnce = true;
		comand[*i] = ButtonLB;
		*i += 1;
		buttonSE(Button, 3);
	}
	//XInputデバイス操作
	GetControl(0);
	BottonCheck();
#ifdef _DEBUG

	if (PadState[ButtonStart] == KeyRelease)
	{
		g_gameScene = PICKGOODS;
	}
#endif
	if (PadState[ButtonA] == KeyRelease)
	{
		soundOnce = true;
		comand[*i] = ButtonA;
		*i += 1;
		buttonSE(Button, 3);
	}
	if (PadState[ButtonB] == KeyRelease)
	{
		soundOnce = true;
		comand[*i] = ButtonB;
		*i += 1;
		buttonSE(Button, 3);
	}
	if (PadState[ButtonX] == KeyRelease)
	{
		soundOnce = true;
		comand[*i] = ButtonX;
		*i += 1;
		buttonSE(Button, 3);
	}
	if (PadState[ButtonY] == KeyRelease)
	{
		soundOnce = true;
		comand[*i] = ButtonY;
		*i += 1;
		buttonSE(Button, 3);
	}
	if (PadState[ButtonRB] == KeyRelease)
	{
		soundOnce = true;
		comand[*i] = ButtonRB;
		*i += 1;
		buttonSE(Button, 3);
	}
	if (PadState[ButtonLB] == KeyRelease)
	{
		soundOnce = true;
		comand[*i] = ButtonLB;
		*i += 1;
		buttonSE(Button, 3);
	}

}

void buttonSE(SoundEffect Button, int SoundNumber) {
	static int buttonKeyID = 0;
	static int prevbuttonKeyID = 1;
	if (buttonKeyID >= SoundNumber) {
		buttonKeyID = 0;
	}

	switch (buttonKeyID) {
	case 9:
		if (buttonKeyID == 9 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE10) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE10, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 0;
			break;
		}
	case 8:
		if (buttonKeyID == 8 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE9) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE9, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 9;
			break;
		}

	case 7:
		if (buttonKeyID == 7 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE8) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE8, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 8;
			break;
		}
	case 6:
		if (buttonKeyID == 6 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE7) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE7, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 7;
			break;
		}
	case 5:
		if (buttonKeyID == 5 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE6) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE6, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 6;
			break;
		}

	case 4:
		if (buttonKeyID == 4 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE5) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE5, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 5;
			break;
		}
	case 3:
		if (buttonKeyID == 3 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE4) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE4, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 4;
			break;
		}
	case 2:
		if (buttonKeyID == 2 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE3) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE3, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 3;
			break;
		}
	case 1:
		if (buttonKeyID == 1 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE2) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE2, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 2;
			break;
		}
	case 0:
		if (buttonKeyID == 0 && buttonKeyID != prevbuttonKeyID) {
			g_SoundSuccess = soundsManager.Stop(Button.SE1) && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start(Button.SE1, false) && g_SoundSuccess;
			prevbuttonKeyID = buttonKeyID;
			buttonKeyID = 1;
			break;
		}
	}
}
void madamBlowOff() {


	mobCentralBlowOff[0].x -= rand() % 15;
	mobCentralBlowOff[0].y -= rand() % 5;

	mobCentralBlowOff[1].x += rand() % 10;
	mobCentralBlowOff[1].y -= rand() % 10;

	mobCentralBlowOff[2].x += rand() % 3;
	mobCentralBlowOff[2].y -= rand() % 10;

	mobCentralBlowOff[3].x -= rand() % 8;
	mobCentralBlowOff[3].y -= rand() % 10;

	mobCentralBlowOff[4].x += rand() % 25;
	mobCentralBlowOff[4].y -= rand() % 30;

	if (g_effectCount > 500) {
		for (int i = 0; i < 5; i++) {
			mobCentralBlowOff[i].y += 35;
		}
	}

}

#include "Main.h"
#include "Timer.h"

#define PI 3.14159265358979
#define LIMIT_TIME 90//秒
#define Limit_frame (LIMIT_TIME*60)


CENTRAL_STATE g_timerSta = { 1210.f, 50.f, 50.f, 50.f };
CENTRAL_STATE g_timeUpSta = { 520.f, 350.f, 260.f, 100.f };

int g_timerCount = 0;
bool g_tern[3];
//タイマー制御処理
VOID timerControl(VOID)
{
	if (g_timerCount < THREE_SECOND + Limit_frame)
	{
		g_timerCount++;
	}

	if (g_timerCount == THREE_SECOND)
	{
		g_isGameStart = true;
	}

	if (g_timerCount == THREE_SECOND + Limit_frame)
	{
		soundsManager.SetVolume("FOOD", 25);
		soundsManager.Stop("FOOD");
		g_isTimeUp = true;
	}
}

//タイマー描画処理
VOID timerRender(VOID)
{
	static float timerRotation = 0.f;

	CUSTOMVERTEX timer[4];
	CUSTOMVERTEX timerHand[4];
	CUSTOMVERTEX timeUp[4];

	CreateSquareVertex(timeUp, g_timeUpSta);
	CreateSquareVertex(timer, g_timerSta);
	CreateSquareVertex(timerHand, g_timerSta);

	//秒針回転
	RevolveZ(timerHand, timerRotation, g_timerSta);

	//タイマーのテクスチャの描画
	SetUpTexture(timer, TIMER_FRAME_TEX);

	//タイマーのテクスチャの描画
	SetUpTexture(timerHand, TIMER_HAND_TEX);
#ifdef _DEBUG
	char debugTime[10];
	sprintf_s(debugTime, 10, "%d", g_timerCount);
	RECT DEBUGText = { 100 ,300,900,600 };
	WriteWord(debugTime, DEBUGText, DT_LEFT, 0xff0000ff, DEBUG_FONT);
	sprintf_s(debugTime, 10, "%d", Limit_frame);
	DEBUGText = { 400 ,300,900,600 };
	WriteWord(debugTime, DEBUGText, DT_LEFT, 0xff0000ff, DEBUG_FONT);
	sprintf_s(debugTime, 10, "%f", ((360.f / Limit_frame) / 180.f)*PI);
	DEBUGText = { 400 ,350,900,600 };
	WriteWord(debugTime, DEBUGText, DT_LEFT, 0xff0000ff, DEBUG_FONT);

#endif
	if (g_timerCount >= THREE_SECOND && !g_isTimeUp)
	{
		timerRotation -= ((360.f / Limit_frame) / 180.f)*PI;
	}

	if (g_isTimeUp)
	{
		//タイムアップのテクスチャの描画
		SetUpTexture(timeUp, TIMEUP_TEX);
	}
}
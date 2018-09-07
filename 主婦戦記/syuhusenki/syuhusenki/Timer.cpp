#include "Main.h"
#include "Timer.h"
#include "GameMain.h"

#define PI 3.14159265358979
#define LIMIT_TIME 60//秒
#define Limit_frame (LIMIT_TIME*60)
#define DEADLINE_SECOND 300
#define HURRY_TIME (20*60)

CENTRAL_STATE g_timerSta = { 1210.f, 50.f, 50.f, 50.f };
CENTRAL_STATE g_timeUpSta = { WIDTH/2, HEIGHT/2, 260.f, 100.f };
bool g_timeDeadline = false;
int g_timerCount = 0;

//タイマー制御処理
void timerControl(void)
{
	if (g_timerCount < THREE_SECOND + Limit_frame)
	{
		g_timerCount++;
	}

	if (g_timerCount == THREE_SECOND)
	{
		g_isGameStart = true;
		soundsManager.Start("WHISYLE", false);

	}
	if (g_isGameStart)
	{
		if ((Limit_frame + THREE_SECOND) - g_timerCount == DEADLINE_SECOND)
		{
			g_SoundSuccess = soundsManager.Stop("FOOD") && g_SoundSuccess;
			g_SoundSuccess = soundsManager.SetVolume("HURRY_UP", 10) && g_SoundSuccess;

			g_SoundSuccess = soundsManager.Start("TIME_LIMIT", false) && g_SoundSuccess;

			g_timeDeadline = true;
		}
		if ((Limit_frame + THREE_SECOND) - g_timerCount < ONE_SECOND)
		{
			g_SoundSuccess = soundsManager.Stop("TIME_LIMIT") && g_SoundSuccess;

		}
		if ((Limit_frame + THREE_SECOND) - g_timerCount < HURRY_TIME)
		{
			g_SoundSuccess = soundsManager.Stop("FOOD") && g_SoundSuccess;
			g_SoundSuccess = soundsManager.Start("HURRY_UP", true) && g_SoundSuccess;
		}
		if (g_timerCount == THREE_SECOND + Limit_frame)
		{
			g_SoundSuccess = soundsManager.Start("GONG", false) && g_SoundSuccess;
			g_timerCount = 0;
			g_SoundSuccess = soundsManager.Stop("HURRY_UP") && g_SoundSuccess;
			g_SoundSuccess = soundsManager.SetVolume("HURRY_UP", 100) && g_SoundSuccess;
			comandCount = 0;

			g_SoundSuccess = soundsManager.Stop("TIME_LIMIT") && g_SoundSuccess;
			g_isGameStart = false;
			g_timeDeadline = false;
			g_isTimeUp = true;
		}
	}
}

//タイマー描画処理
void timerRender(void)
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

	if (g_isTimeUp /*&& g_turn == 2*/)
	{
		//タイムアップのテクスチャの描画
		SetUpTexture(timeUp, TIMEUP_TEX);
		
	}
}

int timeShow()
{
	return ((Limit_frame + THREE_SECOND) - g_timerCount) / 60;
}
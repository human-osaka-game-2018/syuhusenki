#include "Main.h"
#include "Timer.h"

CENTRAL_STATE g_timerSta = { 1210.f, 50.f, 50.f, 50.f };
CENTRAL_STATE g_timeUpSta = { 520.f, 350.f, 260.f, 100.f };

int g_timerCount = 0;

//タイマー制御処理
VOID timerControl(VOID)
{
	if (g_timerCount < THREE_SECOND + THREE_MINUTE)
	{
		g_timerCount++;
	}

	if (g_timerCount == THREE_SECOND)
	{
		g_isGameStart = true;
	}

	if (g_timerCount == THREE_SECOND + THREE_MINUTE)
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

	if (g_timerCount >= THREE_SECOND && !g_isTimeUp)
	{
		timerRotation += -THREE_MINUTE_RADIAN;
	}

	if (g_isTimeUp)
	{
		//タイムアップのテクスチャの描画
		SetUpTexture(timeUp, TIMEUP_TEX);
	}
}
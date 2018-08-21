#ifndef MAIN_H
#define MAIN_H


#include "DirectX_LIB/DirectX_LIB/TrialLib.h"



#ifdef _DEBUG
#include "SoundLib/Debug_x86/Include/SoundsManager.h"
#pragma comment(lib,"SoundLib/Debug_x86/Lib/SoundLib.lib")
#pragma comment(lib, "DirectX_LIB/Debug/DirectX_LIB.lib")
#else
#include "SoundLib/Release_x86/Include/SoundsManager.h"
#pragma comment(lib,"SoundLib/Release_x86/Lib/SoundLib.lib")
#pragma comment(lib, "DirectX_LIB/Release/DirectX_LIB.lib")
#endif //_DEBUG

#define WIDTH 1280
#define HEIGHT 720
#define RED 0xFFFF0000

//ゲームパッドの状態
#define UP_BUTTON 0x0001
#define DOWN_BUTTON 0x0002
#define LEFT_BUTTON 0x0004
#define RIGHT_BUTTON 0x0008
#define START_BUTTOM 0x0010
#define BACK_BUTTON 0x0020
#define LEFT_STICK 0x0040
#define RIGHT_STICK 0x0080
#define LEFT_SHOULDER 0x0100
#define RIGHT_SHOULDER 0x0200
#define A_BUTTON 0x1000
#define B_BUTTON 0x2000
#define X_BUTTON 0x4000
#define Y_BUTTON 0x8000

extern XINPUT_STATE g_Xinput;

//主婦のステータス
struct CHARACTER_STATE
{
	FLOAT strength;
	FLOAT speed;
	FLOAT skill;
};

enum SOUND {
	SE1,
	SE2,
	SOUND_MAX
};

enum SCENE {
	SCENE_TEAMLOGO,
	SCENE_TITLE,
	SCENE_SERECTCHARANDSTAGE,
	SCENE_MAIN,
	SCENE_RESULT,
};

extern SoundLib::SoundsManager soundsManager;
extern bool g_SoundSuccess;
extern const char* soundNum[SOUND_MAX];
extern RECT testWord;
extern int g_scene;

extern FLOAT g_PCSpeed;

//ヤス子のステータス
extern CHARACTER_STATE g_yasukoSta;

//ミツ子のステータス
extern CHARACTER_STATE g_mitukoSta;

//イソ子のステータス
extern CHARACTER_STATE g_isokoSta;

extern int g_inCount;
extern int g_gameCount;

extern bool g_pause;
extern bool g_isGameStart;
extern bool g_isTimeUp;
extern bool g_isSound;
extern bool g_isNextSelect;
extern bool g_isLastCheck;

#endif // !MAIN_H

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
extern bool SoundSuccess;
extern const char* soundNum[SOUND_MAX];
extern RECT testWord;
extern int g_scene;

#endif // !MAIN_H

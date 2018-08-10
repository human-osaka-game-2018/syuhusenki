#ifndef MAIN_H
#define MAIN_H


#include "DirectX_LIB/DirectX_LIB/TrialLib.h"


#include "Sound_Lib/DirectSound.h"
#include "Sound_Lib/SoundManager.h"



#ifdef _DEBUG
#pragma comment(lib, "Sound_Lib/Debug/Sound.lib")
#pragma comment(lib, "DirectX_LIB/Debug/DirectX_LIB.lib")
#else
#pragma comment(lib, "Sound_Lib/Release/Sound.lib")
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
extern SoundManager& soundManager;
extern const char* soundNum[SOUND_MAX];
extern RECT testWord;
extern int g_scene;

void render(void);//‰¼
void control(void);//‰¼
void sound(void);//‰¼

void gamePad(void);

#endif // !MAIN_H

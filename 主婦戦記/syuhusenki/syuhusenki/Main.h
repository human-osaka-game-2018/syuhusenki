#ifndef MAIN_H
#define MAIN_H


#include "DirectX_LIB/DirectX_LIB/TrialLib.h"


#include "SoundLib/DirectSound.h"
#include "SoundLib/SoundManager.h"



#ifdef _DEBUG
#pragma comment(lib, "SoundLib/Debug/Sound.lib")
#pragma comment(lib, "DirectX_LIB/Debug/DirectX_LIB.lib")
#else
#pragma comment(lib, "SoundLib/Release/Sound.lib")
#pragma comment(lib, "DirectX_LIB/Release/DirectX_LIB.lib")
#endif //_DEBUG

#define WIDTH 1920
#define HEIGHT 1080
#define RED 0xFFFF0000

enum SOUND {
	SE1,
	SE2,
	SOUND_MAX
};
enum SCENE {
	SCENE_TEAMLOGO,
	SCENE_TITLE,
	SCENE_SERECTCHAR,
	SCENE_SERECTSTEGE,
	SCENE_MAIN,
	SCENE_RESULT,
};
extern SoundManager& soundManager;

extern RECT testWord;
extern int g_scene;

void render(void);//‰¼
void control(void);//‰¼
void sound(void);//‰¼

void gamePad(void);

#endif // !MAIN_H

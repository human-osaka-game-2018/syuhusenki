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

#define WIDTH 1200
#define HEIGHT 1024
#define RED 0xFFFF0000

SoundManager& soundManager = SoundManager::GetInstance();

enum SCENE {
	SCENE_TEAMLOGO,
	SCENE_TITLE,
	SCENE_SERECTCHAR,
	SCENE_SERECTSTEGE,
	SCENE_MAIN,
	SCENE_RESULT,
};

RECT testWord = { 100,200,1100,500 };

void render(void);//仮
void control(void);//仮
void sound(void);//仮
void gameRoop(void);
void gamePad(void);
int g_scene = SCENE_TEAMLOGO;
bool seOn = false;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstance, LPSTR szStr, INT iCmdShow) {
	HWND hWnd = NULL;


	InitWindowEx("☆主婦戦記☆", &hWnd, WIDTH, HEIGHT, hInst, hInstance, NULL, "Texture/Yasuko.png");

	DirectSound::CreateInstance(hWnd);

	ReadInTexture("Texture/Blank.jpg", BLANK);
	ReadInTexture("Texture/Yasuko.png", YASUKO_TEX);
	ReadInTexture("Texture/karititle.png", BG_TITLE_TEX);

	SetUpFont(100, 70, DEFAULT_CHARSET, NULL, FONT);
	soundManager.Load("Sound/Buppigan.wav");

	FlameRoop(gameRoop);

}
void gameRoop() {
	sound();
	switch (g_scene) {
	case SCENE_TEAMLOGO:
		control();
		render();
		break;
	case SCENE_TITLE:
		control();
		render();
		break;
	case SCENE_SERECTCHAR:
		control();
		render();
		break;
	case SCENE_SERECTSTEGE:
		control();
		render();
		break;
	case SCENE_MAIN:
		control();
		render();
		break;
	case SCENE_RESULT:
		control();
		render();
		break;
	}

}

void control(void) {
	gamePad();
	
	CheckKeyState(DIK_RETURN);
	if (KeyState[DIK_RETURN] == KeyRelease)// ←キーを押してる
	{
		seOn = true;
		switch (g_scene) {
		case SCENE_TEAMLOGO:
			g_scene = SCENE_TITLE;
			break;
		case SCENE_TITLE:
			g_scene = SCENE_SERECTCHAR;
			break;
		case SCENE_SERECTCHAR:
			g_scene = SCENE_SERECTSTEGE;
			break;
		case SCENE_SERECTSTEGE:
			g_scene = SCENE_MAIN;
			break;
		case SCENE_MAIN:
			g_scene = SCENE_RESULT;
			break;
		case SCENE_RESULT:
			g_scene = SCENE_TITLE;
			break;
		}
	}
}

void render(void) {
	BeginSetTexture();
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BLANK);

	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, YASUKO_TEX);

	switch (g_scene) {
	case SCENE_TEAMLOGO:
		WriteWord("心はMadam", testWord, DT_CENTER, RED, FONT);
		break;
	case SCENE_TITLE:
		//WriteWord("主婦戦記", testWord, DT_CENTER, RED, FONT);
		EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BG_TITLE_TEX);

		break;
	case SCENE_SERECTCHAR:
		WriteWord("キャラ選択", testWord, DT_CENTER, RED, FONT);
		break;
	case SCENE_SERECTSTEGE:
		WriteWord("ステージ選択", testWord, DT_CENTER, RED, FONT);
		break;
	case SCENE_MAIN:
		WriteWord("メインゲーム", testWord, DT_CENTER, RED, FONT);
		break;
	case SCENE_RESULT:
		WriteWord("リザルト", testWord, DT_CENTER, RED, FONT);
		break;
	}

	EndSetTexture();

}
void sound(void) {
	if (seOn) {
		soundManager.Play("Sound/Buppigan.wav", false);
		seOn = false;
	}

}
void gamePad() {
	//XInputデバイス操作
	GetControl(0);
	BottonCheck();
	if (PadState[ButtonA] == PadRelease) {
		seOn = true;
		switch (g_scene) {
		case SCENE_TEAMLOGO:
			g_scene = SCENE_TITLE;
			break;
		case SCENE_TITLE:
			g_scene = SCENE_SERECTCHAR;
			break;
		case SCENE_SERECTCHAR:
			g_scene = SCENE_SERECTSTEGE;
			break;
		case SCENE_SERECTSTEGE:
			g_scene = SCENE_MAIN;
			break;
		case SCENE_MAIN:
			g_scene = SCENE_RESULT;
			break;
		case SCENE_RESULT:
			g_scene = SCENE_TITLE;
			break;
		}

	}

}
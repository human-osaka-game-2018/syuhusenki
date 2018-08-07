#include "Main.h"
#include "GameMain.h"

SoundManager& soundManager = SoundManager::GetInstance();

const char* soundNum[SOUND_MAX];

RECT testWord = { 100,200,1100,500 };
void gameRoop();
void soundLoad();
int g_scene = SCENE_TEAMLOGO;
//int g_scene = SCENE_MAIN;

bool seOn = false;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstance, LPSTR szStr, INT iCmdShow) {
	HWND hWnd = NULL;

#ifdef _DEBUG
	InitWindowEx("☆主婦戦記☆", &hWnd, WIDTH, HEIGHT, hInst, hInstance, NULL, "Texture/Yasuko.png");
#else
	InitWindowFullscreenEx("☆主婦戦記☆", &hWnd, WIDTH, HEIGHT, hInst, hInstance, NULL, "Texture/Yasuko.png");
#endif
	DirectSound::CreateInstance(hWnd);

	ReadInTexture("Texture/Blank.jpg", BLANK);
	ReadInTexture("Texture/Yasuko.png", YASUKO_TEX);
	ReadInTexture("Texture/karititle.png", BG_TITLE_TEX);
	ReadInTexture("Texture/shopping_cart_woman.png", MOB_TEX);

	SetUpFont(100, 70, DEFAULT_CHARSET, NULL, FONT);
	soundLoad();
	soundManager.Load(soundNum[SE1]);
	soundManager.Load(soundNum[SE2]);
	//soundManager.Load("Sound/.wav");
	//soundManager.Play("Sound/.wav", true);

	FlameRoop(gameRoop);

}
void gameRoop() {
	static bool isFirst = true;
	sound();
	switch (g_scene) {
	case SCENE_TEAMLOGO:
		if (isFirst) {

		ReadInTexture("Texture/Blank.jpg", BLANK);
		ReadInTexture("Texture/Yasuko.png", YASUKO_TEX);
		ReadInTexture("Texture/karititle.png", BG_TITLE_TEX);
		ReadInTexture("Texture/shopping_cart_woman.png", MOB_TEX);

		isFirst = false;
		}
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
		gameMain();
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
	if (KeyState[DIK_RETURN] == KeyRelease)
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
			//g_scene = SCENE_RESULT;
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

void soundLoad() {
	soundNum[SE1] = "Sound/Buppigan.wav";
	soundNum[SE2] = "Sound/Buppigan2.wav";

}
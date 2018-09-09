#include "Main.h"
#include "GameMain.h"
#include "Title.h"
#include "Result.h"
#include "Goods.h"
#include "Timer.h"
#include "resource.h"

SoundLib::SoundsManager soundsManager;

bool g_SoundSuccess;

RECT testWord = { 50,200,1200,500 };
unsigned int gameRoop();
void soundLoad();
int g_titleScene = TITLE;
int g_scene = SCENE_TEAMLOGO;
//int g_scene = SCENE_MAIN;
void teamlogoRender(void);//âº
void teamlogoControl(void);//âº

DWORD g_cursolColor = 0xffffffff;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstance, LPSTR szStr, INT iCmdShow) {
	HWND hWnd = NULL;

#ifdef _DEBUG
	InitWindowEx("ÅôéÂïwêÌãLÅô", &hWnd, WIDTH, HEIGHT, hInst, hInstance, IDI_ICON1, "Texture/Yasuko.png");
#else
	InitWindowFullscreenEx("ÅôéÂïwêÌãLÅô", &hWnd, WIDTH, HEIGHT, hInst, hInstance, IDI_ICON1, "Texture/Yasuko.png");
#endif
	g_SoundSuccess = soundsManager.Initialize() && g_SoundSuccess;
	ReadInTexture("Texture/nowloading.png", LOAD_TEX);
	setNowLoading();
	g_SoundSuccess = soundsManager.AddFile("Sound/loadEnd.mp3", "LOAD") && g_SoundSuccess;

	ReadInTexture("Texture/Blank.jpg", BLANK);
	ReadInTexture("Texture/Yasuko.png", YASUKO_TEX);
	ReadInTexture("Texture/title.jpg", TITLE_BG_TEX);
	ReadInTexture("Texture/title_select.png", TITLE_UI_TEX);
	ReadInTexture("Texture/UI/pressA.png", PRESS_TEX);

	ReadInTexture("Texture/mob.png", MOB_TEX);
	ReadInTexture("Texture/team_logo.png", TEAMLOGO_TEX);

	ReadInTexture("Texture/Mituko.png",MITUKO_TEX);
	ReadInTexture("Texture/Isoko.png",ISOKO_TEX);
	ReadInTexture("Texture/UI/arrow.png", TITLEICON_TEX);
	ReadInTexture("Texture/calculation2", RESULT_BG_TEX);
	ReadInTexture("Texture/wisdomP1.png", WISDOM1_TEX);
	ReadInTexture("Texture/wisdomP2.png", WISDOM2_TEX);
	ReadInTexture("Texture/wisdomP3.png", WISDOM3_TEX);

	ReadInTexture("Texture/button/a.png", A_TEX);

	SetUpFont(100, 70, DEFAULT_CHARSET, NULL, HOGE_FONT);
	SetUpFont(25, 25, DEFAULT_CHARSET, NULL, DEBUG_FONT);
	SetUpFont(70, 50, DEFAULT_CHARSET, NULL, HAVEGOODS_FONT);

	soundLoad();
	g_SoundSuccess = soundsManager.Start("LOAD", false) && g_SoundSuccess;

	FlameRoop(gameRoop);

}

unsigned int gameRoop() {
	static bool isFirst = true;

	CheckKeyState(DIK_F4);
	if (KeyState[DIK_F4] == KeyRelease && InputKEY(DIK_LSHIFT))
	{
		g_SoundSuccess = soundsManager.Stop("FOOD") && g_SoundSuccess;
		g_SoundSuccess = soundsManager.Stop("HURRY_UP") && g_SoundSuccess;
		g_SoundSuccess = soundsManager.SetVolume("HURRY_UP", 100) && g_SoundSuccess;

		g_SoundSuccess = soundsManager.Stop("TIME_LIMIT") && g_SoundSuccess;

		g_timeDeadline = false;

		selectedGoods[0] = POTATO;
		selectedGoods[1] = BEEF;
		selectedGoods[2] = ONION;
		for (int i = 0; i < 3; i++) {
			foodGoods[selectedGoods[i]].haveValue += 300;
		}
		g_scene = SCENE_RESULT;
	}
	static bool clearCursol = false;
	if (!clearCursol) {
		g_cursolColor -= 2 << 24;
	}
	if (clearCursol) {
		g_cursolColor += 2 << 24;
	}

	if (g_cursolColor == (0xffffffff))
	{
		clearCursol = true;
	}
	if (g_cursolColor <= (0xffffff))
	{
		clearCursol = false;
	}

	switch (g_scene) {
	case SCENE_TEAMLOGO:
		if (isFirst) {

			g_SoundSuccess = soundsManager.Start("LOGO", false) && g_SoundSuccess;

			isFirst = false;
		}
		g_SoundSuccess = soundsManager.SetVolume("FOOD", 25) && g_SoundSuccess;
		teamlogoControl();
		teamlogoRender();
		break;
	case SCENE_TITLE:
		switch (g_titleScene)
		{
		case TITLE:
			titleControl();
			titleRender();
			break;
		case WISDOM:
			wisdomControl();
			wisdomRender();
			break;
		}
		break;
	case SCENE_MAIN:
		if (g_isTimeUp)
		{
			g_isFirst = true;
			g_isTimeUp = false;
			g_timerCount = 0;
			g_gameScene = FLOAMOVE;
			switch (g_turn)
			{

			case 0:
				g_turn = 1;
				break;
			case 1:
				g_turn = 2;
				break;
			case 2:
				g_turn = 0;

				g_scene = SCENE_RESULT;
				break;
			}
			Sleep(3000);

		}
		gameMain();
		break;
	case SCENE_RESULT:
		result();
		break;
	}
	CheckKeyState(DIK_ESCAPE);
	if (KeyState[DIK_ESCAPE] == KeyRelease) 
	{
		return WM_QUIT;
	}
	return WM_NULL;
}

void teamlogoControl(void) {
	
	static DWORD SyncOld = timeGetTime();
	DWORD SyncNow = timeGetTime();
	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_NUMPADENTER);
	if (SyncNow - SyncOld > 4500)
	{
		g_scene = SCENE_TITLE;
	}
	if (KeyState[DIK_RETURN] == KeyRelease || KeyState[DIK_NUMPADENTER] == KeyRelease)
	{
			g_scene = SCENE_TITLE;
	}
	GetControl(0);
	BottonCheck();
	if (PadState[ButtonA] == PadRelease)
	{
		g_scene = SCENE_TITLE;
	}

}

void teamlogoRender(void) {
	CUSTOMVERTEX teamlogo[4];
	CENTRAL_STATE logo{ 640,320,400,400 };
	static DWORD logoColor = 0x00ffffff;
	static bool canCleared = false;
	if (!canCleared) {
		logoColor += 2 << 24;
	}
	if (canCleared && (logoColor > 0xfffffff)) {
		logoColor -= 2 << 24;
	}
	if (canCleared && (logoColor > 0xffffff)) {
		logoColor -= 1 << 24;
	}

	if (logoColor == (0xfeffffff))
	{
		canCleared = true;
	}

	BeginSetTexture();
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT,BLANK);

	CreateSquareVertexColor(teamlogo, logo, logoColor);
	SetUpTexture(teamlogo, TEAMLOGO_TEX);

	EndSetTexture();

}

void soundLoad() {
	g_SoundSuccess = soundsManager.AddFile("Sound/foodbgm.mp3", "FOOD") && g_SoundSuccess;

	g_SoundSuccess = soundsManager.AddFile("Sound/bottun.mp3", "BUTTON1") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/bottun.mp3", "BUTTON2") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/bottun.mp3", "BUTTON3") && g_SoundSuccess;

	g_SoundSuccess = soundsManager.AddFile("Sound/Welcome.mp3", "GREETING") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/thankyou.mp3", "BOW") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/correct answer.mp3", "SUCCESS") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/mistake.mp3", "MISS") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/explosion.mp3", "ATTACK") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/timer.mp3", "TIME_LIMIT") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/salebgm.mp3", "HURRY_UP") && g_SoundSuccess;

	g_SoundSuccess = soundsManager.AddFile("Sound/shopping.mp3", "PICK1") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/shopping.mp3", "PICK2") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/shopping.mp3", "PICK3") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/shopping.mp3", "PICK4") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/shopping.mp3", "PICK5") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/shopping.mp3", "PICK6") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/shopping.mp3", "PICK7") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/shopping.mp3", "PICK8") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/shopping.mp3", "PICK9") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/shopping.mp3", "PICK10") && g_SoundSuccess;

	g_SoundSuccess = soundsManager.AddFile("Sound/selectBGM.mp3", "SELECT") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/cursor.mp3", "CURSOR") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/gong.mp3", "GONG") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/whistle1.mp3", "WHISYLE") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/newop.mp3", "OP_BGM") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/select.mp3", "SELECT_BGM") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/clothBreak.mp3", "BREAK") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/stupid3.mp3", "LOSE") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/trumpet1.mp3", "WIN") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/select.mp3", "SELECT_BGM") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/clothBreak.mp3", "BREAK") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/stupid3.mp3", "LOSE") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/trumpet1.mp3", "WIN") && g_SoundSuccess;

	g_SoundSuccess = soundsManager.AddFile("Sound/money.mp3", "COIN1") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/money.mp3", "COIN2") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/money.mp3", "COIN3") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/money.mp3", "COIN4") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/money.mp3", "COIN5") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/money.mp3", "COIN6") && g_SoundSuccess;

	g_SoundSuccess = soundsManager.AddFile("Sound/madam.mp3", "WISDOM") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/cutin.mp3", "CUTIN") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/tin1.mp3", "LOW_SCORE") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/people.mp3", "MIDLE_SCORE") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/people2.mp3", "HIGH_SCORE") && g_SoundSuccess;

	g_SoundSuccess = soundsManager.AddFile("Sound/sound.mp3", "LOGO") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/cash.mp3", "CASHER") && g_SoundSuccess;
	g_SoundSuccess = soundsManager.AddFile("Sound/drum roll.mp3", "DRUM") && g_SoundSuccess;
	//g_SoundSuccess = soundsManager.AddFile("Sound/.mp3", "") && g_SoundSuccess;

}

void setNowLoading()
{
	BeginSetTexture();
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, LOAD_TEX);
	EndSetTexture();
}

#include "Main.h"
#include "GameMain.h"
#include "Select.h"
#include "Title.h"
#include "Result.h"
#include "Goods.h"

SoundLib::SoundsManager soundsManager;

bool g_SoundSuccess;

RECT testWord = { 50,200,1200,500 };
unsigned int gameRoop();
void soundLoad();
int g_scene = SCENE_TEAMLOGO;
//int g_scene = SCENE_MAIN;
//int g_scene = SCENE_SERECTCHARANDSTAGE;
void render(void);//仮
void control(void);//仮
void gamePad(void);



INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstance, LPSTR szStr, INT iCmdShow) {
	HWND hWnd = NULL;

#ifdef _DEBUG
	InitWindowEx("☆主婦戦記☆", &hWnd, WIDTH, HEIGHT, hInst, hInstance, NULL, "Texture/Yasuko.png");
#else
	InitWindowFullscreenEx("☆主婦戦記☆", &hWnd, WIDTH, HEIGHT, hInst, hInstance, NULL, "Texture/Yasuko.png");
#endif
	g_SoundSuccess = soundsManager.Initialize();
	ReadInTexture("Texture/nowloading.png", LOAD_TEX);
	setNowLoading();
	soundsManager.AddFile("Sound/loadEnd.mp3", "LOAD");

	ReadInTexture("Texture/Blank.jpg", BLANK);
	ReadInTexture("Texture/Yasuko.png", YASUKO_TEX);
	ReadInTexture("Texture/title.png", BG_TITLE_TEX);
	ReadInTexture("Texture/mob.png", MOB_TEX);
	ReadInTexture("Texture/team_logo.png", TEAMLOGO_TEX);

	ReadInTexture("Texture/kariSelect.png",SELECT_BG_TEX);
	ReadInTexture("Texture/Mituko.png",MITUKO_TEX);
	ReadInTexture("Texture/Isoko.png",ISOKO_TEX);
	ReadInTexture("Texture/selectFrame.png",SELECTFRAME_TEX);
	ReadInTexture("Texture/lastCheck.png",SELECTLASTCHECK_TEX);
	ReadInTexture("Texture/arrow.png", TITLEICON_TEX);
	ReadInTexture("Texture/calculation2", RESULT_BG_TEX);

	SetUpFont(100, 70, DEFAULT_CHARSET, NULL, HOGE_FONT);
	SetUpFont(25, 25, DEFAULT_CHARSET, NULL, DEBUG_FONT);
	SetUpFont(70, 50, DEFAULT_CHARSET, NULL, HAVEGOODS_FONT);

	soundLoad();
	g_SoundSuccess = soundsManager.Start("LOAD", false) && g_SoundSuccess;

	FlameRoop(gameRoop);

}

unsigned int gameRoop() {
	static bool isFirst = true;
#ifdef _DEBUG
	CheckKeyState(DIK_F4);
	if (KeyState[DIK_F4] == KeyRelease)
	{
		selectedGoods[0] = POTATO;
		selectedGoods[1] = BEEF;
		selectedGoods[2] = ONION;
		for (int i = 0; i < 3; i++) {
			foodGoods[selectedGoods[i]].haveValue = 100;
		}
		g_scene = SCENE_RESULT;
		g_SoundSuccess = soundsManager.Stop("FOOD") && g_SoundSuccess;
	}

#endif

	switch (g_scene) {
	case SCENE_TEAMLOGO:
		if (isFirst) {


			isFirst = false;
		}
		soundsManager.SetVolume("FOOD", 25);
		control();
		render();
		//商品情報の仮入れ
		//selectedGoods[0] = ICE;
		//selectedGoods[1] = ORANGE;
		//selectedGoods[2] = APPLE;
		//for (int i = 0; i < 3; i++)
		//{
		//	foodGoods[selectedGoods[i]].haveValue = 100;
		//}
		break;
	case SCENE_TITLE:
		titleControl();
		titleRender();
		break;
	case SCENE_SERECTCHARANDSTAGE:

		selectControl();
		selectRender();
		break;
	case SCENE_MAIN:
		if (g_isTimeUp)
		{
			soundsManager.Start("GONG", false);
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

void control(void) {
	gamePad();
	
	static DWORD SyncOld = timeGetTime();
	DWORD SyncNow = timeGetTime();
	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_NUMPADENTER);
	if (SyncNow - SyncOld > 4000)
	{
		g_scene = SCENE_TITLE;
	}
	if (KeyState[DIK_RETURN] == KeyRelease || KeyState[DIK_NUMPADENTER] == KeyRelease)
	{
			g_scene = SCENE_TITLE;
	}
}

void render(void) {
	CUSTOMVERTEX teamlogo[4];
	CENTRAL_STATE logo{ 640,320,400,400 };
	
	BeginSetTexture();
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BLANK);

	CreateSquareVertex(teamlogo, logo);
	SetUpTexture(teamlogo, TEAMLOGO_TEX);

	EndSetTexture();

}
void gamePad() {
	//XInputデバイス操作
	GetControl(0);
	BottonCheck();
	if (PadState[ButtonA] == PadRelease) 
	{
			g_scene = SCENE_TITLE;
	}

}

void soundLoad() {
	soundsManager.AddFile("Sound/foodbgm.mp3", "FOOD");

	soundsManager.AddFile("Sound/bottun.mp3", "BUTTON1");
	soundsManager.AddFile("Sound/bottun.mp3", "BUTTON2");
	soundsManager.AddFile("Sound/bottun.mp3", "BUTTON3");

	soundsManager.AddFile("Sound/Welcome.mp3", "GREETING");
	soundsManager.AddFile("Sound/thankyou.mp3", "BOW");
	soundsManager.AddFile("Sound/correct answer.mp3", "SUCCESS");
	soundsManager.AddFile("Sound/mistake.mp3", "MISS");
	soundsManager.AddFile("Sound/explosion.mp3", "ATTACK");
	soundsManager.AddFile("Sound/timer.mp3", "TIME_LIMIT");
	soundsManager.AddFile("Sound/salebgm.mp3", "HURRY_UP");

	soundsManager.AddFile("Sound/shopping.mp3", "PICK1");
	soundsManager.AddFile("Sound/shopping.mp3", "PICK2");
	soundsManager.AddFile("Sound/shopping.mp3", "PICK3");
	soundsManager.AddFile("Sound/shopping.mp3", "PICK4");
	soundsManager.AddFile("Sound/shopping.mp3", "PICK5");
	soundsManager.AddFile("Sound/shopping.mp3", "PICK6");
	soundsManager.AddFile("Sound/shopping.mp3", "PICK7");
	soundsManager.AddFile("Sound/shopping.mp3", "PICK8");
	soundsManager.AddFile("Sound/shopping.mp3", "PICK9");
	soundsManager.AddFile("Sound/shopping.mp3", "PICK10");

	soundsManager.AddFile("Sound/selectBGM.mp3", "SELECT");
	soundsManager.AddFile("Sound/cursor.mp3", "CURSOR");
	soundsManager.AddFile("Sound/gong.mp3", "GONG");
	soundsManager.AddFile("Sound/whistle1.mp3", "WHISYLE");
	soundsManager.AddFile("Sound/OP.mp3", "OP_BGM");
	soundsManager.AddFile("Sound/select.mp3", "SELECT_BGM");
	soundsManager.AddFile("Sound/clothBreak.mp3", "BREAK"); 
	soundsManager.AddFile("Sound/stupid3.mp3", "LOSE"); 
	soundsManager.AddFile("Sound/trumpet1.mp3", "WIN");
	soundsManager.AddFile("Sound/select.mp3", "SELECT_BGM");
	soundsManager.AddFile("Sound/clothBreak.mp3", "BREAK");
	soundsManager.AddFile("Sound/stupid3.mp3", "LOSE");
	soundsManager.AddFile("Sound/trumpet1.mp3", "WIN");

	soundsManager.AddFile("Sound/money.mp3", "COIN1");
	soundsManager.AddFile("Sound/money.mp3", "COIN2");
	soundsManager.AddFile("Sound/money.mp3", "COIN3");
	soundsManager.AddFile("Sound/money.mp3", "COIN4");
	soundsManager.AddFile("Sound/money.mp3", "COIN5");
	soundsManager.AddFile("Sound/money.mp3", "COIN6");

}

void setNowLoading()
{
	BeginSetTexture();
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, LOAD_TEX);
	EndSetTexture();
}

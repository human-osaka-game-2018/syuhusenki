#include "Main.h"
#include "GameMain.h"
#include "Select.h"
#include "Title.h"

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
void sound(void);//仮

void gamePad(void);


bool seOn = false;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstance, LPSTR szStr, INT iCmdShow) {
	HWND hWnd = NULL;

#ifdef _DEBUG
	InitWindowEx("☆主婦戦記☆", &hWnd, WIDTH, HEIGHT, hInst, hInstance, NULL, "Texture/Yasuko.png");
#else
	InitWindowFullscreenEx("☆主婦戦記☆", &hWnd, WIDTH, HEIGHT, hInst, hInstance, NULL, "Texture/Yasuko.png");
#endif
	g_SoundSuccess = soundsManager.Initialize();

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

	ReadInTexture("Texture/testFrame.png", FRAME_TEX);
	ReadInTexture("Texture/FoodSection.png", FOOD_STAGE_TEX);
	ReadInTexture("Texture/ClothingOrnament.png", CLOTH_STAGE_TEX);
	ReadInTexture("Texture/maxresdefault.png", CUTIN_TEX);
	ReadInTexture("Texture/bakuhuhathu.png", EXPLOSION_TEX);
	//ReadInTexture("Texture/", BG_PICKGGOODS_TEX);
	ReadInTexture("Texture/beef.png", BEEF_TEX);
	ReadInTexture("Texture/chicken.png", CHICKEN_TEX);
	ReadInTexture("Texture/pork.png", PORK_TEX);
	ReadInTexture("Texture/cardboard.png", BOX_TEX);
	ReadInTexture("Texture/durabilityBar.jpg", DURABILITY_TEX);
	ReadInTexture("Texture/ClothBattle.png", CLOTH_BG_TEX);
	ReadInTexture("Texture/smoke.png", SMOKE_TEX);

	ReadInTexture("Texture/timerFrame.png", TIMER_FRAME_TEX);
	ReadInTexture("Texture/timerHand.png", TIMER_HAND_TEX);
	ReadInTexture("Texture/startCount3.png", STARTCOUNT_3_TEX);
	ReadInTexture("Texture/startCount2.png", STARTCOUNT_2_TEX);
	ReadInTexture("Texture/startCount1.png", STARTCOUNT_1_TEX);
	ReadInTexture("Texture/kariStart.png", START_TEX);
	ReadInTexture("Texture/pauseMenu.png", PAUSE_TEX);
	ReadInTexture("Texture/end.png", TIMEUP_TEX);
	//ReadInTexture("Texture/cardboard.png", PC_TEX);
	ReadInTexture("Texture/karistage.png", FLOAMOVE_BG_TEX);

	SetUpFont(100, 70, DEFAULT_CHARSET, NULL, HOGE_FONT);
	SetUpFont(25, 25, DEFAULT_CHARSET, NULL, DEBUG_FONT);
	SetUpFont(125, 100, DEFAULT_CHARSET, NULL, RUSH_FONT);

	soundLoad();
	

	FlameRoop(gameRoop);

}

unsigned int gameRoop() {
	static bool isFirst = true;
	sound();
	switch (g_scene) {
	case SCENE_TEAMLOGO:
		if (isFirst) {

		ReadInTexture("Texture/Blank.jpg", BLANK);
		ReadInTexture("Texture/Yasuko.png", YASUKO_TEX);
	
		
		g_SoundSuccess = soundsManager.Start("FOOD", true) && g_SoundSuccess;

		isFirst = false;
		}
		soundsManager.SetVolume("FOOD", 25);
		control();
		render();
		break;
	case SCENE_TITLE:
		titleControl();
		titleRender();
		break;
	case SCENE_SERECTCHARANDSTAGE:
		g_SoundSuccess = soundsManager.Stop("FOOD") && g_SoundSuccess;
		selectControl();
		selectRender();
		break;
	case SCENE_MAIN:
		gameMain();
		break;
	case SCENE_RESULT:
		control();
		render();
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
	
	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_NUMPADENTER);

	if (KeyState[DIK_RETURN] == KeyRelease || KeyState[DIK_NUMPADENTER] == KeyRelease)
	{
		seOn = true;
		switch (g_scene) {
		case SCENE_TEAMLOGO:
			g_scene = SCENE_TITLE;
			break;
		case SCENE_TITLE:
			g_scene = SCENE_SERECTCHARANDSTAGE;
			break;
		case SCENE_SERECTCHARANDSTAGE:
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


	switch (g_scene) {
	case SCENE_TEAMLOGO:
		EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, TEAMLOGO_TEX);
		break;
	case SCENE_TITLE:
		//WriteWord("主婦戦記", testWord, DT_CENTER, RED, FONT);
		EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, BG_TITLE_TEX);

		break;
	case SCENE_SERECTCHARANDSTAGE:
		EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, YASUKO_TEX);

		WriteWord("キャラ&ステージ\n選択", testWord, DT_CENTER, RED, HOGE_FONT);
		break;
	case SCENE_MAIN:
		EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, YASUKO_TEX);

		WriteWord("メインゲーム", testWord, DT_CENTER, RED, HOGE_FONT);
		break;
	case SCENE_RESULT:
		EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, YASUKO_TEX);

		WriteWord("リザルト", testWord, DT_CENTER, RED, HOGE_FONT);
		break;
	}

	EndSetTexture();

}
void sound(void) {
	if (seOn) {
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
			g_scene = SCENE_SERECTCHARANDSTAGE;
			break;
		case SCENE_SERECTCHARANDSTAGE:
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
	soundsManager.AddFile("Sound/foodbgm.mp3", "FOOD");
	soundsManager.AddFile("Sound/bottun.mp3", "BUTTON1");
	soundsManager.AddFile("Sound/bottun.mp3", "BUTTON2");
	soundsManager.AddFile("Sound/bottun.mp3", "BUTTON3");
	soundsManager.AddFile("Sound/thankyou.mp3", "BOW");
	soundsManager.AddFile("Sound/correct answer.mp3", "SUCCESS");
	soundsManager.AddFile("Sound/mistake.mp3", "MISS");
	soundsManager.AddFile("Sound/explosion.mp3", "ATTACK");
	soundsManager.AddFile("Sound/shopping.mp3", "PICK1");
	soundsManager.AddFile("Sound/shopping.mp3", "PICK2");
	soundsManager.AddFile("Sound/shopping.mp3", "PICK3");
	soundsManager.AddFile("Sound/shopping.mp3", "PICK4");
	soundsManager.AddFile("Sound/shopping.mp3", "PICK5");
	soundsManager.AddFile("Sound/shopping.mp3", "PICK6");
	soundsManager.AddFile("Sound/shopping.mp3", "PICK7");
	soundsManager.AddFile("Sound/selectBGM.mp3", "SELECT");
	soundsManager.AddFile("Sound/cursor.mp3", "CURSOR");
	soundsManager.AddFile("Sound/gong.mp3", "GONG");
	soundsManager.AddFile("Sound/whistle1.mp3", "WHISYLE");
	soundsManager.AddFile("Sound/op.mp3", "OP_BGM");
	soundsManager.AddFile("Sound/select.mp3", "SELECT_BGM");
	soundsManager.AddFile("Sound/clothBreak.mp3", "BREAK"); 
	soundsManager.AddFile("Sound/stupid3.mp3", "LOSE"); 
	soundsManager.AddFile("Sound/trumpet1.mp3", "WIN");
}
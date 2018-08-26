#include "Result.h"
#include "Goods.h"
#include "Main.h"

void resultControl(void);
void resultRender(void);

void result() 
{
	resultControl();
	resultRender();

}

void resultControl(void)
{
	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_NUMPADENTER);

	if (KeyState[DIK_RETURN] == KeyRelease || KeyState[DIK_NUMPADENTER] == KeyRelease)
	{
		g_scene = SCENE_TITLE;
	}
	GetControl(0);
	BottonCheck();
	if (PadState[ButtonA] == PadRelease) {
		g_scene = SCENE_TITLE;
	}
}

void resultRender(void)
{
	BeginSetTexture();

	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, RESULT_BG_TEX);



	EndSetTexture();
}

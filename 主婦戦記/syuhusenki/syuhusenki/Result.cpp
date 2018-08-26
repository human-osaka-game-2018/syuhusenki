#include "Result.h"
#include "Goods.h"
#include "Main.h"

void resultControl(void);
void resultRender(void);

void result() 
{
	static bool isFirst = true;

	if (isFirst) {
		SetUpFont(25, 20, DEFAULT_CHARSET, NULL, RESULT_FONT);
		SetUpFont(70, 50, DEFAULT_CHARSET, NULL, SCORE_FONT);



		isFirst = false;
	}
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

	EasyCreateSquareVertex(0, 0, WIDTH, 700, RESULT_BG_TEX);

	CUSTOMVERTEX resultBaseTex1[4];
	CUSTOMVERTEX resultBaseTex2[4];
	CUSTOMVERTEX resultBaseTex3[4];
	CUSTOMVERTEX resultSeleTex1[4];
	CUSTOMVERTEX resultSeleTex2[4];
	CUSTOMVERTEX resultSeleTex3[4];

	CENTRAL_STATE hoge{ 100,100,100,100 };

	CreateSquareVertex(resultBaseTex1,hoge);
	CreateSquareVertex(resultBaseTex2,hoge);
	CreateSquareVertex(resultBaseTex3,hoge);
	CreateSquareVertex(resultSeleTex1,hoge);
	CreateSquareVertex(resultSeleTex2,hoge);
	CreateSquareVertex(resultSeleTex3,hoge);

	SetUpTexture(resultBaseTex1, rand() % MEET);
	SetUpTexture(resultBaseTex2, rand() % MEET);
	SetUpTexture(resultBaseTex3, rand() % MEET);
	SetUpTexture(resultSeleTex1, rand() % MEET);
	SetUpTexture(resultSeleTex2, rand() % MEET);
	SetUpTexture(resultSeleTex3, rand() % MEET);

	RECT resultBase1{ 200,150,600,300 };
	WriteWord("result", resultBase1, DT_LEFT, BLACK, RESULT_FONT);
	RECT resultBase2{ 200,250,600,300 };
	WriteWord("result", resultBase2, DT_LEFT, BLACK, RESULT_FONT);
	RECT resultBase3{ 200,350,600,500};
	WriteWord("result", resultBase3, DT_LEFT, BLACK, RESULT_FONT);
	RECT resultBaseTotal{ 200,450,440,600 };
	WriteWord("result", resultBaseTotal, DT_RIGHT, BLACK, RESULT_FONT);

	RECT resultSele1{ 950,150,1200,300 };
	WriteWord("result", resultSele1, DT_LEFT, BLACK, RESULT_FONT);
	RECT resultSele2{ 950,250,1200,300 };
	WriteWord("result", resultSele2, DT_LEFT, BLACK, RESULT_FONT);
	RECT resultSele3{ 950,350,1200,500 };
	WriteWord("result", resultSele3, DT_LEFT, BLACK, RESULT_FONT);
	RECT resultSeleTotal{ 950,450,1200,600 };
	WriteWord("result", resultSeleTotal, DT_RIGHT, BLACK, RESULT_FONT);

	RECT resultTotal{ 140,525,1140,700 };
	WriteWord("result", resultTotal, DT_CENTER, BLACK, SCORE_FONT);

	EndSetTexture();
}

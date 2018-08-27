#include "Result.h"
#include "Goods.h"
#include "Main.h"

void resultControl(void);
void resultRender(void);

int selectedGoods[3];

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
	CUSTOMVERTEX resultComboTex[4];

	CENTRAL_STATE BaseTexCentral1{100,175,50,50};
	CENTRAL_STATE BaseTexCentral2{100,275,50,50};
	CENTRAL_STATE BaseTexCentral3{100,375,50,50};
	CENTRAL_STATE SeleTexCentral1{850,175,50,50};
	CENTRAL_STATE SeleTexCentral2{850,275,50,50};
	CENTRAL_STATE SeleTexCentral3{850,375,50,50};
	CENTRAL_STATE comboTexCentral{ 640,300,100,100 };

	CreateSquareVertex(resultBaseTex1, BaseTexCentral1);
	CreateSquareVertex(resultBaseTex2, BaseTexCentral2);
	CreateSquareVertex(resultBaseTex3, BaseTexCentral3);
	CreateSquareVertex(resultSeleTex1, SeleTexCentral1);
	CreateSquareVertex(resultSeleTex2, SeleTexCentral2);
	CreateSquareVertex(resultSeleTex3, SeleTexCentral3);
	CreateSquareVertex(resultComboTex, comboTexCentral);

	SetUpTexture(resultBaseTex1, (rand() % BEER)+12);
	SetUpTexture(resultBaseTex2, (rand() % BEER)+12);
	SetUpTexture(resultBaseTex3, (rand() % BEER)+12);
	SetUpTexture(resultSeleTex1, (rand() % BEER)+12);
	SetUpTexture(resultSeleTex2, (rand() % BEER)+12);
	SetUpTexture(resultSeleTex3, (rand() % BEER)+12);
	SetUpTexture(resultComboTex, (rand() % COMBOMAX) + 36);

	char resulttantValue[32];
	sprintf_s(resulttantValue, 32, "result");
	RECT resultBase1{ 200,150,600,300 };
	WriteWord(resulttantValue, resultBase1, DT_LEFT, BLACK, RESULT_FONT);
	sprintf_s(resulttantValue, 32, "result");
	RECT resultBase2{ 200,250,600,300 };
	WriteWord(resulttantValue, resultBase2, DT_LEFT, BLACK, RESULT_FONT);
	sprintf_s(resulttantValue, 32, "result");
	RECT resultBase3{ 200,350,600,500};
	WriteWord(resulttantValue, resultBase3, DT_LEFT, BLACK, RESULT_FONT);
	sprintf_s(resulttantValue, 32, "result");
	RECT resultBaseTotal{ 200,450,440,600 };
	WriteWord(resulttantValue, resultBaseTotal, DT_RIGHT, BLACK, RESULT_FONT);

	sprintf_s(resulttantValue, 32, "result");
	RECT resultSele1{ 950,150,1200,300 };
	WriteWord(resulttantValue, resultSele1, DT_LEFT, BLACK, RESULT_FONT);
	sprintf_s(resulttantValue, 32, "result");
	RECT resultSele2{ 950,250,1200,300 };
	WriteWord(resulttantValue, resultSele2, DT_LEFT, BLACK, RESULT_FONT);
	sprintf_s(resulttantValue, 32, "result");
	RECT resultSele3{ 950,350,1200,500 };
	WriteWord(resulttantValue, resultSele3, DT_LEFT, BLACK, RESULT_FONT);
	sprintf_s(resulttantValue, 32, "result");
	RECT resultSeleTotal{ 950,450,1200,600 };
	WriteWord(resulttantValue, resultSeleTotal, DT_RIGHT, BLACK, RESULT_FONT);

	sprintf_s(resulttantValue, 32, "result");
	RECT resultTotal{ 140,525,1140,700 };
	WriteWord(resulttantValue, resultTotal, DT_CENTER, BLACK, SCORE_FONT);

	EndSetTexture();
}

#include "Result.h"
#include "Goods.h"
#include "Main.h"

enum RESULTSCENE
{
	PAGE1,
	PAGE2,
	PAGE3
};

CENTRAL_STATE cursolResult{ 100,490,25,25 };

void resultControl(void);
void resultRenderOne(void);
void resultRenderTwo(void);
void resultRenderThree(void);

int addPrice(int num, int nomalOrSale);

int selectedGoods[3];
static int resultPage;
static int nomalSum = 0;
static int saleSale = 0;

void result() 
{
	static bool isFirst = true;

	if (isFirst) {
		setNuwLoading();

		SetUpFont(25, 20, DEFAULT_CHARSET, NULL, RESULT_FONT);
		SetUpFont(70, 50, DEFAULT_CHARSET, NULL, SCORE_FONT);
		SetUpFont(100, 75, DEFAULT_CHARSET, NULL, LAST_SCORE_FONT);

		ReadInTexture("Texture/calculation2.png", RESULT_BG_TEX);
		ReadInTexture("Texture/resultLust.png", RESULT_POP_TEX);
		ReadInTexture("Texture/R_UI.png", RESULT_END_TEX);

		for (int i = 0; i < 3; i++)
		{
			nomalSum += addPrice(i, 0);
			saleSale += addPrice(i, 1);
		}

		g_SoundSuccess = soundsManager.Start("LOAD", false) && g_SoundSuccess;

		isFirst = false;
	}
	resultControl();
	BeginSetTexture();
	switch (resultPage)
	{
	case PAGE1:
		resultRenderOne();
		break;
	case PAGE2:
		resultRenderOne();
		resultRenderTwo();
		break;
	case PAGE3:
		resultRenderOne();
		resultRenderTwo();
		resultRenderThree();
	}
	EndSetTexture();
}

void resultControl(void)
{
	CheckKeyState(DIK_RETURN);
	CheckKeyState(DIK_NUMPADENTER);
	CheckKeyState(DIK_SPACE);
	CheckKeyState(DIK_UP);
	CheckKeyState(DIK_DOWN);

	if (KeyState[DIK_RETURN] == KeyRelease || KeyState[DIK_NUMPADENTER] == KeyRelease)
	{
		switch (resultPage)
		{
		case PAGE1:
			resultPage = PAGE2;
			break;
		case PAGE2:
			resultPage = PAGE3;
			break;
		case PAGE3:
			resultPage = PAGE1;
			g_scene = SCENE_TITLE;
			break;
		}
	}
	if (KeyState[DIK_SPACE] == KeyRelease)
	{
		g_scene = SCENE_TITLE;
	}

	GetControl(0);
	BottonCheck();
	if (PadState[ButtonA] == PadRelease) {
		g_scene = SCENE_TITLE;
	}
}

void resultRenderOne(void)
{

	EasyCreateSquareVertex(0, 0, WIDTH, 700, RESULT_BG_TEX);

	CUSTOMVERTEX resultBaseTex1[4];
	CUSTOMVERTEX resultBaseTex2[4];
	CUSTOMVERTEX resultBaseTex3[4];
	CUSTOMVERTEX resultSeleTex1[4];
	CUSTOMVERTEX resultSeleTex2[4];
	CUSTOMVERTEX resultSeleTex3[4];
	CUSTOMVERTEX resultComboTex[4];

	CENTRAL_STATE BaseTexCentral1{ 100,175,50,50 };
	CENTRAL_STATE BaseTexCentral2{ 100,275,50,50 };
	CENTRAL_STATE BaseTexCentral3{ 100,375,50,50 };
	CENTRAL_STATE SeleTexCentral1{ 850,175,50,50 };
	CENTRAL_STATE SeleTexCentral2{ 850,275,50,50 };
	CENTRAL_STATE SeleTexCentral3{ 850,375,50,50 };
	CENTRAL_STATE comboTexCentral{ 640,315,100,100 };

	CreateSquareVertex(resultBaseTex1, BaseTexCentral1);
	CreateSquareVertex(resultBaseTex2, BaseTexCentral2);
	CreateSquareVertex(resultBaseTex3, BaseTexCentral3);
	CreateSquareVertex(resultSeleTex1, SeleTexCentral1);
	CreateSquareVertex(resultSeleTex2, SeleTexCentral2);
	CreateSquareVertex(resultSeleTex3, SeleTexCentral3);
	CreateSquareVertex(resultComboTex, comboTexCentral);

	SetUpTexture(resultBaseTex1, foodGoods[selectedGoods[0]].textureID);
	SetUpTexture(resultBaseTex2, foodGoods[selectedGoods[1]].textureID);
	SetUpTexture(resultBaseTex3, foodGoods[selectedGoods[2]].textureID);
	SetUpTexture(resultSeleTex1, foodGoods[selectedGoods[0]].textureID);
	SetUpTexture(resultSeleTex2, foodGoods[selectedGoods[1]].textureID);
	SetUpTexture(resultSeleTex3, foodGoods[selectedGoods[2]].textureID);
	SetUpTexture(resultComboTex, foodCombo[comboSucceceCheck()].textureID);


	char resulttantValue[32];

	sprintf_s(resulttantValue, 32, "%d~%d=%d", foodGoods[selectedGoods[0]].nominalCost, foodGoods[selectedGoods[0]].haveValue, addPrice(0, 0));
	RECT resultBase1{ 200,150,600,300 };
	WriteWord(resulttantValue, resultBase1, DT_LEFT, BLACK, RESULT_FONT);
	sprintf_s(resulttantValue, 32, "%d~%d=%d", foodGoods[selectedGoods[1]].nominalCost, foodGoods[selectedGoods[1]].haveValue, addPrice(1, 0));
	RECT resultBase2{ 200,250,600,300 };
	WriteWord(resulttantValue, resultBase2, DT_LEFT, BLACK, RESULT_FONT);
	sprintf_s(resulttantValue, 32, "%d~%d=%d", foodGoods[selectedGoods[2]].nominalCost, foodGoods[selectedGoods[2]].haveValue, addPrice(2,0));
	RECT resultBase3{ 200,350,600,500};
	WriteWord(resulttantValue, resultBase3, DT_LEFT, BLACK, RESULT_FONT);
	sprintf_s(resulttantValue, 32, "%d", nomalSum);
	RECT resultBaseTotal{ 200,450,440,600 };
	WriteWord(resulttantValue, resultBaseTotal, DT_RIGHT, BLACK, RESULT_FONT);

	sprintf_s(resulttantValue, 32, "%d~%d=%d", foodGoods[selectedGoods[0]].selePrice, foodGoods[selectedGoods[0]].haveValue, addPrice(0, 1));
	RECT resultSele1{ 950,150,1200,300 };
	WriteWord(resulttantValue, resultSele1, DT_LEFT, BLACK, RESULT_FONT);
	sprintf_s(resulttantValue, 32, "%d~%d=%d", foodGoods[selectedGoods[1]].selePrice, foodGoods[selectedGoods[1]].haveValue, addPrice(1, 1));
	RECT resultSele2{ 950,250,1200,300 };
	WriteWord(resulttantValue, resultSele2, DT_LEFT, BLACK, RESULT_FONT);
	sprintf_s(resulttantValue, 32, "%d~%d=%d", foodGoods[selectedGoods[2]].selePrice, foodGoods[selectedGoods[2]].haveValue, addPrice(2, 1));
	RECT resultSele3{ 950,350,1200,500 };
	WriteWord(resulttantValue, resultSele3, DT_LEFT, BLACK, RESULT_FONT);
	sprintf_s(resulttantValue, 32, "%d", saleSale);
	RECT resultSeleTotal{ 950,450,1200,600 };
	WriteWord(resulttantValue, resultSeleTotal, DT_RIGHT, BLACK, RESULT_FONT);

	sprintf_s(resulttantValue, 32, "%d-%d=%d", nomalSum, saleSale, nomalSum - saleSale);
	RECT resultTotal{ 140,525,1140,700 };
	WriteWord(resulttantValue, resultTotal, DT_CENTER, BLACK, SCORE_FONT);

}

void resultRenderTwo(void)
{
	EasyCreateSquareVertexColor(0, 0, WIDTH, HEIGHT, HARFCLEAR, BLANK);
	EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT,RESULT_POP_TEX);

	char resulttantValue[32];
	sprintf_s(resulttantValue, 32, "%d",nomalSum - saleSale);
	RECT resultTotal{ 50,250,350,400 };
	WriteWord(resulttantValue, resultTotal, DT_CENTER, BLACK, LAST_SCORE_FONT);

}

void resultRenderThree(void)
{
	CUSTOMVERTEX cursol[4];
	CreateSquareVertex(cursol, cursolResult);
	EasyCreateSquareVertex(50, 450, 500, 600, RESULT_END_TEX);
	SetUpTexture(cursol, TITLEICON_TEX);
}

int addPrice(int num, int nomalOrSale)
{
	switch(nomalOrSale)
	{
	case 0:
		return foodGoods[selectedGoods[num]].nominalCost * foodGoods[selectedGoods[num]].haveValue;
		break;
	case 1:
		return foodGoods[selectedGoods[num]].selePrice * foodGoods[selectedGoods[num]].haveValue;
		break;
	}
}
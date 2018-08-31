#include "Goods.h"
#include "Main.h"

TIMESALEPARAMETER popSales[3];

GOODSPARAMETER foodGoods[GOODS_MAX]
{
{BLANKGOODS,BLANK,0,0,0},
//肉
{ BEEF,BEEF_TEX,300,200,0 },
{ PORK,PORK_TEX,200,150,0 },
{ CHICKEN,CHICKEN_TEX,100,80,0 },
{ VIENNESE,VIENNESE_TEX,200,100,0 },
{ MINCE,MINCE_TEX,150,100,0 },
//魚
{ SHRIMP,SHRIMP_TEX,250,200,0 },
{ OCTOPUS,OCTOPUS_TEX,300,180,0 },
{ INKFISH,INKFISH_TEX,200,180,0 },
{ FISH,FISH_TEX,200,150,0 },
//野菜
{ GINESENG,GINESENG_TEX,50,30,0 },
{ ONION,ONION_TEX,60,40,0 },
{ POTATO,POTATO_TEX,65,40,0 },
{ TOMATO,TOMATO_TEX,100,50,0 },
{ RADISH,RADISH_TEX,200,150,0 },
//お菓子
{ POTATOCHIPS,POTATOCHIPS_TEX,100,80,0 },
{ CHOCOLATE,CHOCOLATE_TEX,100,50,0 },
{ ICE,ICE_TEX,150,50,0 },
{ RICECRACKER,RICECRACKER_TEX,100,60,0 },
//果物
{ APPLE,APPLE_TEX,100,80,0 },
{ ORANGE,ORANGE_TEX,200,150,0 },
{ BANANA,BANANA_TEX,100,80,0 },
//飲み物
{ TEA,TEA_TEX,100,70,0 },
{ JUICE,JUICE_TEX,150,80,0 },
{ BEER,BEER_TEX,200,100,0 },

{ MEET,BLANK,0,0,0 },
{ FRUIT,BLANK,0,0,0 },

};

COMBOPARAMETER foodCombo[COMBOMAX]{
{ BURIDAIKON,BURIDAIKON_TEX,RARE1, FISH,RADISH,BLANKGOODS,false },
{ RELISH,RELISH_TEX,RARE1,BEER,VIENNESE, BLANKGOODS,false },
{ TEATIME,TEATIME_TEX, RARE1, TEA, RICECRACKER , BLANKGOODS,false },
{ CURRY, CURRY_TEX,RARE2, POTATO, ONION, MEET,false },
{ HAMBERG,HAMBERG_TEX, RARE2, MINCE, ONION, GINESENG ,false },
{ ASSORTEDSASHIMI,ASSORTEDSASHIMI_TEX, RARE2, SHRIMP, OCTOPUS, INKFISH ,false },
{ AFTERNOONREFRESHMENT,AFTERNOONREFRESHMENT_TEX,RARE2,ICE,JUICE,FRUIT,false },
{ SOUP,SOUP_TEX,RARE3,VIENNESE,TOMATO,ONION ,false },
{ NIMONO,NIMONO_TEX,RARE3,RADISH,FISH,OCTOPUS ,false },
{ PARFAIT,PARFAIT_TEX,RARE3,ICE,FRUIT,FRUIT,false },
{ BLANK_COMBO,BLANK,0,BLANKGOODS,BLANKGOODS,BLANKGOODS,false },

};

struct COMBO_OK {
	bool one;
	bool twe;
	bool three;
};
COMBO_OK checkOk{false,false,false};
int selectedGoods[3];

void comboCheck(int goodsId1, int goodsId2, int goodsId3 )
{
	if (foodGoods[goodsId1].haveValue)
	{
		for (int i = 0; i < COMBOMAX; i++) {
			checkOk.one = false;
			checkOk.twe = false;
			checkOk.three = false;
			if (BLANKGOODS == foodCombo[i].comboElement3 && (!checkOk.three)) {
				checkOk.three = true;
			}
			//1つ目のチェック
			//第一項目
			if (foodGoods[goodsId1].goodsID == foodCombo[i].comboElement1 && (!checkOk.one))
			{
				checkOk.one = true;
			}
			//第二項目
			else if ((foodCombo[i].comboElement2 == FRUIT) && (foodCombo[i].comboElement3 == FRUIT) && (!checkOk.twe))
			{
				if (foodGoods[goodsId1].goodsID == APPLE)
				{
					checkOk.twe = true;
				}
				else if (foodGoods[goodsId1].goodsID == ORANGE)
				{
					checkOk.twe = true;
				}
				else if (foodGoods[goodsId1].goodsID == BANANA)
				{
					checkOk.twe = true;
				}
			}
			else if (foodGoods[goodsId1].goodsID == foodCombo[i].comboElement2 && (!checkOk.twe))
			{
				checkOk.twe = true;
			}
			//第三項目
			else if (foodCombo[i].comboElement3 == MEET && (!checkOk.three))
			{
				if (foodGoods[goodsId1].goodsID == BEEF)
				{
					checkOk.three = true;
				}
				else if (foodGoods[goodsId1].goodsID == PORK)
				{
					checkOk.three = true;
				}
				else if (foodGoods[goodsId1].goodsID == CHICKEN)
				{
					checkOk.three = true;
				}

			}
			else if (foodCombo[i].comboElement3 == FRUIT && (!checkOk.three))
			{
				if (foodGoods[goodsId1].goodsID == APPLE)
				{
					checkOk.three = true;
				}
				else if (foodGoods[goodsId1].goodsID == ORANGE)
				{
					checkOk.three = true;
				}
				else if (foodGoods[goodsId1].goodsID == BANANA)
				{
					checkOk.three = true;
				}
			}
			else if (foodGoods[goodsId1].goodsID == foodCombo[i].comboElement3 && (!checkOk.three))
			{

				checkOk.three = true;
			}
			//2つ目のチェック
			//第一項目
			if (foodGoods[goodsId2].haveValue)
			{
				if (foodGoods[goodsId2].goodsID == foodCombo[i].comboElement1 && (!checkOk.one))
				{
					checkOk.one = true;
				}
				//第二項目
				if ((foodCombo[i].comboElement2 == FRUIT) && (foodCombo[i].comboElement3 == FRUIT) && (!checkOk.twe))
				{
					if (foodGoods[goodsId2].goodsID == APPLE)
					{
						checkOk.twe = true;
					}
					else if (foodGoods[goodsId2].goodsID == ORANGE)
					{
						checkOk.twe = true;
					}
					else if (foodGoods[goodsId2].goodsID == BANANA)
					{
						checkOk.twe = true;
					}
				}
				else if (foodGoods[goodsId2].goodsID == foodCombo[i].comboElement2 && (!checkOk.twe))
				{

					checkOk.twe = true;
				}
				//第三項目
				if (foodCombo[i].comboElement3 == MEET && (!checkOk.three))
				{
					if (foodGoods[goodsId2].goodsID == BEEF)
					{
						checkOk.three = true;
					}
					else if (foodGoods[goodsId2].goodsID == PORK)
					{
						checkOk.three = true;
					}
					else if (foodGoods[goodsId2].goodsID == CHICKEN)
					{
						checkOk.three = true;
					}
				}
				else if (foodCombo[i].comboElement3 == FRUIT && (!checkOk.three))
				{
					if (foodGoods[goodsId2].goodsID == APPLE)
					{
						checkOk.three = true;
					}
					else if (foodGoods[goodsId2].goodsID == ORANGE)
					{
						checkOk.three = true;
					}
					else if (foodGoods[goodsId2].goodsID == BANANA)
					{
						checkOk.three = true;
					}
				}
				else if (foodGoods[goodsId2].goodsID == foodCombo[i].comboElement3 && (!checkOk.three))
				{
					checkOk.three = true;
				}
			}

			//3つ目のチェック
			//第一項目
			if (goodsId3 != BLANKGOODS && foodGoods[goodsId3].haveValue)
			{
				if (foodGoods[goodsId3].goodsID == foodCombo[i].comboElement1 && (!checkOk.one))
				{
					checkOk.one = true;
				}
				//第二項目
				if ((foodCombo[i].comboElement2 == FRUIT) && (foodCombo[i].comboElement3 == FRUIT) && (!checkOk.twe))
				{
					if (foodGoods[goodsId3].goodsID == APPLE)
					{
						checkOk.twe = true;
					}
					else if (foodGoods[goodsId3].goodsID == ORANGE)
					{
						checkOk.twe = true;
					}
					else if (foodGoods[goodsId3].goodsID == BANANA)
					{
						checkOk.twe = true;
					}
				}
				else if (foodGoods[goodsId3].goodsID == foodCombo[i].comboElement2 && (!checkOk.twe))
				{
					checkOk.twe = true;
				}
				//第三項目
				if (foodCombo[i].comboElement3 == MEET && (!checkOk.three))
				{
					if (foodGoods[goodsId3].goodsID == BEEF)
					{
						checkOk.three = true;
					}
					else if (foodGoods[goodsId3].goodsID == PORK)
					{
						checkOk.three = true;
					}
					else if (foodGoods[goodsId3].goodsID == CHICKEN)
					{
						checkOk.three = true;
					}
				}
				else if (foodCombo[i].comboElement3 == FRUIT && (!checkOk.three))
				{
					if (foodGoods[goodsId3].goodsID == APPLE)
					{
						checkOk.three = true;
					}
					else if (foodGoods[goodsId3].goodsID == ORANGE)
					{
						checkOk.three = true;
					}
					else if (foodGoods[goodsId3].goodsID == BANANA)
					{
						checkOk.three = true;
					}

				}
				else if (foodGoods[goodsId3].goodsID == foodCombo[i].comboElement3 && (!checkOk.three))
				{

					checkOk.three = true;
				}
			}
			if (checkOk.one && checkOk.twe && checkOk.three)
			{
				foodCombo[i].comboSucceed = true;
				//g_SoundSuccess = soundsManager.Start("SUCCESS", false) && g_SoundSuccess;
				return;
			}

			if (!checkOk.one || !checkOk.twe || !checkOk.three) {
				//g_SoundSuccess = soundsManager.Start("MISS", false) && g_SoundSuccess;
				foodCombo[i].comboSucceed = false;
			}
		}
	}
}
int comboSucceceCheck(void)
{
	for (int i = 0; i < COMBOMAX; i++) 
	{
		if (foodCombo[i].comboSucceed)
		{
			return i;
		}
	}
	return BLANK_COMBO;
}
void selectGoods(TIMESALEPARAMETER* popSales)
{
	int randBuff[2];
	switch (popSales->goodsSorting)
	{
	case MEET_SORT:
		randBuff[0] = rand() % 5;
		switch (randBuff[0])
		{
		case 0:
			popSales->merchandise[0] = BEEF;
			break;
		case 1:
			popSales->merchandise[0] = PORK;
			break;
		case 2:
			popSales->merchandise[0] = CHICKEN;
			break;
		case 3:
			popSales->merchandise[0] = VIENNESE;
			break;
		case 4:
			popSales->merchandise[0] = MINCE;
			break;
		}

		randBuff[1] = rand() % 5;
		while (randBuff[0] == randBuff[1]) {
			randBuff[1] = rand() % 5;
		}

		switch (randBuff[1])
		{
		case 0:
			popSales->merchandise[1] = BEEF;
			break;
		case 1:
			popSales->merchandise[1] = PORK;
			break;
		case 2:
			popSales->merchandise[1] = CHICKEN;
			break;
		case 3:
			popSales->merchandise[1] = VIENNESE;
			break;
		case 4:
			popSales->merchandise[1] = MINCE;
			break;
		}
		break;
	case VEGETABLE_SORT:
	{
		randBuff[0] = rand() % 5;
		switch (randBuff[0])
		{
		case 0:
			popSales->merchandise[0] = GINESENG;
			break;
		case 1:
			popSales->merchandise[0] = ONION;
			break;
		case 2:
			popSales->merchandise[0] = POTATO;
			break;
		case 3:
			popSales->merchandise[0] = TOMATO;
			break;
		case 4:
			popSales->merchandise[0] = RADISH;
			break;
		}

		randBuff[1] = rand() % 5;

		while (randBuff[0] == randBuff[1]) {
			randBuff[1] = rand() % 5;
		}

		switch (randBuff[1])
		{
		case 0:
			popSales->merchandise[1] = GINESENG;
			break;
		case 1:
			popSales->merchandise[1] = ONION;
			break;
		case 2:
			popSales->merchandise[1] = POTATO;
			break;
		case 3:
			popSales->merchandise[1] = TOMATO;
			break;
		case 4:
			popSales->merchandise[1] = RADISH;
			break;
		}
		break;
	}
	case SEAFOOD_SORT:
	{
		randBuff[0] = rand() % 4;
		switch (randBuff[0])
		{
		case 0:
			popSales->merchandise[0] = SHRIMP;
			break;
		case 1:
			popSales->merchandise[0] = OCTOPUS;
			break;
		case 2:
			popSales->merchandise[0] = INKFISH;
			break;
		case 3:
			popSales->merchandise[0] = FISH;
			break;
		}

		randBuff[1] = rand() % 4;
		while (randBuff[0] == randBuff[1]) {
			randBuff[1] = rand() % 4;
		}

		switch (randBuff[1])
		{
		case 0:
			popSales->merchandise[1] = SHRIMP;
			break;
		case 1:
			popSales->merchandise[1] = OCTOPUS;
			break;
		case 2:
			popSales->merchandise[1] = INKFISH;
			break;
		case 3:
			popSales->merchandise[1] = FISH;
			break;
		}
		break;
	}
	case SWEET_SORT:
	{
		randBuff[0] = rand() % 4;
		switch (randBuff[0])
		{
		case 0:
			popSales->merchandise[0] = POTATOCHIPS;
			break;
		case 1:
			popSales->merchandise[0] = CHOCOLATE;
			break;
		case 2:
			popSales->merchandise[0] = ICE;
			break;
		case 3:
			popSales->merchandise[0] = RICECRACKER;
			break;
		}

		randBuff[1] = rand() % 4;
		while (randBuff[0] == randBuff[1]) {
			randBuff[1] = rand() % 4;
		}

		switch (randBuff[1])
		{
		case 0:
			popSales->merchandise[1] = POTATOCHIPS;
			break;
		case 1:
			popSales->merchandise[1] = CHOCOLATE;
			break;
		case 2:
			popSales->merchandise[1] = ICE;
			break;
		case 3:
			popSales->merchandise[1] = RICECRACKER;
			break;
		}

		break;
	}
	case FRUIT_SORT:
	{
		randBuff[0] = rand() % 3;
		switch (randBuff[0])
		{
		case 0:
			popSales->merchandise[0] = APPLE;
			break;
		case 1:
			popSales->merchandise[0] = ORANGE;
			break;
		case 2:
			popSales->merchandise[0] = BANANA;
			break;
		}

		randBuff[1] = rand() % 3;
		while (randBuff[0] == randBuff[1]) {
			randBuff[1] = rand() % 3;
		}

		switch (randBuff[1])
		{
		case 0:
			popSales->merchandise[1] = APPLE;
			break;
		case 1:
			popSales->merchandise[1] = ORANGE;
			break;
		case 2:
			popSales->merchandise[1] = BANANA;
			break;
		}
		break;
	}
	case DRINK_SORT:
	{
		randBuff[0] = rand() % 3;
		switch (randBuff[0])
		{
		case 0:
			popSales->merchandise[0] = TEA;
			break;
		case 1:
			popSales->merchandise[0] = JUICE;
			break;
		case 2:
			popSales->merchandise[0] = BEER;
			break;
		}

		randBuff[1] = rand() % 3;
		while (randBuff[0] == randBuff[1]) {
			randBuff[1] = rand() % 3;
		}

		switch (randBuff[1])
		{
		case 0:
			popSales->merchandise[1] = TEA;
			break;
		case 1:
			popSales->merchandise[1] = JUICE;
			break;
		case 2:
			popSales->merchandise[1] = BEER;
			break;
		}
		break;
	}
	}
}
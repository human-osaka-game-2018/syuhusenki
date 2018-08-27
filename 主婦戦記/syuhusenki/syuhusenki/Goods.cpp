#include "Goods.h"
#include "Main.h"

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
{ BURIDAIKON,BURIDAIKON_TEX,RARE1, FISH,RADISH,false },
{ RELISH,RELISH_TEX,RARE1,BEER,VIENNESE ,false },
{ TEATIME,TEATIME_TEX, RARE1, TEA, RICECRACKER ,false },
{ CURRY, CURRY_TEX,RARE2, POTATO, ONION, MEET,false },
{ HAMBERG,HAMBERG_TEX, RARE2, MINCE, ONION, GINESENG ,false },
{ ASSORTEDSASHIMI,ASSORTEDSASHIMI_TEX, RARE2, SHRIMP, OCTOPUS, INKFISH ,false },
{ AFTERNOONREFRESHMENT,AFTERNOONREFRESHMENT_TEX,RARE2,ICE,JUICE,FRUIT,false },
{ SOUP,SOUP_TEX,RARE3,VIENNESE,TOMATO,ONION ,false },
{ NIMONO,NIMONO_TEX,RARE3,RADISH,FISH,OCTOPUS ,false },
{ PARFAIT,PARFAIT_TEX,RARE3,ICE,FRUIT,FRUIT,false },
};

struct COMBO_OK {
	bool one;
	bool twe;
	bool three;
};
COMBO_OK checkOk{false,false,false};
void comboCheck(int goodsId1, int goodsId2, int goodsId3 )
{
	if (foodGoods[goodsId1].haveValue)
	{
		for (int i = 0; i < COMBOMAX; i++) {
			checkOk.one = false;
			checkOk.twe = false;
			checkOk.three = false;
			//1つ目のチェック
			//第一項目
			if (foodGoods[goodsId1].goodsID == foodCombo[i].comboElement1 && (!checkOk.one))
			{
				checkOk.one = true; 
			}
			//第二項目
			else if (foodCombo[i == PARFAIT].comboElement2 == FRUIT && foodCombo[i== PARFAIT].comboElement3 == FRUIT && (!checkOk.twe))
			{
				if (foodGoods[goodsId1].goodsID == APPLE)
				{
					checkOk.twe = true; 
				}
				if (foodGoods[goodsId1].goodsID == ORANGE)
				{
					checkOk.twe = true; 
				}
				if (foodGoods[goodsId1].goodsID == BANANA)
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
				if (foodGoods[goodsId1].goodsID == PORK)
				{
					checkOk.three = true; 
				}
				if (foodGoods[goodsId1].goodsID == CHICKEN)
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
				if (foodGoods[goodsId1].goodsID == ORANGE)
				{
					checkOk.three = true; 
				}
				if (foodGoods[goodsId1].goodsID == BANANA)
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
				if (foodCombo[i == PARFAIT].comboElement2 == FRUIT && foodCombo[i == PARFAIT].comboElement3 == FRUIT && (!checkOk.twe))
				{
					if (foodGoods[goodsId2].goodsID == APPLE)
					{
						checkOk.twe = true; 
					}
					if (foodGoods[goodsId2].goodsID == ORANGE)
					{
						checkOk.twe = true; 
					}
					if (foodGoods[goodsId2].goodsID == BANANA)
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
					if (foodGoods[goodsId2].goodsID == PORK)
					{
						checkOk.three = true; 
					}
					if (foodGoods[goodsId2].goodsID == CHICKEN)
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
					if (foodGoods[goodsId2].goodsID == ORANGE)
					{
						checkOk.three = true; 
					}
					if (foodGoods[goodsId2].goodsID == BANANA)
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
				if (foodCombo[i == PARFAIT].comboElement2 == FRUIT && foodCombo[i == PARFAIT].comboElement3 == FRUIT && (!checkOk.twe))
				{
					if (foodGoods[goodsId3].goodsID == APPLE)
					{
						checkOk.twe = true; 
					}
					if (foodGoods[goodsId3].goodsID == ORANGE)
					{
						checkOk.twe = true; 
					}
					if (foodGoods[goodsId3].goodsID == BANANA)
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
					if (foodGoods[goodsId3].goodsID == PORK)
					{
						checkOk.three = true; 
					}
					if (foodGoods[goodsId3].goodsID == CHICKEN)
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
					if (foodGoods[goodsId3].goodsID == ORANGE)
					{
						checkOk.three = true; 
					}
					if (foodGoods[goodsId3].goodsID == BANANA)
					{
						checkOk.three = true; 
					}

				}
				else if (foodGoods[goodsId3].goodsID == foodCombo[i].comboElement3 && (!checkOk.three))
				{
					
					checkOk.three = true; 
				}
			}
			else if (goodsId3 == BLANKGOODS) {
				checkOk.three = true;
			}
			if (checkOk.one && checkOk.twe && checkOk.three)
			{
				foodCombo[i].comboSucceed = true;
				g_SoundSuccess = soundsManager.Start("SUCCESS", false) && g_SoundSuccess;
			}
			else if (!checkOk.one || !checkOk.twe || !checkOk.three) {
				g_SoundSuccess = soundsManager.Start("MISS", false) && g_SoundSuccess;
			}
		}
	}
}

void selectGoods(int goodssort,int goodsSelector[]) {
	int randBuff[2];
	switch (goodssort)
	{
	case MEET_SORT:
		randBuff[0] = rand() % 5;
		switch (randBuff[0])
		{
			case 0:
				goodsSelector[0] = BEEF;
			break;
			case 1:
				goodsSelector[0] = PORK;
				break;
			case 2:
				goodsSelector[0] = CHICKEN;
				break;
			case 3:
				goodsSelector[0] = VIENNESE;
				break;
			case 4:
				goodsSelector[0] = MINCE;
				break;
		}

		randBuff[1] = rand() % 5;
		while (randBuff[0] == randBuff[1]) {
			randBuff[1] = rand() % 5;
		}

		switch (randBuff[1])
		{
		case 0:
			goodsSelector[1] = BEEF;
			break;
		case 1:
			goodsSelector[1] = PORK;
			break;
		case 2:
			goodsSelector[1] = CHICKEN;
			break;
		case 3:
			goodsSelector[1] = VIENNESE;
			break;
		case 4:
			goodsSelector[1] = MINCE;
			break;
		}

		//goodsSelector[0]
		break;
	case VEGETABLE_SORT:
		break;
	case SEAFOOD_SORT:
		break;
	case FRUIT_SORT:
		break;
	case DRINK_SORT:
		break;
	}
}
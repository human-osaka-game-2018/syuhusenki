#include "Goods.h"
#include "Main.h"

GOODSPARAMETER foodGoods[GOODS_MAX]
{
{BLANKGOODS,0,0,0},
//肉
{ BEEF,300,200,0 },
{ PORK,200,150,0 },
{ CHICKEN,100,80,0 },
{ VIENNESE,200,100,0 },
{ MINCE,150,100,0 },
//魚
{ SHRIMP,250,200,0 },
{ OCTOPUS,300,180,0 },
{ INKFISH,200,180,0 },
{ FISH,200,150,0 },
//野菜
{ GINESENG,50,30,0 },
{ ONION,60,40,0 },
{ POTATO,65,40,0 },
{ TOMATO,100,50,0 },
{ RADISH,200,150,0 },
//お菓子
{ POTATOCHIPS,100,80,0 },
{ CHOCOLATE,100,50,0 },
{ ICE,150,50,0 },
{ RICECRACKER,100,60,0 },
//果物
{ APPLE,100,80,0 },
{ ORANGE,200,150,0 },
{ BANANA, 100,80,0 },
//飲み物
{ TEA,100,70,0 },
{ JUICE,150,80,0 },
{ BEER,200,100,0 },

{ MEET,0,0,0 },
{ FRUIT,0,0,0 },

};

COMBOPARAMETER foodCombo[COMBOMAX]{
{ BURIDAIKON,100, FISH,RADISH,false },
{ RELISH,100,BEER,VIENNESE ,false },
{ TEATIME, 100, TEA, RICECRACKER ,false },
{ CURRY, 150, POTATO, ONION, MEET,false },
{ HAMBERG, 150, MINCE, ONION, GINESENG ,false },
{ ASSORTEDSASHIMI, 150, SHRIMP, OCTOPUS, INKFISH ,false },
{ AFTERNOONREFRESHMENT,150,ICE,JUICE,FRUIT,false },
{ SOUP,200,VIENNESE,TOMATO,ONION ,false },
{ NIMONO,200,RADISH,FISH,OCTOPUS ,false },
{ PARFAIT,200,ICE,FRUIT,FRUIT,false },
};

struct COMBO_OK {
	bool one;
	bool twe;
	bool three;
};
COMBO_OK checkOk{false,false,false};
int count = 0;
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
				checkOk.one = true; count++;
			}
			//第二項目
			else if (foodCombo[i == PARFAIT].comboElement2 == FRUIT && foodCombo[i== PARFAIT].comboElement3 == FRUIT && (!checkOk.twe))
			{
				if (foodGoods[goodsId1].goodsID == APPLE)
				{
					checkOk.twe = true; count++;
				}
				if (foodGoods[goodsId1].goodsID == ORANGE)
				{
					checkOk.twe = true; count++;
				}
				if (foodGoods[goodsId1].goodsID == BANANA)
				{
					checkOk.twe = true; count++;
				}
			}
			else if (foodGoods[goodsId1].goodsID == foodCombo[i].comboElement2 && (!checkOk.twe))
			{
				checkOk.twe = true; count++;
			}
			//第三項目
			else if (foodCombo[i].comboElement3 == MEET && (!checkOk.three))
			{
				if (foodGoods[goodsId1].goodsID == BEEF)
				{
					checkOk.three = true; count++;
				}
				if (foodGoods[goodsId1].goodsID == PORK)
				{
					checkOk.three = true; count++;
				}
				if (foodGoods[goodsId1].goodsID == CHICKEN)
				{
					checkOk.three = true; count++;
				}

			}
			else if (foodCombo[i].comboElement3 == FRUIT && (!checkOk.three))
			{
				if (foodGoods[goodsId1].goodsID == APPLE)
				{
					checkOk.three = true; count++;
				}
				if (foodGoods[goodsId1].goodsID == ORANGE)
				{
					checkOk.three = true; count++;
				}
				if (foodGoods[goodsId1].goodsID == BANANA)
				{
					checkOk.three = true; count++;
				}
			}
			else if (foodGoods[goodsId1].goodsID == foodCombo[i].comboElement3 && (!checkOk.three))
			{

				checkOk.three = true; count++;
			}
			//2つ目のチェック
			//第一項目
			if (foodGoods[goodsId2].haveValue)
			{
				if (foodGoods[goodsId2].goodsID == foodCombo[i].comboElement1 && (!checkOk.one))
				{
					checkOk.one = true; count++;
				}
				//第二項目
				if (foodCombo[i == PARFAIT].comboElement2 == FRUIT && foodCombo[i == PARFAIT].comboElement3 == FRUIT && (!checkOk.twe))
				{
					if (foodGoods[goodsId2].goodsID == APPLE)
					{
						checkOk.twe = true; count++;
					}
					if (foodGoods[goodsId2].goodsID == ORANGE)
					{
						checkOk.twe = true; count++;
					}
					if (foodGoods[goodsId2].goodsID == BANANA)
					{
						checkOk.twe = true; count++;
					}
				}
				else if (foodGoods[goodsId2].goodsID == foodCombo[i].comboElement2 && (!checkOk.twe))
				{

					checkOk.twe = true; count++;
				}
				//第三項目
				if (foodCombo[i].comboElement3 == MEET && (!checkOk.three))
				{
					if (foodGoods[goodsId2].goodsID == BEEF)
					{
						checkOk.three = true; count++;
					}
					if (foodGoods[goodsId2].goodsID == PORK)
					{
						checkOk.three = true; count++;
					}
					if (foodGoods[goodsId2].goodsID == CHICKEN)
					{
						checkOk.three = true; count++;
					}
				}
				else if (foodCombo[i].comboElement3 == FRUIT && (!checkOk.three))
				{
					if (foodGoods[goodsId2].goodsID == APPLE)
					{
						checkOk.three = true; count++;
					}
					if (foodGoods[goodsId2].goodsID == ORANGE)
					{
						checkOk.three = true; count++;
					}
					if (foodGoods[goodsId2].goodsID == BANANA)
					{
						checkOk.three = true; count++;
					}
				}
				else if (foodGoods[goodsId2].goodsID == foodCombo[i].comboElement3 && (!checkOk.three))
				{
					checkOk.three = true; count++;
				}
			}

			//3つ目のチェック
			//第一項目
			if (goodsId3 != BLANKGOODS && foodGoods[goodsId3].haveValue)
			{
				if (foodGoods[goodsId3].goodsID == foodCombo[i].comboElement1 && (!checkOk.one))
				{
					checkOk.one = true; count++;
				}
				//第二項目
				if (foodCombo[i == PARFAIT].comboElement2 == FRUIT && foodCombo[i == PARFAIT].comboElement3 == FRUIT && (!checkOk.twe))
				{
					if (foodGoods[goodsId3].goodsID == APPLE)
					{
						checkOk.twe = true; count++;
					}
					if (foodGoods[goodsId3].goodsID == ORANGE)
					{
						checkOk.twe = true; count++;
					}
					if (foodGoods[goodsId3].goodsID == BANANA)
					{
						checkOk.twe = true; count++;
					}
				}
				else if (foodGoods[goodsId3].goodsID == foodCombo[i].comboElement2 && (!checkOk.twe))
				{
					checkOk.twe = true; count++;
				}
				//第三項目
				if (foodCombo[i].comboElement3 == MEET && (!checkOk.three))
				{
					if (foodGoods[goodsId3].goodsID == BEEF)
					{
						checkOk.three = true; count++;
					}
					if (foodGoods[goodsId3].goodsID == PORK)
					{
						checkOk.three = true; count++;
					}
					if (foodGoods[goodsId3].goodsID == CHICKEN)
					{
						checkOk.three = true; count++;
					}
				}
				else if (foodCombo[i].comboElement3 == FRUIT && (!checkOk.three))
				{
					if (foodGoods[goodsId3].goodsID == APPLE)
					{
						checkOk.three = true; count++;
					}
					if (foodGoods[goodsId3].goodsID == ORANGE)
					{
						checkOk.three = true; count++;
					}
					if (foodGoods[goodsId3].goodsID == BANANA)
					{
						checkOk.three = true; count++;
					}

				}
				else if (foodGoods[goodsId3].goodsID == foodCombo[i].comboElement3 && (!checkOk.three))
				{
					
					checkOk.three = true; count++;
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
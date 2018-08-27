#ifndef GOODS_H
#define GOODS_H

#define RARE1 100
#define RARE2 150
#define RARE3 200

enum GOODSNUMBER {
	BLANKGOODS,
	BEEF,
	PORK,
	CHICKEN,
	VIENNESE,
	MINCE,
	SHRIMP,
	OCTOPUS,
	INKFISH,
	FISH,
	GINESENG,
	ONION,
	POTATO,
	TOMATO,
	RADISH,
	POTATOCHIPS,
	CHOCOLATE,
	ICE,
	RICECRACKER,
	APPLE,
	ORANGE,
	BANANA,
	TEA,
	JUICE,
	BEER,
	MEET,
	FRUIT,
	GOODS_MAX
};

enum COMBOMEUE {
	BURIDAIKON,
	RELISH,
	TEATIME,
	CURRY,
	HAMBERG,
	ASSORTEDSASHIMI,
	AFTERNOONREFRESHMENT,
	SOUP,
	NIMONO,
	PARFAIT,
	COMBOMAX
};

enum GOODSSORTING
{
	MEET_SORT,
	VEGETABLE_SORT,
	SEAFOOD_SORT,
	FRUIT_SORT,
	DRINK_SORT
};
struct GOODSPARAMETER {
	const int goodsID;
	const int textureID;
	const int nominalCost;
	const int selePrice;
	int haveValue;

};

struct COMBOPARAMETER {
	const int comboID;
	const int textureID;
	const int comboBonus;
	const int comboElement1;
	const int comboElement2;
	const int comboElement3;
	bool comboSucceed;
};
extern GOODSPARAMETER foodGoods[GOODS_MAX];
extern COMBOPARAMETER foodCombo[COMBOMAX];

void comboCheck(int goodsId1, int goodsId2, int goodsId3);
void selectGoods(int goodssort, int goodsSelector[]);
#endif
#ifndef GOODS_H
#define GOODS_H

enum GOODSNUMBER {
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
	CONBOMAX
};

struct GOODSPARAMETER {
	const int goodsID;
	const int nominalCost;
	const int selePrice;
	int haveValue;
};

struct COMBOPARAMETER {
	const int comboID;
	const int comboBonus;
	const int comboElement1;
	const int comboElement2;
	const int comboElement3;
};

//ì˜
extern GOODSPARAMETER beef;
extern GOODSPARAMETER pork;
extern GOODSPARAMETER chicken;
extern GOODSPARAMETER viennese;
extern GOODSPARAMETER mince;
//ãõ
extern GOODSPARAMETER shrimp;
extern GOODSPARAMETER octopus;
extern GOODSPARAMETER inkfish;
extern GOODSPARAMETER fish;
//ñÏçÿ
extern GOODSPARAMETER ginseng;
extern GOODSPARAMETER onion;
extern GOODSPARAMETER potato;
extern GOODSPARAMETER tomato;
extern GOODSPARAMETER radish;
//Ç®âŸéq
extern GOODSPARAMETER potatoChips;
extern GOODSPARAMETER chocolate;
extern GOODSPARAMETER ice;
extern GOODSPARAMETER riceCracker;
//â ï®
extern GOODSPARAMETER apple;
extern GOODSPARAMETER orange;
extern GOODSPARAMETER banana;
//à˘Ç›ï®
extern GOODSPARAMETER tea;
extern GOODSPARAMETER juice;
extern GOODSPARAMETER beer;



#endif
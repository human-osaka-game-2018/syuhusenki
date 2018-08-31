#ifndef GAMEMAIN_H
#define GAMEMAIN_H


struct SoundEffect {
	const char SE1[20];
	const char SE2[20];
	const char SE3[20];
	const char SE4[20];
	const char SE5[20];
	const char SE6[20];
	const char SE7[20];
	const char SE8[20];
	const char SE9[20];
	const char SE10[20];

};

enum GAMESCENE {
	FLOAMOVE,
	CHOSEGOODS,
	PUSHENEMY,
	PICKGOODS,
#ifdef _DEBUG
	TESTSCENE,
#endif
};

enum FLOA {
	FOOD,
	CLOTH
};

extern int texturePC;
extern int g_selectFloa;
extern int g_gameScene;
extern SoundEffect Button;
extern int turn;
void gameMain();
void goodsScoreShow();
void buttonSE(SoundEffect Button, int SoundNumber);

#endif
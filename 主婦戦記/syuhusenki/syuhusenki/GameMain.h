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
};
enum GAMESCENE {
	FLOAMOVE,
	PUSHENEMY,
	PICKGOODS
};
extern int g_gameScene;
extern SoundEffect Button;

void gameMain();

void buttonSE(SoundEffect Button, int SoundNumber);

#endif
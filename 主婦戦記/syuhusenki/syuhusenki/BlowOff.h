#ifndef BLOWOFF_H
#define BLOWOFF_H


extern CUSTOMVERTEX effectExplosion[4];
extern CENTRAL_STATE effectExplosionCentral;

extern bool g_isBlowOff;

void blowOff();
void blowOffControl();
void blowOffRender();
void blowOffDeviseControl(int* i, int comand[]);
void madamBlowOff();
int comandCheck(int comand[], int inputComand[], int count);
void comandMake();
char comandButton(int comand);
int comandButtonTexture(int comand);

#endif
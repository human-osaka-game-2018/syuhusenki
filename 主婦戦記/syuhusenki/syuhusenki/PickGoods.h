#ifndef PICKGOODS_H
#define PICKGOODS_H



extern CENTRAL_STATE playerCutinCentral;
extern int salesChoice;

void pickGoods();
void pickGoodsControl();
void pickGoodsRender();
void pickGoodsDeviseControl(int* rushInput);
void rushButtonCheck(int rushInput, int rushShow);

#endif
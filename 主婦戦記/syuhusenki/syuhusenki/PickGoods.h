#ifndef PICKGOODS_H
#define PICKGOODS_H



extern CENTRAL_STATE playerCutinCentral;

void pickGoods();
void pickGoodsControl();
void pickGoodsRender();
void pickGoodsDeviseControl(int* rushInput);
void rushButtonCheck(int rushInput, int rushShow);

#endif
#ifndef FLOAMOVE_H
#define FLOAMOVE_H

enum SALESPOSITION
{
	POS_MEET,
	POS_VEGETABLE1,
	POS_VEGETABLE2,
	POS_SEAFOOD1,
	POS_SEAFOOD2,
	POS_SWEET1,
	POS_SWEET2,
	POS_SWEET3,
	POS_DRINK1,
	POS_DRINK2,
	POS_FRUIT1,
	POS_FRUIT2,
	POS_FRUIT3,
	POS_NOTING
};

//ƒ‚ƒu‚Ì‰æ‘œ’¸“_
extern CUSTOMVERTEX mobFloa[4];
extern CENTRAL_STATE mobCentralFloa[4];
extern CENTRAL_STATE mobCentralBlowOff[5];

extern CENTRAL_STATE g_PCSta;
extern CENTRAL_STATE g_startCountSta;
extern CENTRAL_STATE g_startSta;

void floaMove();

#endif // !FLOAMOVE_H
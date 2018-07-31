#ifndef TRIALLIB_H
#define TRIALLIB_H

#include <Windows.h>
#include <d3dx9.h>
#include <dinput.h>
#include <D3dx9core.h>
#include <time.h>
#include <stdio.h>
#include<Xinput.h>

#include "TrialEnums.h"//自分のslnフォルダに入れておくこと

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "Xinput.lib")


enum PADSTATE
{
	PadOn,
	PadOff,
	PadPush,
	PadRelease
};

enum ButtonIndex
{
	ButtonA,
	ButtonB,
	ButtonX,
	ButtonY,
	ButtonRB,
	ButtonLB,
	ButtonStart,
	ButtonBack,
	ButtonUP,
	ButtonDOWN,
	ButtonLEFT,
	ButtonRIGHT,
	buttomindexMAX
};

enum Analog
{
	ANALOGUP,
	ANALOGDOWN,
	ANALOGLEFT,
	ANALOGRIGHT,
	ANALOGMAX
};



typedef struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;
	DWORD	color;
	FLOAT	tu, tv;
}CUSTOMVERTEX;

struct CENTRAL_STATE
{
	float x, y, scaleX, scaleY;
};
struct CIRCLE_STATE{
	int x, y, r;//中心X座標、中心Y座標、半径

};

extern LPDIRECT3D9 g_pDirect3D;		//	Direct3Dのインターフェイス
extern LPDIRECT3DTEXTURE9	  g_pTexture[128];	//	画像の情報を入れておく為のポインタ配列
extern IDirect3DDevice9*	  g_pD3Device;		//	Direct3Dのデバイス
extern D3DDISPLAYMODE		  g_D3DdisplayMode;
extern D3DPRESENT_PARAMETERS g_D3dPresentParameters;
extern LPDIRECTINPUT8 g_pDinput;
extern LPDIRECTINPUTDEVICE8 g_pKeyDevice;
extern LPD3DXFONT g_pFont[128];
extern PADSTATE PadState[buttomindexMAX];
extern PADSTATE PadOldState[buttomindexMAX];
extern BYTE KeyState[256];
extern BYTE KeyOldState[256];



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT InitD3d(HWND hWnd, LPCSTR pSrcFile);
HRESULT InitDinput(HWND hWnd);
HRESULT InitDirectX(HWND hWnd, LPCSTR pSrcFile);

void FreeDx();

//WINAPIの空ウィンドウ生成
int InitWindow(LPCSTR WndName, int WIDTH, int HEIGHT, HINSTANCE hInst, HINSTANCE hInstance, int IconIDI, LPCSTR pSrcFile);
int InitWindowEx(LPCSTR WndName, HWND* hWnd, int WIDTH, int HEIGHT, HINSTANCE hInst, HINSTANCE hInstance, int IconIDI, LPCSTR pSrcFile);

int FlameRoop(void gameroop(void));

//描画
void BeginSetTexture();
void EndSetTexture();

//画像読み込み
void ReadInTexture(LPCSTR pTextureName, int TexNum);

//画像表示
void SetUpTexture(CUSTOMVERTEX* Vertex, int TexNum);

//2頂点設定描画
void EasyCreateSquareVertex(float Left, float Top, float Right, float Bottom, int TexNum);
void EasyCreateSquareVertexColor(float Left, float Top, float Right, float Bottom, DWORD color, int TexNum);
void EasyCreateSquareVertexEx( float Left, float Top, float Right, float Bottom, DWORD  color, float tu, float tv, float scaleTu, float scaleTv, int TexNum);

//RECT引数2頂点設定描画
void EasyCreateRECTVertex(RECT Vertex, int TexNum);
void EasyCreateRECTVertexColor(RECT Vertex, DWORD color, int TexNum);
void EasyCreateRECTVertexEx(RECT Vertex, DWORD color, float tu, float tv, float scaleTu, float scaleTv, int TexNum);

//4頂点設定
void CreateSquareVertex(CUSTOMVERTEX* Vertex, CENTRAL_STATE Central);
void CreateSquareVertexEx(CUSTOMVERTEX* Vertex, CENTRAL_STATE Central, float tu, float tv, float scaleTu, float scaleTv);
void CreateSquareVertexColorEx(CUSTOMVERTEX* Vertex, CENTRAL_STATE Central, DWORD  color, float tu, float tv, float scaleTu, float scaleTv);
void CreateSquareVertexColor(CUSTOMVERTEX* Vertex, CENTRAL_STATE Central, DWORD  color);

//DXフォント
//文字設定
void SetUpFont(int WordHeight, int WordWidth, int CharSet, LPCSTR FontName, int FontNum);
//描画設定
void WriteWord(LPCSTR Texts, RECT Vertex, int TextFormat, int color, int FontNum);

//回転、円運動関数
void RevolveAndCircularMotion(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float motionRadius);
//回転、楕円運動関数
void RevolveAndOvalCircularMotion(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float motionRadiusX, float motionRadiusY);
//Z軸回転
void RevolveZ(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central);
void RevolveZEX(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float 	RevolvingShaftX, float 	RevolvingShaftY);
//Y軸回転
void RevolveY(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central);
void RevolveYEX(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float RevolvingShaftX, float RevolvingShaftZ);
//X軸回転
void RevolveX(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central);
void RevolveXEX(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float RevolvingShaftY, float RevolvingShaftZ);
//円運動
void CircularMotion(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float motionRadius);
//楕円運動
void OvalCircularMotion(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float motionRadiusX, float motionRadiusY);

//Dinputキーボード
bool InputKEY(int KeyName);
void CheckKeyState(int KeyName);
//XInput
void GetControl(int GamePadNumber);
PADSTATE GetButton(ButtonIndex index);
bool GetAnalogL(Analog analogstate);
bool GetAnalogR(Analog AnalogState);
void CheckButtonState(WORD, int);
void BottonCheck();
//当たり判定
////円と円の当たり判定
bool CtoCContact(float PosX1, float PosY1, float Radius1, float PosX2, float PosY2, float Radius2);
bool CtoCContact(CIRCLE_STATE* a, CIRCLE_STATE* b);
////矩形と矩形の当たり判定
bool BtoBContact(CENTRAL_STATE* central1, CENTRAL_STATE* central2);
//行動エリア制限
////矩形が指定範囲外に出ないようにする
void MoveInToErea(CENTRAL_STATE* central, float Left, float Top, float Right, float Bottom);

#endif TRIALLIB_H
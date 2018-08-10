#include "TrialLib.h"

#pragma comment(lib, "DirectX_LIB.lib")



#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

LPDIRECT3D9 g_pDirect3D;		//	Direct3Dのインターフェイス
LPDIRECT3DTEXTURE9	  g_pTexture[128];	//	画像の情報を入れておく為のポインタ配列
IDirect3DDevice9*	  g_pD3Device = NULL;		//	Direct3Dのデバイス
D3DDISPLAYMODE		  g_D3DdisplayMode;
D3DPRESENT_PARAMETERS g_D3dPresentParameters;
LPDIRECTINPUT8 g_pDinput = NULL;
LPDIRECTINPUTDEVICE8 g_pKeyDevice = NULL;
LPD3DXFONT g_pFont[128];

XINPUT_STATE g_Xinput;
PADSTATE PadState[ButtomIndexMAX];
PADSTATE PadOldState[ButtomIndexMAX] = { PadOff };
BYTE KeyState[256];
BYTE KeyOldState[256] = { PadOff };


void FreeDx()
{
	SAFE_RELEASE(g_pD3Device);
	SAFE_RELEASE(g_pDirect3D);
	SAFE_RELEASE(g_pDinput);

	for (int i = 0; i <= TEXMAX; i++)
	{
		SAFE_RELEASE(g_pTexture[i]);
	}
	for (int i = 0; i < FONTMAX; i++)
	{
		SAFE_RELEASE(g_pFont[i]);
	}


}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}

HRESULT InitD3d(HWND hWnd, LPCSTR pSrcFile)
{
	// 「Direct3D」オブジェクトの作成
	if (!(g_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "Direct3Dの作成に失敗しました", "", MB_OK);
		return E_FAIL;
	}

	// 「DIRECT3Dデバイス」オブジェクトの作成
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;

	if (FAILED(g_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING,
		&d3dpp, &g_pD3Device)))
	{
		MessageBox(0, "HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します", NULL, MB_OK);
		if (FAILED(g_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
			D3DCREATE_MIXED_VERTEXPROCESSING,
			&d3dpp, &g_pD3Device)))
		{
			MessageBox(0, "DIRECT3Dデバイスの作成に失敗しました", NULL, MB_OK);
			return E_FAIL;
		}
	}
	//「テクスチャオブジェクト」の作成
	if (FAILED(D3DXCreateTextureFromFileEx(g_pD3Device, pSrcFile, 100, 100, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT,
		0xff000000, NULL, NULL, &g_pTexture[TEXMAX])))
	{
		MessageBox(0, "テクスチャの作成に失敗しました", "", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}
HRESULT InitD3dFullscreen(HWND hWnd, LPCSTR pSrcFile, int ResolutionWidth, int ResolutionHeight)
{
	// 「Direct3D」オブジェクトの作成
	if (!(g_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "Direct3Dの作成に失敗しました", "", MB_OK);
		return E_FAIL;
	}

	// 「DIRECT3Dデバイス」オブジェクトの作成
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = ResolutionWidth;
	d3dpp.BackBufferHeight = ResolutionHeight;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;
	//d3dpp.EnableAutoDepthStencil = TRUE;
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	if (FAILED(g_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING,
		&d3dpp, &g_pD3Device)))
	{
		MessageBox(0, "HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します", NULL, MB_OK);
		if (FAILED(g_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
			D3DCREATE_MIXED_VERTEXPROCESSING,
			&d3dpp, &g_pD3Device)))
		{
			MessageBox(0, "DIRECT3Dデバイスの作成に失敗しました", NULL, MB_OK);
			return E_FAIL;
		}
	}
	//「テクスチャオブジェクト」の作成
	if (FAILED(D3DXCreateTextureFromFileEx(g_pD3Device, pSrcFile, 100, 100, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT,
		0xff000000, NULL, NULL, &g_pTexture[TEXMAX])))
	{
		MessageBox(0, "テクスチャの作成に失敗しました", "", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

HRESULT InitDinput(HWND hWnd) {
	HRESULT hr;
	// 「DirectInput」オブジェクトの作成
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&g_pDinput, NULL)))
	{
		return hr;
	}
	// 「DirectInputデバイス」オブジェクトの作成
	if (FAILED(hr = g_pDinput->CreateDevice(GUID_SysKeyboard,
		&g_pKeyDevice, NULL)))
	{
		return hr;
	}
	// デバイスをキーボードに設定
	if (FAILED(hr = g_pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}
	// 協調レベルの設定
	if (FAILED(hr = g_pKeyDevice->SetCooperativeLevel(
		hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}
	// デバイスを「取得」する
	g_pKeyDevice->Acquire();
	return S_OK;
}

//初期化関数
HRESULT InitDirectX(HWND hWnd, LPCSTR pSrcFile) {
	//ダイレクト３Dの初期化関数を呼ぶ
	if (FALSE(InitD3d(hWnd, pSrcFile)))
	{
		MessageBox(0, "DirectXの初期化に失敗しました", "", MB_OK);
		return 0;
	}
	else InitD3d(hWnd, pSrcFile);

	//ダイレクトインプットの初期化関数を呼ぶ
	if (FAILED(InitDinput(hWnd)))
	{
		MessageBox(0, "DirectInputの初期化に失敗しました", "", MB_OK);
		return E_FAIL;
	}
	else InitDinput(hWnd);

	//Display Mode の設定
	g_pDirect3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,
		&g_D3DdisplayMode);

	ZeroMemory(&g_D3dPresentParameters,
		sizeof(D3DPRESENT_PARAMETERS));
	g_D3dPresentParameters.BackBufferFormat = g_D3DdisplayMode.Format;
	g_D3dPresentParameters.BackBufferCount = 1;
	g_D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3dPresentParameters.Windowed = TRUE;

	//デバイスを作る
	g_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&g_D3dPresentParameters, &g_pD3Device);
	//生成チェック
	if (!g_pD3Device)
	{
		//生成に失敗したらDirectXオブジェクトを開放して終了する
		g_pDirect3D->Release();
		return E_FAIL;
	}
	//描画設定
	g_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
	g_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	//頂点に入れるデータを設定
	g_pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);

	return S_OK;
}
HRESULT InitDirectXFullscreen(HWND hWnd, LPCSTR pSrcFile,int ResolutionWidth,int ResolutionHeight) {
	//ダイレクト３Dの初期化関数を呼ぶ
	if (FALSE(InitD3dFullscreen(hWnd, pSrcFile, ResolutionWidth, ResolutionHeight)))
	{
		MessageBox(0, "DirectXの初期化に失敗しました", "", MB_OK);
		return 0;
	}
	else InitD3dFullscreen(hWnd, pSrcFile, ResolutionWidth, ResolutionHeight);

	//ダイレクトインプットの初期化関数を呼ぶ
	if (FAILED(InitDinput(hWnd)))
	{
		MessageBox(0, "DirectInputの初期化に失敗しました", "", MB_OK);
		return E_FAIL;
	}
	else InitDinput(hWnd);

	//Display Mode の設定
	g_pDirect3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,
		&g_D3DdisplayMode);

	ZeroMemory(&g_D3dPresentParameters, sizeof(D3DPRESENT_PARAMETERS));
	g_D3dPresentParameters.BackBufferFormat = g_D3DdisplayMode.Format;
	g_D3dPresentParameters.BackBufferCount = 1;
	g_D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3dPresentParameters.Windowed = TRUE;

	ZeroMemory(&g_D3dPresentParameters, sizeof(D3DPRESENT_PARAMETERS));
	g_D3dPresentParameters.BackBufferWidth = ResolutionWidth;
	g_D3dPresentParameters.BackBufferHeight = ResolutionHeight;
	g_D3dPresentParameters.BackBufferFormat = D3DFMT_X8R8G8B8;
	g_D3dPresentParameters.BackBufferCount = 1;
	g_D3dPresentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	g_D3dPresentParameters.MultiSampleQuality = 0;
	g_D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3dPresentParameters.hDeviceWindow = hWnd;
	g_D3dPresentParameters.Windowed = FALSE;
	//g_D3dPresentParameters.EnableAutoDepthStencil = FALSE;
	//g_D3dPresentParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	g_D3dPresentParameters.Flags = 0;
	g_D3dPresentParameters.FullScreen_RefreshRateInHz = 0;
	g_D3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//デバイスを作る
	g_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&g_D3dPresentParameters, &g_pD3Device);
	//生成チェック
	if (!g_pD3Device)
	{
		//生成に失敗したらDirectXオブジェクトを開放して終了する
		g_pDirect3D->Release();
		return E_FAIL;
	}
	//描画設定
	g_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
	g_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	//頂点に入れるデータを設定
	g_pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);

	return S_OK;
}

//WINAPIの空ウィンドウ生成
int InitWindow(LPCSTR WndName,int WIDTH,int HEIGHT, HINSTANCE hInst, HINSTANCE hInstance,int IconIDI, LPCSTR pSrcFile) {
	
	HWND hWnd = NULL;
	
	WNDCLASS Wndclass;

	//Windows情報の設定
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = hInst;
	Wndclass.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IconIDI));
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = WndName;

	RegisterClass(&Wndclass);
	//Windowの登録

	//Windowの生成
	hWnd = CreateWindow(
		WndName,						//ウィンドウのクラス名
		WndName,  				//ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//ウィンドウスタイル
		CW_USEDEFAULT,						// ウィンドウの横方向の位置x
		CW_USEDEFAULT,						// ウィンドウの縦方向の位置y
		WIDTH,							// Width（幅）
		HEIGHT,							// Height（高さ）
		NULL,
		NULL,
		hInstance,							// アプリケーションインスタンスのハンドル
		NULL
	);

	if (!hWnd) {
		return 0;
	}

	if (FAILED(InitDirectX(hWnd,pSrcFile)))
	{
		return 0;
	}
}
int InitWindowEx(LPCSTR WndName, HWND* hWnd, int WIDTH, int HEIGHT, HINSTANCE hInst, HINSTANCE hInstance, int IconIDI, LPCSTR pSrcFile) {

	WNDCLASS Wndclass;

	//Windows情報の設定
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = hInst;
	Wndclass.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IconIDI));
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = WndName;

	RegisterClass(&Wndclass);
	//Windowの登録

	//Windowの生成
	*hWnd = CreateWindow(
		WndName,						//ウィンドウのクラス名
		WndName,  				//ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//ウィンドウスタイル
		CW_USEDEFAULT,						// ウィンドウの横方向の位置x
		CW_USEDEFAULT,						// ウィンドウの縦方向の位置y
		WIDTH,							// Width（幅）
		HEIGHT,							// Height（高さ）
		NULL,
		NULL,
		hInstance,							// アプリケーションインスタンスのハンドル
		NULL
	);

	if (!hWnd) {
		return 0;
	}

	if (FAILED(InitDirectX(*hWnd, pSrcFile)))
	{
		return 0;
	}
}
int InitWindowFullscreenEx(LPCSTR WndName, HWND* hWnd, int WIDTH, int HEIGHT, HINSTANCE hInst, HINSTANCE hInstance, int IconIDI, LPCSTR pSrcFile) {

	WNDCLASS Wndclass;

	//Windows情報の設定
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = hInst;
	Wndclass.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IconIDI));
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = WndName;

	RegisterClass(&Wndclass);
	//Windowの登録

	//Windowの生成
	*hWnd = CreateWindow(
		WndName,						//ウィンドウのクラス名
		WndName,  				//ウィンドウのタイトル
		WS_POPUP | WS_VISIBLE,	//ウィンドウスタイル
		CW_USEDEFAULT,						// ウィンドウの横方向の位置x
		CW_USEDEFAULT,						// ウィンドウの縦方向の位置y
		WIDTH,							// Width（幅）
		HEIGHT,							// Height（高さ）
		NULL,
		NULL,
		hInstance,							// アプリケーションインスタンスのハンドル
		NULL
	);

	if (!hWnd) {
		return 0;
	}

	if (FAILED(InitDirectXFullscreen(*hWnd, pSrcFile, WIDTH,HEIGHT)))
	{
		return 0;
	}
}

int FlameRoop(void gameroop(void)) {
	MSG msg;

	DWORD SyncOld = timeGetTime();	//	システム時間を取得
	DWORD SyncNow;
	timeBeginPeriod(1);
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SyncNow = timeGetTime();
			if (SyncNow - SyncOld >= 1000 / 60)
			{
				gameroop();
				SyncOld = SyncNow;
			}
		}
	}
	timeEndPeriod(1);
	FreeDx();
	return (int)msg.wParam;
}


//画像関連
void BeginSetTexture() {
	//画面の消去
	g_pD3Device->Clear(0, NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0x00, 0x00, 0x00),
		1.0, 0);

	//描画の開始
	g_pD3Device->BeginScene();

}
void EndSetTexture() {
	//描画の終了
	g_pD3Device->EndScene();
	//表示
	g_pD3Device->Present(NULL, NULL, NULL, NULL);

}

//画像読み込み
void ReadInTexture(LPCSTR pTextureName, int TexNum) {
	D3DXCreateTextureFromFile(
		g_pD3Device,
		pTextureName,
		&g_pTexture[TexNum]);
}
//画像表示
void SetUpTexture(CUSTOMVERTEX* Vertex, int TexNum) {
	g_pD3Device->SetTexture(0, g_pTexture[TexNum]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, Vertex, sizeof(CUSTOMVERTEX));
}

//DXフォント
//文字設定
void SetUpFont(int WordHeight,int WordWidth,int CharSet,LPCSTR FontName, int FontNum) {
	D3DXCreateFont(
		g_pD3Device,
		WordHeight,
		WordWidth,
		FW_DEMIBOLD,
		NULL,
		FALSE,
		CharSet,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		FIXED_PITCH | FF_SCRIPT,
		FontName,
		&g_pFont[FontNum]);
}
//描画設定
void WriteWord(LPCSTR Texts,RECT Vertex,int TextFormat,int color, int FontNum) {
	g_pFont[FontNum]->DrawText(
		NULL,							
		Texts,					// 描画テキスト
		-1,								// 全て表示
		&Vertex,							// 表示範囲
		TextFormat,
		color
	);
}


//2点設定描画
void EasyCreateSquareVertex( float Left, float Top, float Right, float Bottom, int TexNum) {
	

	EasyCreateSquareVertexEx( Left, Top, Right, Bottom, 0xffffffff, NULL, NULL, 1, 1, TexNum);

}
void EasyCreateSquareVertexColor( float Left, float Top, float Right, float Bottom, DWORD color, int TexNum) {
	CUSTOMVERTEX Vertex[4];

	Vertex[0] = { Left,  Top,    1.f, 1.f, color, 0, 0 };
	Vertex[1] = { Right, Top,    1.f, 1.f, color, 1, 0 };
	Vertex[2] = { Right, Bottom, 1.f, 1.f, color, 1, 1 };
	Vertex[3] = { Left,  Bottom, 1.f, 1.f, color, 0, 1 };

	SetUpTexture(Vertex, TexNum);

}
void EasyCreateSquareVertexEx( float Left, float Top, float Right, float Bottom, DWORD color, float tu, float tv, float scaleTu, float scaleTv, int TexNum) {
	CUSTOMVERTEX Vertex[4];


	Vertex[0] = {  Left,  Top, 1.f, 1.f, color, tu, tv };
	Vertex[1] = {  Right, Top, 1.f, 1.f, color, tu + scaleTu, tv };
	Vertex[2] = {  Right, Bottom, 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
	Vertex[3] = {  Left,  Bottom, 1.f, 1.f, color, tu, tv + scaleTv };

	SetUpTexture(Vertex, TexNum);
}

//RECT引数2頂点設定描画
void EasyCreateRECTVertex(RECT Vertex, int TexNum) {


	EasyCreateSquareVertexEx(Vertex.left, Vertex.top, Vertex.right, Vertex.bottom, 0xffffffff, NULL, NULL, 1, 1, TexNum);

}
void EasyCreateRECTVertexColor(RECT Vertex, DWORD color, int TexNum) {
	CUSTOMVERTEX Vertex4[4];

	Vertex4[0] = { (float)Vertex.left, (float)Vertex.top,    1.f, 1.f, color, 0, 0 };
	Vertex4[1] = { (float)Vertex.right,(float)Vertex.top,    1.f, 1.f, color, 1, 0 };
	Vertex4[2] = { (float)Vertex.right,(float)Vertex.bottom, 1.f, 1.f, color, 1, 1 };
	Vertex4[3] = { (float)Vertex.left, (float)Vertex.bottom, 1.f, 1.f, color, 0, 1 };

	SetUpTexture(Vertex4, TexNum);

}
void EasyCreateRECTVertexEx(RECT Vertex, DWORD color, float tu, float tv, float scaleTu, float scaleTv, int TexNum) {
	CUSTOMVERTEX Vertex4[4];
	

	Vertex4[0] = { (float)Vertex.left,  (float)Vertex.top, 1.f, 1.f, color, tu, tv };
	Vertex4[1] = { (float)Vertex.right, (float)Vertex.top, 1.f, 1.f, color, tu + scaleTu, tv };
	Vertex4[2] = { (float)Vertex.right, (float)Vertex.bottom, 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
	Vertex4[3] = { (float)Vertex.left,  (float)Vertex.bottom, 1.f, 1.f, color, tu, tv + scaleTv };

	SetUpTexture(Vertex4, TexNum);
}

//4頂点設定
void CreateSquareVertex(CUSTOMVERTEX* Vertex,CENTRAL_STATE Central) {
	
	
	CreateSquareVertexEx(Vertex,Central,NULL,NULL,1,1);
	
	
}
void CreateSquareVertexEx(CUSTOMVERTEX* Vertex, CENTRAL_STATE Central,float tu,float tv,float scaleTu,float scaleTv) {
	CreateSquareVertexColorEx(Vertex, Central, 0xffffffff,tu, tv, scaleTu, scaleTv);
}
void CreateSquareVertexColorEx(CUSTOMVERTEX* Vertex, CENTRAL_STATE Central,DWORD color ,float tu, float tv, float scaleTu, float scaleTv) {
	Vertex[0] = { Central.x - Central.scaleX, Central.y - Central.scaleY, 1.f, 1.f, color, tu, tv };
	Vertex[1] = { Central.x + Central.scaleX, Central.y - Central.scaleY, 1.f, 1.f, color, tu + scaleTu, tv };
	Vertex[2] = { Central.x + Central.scaleX, Central.y + Central.scaleY, 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
	Vertex[3] = { Central.x - Central.scaleX, Central.y + Central.scaleY, 1.f, 1.f, color, tu, tv + scaleTv };
}
void CreateSquareVertexColor(CUSTOMVERTEX* Vertex, CENTRAL_STATE Central, DWORD color){
	CreateSquareVertexColorEx(Vertex, Central, 0xffffffff, NULL, NULL, 1, 1);
}




//回転、円運動関数
void RevolveAndCircularMotion(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float motionRadius) {
	float CharVertexX[4];
	float CharVertexY[4];

	CharVertexX[0] = Central.x - Central.scaleX;
	CharVertexX[1] = Central.x + Central.scaleX;
	CharVertexX[2] = Central.x + Central.scaleX;
	CharVertexX[3] = Central.x - Central.scaleX;

	CharVertexY[0] = Central.y - Central.scaleY;
	CharVertexY[1] = Central.y - Central.scaleY;
	CharVertexY[2] = Central.y + Central.scaleY;
	CharVertexY[3] = Central.y + Central.scaleY;

	for (int RoteCnt = 0; RoteCnt < 4; RoteCnt++) {

		CharVertexX[RoteCnt] -= Central.x;
		CharVertexY[RoteCnt] -= Central.y;

		float KEEPER = CharVertexX[RoteCnt];

		CharVertexX[RoteCnt] = (CharVertexX[RoteCnt] * cos(-Rad)) - (CharVertexY[RoteCnt] * sin(-Rad));
		CharVertexY[RoteCnt] = (CharVertexY[RoteCnt] * cos(-Rad)) + (KEEPER * sin(-Rad));

		CharVertexX[RoteCnt] += Central.x;
		CharVertexY[RoteCnt] += Central.y;

	}
	for (int i = 0; i < 4; i++) {
		CharVertexX[i] += cos(Rad) * motionRadius;
		CharVertexY[i] += sin(Rad) * motionRadius;
	}

	Vertex[0] = { CharVertexX[0], CharVertexY[0], 1.f, 1.f, 0xffffffff, 0.f, 0.f };
	Vertex[1] = { CharVertexX[1], CharVertexY[1], 1.f, 1.f, 0xffffffff, 1.f, 0.f };
	Vertex[2] = { CharVertexX[2], CharVertexY[2], 1.f, 1.f, 0xffffffff, 1.f, 1.f };
	Vertex[3] = { CharVertexX[3], CharVertexY[3], 1.f, 1.f, 0xffffffff, 0.f, 1.f };
}
//回転、楕円運動関数
void RevolveAndOvalCircularMotion(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float motionRadiusX, float motionRadiusY) {
	float CharVertexX[4];
	float CharVertexY[4];

	CharVertexX[0] = Central.x - Central.scaleX;
	CharVertexX[1] = Central.x + Central.scaleX;
	CharVertexX[2] = Central.x + Central.scaleX;
	CharVertexX[3] = Central.x - Central.scaleX;

	CharVertexY[0] = Central.y - Central.scaleY;
	CharVertexY[1] = Central.y - Central.scaleY;
	CharVertexY[2] = Central.y + Central.scaleY;
	CharVertexY[3] = Central.y + Central.scaleY;

	for (int RoteCnt = 0; RoteCnt < 4; RoteCnt++) {

		CharVertexX[RoteCnt] -= Central.x;
		CharVertexY[RoteCnt] -= Central.y;

		float KEEPER = CharVertexX[RoteCnt];

		CharVertexX[RoteCnt] = (CharVertexX[RoteCnt] * cos(-Rad)) - (CharVertexY[RoteCnt] * sin(-Rad));
		CharVertexY[RoteCnt] = (CharVertexY[RoteCnt] * cos(-Rad)) + (KEEPER * sin(-Rad));

		CharVertexX[RoteCnt] += Central.x;
		CharVertexY[RoteCnt] += Central.y;

	}
	for (int i = 0; i < 4; i++) {
		CharVertexX[i] += cos(Rad) * motionRadiusX;
		CharVertexY[i] += sin(Rad) * motionRadiusY;
	}

	Vertex[0] = { CharVertexX[0], CharVertexY[0], 1.f, 1.f, 0xffffffff, 0.f, 0.f };
	Vertex[1] = { CharVertexX[1], CharVertexY[1], 1.f, 1.f, 0xffffffff, 1.f, 0.f };
	Vertex[2] = { CharVertexX[2], CharVertexY[2], 1.f, 1.f, 0xffffffff, 1.f, 1.f };
	Vertex[3] = { CharVertexX[3], CharVertexY[3], 1.f, 1.f, 0xffffffff, 0.f, 1.f };
}

//Z軸回転
void RevolveZ(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central) {

	float CharVertexX[4];
	float CharVertexY[4];

	CharVertexX[0] = Central.x - Central.scaleX;
	CharVertexX[1] = Central.x + Central.scaleX;
	CharVertexX[2] = Central.x + Central.scaleX;
	CharVertexX[3] = Central.x - Central.scaleX;

	CharVertexY[0] = Central.y - Central.scaleY;
	CharVertexY[1] = Central.y - Central.scaleY;
	CharVertexY[2] = Central.y + Central.scaleY;
	CharVertexY[3] = Central.y + Central.scaleY;

	for (int RoteCnt = 0; RoteCnt < 4; RoteCnt++) {

		CharVertexX[RoteCnt] -= Central.x;
		CharVertexY[RoteCnt] -= Central.y;

		float KEEPER = CharVertexX[RoteCnt];

		CharVertexX[RoteCnt] = (CharVertexX[RoteCnt] * cos(-Rad)) - (CharVertexY[RoteCnt] * sin(-Rad));
		CharVertexY[RoteCnt] = (CharVertexY[RoteCnt] * cos(-Rad)) + (KEEPER * sin(-Rad));

		CharVertexX[RoteCnt] += Central.x;
		CharVertexY[RoteCnt] += Central.y;

	}

	Vertex[0] = { CharVertexX[0], CharVertexY[0], 1.f, 1.f, 0xffffffff, 0.f, 0.f };
	Vertex[1] = { CharVertexX[1], CharVertexY[1], 1.f, 1.f, 0xffffffff, 1.f, 0.f };
	Vertex[2] = { CharVertexX[2], CharVertexY[2], 1.f, 1.f, 0xffffffff, 1.f, 1.f };
	Vertex[3] = { CharVertexX[3], CharVertexY[3], 1.f, 1.f, 0xffffffff, 0.f, 1.f };

}
//Z軸　回転軸指定
void RevolveZEX(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central,float RevolvingShaftX,float RevolvingShaftY) {

	float CharVertexX[4];
	float CharVertexY[4];

	CharVertexX[0] = Central.x - Central.scaleX;
	CharVertexX[1] = Central.x + Central.scaleX;
	CharVertexX[2] = Central.x + Central.scaleX;
	CharVertexX[3] = Central.x - Central.scaleX;

	CharVertexY[0] = Central.y - Central.scaleY;
	CharVertexY[1] = Central.y - Central.scaleY;
	CharVertexY[2] = Central.y + Central.scaleY;
	CharVertexY[3] = Central.y + Central.scaleY;

	for (int RoteCnt = 0; RoteCnt < 4; RoteCnt++) {

		CharVertexX[RoteCnt] -= RevolvingShaftX;
		CharVertexY[RoteCnt] -= RevolvingShaftY;

		float KEEPER = CharVertexX[RoteCnt];

		CharVertexX[RoteCnt] = (CharVertexX[RoteCnt] * cos(-Rad)) - (CharVertexY[RoteCnt] * sin(-Rad));
		CharVertexY[RoteCnt] = (CharVertexY[RoteCnt] * cos(-Rad)) + (KEEPER * sin(-Rad));

		CharVertexX[RoteCnt] += RevolvingShaftX;
		CharVertexY[RoteCnt] += RevolvingShaftY;

	}

	Vertex[0] = { CharVertexX[0], CharVertexY[0], 1.f, 1.f, 0xffffffff, 0.f, 0.f };
	Vertex[1] = { CharVertexX[1], CharVertexY[1], 1.f, 1.f, 0xffffffff, 1.f, 0.f };
	Vertex[2] = { CharVertexX[2], CharVertexY[2], 1.f, 1.f, 0xffffffff, 1.f, 1.f };
	Vertex[3] = { CharVertexX[3], CharVertexY[3], 1.f, 1.f, 0xffffffff, 0.f, 1.f };

}

//Y軸回転
void RevolveY(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central) {

	float CharVertexX[4];

	CharVertexX[0] = Central.x - Central.scaleX;
	CharVertexX[1] = Central.x + Central.scaleX;
	CharVertexX[2] = Central.x + Central.scaleX;
	CharVertexX[3] = Central.x - Central.scaleX;


	for (int RoteCnt = 0; RoteCnt < 4; RoteCnt++) {

		CharVertexX[RoteCnt] -= Central.x;
		Vertex[RoteCnt].z -= 1;

		float KEEPER = CharVertexX[RoteCnt];

		CharVertexX[RoteCnt] = (CharVertexX[RoteCnt] * cos(-Rad)) - (Vertex[RoteCnt].z * sin(-Rad));
		Vertex[RoteCnt].z = (Vertex[RoteCnt].z * cos(-Rad)) + (KEEPER * sin(-Rad));

		CharVertexX[RoteCnt] += Central.x;
		Vertex[RoteCnt].z += 1;

	}

	Vertex[0] = { CharVertexX[0], Central.y - Central.scaleY, Vertex[0].z, 1.f, 0xffffffff, 0.f, 0.f };
	Vertex[1] = { CharVertexX[1], Central.y - Central.scaleY, Vertex[1].z, 1.f, 0xffffffff, 1.f, 0.f };
	Vertex[2] = { CharVertexX[2], Central.y + Central.scaleY, Vertex[2].z, 1.f, 0xffffffff, 1.f, 1.f };
	Vertex[3] = { CharVertexX[3], Central.y + Central.scaleY, Vertex[3].z, 1.f, 0xffffffff, 0.f, 1.f };

}
//Y軸　回転軸指定
void RevolveYEX(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float RevolvingShaftX, float RevolvingShaftZ) {

	float CharVertexX[4];

	CharVertexX[0] = Central.x - Central.scaleX;
	CharVertexX[1] = Central.x + Central.scaleX;
	CharVertexX[2] = Central.x + Central.scaleX;
	CharVertexX[3] = Central.x - Central.scaleX;


	for (int RoteCnt = 0; RoteCnt < 4; RoteCnt++) {

		CharVertexX[RoteCnt] -= RevolvingShaftX;
		Vertex[RoteCnt].z -= RevolvingShaftZ;

		float KEEPER = CharVertexX[RoteCnt];

		CharVertexX[RoteCnt] = (CharVertexX[RoteCnt] * cos(-Rad)) - (Vertex[RoteCnt].z * sin(-Rad));
		Vertex[RoteCnt].z = (Vertex[RoteCnt].z * cos(-Rad)) + (KEEPER * sin(-Rad));

		CharVertexX[RoteCnt] += RevolvingShaftX;
		Vertex[RoteCnt].z += RevolvingShaftZ;

	}

	Vertex[0] = { CharVertexX[0], Central.y - Central.scaleY, Vertex[0].z, 1.f, 0xffffffff, 0.f, 0.f };
	Vertex[1] = { CharVertexX[1], Central.y - Central.scaleY, Vertex[1].z, 1.f, 0xffffffff, 1.f, 0.f };
	Vertex[2] = { CharVertexX[2], Central.y + Central.scaleY, Vertex[2].z, 1.f, 0xffffffff, 1.f, 1.f };
	Vertex[3] = { CharVertexX[3], Central.y + Central.scaleY, Vertex[3].z, 1.f, 0xffffffff, 0.f, 1.f };

}

//X軸回転
void RevolveX(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central) {
	
	float CharVertexY[4];


	CharVertexY[0] = Central.y - Central.scaleY;
	CharVertexY[1] = Central.y - Central.scaleY;
	CharVertexY[2] = Central.y + Central.scaleY;
	CharVertexY[3] = Central.y + Central.scaleY;

	for (int RoteCnt = 0; RoteCnt < 4; RoteCnt++) {

		Vertex[RoteCnt].z -= 1;
		CharVertexY[RoteCnt] -= Central.y;

		float KEEPER = Vertex[RoteCnt].z;

		Vertex[RoteCnt].z = (Vertex[RoteCnt].z * cos(-Rad)) - (CharVertexY[RoteCnt] * sin(-Rad));
		CharVertexY[RoteCnt] = (CharVertexY[RoteCnt] * cos(-Rad)) + (KEEPER * sin(-Rad));

		Vertex[RoteCnt].z += 1;
		CharVertexY[RoteCnt] += Central.y;

	}

	Vertex[0] = { Central.x - Central.scaleX,CharVertexY[0],Vertex[0].z, 1.f, 0xffffffff, 0.f, 0.f };
	Vertex[1] = { Central.x + Central.scaleX,CharVertexY[1],Vertex[1].z, 1.f, 0xffffffff, 1.f, 0.f };
	Vertex[2] = { Central.x + Central.scaleX,CharVertexY[2],Vertex[2].z, 1.f, 0xffffffff, 1.f, 1.f };
	Vertex[3] = { Central.x - Central.scaleX,CharVertexY[3],Vertex[3].z, 1.f, 0xffffffff, 0.f, 1.f };

}
//X軸　回転軸指定
void RevolveXEX(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float RevolvingShaftY, float RevolvingShaftZ) {

	float CharVertexY[4];


	CharVertexY[0] = Central.y - Central.scaleY;
	CharVertexY[1] = Central.y - Central.scaleY;
	CharVertexY[2] = Central.y + Central.scaleY;
	CharVertexY[3] = Central.y + Central.scaleY;

	for (int RoteCnt = 0; RoteCnt < 4; RoteCnt++) {

		CharVertexY[RoteCnt] -= RevolvingShaftY;
		Vertex[RoteCnt].z -= RevolvingShaftZ;

		float KEEPER = Vertex[RoteCnt].z;

		Vertex[RoteCnt].z = (Vertex[RoteCnt].z * cos(-Rad)) - (CharVertexY[RoteCnt] * sin(-Rad));
		CharVertexY[RoteCnt] = (CharVertexY[RoteCnt] * cos(-Rad)) + (KEEPER * sin(-Rad));

		CharVertexY[RoteCnt] += RevolvingShaftY;
		Vertex[RoteCnt].z += RevolvingShaftZ;

	}

	Vertex[0] = { Central.x - Central.scaleX,CharVertexY[0],Vertex[0].z, 1.f, 0xffffffff, 0.f, 0.f };
	Vertex[1] = { Central.x + Central.scaleX,CharVertexY[1],Vertex[1].z, 1.f, 0xffffffff, 1.f, 0.f };
	Vertex[2] = { Central.x + Central.scaleX,CharVertexY[2],Vertex[2].z, 1.f, 0xffffffff, 1.f, 1.f };
	Vertex[3] = { Central.x - Central.scaleX,CharVertexY[3],Vertex[3].z, 1.f, 0xffffffff, 0.f, 1.f };

}

//円運動
void CircularMotion(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central,float motionRadius) {

	float CharVertexX[4];
	float CharVertexY[4];

	CharVertexX[0] = Central.x - Central.scaleX;
	CharVertexX[1] = Central.x + Central.scaleX;
	CharVertexX[2] = Central.x + Central.scaleX;
	CharVertexX[3] = Central.x - Central.scaleX;

	CharVertexY[0] = Central.y - Central.scaleY;
	CharVertexY[1] = Central.y - Central.scaleY;
	CharVertexY[2] = Central.y + Central.scaleY;
	CharVertexY[3] = Central.y + Central.scaleY;

	
	for (int i = 0; i < 4; i++) {
		CharVertexX[i] += cos(Rad) * motionRadius;
		CharVertexY[i] += sin(Rad) * motionRadius;
	}

	Vertex[0] = { CharVertexX[0], CharVertexY[0], 1.f, 1.f, 0xffffffff, 0.f, 0.f };
	Vertex[1] = { CharVertexX[1], CharVertexY[1], 1.f, 1.f, 0xffffffff, 1.f, 0.f };
	Vertex[2] = { CharVertexX[2], CharVertexY[2], 1.f, 1.f, 0xffffffff, 1.f, 1.f };
	Vertex[3] = { CharVertexX[3], CharVertexY[3], 1.f, 1.f, 0xffffffff, 0.f, 1.f };

}
//楕円運動
void OvalCircularMotion(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float motionRadiusX, float motionRadiusY) {

	float CharVertexX[4];
	float CharVertexY[4];

	CharVertexX[0] = Central.x - Central.scaleX;
	CharVertexX[1] = Central.x + Central.scaleX;
	CharVertexX[2] = Central.x + Central.scaleX;
	CharVertexX[3] = Central.x - Central.scaleX;

	CharVertexY[0] = Central.y - Central.scaleY;
	CharVertexY[1] = Central.y - Central.scaleY;
	CharVertexY[2] = Central.y + Central.scaleY;
	CharVertexY[3] = Central.y + Central.scaleY;


	for (int i = 0; i < 4; i++) {
		CharVertexX[i] += cos(Rad) * motionRadiusX;
		CharVertexY[i] += sin(Rad) * motionRadiusY;
	}

	Vertex[0] = { CharVertexX[0], CharVertexY[0], 1.f, 1.f, 0xffffffff, 0.f, 0.f };
	Vertex[1] = { CharVertexX[1], CharVertexY[1], 1.f, 1.f, 0xffffffff, 1.f, 0.f };
	Vertex[2] = { CharVertexX[2], CharVertexY[2], 1.f, 1.f, 0xffffffff, 1.f, 1.f };
	Vertex[3] = { CharVertexX[3], CharVertexY[3], 1.f, 1.f, 0xffffffff, 0.f, 1.f };

}

//Dinputキーボード
bool InputKEY(int KeyName) {
	HRESULT hr = g_pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE)) {
		BYTE diks[256];
		g_pKeyDevice->GetDeviceState(sizeof(diks), &diks);

		if (diks[KeyName] & 0x80) {
			return true;
		}
		else return false;
	}
}
void CheckKeyState(int KeyName)
{

		HRESULT hr = g_pKeyDevice->Acquire();
		if ((hr == DI_OK) || (hr == S_FALSE)) {
			BYTE diks[256];
			g_pKeyDevice->GetDeviceState(sizeof(diks), &diks);

			if (diks[KeyName] & 0x80)
			{
				if (KeyOldState[KeyName] == KeyOn)
				{
					KeyState[KeyName] = KeyOn;
				}
				else
				{
					KeyState[KeyName] = KeyPush;
				}

				KeyOldState[KeyName] = KeyOn;
			}
			else
			{
				if (KeyOldState[KeyName] == KeyOn)
				{
					KeyState[KeyName] = KeyRelease;
				}
				else
				{
					KeyState[KeyName] = KeyOff;
				}
				KeyOldState[KeyName] = KeyOff;
			}
		}
}

//XInput
void GetControl(int GamePadNumber)
{
	XInputGetState(GamePadNumber, &g_Xinput);
}

PADSTATE GetButton(ButtonIndex Index)
{
	return PadState[Index];
}

bool GetAnalogL(Analog AnalogState)
{
	switch (AnalogState)
	{
	case ANALOGUP:
		if (g_Xinput.Gamepad.sThumbLY > -65535 / 4)
		{
			return true;
		}
		break;
	case ANALOGDOWN:
		if (g_Xinput.Gamepad.sThumbLY < 65535 / 4)
		{
			return true;
		}
		break;
	case ANALOGLEFT:
		if (g_Xinput.Gamepad.sThumbLX <-65535 / 4)
		{
			return true;
		}
		break;
	case ANALOGRIGHT:
		if (g_Xinput.Gamepad.sThumbLX >65535 / 4)
		{
			return true;
		}
		break;
	default:
		return false;
	}
	return false;
}
bool GetAnalogR(Analog AnalogState)
{
	switch (AnalogState)
	{
	case ANALOGUP:
		if (g_Xinput.Gamepad.sThumbRY > -65535 / 4)
		{
			return true;
		}
		break;
	case ANALOGDOWN:
		if (g_Xinput.Gamepad.sThumbRY < 65535 / 4)
		{
			return true;
		}
		break;
	case ANALOGLEFT:
		if (g_Xinput.Gamepad.sThumbRX <-65535 / 4)
		{
			return true;
		}
		break;
	case ANALOGRIGHT:
		if (g_Xinput.Gamepad.sThumbRX >65535 / 4)
		{
			return true;
		}
		break;
	default:
		return false;
	}
	return false;
}

void CheckButtonState(WORD ButtomID, ButtonIndex ButtomIndex)
{
	if (g_Xinput.Gamepad.wButtons & ButtomID)
	{
		if (PadOldState[ButtomIndex] == PadOn)
		{
			PadState[ButtomIndex] = PadOn;
		}
		else
		{
			PadState[ButtomIndex] = PadPush;
		}

		PadOldState[ButtomIndex] = PadOn;
	}
	else
	{
		if (PadOldState[ButtomIndex] == PadOn)
		{
			PadState[ButtomIndex] = PadRelease;
		}
		else
		{
			PadState[ButtomIndex] = PadOff;
		}
		PadOldState[ButtomIndex] = PadOff;
	}

}
void BottonCheck() {

	CheckButtonState(XINPUT_GAMEPAD_A, ButtonA);
	CheckButtonState(XINPUT_GAMEPAD_B, ButtonB);
	CheckButtonState(XINPUT_GAMEPAD_X, ButtonX);
	CheckButtonState(XINPUT_GAMEPAD_Y, ButtonY);
	CheckButtonState(XINPUT_GAMEPAD_START, ButtonStart);
	CheckButtonState(XINPUT_GAMEPAD_BACK, ButtonBack);
	CheckButtonState(XINPUT_GAMEPAD_LEFT_SHOULDER, ButtonLB);
	CheckButtonState(XINPUT_GAMEPAD_RIGHT_SHOULDER, ButtonRB);
	CheckButtonState(XINPUT_GAMEPAD_DPAD_UP, ButtonUP);
	CheckButtonState(XINPUT_GAMEPAD_DPAD_DOWN, ButtonDOWN);
	CheckButtonState(XINPUT_GAMEPAD_DPAD_LEFT, ButtonLEFT);
	CheckButtonState(XINPUT_GAMEPAD_DPAD_RIGHT, ButtonRIGHT);
	CheckButtonState(XINPUT_GAMEPAD_START, ButtonStart);
	CheckButtonState(XINPUT_GAMEPAD_BACK, ButtonBack);
	CheckButtonState(XINPUT_GAMEPAD_LEFT_THUMB, ButtonLeftThumb);
	CheckButtonState(XINPUT_GAMEPAD_RIGHT_THUMB, ButtonRightThumb);

}
//当たり判定
////円と円の当たり判定
bool CtoCContact(float PosX1,float PosY1,float Radius1, float PosX2, float PosY2, float Radius2) {
	if ((pow(PosX1 - PosX2, 2) + pow(PosY1 - PosY2, 2) <= pow(Radius1 + Radius2, 2))
		|| (pow(PosX2 - PosX1, 2) + pow(PosY2 - PosY1, 2) <= pow(Radius1 + Radius2, 2))) {
		return true;
	}
	else return false;
}
bool CtoCContact(CIRCLE_STATE* CircleA, CIRCLE_STATE* CircleB) {
	if ((pow(CircleA->x - CircleB->x, 2) + pow(CircleA->y - CircleB->y, 2) <= pow(CircleA->r + CircleB->r, 2)) || (pow(CircleB->x - CircleA->x, 2) + pow(CircleB->y - CircleA->y, 2) <= pow(CircleA->r + CircleB->r, 2))) {
		return true;
	}
	else return false;
}
////矩形と矩形の当たり判定
bool BtoBContact(CENTRAL_STATE* central1, CENTRAL_STATE* central2) {
	if ((central1->x <= central2->x + central2->scaleX) && (central2->x <= central1->x + central1->scaleX)
		&& (central1->y <= central2->y + central2->scaleY) && (central2->y <= central1->y + central1->scaleY)) {
		return true;
	}
	else return false;
}
////矩形が指定範囲外に出ないようにする
void MoveInToErea(CENTRAL_STATE* central, float Left, float Top, float Right, float Bottom) {
	if (Left >= central->x - central->scaleX || central->x + central->scaleX >= Right
		|| Top >= central->y || central->y + central->scaleY >= Bottom) {

		if (Left >= central->x - central->scaleX) {
			central->x = Left + central->scaleX;
		}
		if (central->x + central->scaleX >= Right) {
			central->x = Right - central->scaleX;
		}
		if (Top >= central->y) {
			central->y = Top;
		}
		if (central->y + central->scaleY >= Bottom) {
			central->y = Bottom - central->scaleY;
		}
	}
}
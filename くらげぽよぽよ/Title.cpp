/*******************************************************************************
* タイトル:		Title処理
* プログラム名:	Title.cpp
* 作成者:		GP11A331 4 伊原佑稀
* 作成日:		2016/02/23
********************************************************************************
* 更新履歴:		- 2016/02/23	 伊原
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "Title.h"
#include "Texture.h"
#include "input.h"
#include "Light.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define POLYGON_POS_X_GAMENAME	(SCREEN_WIDTH/2)//ポリゴン中心のX
#define POLYGON_POS_Y_GAMENAME	(200)//ポリゴンの中心のY
#define POLYGON_SIZE_X_GAMENAME	(800)//ポリゴンのSIZE X
#define POLYGON_SIZE_Y_GAMENAME	(400)//ポリゴンのSIZE Y
//#define POLYGON_TEXTURENAME_GAMENAME "data/TEXTURE/TitleGameName.png"

#define POLYGON_POS_X_GAMESTART	(SCREEN_WIDTH/2)//ポリゴン中心のX
#define POLYGON_POS_Y_GAMESTART	(800)//ポリゴンの中心のY
#define POLYGON_SIZE_X_GAMESTART	(400)//ポリゴンのSIZE X
#define POLYGON_SIZE_Y_GAMESTART	(200)//ポリゴンのSIZE Y
//#define POLYGON_TEXTURENAME_GAMESTART "data/TEXTURE/TitleIconStart.png"


/*******************************************************************************
* 構造体定義
*******************************************************************************/

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
HRESULT MakeVertexTitleGameName(LPDIRECT3DDEVICE9 pDevice);
void SetVertexTitleGameName(void);
HRESULT InitTitleGameName(void);
void UninitTitleGameName(void);
void UpdateTitleGameName(void);
void DrawTitleGameName(void);

HRESULT MakeVertexTitleGameStart(LPDIRECT3DDEVICE9 pDevice);
void SetVertexTitleGameStart(void);
HRESULT InitTitleGameStart(void);
void UninitTitleGameStart(void);
void UpdateTitleGameStart(void);
void DrawTitleGameStart(void);
/*******************************************************************************
* グローバル変数
*******************************************************************************/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferTitleGameName = NULL;
LPDIRECT3DTEXTURE9 g_pTextureTitleGameName = NULL;
//int g_aniPattenTitleGameName;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferTitleGameStart = NULL;
LPDIRECT3DTEXTURE9 g_pTextureTitleGameStart = NULL;

void InitTitle(void)
{
	InitTitleGameName();
	InitTitleGameStart();
	
}
void UninitTitle(void)
{
	UninitTitleGameName();
	UninitTitleGameStart();
}
void UpdateTitle(void)
{
	UpdateTitleGameName();
	UpdateTitleGameStart();
	if(GetMouseLeftTrigger())
	{
		SetMode(MODE_GAME);
	}

}
void DrawTitle(void)
{
	DrawTitleGameName();
	DrawTitleGameStart();
}

/*******************************************************************************
* InitGameName
*******************************************************************************/
HRESULT InitTitleGameName(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点情報の作成
	if(FAILED(MakeVertexTitleGameName(pDevice)))
	{
		return E_FAIL;
	}


	return S_OK;
}
/*******************************************************************************
* DrawGameName
*******************************************************************************/
void DrawTitleGameName(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 *pTitleTex = GetTitleTexture();

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBufferTitleGameName, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTitleTex[KURAGEPOYOPOYO]);

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,						//ロードする最初の頂点インデックス
		NUM_POLYGON				//ポリゴンの数
	);


}

/*******************************************************************************
* UninitGameName
*******************************************************************************/
void UninitTitleGameName(void)
{
	if(g_pTextureTitleGameName != NULL)
	{
		g_pTextureTitleGameName->Release();
		g_pTextureTitleGameName = NULL;
	}
	if(g_pVtxBufferTitleGameName != NULL)
	{
		g_pVtxBufferTitleGameName->Release();
		g_pVtxBufferTitleGameName = NULL;
	}
}
/*******************************************************************************
* MakeVertexTitleGameName
*******************************************************************************/
HRESULT MakeVertexTitleGameName(LPDIRECT3DDEVICE9 pDevice)
{

	if(FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	//頂点データのバッファサイズ 
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_2D,					//頂点フォーマット
		D3DPOOL_MANAGED, 
		&g_pVtxBufferTitleGameName,			//頂点バッファインターフェースのポインタ
		NULL)))
	{
		return E_FAIL;
	}
	{
	//頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBufferTitleGameName->Lock( 0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].vtx = D3DXVECTOR3(POLYGON_POS_X_GAMENAME - POLYGON_SIZE_X_GAMENAME/2, POLYGON_POS_Y_GAMENAME - POLYGON_SIZE_Y_GAMENAME/2, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(POLYGON_POS_X_GAMENAME + POLYGON_SIZE_X_GAMENAME/2, POLYGON_POS_Y_GAMENAME - POLYGON_SIZE_Y_GAMENAME/2, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(POLYGON_POS_X_GAMENAME - POLYGON_SIZE_X_GAMENAME/2, POLYGON_POS_Y_GAMENAME + POLYGON_SIZE_Y_GAMENAME/2, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(POLYGON_POS_X_GAMENAME + POLYGON_SIZE_X_GAMENAME/2, POLYGON_POS_Y_GAMENAME + POLYGON_SIZE_Y_GAMENAME/2, 0.0f);

	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;


	//color
	pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);


	//テクスチャ座標指定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	//D3DXCreateTextureFromFile(pDevice,POLYGON_TEXTURENAME_GAMENAME,&g_pTextureTitleGameName);
	
	g_pVtxBufferTitleGameName->Unlock();

	}
	return S_OK;
}
/*******************************************************************************
* update TitleGameName
*******************************************************************************/
void UpdateTitleGameName(void)
{
}

/*******************************************************************************
* InitGameStart
*******************************************************************************/
HRESULT InitTitleGameStart(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点情報の作成
	if(FAILED(MakeVertexTitleGameStart(pDevice)))
	{
		return E_FAIL;
	}


	return S_OK;
}
/*******************************************************************************
* DrawGameStart
*******************************************************************************/
void DrawTitleGameStart(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 *pTitleTex = GetTitleTexture();

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBufferTitleGameStart, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTitleTex[TITLE_START]);

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,						//ロードする最初の頂点インデックス
		NUM_POLYGON				//ポリゴンの数
	);


}

/*******************************************************************************
* UninitGameStart
*******************************************************************************/
void UninitTitleGameStart(void)
{
	if(g_pTextureTitleGameStart != NULL)
	{
		g_pTextureTitleGameStart->Release();
		g_pTextureTitleGameStart = NULL;
	}
	if(g_pVtxBufferTitleGameStart != NULL)
	{
		g_pVtxBufferTitleGameStart->Release();
		g_pVtxBufferTitleGameStart = NULL;
	}
}
/*******************************************************************************
* MakeVertexTitleGameStart
*******************************************************************************/
HRESULT MakeVertexTitleGameStart(LPDIRECT3DDEVICE9 pDevice)
{

	if(FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	//頂点データのバッファサイズ 
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_2D,					//頂点フォーマット
		D3DPOOL_MANAGED, 
		&g_pVtxBufferTitleGameStart,			//頂点バッファインターフェースのポインタ
		NULL)))
	{
		return E_FAIL;
	}
	{
	//頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBufferTitleGameStart->Lock( 0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].vtx = D3DXVECTOR3(POLYGON_POS_X_GAMESTART - POLYGON_SIZE_X_GAMESTART/2, POLYGON_POS_Y_GAMESTART - POLYGON_SIZE_Y_GAMESTART/2, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(POLYGON_POS_X_GAMESTART + POLYGON_SIZE_X_GAMESTART/2, POLYGON_POS_Y_GAMESTART - POLYGON_SIZE_Y_GAMESTART/2, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(POLYGON_POS_X_GAMESTART - POLYGON_SIZE_X_GAMESTART/2, POLYGON_POS_Y_GAMESTART + POLYGON_SIZE_Y_GAMESTART/2, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(POLYGON_POS_X_GAMESTART + POLYGON_SIZE_X_GAMESTART/2, POLYGON_POS_Y_GAMESTART + POLYGON_SIZE_Y_GAMESTART/2, 0.0f);

	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;


	//color
	pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);


	//テクスチャ座標指定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	//D3DXCreateTextureFromFile(pDevice,POLYGON_TEXTURENAME_GAMESTART,&g_pTextureTitleGameStart);
	
	g_pVtxBufferTitleGameStart->Unlock();

	}
	return S_OK;
}
/*******************************************************************************
* UpdateTitleGameStart
*******************************************************************************/
void UpdateTitleGameStart(void)
{

}
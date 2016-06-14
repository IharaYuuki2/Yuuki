/*******************************************************************************
* タイトル:		UI処理
* プログラム名:	UI.cpp
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2016/02/01
********************************************************************************
* 更新履歴:		- 2016/02/25	伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "UI.h"
#include "Texture.h"
#include "Camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	SIZE_X		(25.0f)							// ビルボードの幅
#define SIZE_Y		(25.0f)							// ビルボードの高さ
/*******************************************************************************
* 構造体定義
*******************************************************************************/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuff;			// 頂点バッファへのポインタ
																
	D3DXMATRIX				mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3             pos;					// 位置
	D3DXVECTOR3				truePos[4];
	D3DXVECTOR3             scl; 						// スケール
	int						alphatest;
	int						mode;
	bool					bUse;

}STATUSUPTEXTURE;
//*****************************************************************************
// グローバル変数
//*****************************************************************************
STATUSUPTEXTURE g_statusUpTexture;
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
HRESULT MakeVertexStatusUpTexture(LPDIRECT3DDEVICE9 pDevice);
void SetVertexStatusUpTexture(float fSizeX, float fSizeY);
void InitStatusUpTexture(void);
void UpdateStatusUpTexture(void);
void UninitStatusUpTexture(void);
void DrawStatusUpTexture(void);


void InitUI()
{
	InitStatusUpTexture();
}
void UpdateUI()
{
	UpdateStatusUpTexture();

	//POINT mouseClientPos = GetMouseClientPos();

	//if(image.pos.x - image.size.x / 2 < mouseClientPos.x &&
	//	image.pos.x + image.size.x / 2 > mos\useCLientPos.x&&&&&&&)
	//{
	//	if(GetMousePressRight())
	//	{
	//		if(bPressed)
	//		{

	//		}
	//		
	//	}
	//}
}
void UninitUI()
{
	UninitStatusUpTexture();
}

void DrawUI()
{
	DrawStatusUpTexture();
}


//--------------------------------------------------------------------
void InitStatusUpTexture(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 位置の初期化(D3DXVECTOR3を使用)
	 g_statusUpTexture.pos = D3DXVECTOR3(200.0f,20.0f,200.0f);

	
	// スケールの初期化(D3DXVECTOR3を使用)
	 g_statusUpTexture.scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//
	 g_statusUpTexture.bUse = false;
	 g_statusUpTexture.mode = STATUS_UP_NONE;

	// 頂点情報の作成
	MakeVertexStatusUpTexture(pDevice);

	

}

void UninitStatusUpTexture(void)
{


	//if(g_pD3DVtxBuffBillboard != NULL)
	//{// 頂点バッファの開放
	//	g_pD3DVtxBuffBillboard->Release();
	//	g_pD3DVtxBuffBillboard = NULL;
	//}
}

void UpdateStatusUpTexture(void)
{

}

void DrawStatusUpTexture(void)
{
	LPDIRECT3DTEXTURE9 *pUITexture  = GetUITexture();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;
	CAMERA *pCamera;
	

	// カメラの取得
	pCamera = GetCamera();
	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);

	//VERTEX_3D  *pVtx;

	//// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	//g_statusUpTexture.pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(& g_statusUpTexture.mtxWorld);
	// ポリゴンを正面に向ける(逆行列を求める)
	 g_statusUpTexture.mtxWorld._11 = pCamera->mtxView._11;
	 g_statusUpTexture.mtxWorld._22 = pCamera->mtxView._22;
	 g_statusUpTexture.mtxWorld._33 = pCamera->mtxView._33;

	 g_statusUpTexture.mtxWorld._32 = pCamera->mtxView._23;
	 g_statusUpTexture.mtxWorld._23 = pCamera->mtxView._32;
	 g_statusUpTexture.mtxWorld._31 = pCamera->mtxView._13;

	 g_statusUpTexture.mtxWorld._13 = pCamera->mtxView._31;
	 g_statusUpTexture.mtxWorld._12 = pCamera->mtxView._21;
	 g_statusUpTexture.mtxWorld._21 = pCamera->mtxView._12;
	// スケールを反映
	D3DXMatrixScaling(&mtxScale, g_statusUpTexture.scl.x, g_statusUpTexture.scl.y,  g_statusUpTexture.scl.z);
	
	D3DXMatrixMultiply(&g_statusUpTexture.mtxWorld,&g_statusUpTexture.mtxWorld,&mtxScale);
	
	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate,g_statusUpTexture.pos.x,g_statusUpTexture.pos.y,g_statusUpTexture.pos.z);

	D3DXMatrixMultiply(&g_statusUpTexture.mtxWorld,&g_statusUpTexture.mtxWorld,&mtxTranslate);

	//// 頂点座標の計算

	//D3DXVec3TransformCoord(&g_statusUpTexture.truePos[0],&pVtx[0].vtx,&g_statusUpTexture.mtxWorld);
	//D3DXVec3TransformCoord(&g_statusUpTexture.truePos[1],&pVtx[1].vtx,&g_statusUpTexture.mtxWorld);
	//D3DXVec3TransformCoord(&g_statusUpTexture.truePos[2],&pVtx[2].vtx,&g_statusUpTexture.mtxWorld);
	//D3DXVec3TransformCoord(&g_statusUpTexture.truePos[3],&pVtx[3].vtx,&g_statusUpTexture.mtxWorld);

	//// 頂点データをアンロックする
	//g_statusUpTexture.pD3DVtxBuff->Unlock();


	// ワールドマトリックスの設定
	pDevice -> SetTransform(D3DTS_WORLD,&g_statusUpTexture.mtxWorld);
	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0,g_statusUpTexture.pD3DVtxBuff,0,sizeof(VERTEX_3D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	// テクスチャの設定

	switch(g_statusUpTexture.mode)
	{
		case STATUS_INTELLIGENCE_UP :
			pDevice->SetTexture(0,pUITexture[UI_INTELLIGENCEUP]);
			break;
		case STATUS_MOBILITY_UP:
			pDevice->SetTexture(0,pUITexture[UI_MOTILITYUP]);
			break;
		case STATUS_JUSTICE_UP:
			pDevice->SetTexture(0,pUITexture[UI_JUSTICEUP]);
			break;
		case STATUS_SENSIBILITY_UP:
			pDevice->SetTexture(0,pUITexture[UI_SENSIBILITYUP]);
			break;
	}
	// アルファ テストの設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);

	pDevice->SetRenderState(D3DRS_ALPHAREF,g_statusUpTexture.alphatest);

	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);


	// ポリゴンの描画
	if(g_statusUpTexture.bUse == true)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,NUM_VERTEX);
	}
		//
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
	// ラインティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);


}


//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexStatusUpTexture(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&g_statusUpTexture.pD3DVtxBuff,
											NULL)))
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D  *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_statusUpTexture.pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-SIZE_X / 2.0f,+SIZE_Y / 2.0f,0.0f);
			pVtx[1].vtx = D3DXVECTOR3(+SIZE_X / 2.0f,+SIZE_Y / 2.0f,0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-SIZE_X / 2.0f,-SIZE_Y / 2.0f,0.0f);
			pVtx[3].vtx = D3DXVECTOR3(+SIZE_X / 2.0f,-SIZE_Y / 2.0f,0.0f);
			// 頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

		// 頂点データをアンロックする
		g_statusUpTexture.pD3DVtxBuff->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexStatusUpTexture(float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_statusUpTexture.pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-SIZE_X / 2.0f,+SIZE_Y / 2.0f,0.0f);
		pVtx[1].vtx = D3DXVECTOR3(+SIZE_X / 2.0f,+SIZE_Y / 2.0f,0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-SIZE_X / 2.0f,-SIZE_Y / 2.0f,0.0f);
		pVtx[3].vtx = D3DXVECTOR3(+SIZE_X / 2.0f,-SIZE_Y / 2.0f,0.0f);
		
		// 頂点データをアンロックする
		g_statusUpTexture.pD3DVtxBuff->Unlock();
	}
}

void SetStatusUpTexture(D3DXVECTOR3 pos,STATUSUPMODE statusMode)
{
	g_statusUpTexture.bUse = true;
	g_statusUpTexture.pos = pos;
	g_statusUpTexture.pos.y += 30.0f;
	g_statusUpTexture.mode = statusMode;
}

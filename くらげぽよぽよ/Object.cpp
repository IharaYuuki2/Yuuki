/*******************************************************************************
* タイトル:		3D空間内のオブジェクト・ポリゴンの処理
* プログラム名:	Object.cpp
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2016/01/24
********************************************************************************
* 更新履歴:		- 2016/01/24	伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "Object.h"
#include "XFile.h"
#include "DebugProc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define KURAGEMOVE					(0.50f)			// くらげの移動速度
#define KURAGEROTATE				(0.20f)			// くらげの回転速度
#define KURAGESIZEX					(1.0f)			// くらげのサイズ(X方向)
#define KURAGESIZEY					(1.0f)			// くらげのサイズ(Y方向)

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitJellyfish(void);
void UninitJellyfish(void);
void UpdateJellyfish(void);
void DrawJellyfish(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
JELLY_FISH g_Jellyfish;

/*******************************************************************************
関数名:	void InitObject(void)
引数:	なし
戻り値:	なし
説明:	オブジェクトの初期化処理
*******************************************************************************/
void InitObject(void)
{
	InitJellyfish();
}
/*******************************************************************************
関数名:	void UpdateObject(void)
引数:	なし
戻り値:	なし
説明:	オブジェクトの更新処理
*******************************************************************************/
void UpdateObject(void)
{
	UpdateJellyfish();
}
/*******************************************************************************
関数名:	void DrawObject(void)
引数:	なし
戻り値:	なし
説明:	オブジェクトの描画
*******************************************************************************/
void DrawObject(void)
{
	DrawJellyfish();
}

/*******************************************************************************
関数名:	void InitJellyfish(void)
引数:	なし
戻り値:	なし
説明:	クラゲモデルの初期化処理
*******************************************************************************/
void InitJellyfish(void)
{
	// 位置を設定
	g_Jellyfish.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	// 向きを設定
	g_Jellyfish.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	// スケールを設定
	g_Jellyfish.scl = D3DXVECTOR3(20.0f,20.0f,20.0f);
	// 使用中に変更
	g_Jellyfish.bUse = true;
	// パラメータの初期化(各パラメータのMAX値は100)
	g_Jellyfish.nIntelligence = 5;		// 知力/*各パラメータ値MAXは100*/
	g_Jellyfish.nMobility = 5;			// 体力
	g_Jellyfish.nSensibility = 5;		// 感性
	g_Jellyfish.nJustice = 5;			// 正義感
	g_Jellyfish.nFoodFull = 50;			// 満腹
	g_Jellyfish.nMotivation = 50;		// やる気


}
/*******************************************************************************
関数名:	void UninitJellyfish(void)
引数:	なし
戻り値:	なし
説明:	クラゲモデルの終了処理
*******************************************************************************/
void UninitJellyfish(void)
{
	
}
/*******************************************************************************
関数名:	void UpdateJellyfish(void)
引数:	なし
戻り値:	なし
説明:	クラゲモデルの更新処理
*******************************************************************************/
void UpdateJellyfish(void)
{
	PrintDebugProc("[クラゲX座標 : (%d)]\n",g_Jellyfish.pos.x);
	PrintDebugProc("[クラゲY座標 : (%d)]\n\n",g_Jellyfish.pos.y);

}
/*******************************************************************************
関数名:	void DrawJellyfish(void)
引数:	なし
戻り値:	なし
説明:	クラゲモデルの描画処理
*******************************************************************************/
void DrawJellyfish(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	XFILE *pJellyfishXFile = GetpJellyfishXFile();
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Jellyfish.mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl,g_Jellyfish.scl.x,g_Jellyfish.scl.y,g_Jellyfish.scl.z);
	D3DXMatrixMultiply(&g_Jellyfish.mtxWorld,&g_Jellyfish.mtxWorld,&mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_Jellyfish.rot.y,g_Jellyfish.rot.x,g_Jellyfish.rot.z);
	D3DXMatrixMultiply(&g_Jellyfish.mtxWorld,&g_Jellyfish.mtxWorld,&mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate,g_Jellyfish.pos.x,g_Jellyfish.pos.y,g_Jellyfish.pos.z);
	D3DXMatrixMultiply(&g_Jellyfish.mtxWorld,&g_Jellyfish.mtxWorld,&mtxTranslate);

	// ワールドマトリックスの設定
	pDevice -> SetTransform(D3DTS_WORLD,&g_Jellyfish.mtxWorld);

	// 現在のマテリアルを取得
	pDevice -> GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL * )pJellyfishXFile[XFILE_TEST_FILE].pD3DXBuffMate -> GetBufferPointer();

	// マテリアルの設定
	pDevice -> SetMaterial(&pD3DXMat[XFILE_TEST_FILE].MatD3D);

	// テクスチャの設定
	pDevice -> SetTexture(0,pJellyfishXFile[XFILE_TEST_FILE].pD3DTexture);

	// 描画
	pJellyfishXFile[XFILE_TEST_FILE].pD3DXMesh -> DrawSubset(0);

	// マテリアルをデフォルトに戻す
	pDevice -> SetMaterial(&matDef);
}
/*******************************************************************************
関数名:	void ChangeJellyfishStatus(JELLYFISH_STATUS_TYPE statusType, int valu)
引数:	JELLYFISH_STATUS_TYPE statusType:	変更したいステータス選択,
		int valu:							変更したい数値
戻り値:	なし
説明:	クラゲのステータス変更
*******************************************************************************/
void ChangeJellyfishStatus(JELLYFISH_STATUS_TYPE statusType, int valu)
{
	switch(statusType)
	{
		case INTELLIGENCE:
			g_Jellyfish.nIntelligence += valu;
			break;
		case MOBILLITY:
			g_Jellyfish.nMobility += valu;
			break;
		case SENSIBILLITY:
			g_Jellyfish.nSensibility += valu;
			break;
		case JUSTICE:
			g_Jellyfish.nJustice += valu;
			break;
		case FOODFULL:
			g_Jellyfish.nFoodFull += valu;
			break;
		case MOTIVATION:
			g_Jellyfish.nMotivation += valu;
			break;
	}
}
/*******************************************************************************
関数名:	JELLY_FISH *GetJellyfishStatus(void)
引数:	なし
戻り値:	クラゲのステータス
説明:	クラゲの構造体のアドレス
*******************************************************************************/
JELLY_FISH *GetJellyfishStatus(void)
{
	return &g_Jellyfish;
}
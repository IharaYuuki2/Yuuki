/*******************************************************************************
* タイトル:		UI処理
* プログラム名:	UI.cpp
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2016/02/01
********************************************************************************
* 更新履歴:		- 2016/02/25	伊原佑稀
*					- V1.00		Initial Version
*				- 2016/05/29	大塚慧
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "UI.h"
#include "DebugProc.h"
#include "Texture.h"
#include "Object.h"
#include "Game.h"

/*****************************************************************************
* マクロ定義
******************************************************************************/
// メニューアイコン関係
#define HOME_MENW_ICON_NUM	(7)		// メニューアイコン数(縦の分割数)
#define HOME_MENW_ICON_POS_X	(500.0f)		// メニューアイコン位置X(1枚目の中心座標X)
#define HOME_MENW_ICON_POS_Y	(80.0f)			// メニューアイコン位置Y(1枚目の中心座標Y)
#define HOME_MENW_ICON_OUT_POS	(2000.0f)		// メニューアイコン位置(非表示)
#define HOME_MENW_ICON_IN_POS	(1000.0f)		// メニューアイコン位置(表示)
#define HOME_MENW_ICON_SIZE_X	(300.0f)		// メニューアイコン1つの大きさX方向
#define HOME_MENW_ICON_SIZE_Y	(140.0f)		// メニューアイコン1つの大きさY方向
#define HOME_MENW_ICON_INTERVAL_HEIGHT	(0.0f)	// メニューアイコン高さ方向の幅

// トレーニングアイコン関係
#define HOME_TRAINING_ICON_NUM	(4)		// トレーニングアイコン(縦の分割数)
#define HOME_TRAINING_ICON_POS_X	(500.0f)		// メニューアイコン位置X(1枚目の中心座標X)
#define HOME_TRAINING_ICON_POS_Y	(80.0f)			// メニューアイコン位置Y(1枚目の中心座標Y)
#define HOME_TRAINING_ICON_OUT_POS	(2000.0f)		// メニューアイコン位置(非表示)		/*位置は要検討*/
#define HOME_TRAINING_ICON_IN_POS	(1000.0f)		// メニューアイコン位置(表示)
#define HOME_TRAINING_ICON_SIZE_X	(300.0f)		// メニューアイコン1つの大きさX方向
#define HOME_TRAINING_ICON_SIZE_Y	(140.0f)		// メニューアイコン1つの大きさY方向
#define HOME_TRAINING_ICON_INTERVAL_HEIGHT	(0.0f)	// メニューアイコン高さ方向の幅

// アドバイス関係
#define HOME_ADVICE_NUM	(3)		// アドバイスコメント(縦の分割数)
#define HOME_ADVICE_POS_X	(500.0f)	// アドバイスコメント位置X(初期値,実際はクラゲの位置から描画場所を決める)
#define HOME_ADVICE_POS_Y	(500.0f)	// アドバイスコメント位置Y(初期値,実際はクラゲの位置から描画場所を決める)
#define HOME_ADVICE_SIZE_X	(100.0f)	// アドバイスコメント1つのサイズX
#define HOME_ADVICE_SIZE_Y	(50.0f)		// アドバイスコメント1つのサイズY

/*****************************************************************************
* グローバル変数
*****************************************************************************/
// ホームメニューアイコン
bool g_bHomeMenwIconMoveFlage = false;		// アイコンがtrue:動いてる、false:止まってる
UI_2D g_homeMenwIcon[HOME_MENW_ICON_NUM];	// メニューアイコン構造体
// トレーニングアイコン
UI_2D g_homeTrainingIcon[HOME_TRAINING_ICON_NUM];	// トレーニングアイコン構造体
// ホームアドバイス
UI_2D g_homeAdvice;							// アドバイス

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
// ホームメニューアイコン
HRESULT InitUIHomeMenwIcon(void);
void UninitUIHomeMenwIcon(void);
HRESULT MakeVertexUIHomeMenwIcon(LPDIRECT3DDEVICE9 pDevice);
void DrawGameUIHomeMenwIcon(void);
void UpdateUIHomeMenwIcon(void);
void SetTextureUIHomeMenwIcon(int nCnt);		//	メニューアイコン位置変更

// トレーニングアイコン
HRESULT InitUIHomeTrainingIcon(void);
void UninitUIHomeTrainingIcon(void);
HRESULT MakeVertexUIHomeTrainingIcon(LPDIRECT3DDEVICE9 pDevice);
void DrawGameUIHomeTrainingIcon(void);
void UpdateUIHomeTrainingIcon(void);
void SetTextureUIHomeTrainingIcon(int nCnt);	//	トレーニングアイコン位置変更

// ホームアドバイス
HRESULT InitUIHomeAdvice(void);
void UninitUIHomeAdvice(void);
HRESULT MakeVertexUIHomeAdvice(LPDIRECT3DDEVICE9 pDevice);
void DrawGameUIHomeAdvice(void);
void UpdateUIHomeAdvice(void);
void SetTextureUIHomeAdvice(void);		//	アドバイスコメント＆透明度変更

/*******************************************************************************
関数名:	HRESULT InitUI(void)
引数:	なし
戻り値:	正常終了: int型の 0
説明:	Gameの初期化
*******************************************************************************/
HRESULT InitUI(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	switch(GetMainMode())
	{
		// タイトルモードでの初期化
		case MODE_TITLE:
			break;
		// ゲームモードでの初期化処理
		case MODE_GAME:
			// メニューアイコンの初期化
			InitUIHomeMenwIcon();
			// トレアイコン初期化
			InitUIHomeTrainingIcon();
			// アドバイス初期化
			InitUIHomeAdvice();
			break;
		// リザルトモードでの初期化
		case MODE_RESULT:
			break;
	}

	return S_OK;
}
/*******************************************************************************
関数名:	void UninitUI(void)
引数:	なし
戻り値:	なし
説明:	Gameの終了処理
*******************************************************************************/
void UninitUI(void)
{
	switch(GetMainMode())
	{
		// タイトルモードでの終了処理
		case MODE_TITLE:
			break;
		// ゲームモードの終了処理
		case MODE_GAME:
			// メニューアイコン
			UninitUIHomeMenwIcon();
			UninitUIHomeTrainingIcon();
			break;
		// リザルトモードでの終了処理
		case MODE_RESULT:
			break;
	}

}
/*******************************************************************************
関数名:	void UpdateUI(void)
引数:	なし
戻り値:	なし
説明:	Gameの更新処理
*******************************************************************************/
void UpdateUI(void)
{
	switch(GetMainMode())
	{
		// タイトルモードでの更新処理
		case MODE_TITLE:
			break;
		// ゲームモードでの更新処理
		case MODE_GAME:
			switch(GetGameMode())
			{
				case GAME_MODE_HOME:
					// 画像の更新処理
					UpdateUIHomeMenwIcon();
					UpdateUIHomeAdvice();
					break;
				case GAME_MODE_TRAINING:
					UpdateUIHomeTrainingIcon();
					switch(GetTraningMode())
					{
						case TRAINING_MODE_INTELLIGENCE:
							UpdateUIHomeTrainingIcon();
							break;
						case TRAINING_MODE_MOBILITY:
							break;
						case TRAINING_MODE_SENSIBILLITY:
							break;
						case TRAINING_MODE_JUSTICE:
							break;
					}
					break;
				case GAME_MODE_REST:
					break;
				case GAME_MODE_CONTACT:
					break;
				case GAME_MODE_FOOD:
					break;
				case GAME_MODE_CAMERA:
					break;
				case GAME_MODE_HISTORY:
					break;
				case GAME_MODE_OPTION:
					break;
			}
		// リザルトモードでの更新処理
		case MODE_RESULT:
			break;
	}
}
/*******************************************************************************
関数名:	void DrawUI(void)
引数:	なし
戻り値:	なし
説明:	Gameの描画
*******************************************************************************/
void DrawUI(void)
{
	switch(GetMainMode())
	{
		// タイトルモードでの描画処理
		case MODE_TITLE:
			break;
		// ゲームモードでの描画処理
		case MODE_GAME:
			switch(GetGameMode())
			{
				case GAME_MODE_HOME:		// ホーム画面
					DrawGameUIHomeMenwIcon();
					DrawGameUIHomeAdvice();
					break;
				case GAME_MODE_TRAINING:	// トレーニング画面
					DrawGameUIHomeTrainingIcon();
					switch(GetTraningMode())
					{
						case TRAINING_MODE_INTELLIGENCE:
							break;
						case TRAINING_MODE_MOBILITY:
							break;
						case TRAINING_MODE_SENSIBILLITY:
							break;
						case TRAINING_MODE_JUSTICE:
							break;
					}
					break;
				case GAME_MODE_REST:		// 休憩画面
					break;
				case GAME_MODE_FOOD:		// エサ上げ
					break;
				case GAME_MODE_CAMERA:		// カメラの切り替え
					break;
				case GAME_MODE_HISTORY:		// クラゲ図鑑
					break;
				case GAME_MODE_OPTION:		// オプション切り替え
					break;
			}
		// リザルトモードでの描画処理
		case MODE_RESULT:
			break;
	}
}

/*******************************************************************************
関数名:	HRESULT InitUIHomeMenwIcon(void)
引数:	なし
戻り値:	正常終了: int型の 0
説明:	ホームメニューの初期化
*******************************************************************************/
HRESULT InitUIHomeMenwIcon(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 各パラメータの初期化
	for(int nCnt=0;nCnt<HOME_MENW_ICON_NUM;nCnt++)
	{
		g_homeMenwIcon[nCnt].bChoice = false;
		g_homeMenwIcon[nCnt].pD3DVtxBuff = NULL;
		g_homeMenwIcon[nCnt].vPos = D3DXVECTOR3(HOME_MENW_ICON_OUT_POS,HOME_MENW_ICON_POS_Y+((HOME_MENW_ICON_SIZE_Y+HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt),0.0f);
	}
	//頂点情報の作成
	if(FAILED(MakeVertexUIHomeMenwIcon(pDevice)))
	{
		return E_FAIL;
	}
	return S_OK;
}
/*******************************************************************************
関数名:	void UninitUIHomeMenwIcon(void)
引数:	なし
戻り値:	なし
説明:	ホームメニューの終了処理
*******************************************************************************/
void UninitUIHomeMenwIcon(void)
{
	// 頂点の終了処理
	for(int nCnt=0;nCnt<HOME_MENW_ICON_NUM;nCnt++)
	{
		if(g_homeMenwIcon[nCnt].pD3DVtxBuff != NULL)
		{	//バッファーの解放
			g_homeMenwIcon[nCnt].pD3DVtxBuff -> Release();
			g_homeMenwIcon[nCnt].pD3DVtxBuff = NULL;
		}
	}
}
/*******************************************************************************
関数名:	HRESULT MakeVertexUIMenwTexture(LPDIRECT3DDEVICE9 pDevice)
引数:	LPDIRECT3DDEVICE9型 pDevice
戻り値:	なし
説明:	Gameでのメニューアイコン画像頂点作成
*******************************************************************************/
HRESULT MakeVertexUIHomeMenwIcon(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを作成
	for(int nCnt=0;nCnt<HOME_MENW_ICON_NUM;nCnt++)
	{
		if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_2D,
												D3DPOOL_MANAGED,
												&g_homeMenwIcon[nCnt].pD3DVtxBuff,
												NULL)))
		{
			return E_FAIL;
		}
	}

	{// 頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		for(int nCnt=0;nCnt<HOME_MENW_ICON_NUM;nCnt++)
		{
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			g_homeMenwIcon[nCnt].pD3DVtxBuff -> Lock(0,0,(void**)&pVtx,0);

			//頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(g_homeMenwIcon[nCnt].vPos.x - HOME_MENW_ICON_SIZE_X/2,g_homeMenwIcon[nCnt].vPos.y - HOME_MENW_ICON_SIZE_Y/2 + (HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
			pVtx[1].vtx = D3DXVECTOR3(g_homeMenwIcon[nCnt].vPos.x + HOME_MENW_ICON_SIZE_X/2,g_homeMenwIcon[nCnt].vPos.y - HOME_MENW_ICON_SIZE_Y/2 + (HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
			pVtx[2].vtx = D3DXVECTOR3(g_homeMenwIcon[nCnt].vPos.x - HOME_MENW_ICON_SIZE_X/2,g_homeMenwIcon[nCnt].vPos.y + HOME_MENW_ICON_SIZE_Y/2 + (HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
			pVtx[3].vtx = D3DXVECTOR3(g_homeMenwIcon[nCnt].vPos.x + HOME_MENW_ICON_SIZE_X/2,g_homeMenwIcon[nCnt].vPos.y + HOME_MENW_ICON_SIZE_Y/2 + (HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
	
			// rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
	
			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
			pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
			pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
			pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);
	
			// テクスチャ座標指定
			pVtx[0].tex = D3DXVECTOR2(0.0f,(1.0f/HOME_MENW_ICON_NUM)*nCnt);
			pVtx[1].tex = D3DXVECTOR2(1.0f,(1.0f/HOME_MENW_ICON_NUM)*nCnt);
			pVtx[2].tex = D3DXVECTOR2(0.0f,(1.0f/HOME_MENW_ICON_NUM)*(nCnt+1));
			pVtx[3].tex = D3DXVECTOR2(1.0f,(1.0f/HOME_MENW_ICON_NUM)*(nCnt+1));

			// 頂点データをアンロックする
			g_homeMenwIcon[nCnt].pD3DVtxBuff -> Unlock();
		}
	}
	return S_OK;
}
/*******************************************************************************
関数名:	void DrawGameUIHomeMenwIcon(void)
引数:	なし
戻り値:	なし
説明:	Gameでのメニューアイコン画像表示
*******************************************************************************/
void DrawGameUIHomeMenwIcon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 *pTex = GetUITexture();

	for(int nCnt=0;nCnt<HOME_MENW_ICON_NUM;nCnt++)
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice -> SetStreamSource(0,g_homeMenwIcon[nCnt].pD3DVtxBuff,0,sizeof(VERTEX_2D));
		//頂点フォーマットの設定
		pDevice -> SetFVF(FVF_VERTEX_2D);
		//テクスチャの設定
		pDevice -> SetTexture(0,pTex[UI_MOHE_MENW_ICON_TEXTURE]);
		//ポリゴン描画
		pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,0,NUM_POLYGON);
	}

}
/*******************************************************************************
関数名:	void UpdateUIHomeMenwIcon(void)
引数:	なし
戻り値:	なし
説明:	Gameでのメニューアイコン画像更新
*******************************************************************************/
void UpdateUIHomeMenwIcon(void)
{
	POINT gameUIMouseClientPos = GetMouseClientPos();
	JELLY_FISH *gameUIJellyfish = GetJellyfishStatus();

	// クリックされたら表示/非表示
	if(GetMouseRightTrigger())
	{
		if(!g_homeMenwIcon[0].bUse)
		{
			g_homeMenwIcon[0].bUse = true;
			for(int nCnt=0;nCnt<HOME_MENW_ICON_NUM;nCnt++)
			{
				g_homeMenwIcon[nCnt].vPos = D3DXVECTOR3(HOME_MENW_ICON_IN_POS,HOME_MENW_ICON_POS_Y+((HOME_MENW_ICON_SIZE_Y+HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt),0.0f);
				SetTextureUIHomeMenwIcon(nCnt);
			}
		}
		else
		{
			g_homeMenwIcon[0].bUse = false;
			for(int nCnt=0;nCnt<HOME_MENW_ICON_NUM;nCnt++)
			{
				g_homeMenwIcon[nCnt].vPos = D3DXVECTOR3(HOME_MENW_ICON_OUT_POS,HOME_MENW_ICON_POS_Y+((HOME_MENW_ICON_SIZE_Y+HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt),0.0f);
				SetTextureUIHomeMenwIcon(nCnt);
			}
		}
	}

	// 各アイコンのクリック判定
	if(GetMouseLeftTrigger() && g_homeMenwIcon[0].bUse)		// 左トリガーが入ったら
	{
		// どのアイコンクリックしたか判定
		for(int nCnt=0;nCnt<HOME_MENW_ICON_NUM;nCnt++)
		{
			if( g_homeMenwIcon[nCnt].vPos.y - HOME_MENW_ICON_SIZE_Y/2.0f < gameUIMouseClientPos.y &&
				g_homeMenwIcon[nCnt].vPos.y + HOME_MENW_ICON_SIZE_Y/2.0f > gameUIMouseClientPos.y &&
				g_homeMenwIcon[nCnt].vPos.x - HOME_MENW_ICON_SIZE_X/2.0f < gameUIMouseClientPos.x &&
				g_homeMenwIcon[nCnt].vPos.x + HOME_MENW_ICON_SIZE_X/2.0f > gameUIMouseClientPos.x)
			{
				g_homeMenwIcon[nCnt].bChoice = true;
//				InitUIHomeMenwIcon();
				break;
			}
		}
	}

	// 選ばれたアイコンによっての処理
	if(g_homeMenwIcon[0].bChoice)
	{
		SetGameMode(GAME_MODE_TRAINING);
	}
	else if(g_homeMenwIcon[1].bChoice)
	{
		SetGameMode(GAME_MODE_REST);
	}
	else if(g_homeMenwIcon[2].bChoice)
	{
		SetGameMode(GAME_MODE_CONTACT);
	}
	else if(g_homeMenwIcon[3].bChoice)
	{
		SetGameMode(GAME_MODE_FOOD);
	}
	else if(g_homeMenwIcon[4].bChoice)
	{
		SetGameMode(GAME_MODE_CAMERA);
	}
	else if(g_homeMenwIcon[5].bChoice)
	{
		SetGameMode(GAME_MODE_HISTORY);
	}
	else if(g_homeMenwIcon[5].bChoice)
	{
		SetGameMode(GAME_MODE_OPTION);
	}
}
/*******************************************************************************
関数名:	void SetTextureUIHomeMenwIcon(int nCnt)
引数:	int nCnt:どのメニューアイコンを動かすか
戻り値:	
説明:	メニューアイコンの位置変更
*******************************************************************************/
void SetTextureUIHomeMenwIcon(int nCnt)
{
	// 頂点バッファの中身を埋める
	VERTEX_2D *pVtx;
	{
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_homeMenwIcon[nCnt].pD3DVtxBuff -> Lock(0,0,(void**)&pVtx,0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(g_homeMenwIcon[nCnt].vPos.x - HOME_MENW_ICON_SIZE_X/2,g_homeMenwIcon[nCnt].vPos.y - HOME_MENW_ICON_SIZE_Y/2 + (HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
		pVtx[1].vtx = D3DXVECTOR3(g_homeMenwIcon[nCnt].vPos.x + HOME_MENW_ICON_SIZE_X/2,g_homeMenwIcon[nCnt].vPos.y - HOME_MENW_ICON_SIZE_Y/2 + (HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
		pVtx[2].vtx = D3DXVECTOR3(g_homeMenwIcon[nCnt].vPos.x - HOME_MENW_ICON_SIZE_X/2,g_homeMenwIcon[nCnt].vPos.y + HOME_MENW_ICON_SIZE_Y/2 + (HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
		pVtx[3].vtx = D3DXVECTOR3(g_homeMenwIcon[nCnt].vPos.x + HOME_MENW_ICON_SIZE_X/2,g_homeMenwIcon[nCnt].vPos.y + HOME_MENW_ICON_SIZE_Y/2 + (HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);

		// 頂点データをアンロックする
		g_homeMenwIcon[nCnt].pD3DVtxBuff -> Unlock();
	}
}

/*******************************************************************************
関数名:	HRESULT InitUIHomeTrainingIcon(void)
引数:	なし
戻り値:	正常終了: int型の 0
説明:	トレーニングの初期化
*******************************************************************************/
HRESULT InitUIHomeTrainingIcon(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 各パラメータの初期化
	for(int nCnt=0;nCnt<HOME_TRAINING_ICON_NUM;nCnt++)
	{
		g_homeTrainingIcon[nCnt].bChoice = false;
		g_homeTrainingIcon[nCnt].bUse = false;
		g_homeTrainingIcon[nCnt].pD3DVtxBuff = NULL;
		g_homeTrainingIcon[nCnt].vPos = D3DXVECTOR3(HOME_TRAINING_ICON_IN_POS,HOME_TRAINING_ICON_POS_Y+((HOME_TRAINING_ICON_SIZE_Y+HOME_TRAINING_ICON_INTERVAL_HEIGHT)*nCnt),0.0f);
	}
	// トレアイコン頂点情報の作成
	if(FAILED(MakeVertexUIHomeTrainingIcon(pDevice)))
	{
		return E_FAIL;
	}
	return S_OK;
}
/*******************************************************************************
関数名:	void UninitUIHomeTrainingIcon(void)
引数:	なし
戻り値:	なし
説明:	ホームメニューの終了処理
*******************************************************************************/
void UninitUIHomeTrainingIcon(void)
{
	// 頂点の終了処理
	for(int nCnt=0;nCnt<HOME_TRAINING_ICON_NUM;nCnt++)
	{
		if(g_homeTrainingIcon[nCnt].pD3DVtxBuff != NULL)
		{	//バッファーの解放
			g_homeTrainingIcon[nCnt].pD3DVtxBuff -> Release();
			g_homeTrainingIcon[nCnt].pD3DVtxBuff = NULL;
		}
	}
}
/*******************************************************************************
関数名:	HRESULT MakeVertexUIHomeTrainingIcon(LPDIRECT3DDEVICE9 pDevice)
引数:	LPDIRECT3DDEVICE9型 pDevice
戻り値:	なし
説明:	Gameでのトレーニングアイコン画像頂点作成
*******************************************************************************/
HRESULT MakeVertexUIHomeTrainingIcon(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを作成
	for(int nCnt=0;nCnt<HOME_TRAINING_ICON_NUM;nCnt++)
	{
		if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_2D,
												D3DPOOL_MANAGED,
												&g_homeTrainingIcon[nCnt].pD3DVtxBuff,
												NULL)))
		{
			return E_FAIL;
		}
	}

	{// 頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		for(int nCnt=0;nCnt<HOME_TRAINING_ICON_NUM;nCnt++)
		{
			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			g_homeTrainingIcon[nCnt].pD3DVtxBuff -> Lock(0,0,(void**)&pVtx,0);

			//頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(g_homeTrainingIcon[nCnt].vPos.x - HOME_TRAINING_ICON_SIZE_X/2,g_homeTrainingIcon[nCnt].vPos.y - HOME_TRAINING_ICON_SIZE_Y/2 + (HOME_TRAINING_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
			pVtx[1].vtx = D3DXVECTOR3(g_homeTrainingIcon[nCnt].vPos.x + HOME_TRAINING_ICON_SIZE_X/2,g_homeTrainingIcon[nCnt].vPos.y - HOME_TRAINING_ICON_SIZE_Y/2 + (HOME_TRAINING_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
			pVtx[2].vtx = D3DXVECTOR3(g_homeTrainingIcon[nCnt].vPos.x - HOME_TRAINING_ICON_SIZE_X/2,g_homeTrainingIcon[nCnt].vPos.y + HOME_TRAINING_ICON_SIZE_Y/2 + (HOME_TRAINING_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
			pVtx[3].vtx = D3DXVECTOR3(g_homeTrainingIcon[nCnt].vPos.x + HOME_TRAINING_ICON_SIZE_X/2,g_homeTrainingIcon[nCnt].vPos.y + HOME_TRAINING_ICON_SIZE_Y/2 + (HOME_TRAINING_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
	
			// rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
	
			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
			pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
			pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
			pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);
	
			// テクスチャ座標指定
			pVtx[0].tex = D3DXVECTOR2(0.0f,(1.0f/HOME_TRAINING_ICON_NUM)*nCnt);
			pVtx[1].tex = D3DXVECTOR2(1.0f,(1.0f/HOME_TRAINING_ICON_NUM)*nCnt);
			pVtx[2].tex = D3DXVECTOR2(0.0f,(1.0f/HOME_TRAINING_ICON_NUM)*(nCnt+1));
			pVtx[3].tex = D3DXVECTOR2(1.0f,(1.0f/HOME_TRAINING_ICON_NUM)*(nCnt+1));

			// 頂点データをアンロックする
			g_homeTrainingIcon[nCnt].pD3DVtxBuff -> Unlock();
		}
	}
	return S_OK;
}
/*******************************************************************************
関数名:	void DrawGameUIHomeTrainingIcon(void)
引数:	なし
戻り値:	なし
説明:	Gameでのメニューアイコン画像表示
*******************************************************************************/
void DrawGameUIHomeTrainingIcon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 *pTex = GetUITexture();

	for(int nCnt=0;nCnt<HOME_TRAINING_ICON_NUM;nCnt++)
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice -> SetStreamSource(0,g_homeTrainingIcon[nCnt].pD3DVtxBuff,0,sizeof(VERTEX_2D));
		//頂点フォーマットの設定
		pDevice -> SetFVF(FVF_VERTEX_2D);
		//テクスチャの設定
		pDevice -> SetTexture(0,pTex[UI_MOHE_TRAINING_TEXTURE]);
		//ポリゴン描画
		pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,0,NUM_POLYGON);
	}

}
/*******************************************************************************
関数名:	void UpdateUIHomeTrainingIcon(void)
引数:	なし
戻り値:	なし
説明:	Gameでのメニューアイコン画像更新
*******************************************************************************/
void UpdateUIHomeTrainingIcon(void)
{
	// マウスの情報を受け取る
	POINT gameUIMouseClientPos = GetMouseClientPos();

	// 各アイコンのクリック判定
	if(GetMouseLeftTrigger())		// 右トリガーが入ったら
	{
		// どのアイコンクリックしたか判定
		for(int nCnt=0;nCnt<HOME_MENW_ICON_NUM;nCnt++)
		{
			if( g_homeTrainingIcon[nCnt].vPos.y - HOME_TRAINING_ICON_SIZE_Y/2.0f < gameUIMouseClientPos.y &&
				g_homeTrainingIcon[nCnt].vPos.y + HOME_TRAINING_ICON_SIZE_Y/2.0f > gameUIMouseClientPos.y &&
				g_homeTrainingIcon[nCnt].vPos.x - HOME_TRAINING_ICON_SIZE_X/2.0f < gameUIMouseClientPos.x &&
				g_homeTrainingIcon[nCnt].vPos.x + HOME_TRAINING_ICON_SIZE_X/2.0f > gameUIMouseClientPos.x)
			{
				// クリックされたアイコンを選択に
				g_homeTrainingIcon[nCnt].bChoice = true;
				break;
			}
			// アイコン外をクリックでホームメニューに戻る
			else
			{
				SetGameMode(GAME_MODE_HOME);
				InitUIHomeTrainingIcon();
			}
		}
	}
	// 選ばれたアイコンによる処理
	if(g_homeTrainingIcon[0].bChoice)
	{
		SetTraningMode(TRAINING_MODE_INTELLIGENCE);
	}
	else if(g_homeTrainingIcon[1].bChoice)
	{
		SetTraningMode(TRAINING_MODE_MOBILITY);
	}
	else if(g_homeTrainingIcon[2].bChoice)
	{
		SetTraningMode(TRAINING_MODE_SENSIBILLITY);
	}
	else if(g_homeTrainingIcon[3].bChoice)
	{
		SetTraningMode(TRAINING_MODE_JUSTICE);
	}

	// 右クリックキャンセル
	if(GetMouseRightTrigger())
	{
		SetGameMode(GAME_MODE_HOME);
		InitUIHomeTrainingIcon();
	}

}
/*******************************************************************************
関数名:	void SetTextureUIHomeTrainingIcon(int nCnt)
引数:	int nCnt:どのメニューアイコンを動かすか
戻り値:	
説明:	メニューアイコンの位置変更
*******************************************************************************/
void SetTextureUIHomeTrainingIcon(int nCnt)
{
}

/*******************************************************************************
関数名:	HRESULT InitUIHomeAdvice(void)
引数:	なし
戻り値:	正常終了: int型の 0
説明:	トレーニングの初期化
*******************************************************************************/
HRESULT InitUIHomeAdvice(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 各パラメータの初期化
	g_homeAdvice.bChoice = false;
	g_homeAdvice.bUse = false;
	g_homeAdvice.pD3DVtxBuff = NULL;
	g_homeAdvice.vPos = D3DXVECTOR3(HOME_ADVICE_POS_X,HOME_ADVICE_POS_Y,0.0f);

	// アドバイス頂点情報の作成
	if(FAILED(MakeVertexUIHomeAdvice(pDevice)))
	{
		return E_FAIL;
	}

	return S_OK;
}
/*******************************************************************************
関数名:	void UninitUIHomeAdvice(void)
引数:	なし
戻り値:	なし
説明:	ホームメニューの終了処理
*******************************************************************************/
void UninitUIHomeAdvice(void)
{
	// 頂点の終了処理
	if(g_homeAdvice.pD3DVtxBuff != NULL)
	{	//バッファーの解放
		g_homeAdvice.pD3DVtxBuff -> Release();
		g_homeAdvice.pD3DVtxBuff = NULL;
	}
}
/*******************************************************************************
関数名:	HRESULT MakeVertexUIHomeAdvice(LPDIRECT3DDEVICE9 pDevice)
引数:	LPDIRECT3DDEVICE9型 pDevice
戻り値:	なし
説明:	Gameでのメニューアイコン画像頂点作成
*******************************************************************************/
HRESULT MakeVertexUIHomeAdvice(LPDIRECT3DDEVICE9 pDevice) 
{
	// オブジェクトの頂点バッファを作成
	if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_2D,
											D3DPOOL_MANAGED,
											&g_homeAdvice.pD3DVtxBuff,
											NULL)))
	{
		return E_FAIL;
	}

	{// 頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_homeAdvice.pD3DVtxBuff -> Lock(0,0,(void**)&pVtx,0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(g_homeAdvice.vPos.x - HOME_ADVICE_SIZE_X/2.0f,g_homeAdvice.vPos.y - HOME_ADVICE_SIZE_Y/2.0f,0.0f);
		pVtx[1].vtx = D3DXVECTOR3(g_homeAdvice.vPos.x + HOME_ADVICE_SIZE_X/2.0f,g_homeAdvice.vPos.y - HOME_ADVICE_SIZE_Y/2.0f,0.0f);
		pVtx[2].vtx = D3DXVECTOR3(g_homeAdvice.vPos.x - HOME_ADVICE_SIZE_X/2.0f,g_homeAdvice.vPos.y + HOME_ADVICE_SIZE_Y/2.0f,0.0f);
		pVtx[3].vtx = D3DXVECTOR3(g_homeAdvice.vPos.x + HOME_ADVICE_SIZE_X/2.0f,g_homeAdvice.vPos.y + HOME_ADVICE_SIZE_Y/2.0f,0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
		pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
		pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
		pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

		// テクスチャ座標指定
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f,(1.0f/ADVICE_TYPE_MAX));
		pVtx[3].tex = D3DXVECTOR2(1.0f,(1.0f/ADVICE_TYPE_MAX));

		// 頂点データをアンロックする
		g_homeAdvice.pD3DVtxBuff -> Unlock();
	}
	return S_OK;
}
/*******************************************************************************
関数名:	void DrawGameUIHomeAdvice(void)
引数:	なし
戻り値:	なし
説明:	Gameでのアドバイス画像表示
*******************************************************************************/
void DrawGameUIHomeAdvice(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 *pTex = GetUITexture();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice -> SetStreamSource(0,g_homeAdvice.pD3DVtxBuff,0,sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice -> SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice -> SetTexture(0,pTex[UI_MOHE_ADVICE_TEXTURE]);
	//ポリゴン描画
	pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,0,NUM_POLYGON);
}
/*******************************************************************************
関数名:	void UpdateUIHomeAdvice(void)
引数:	なし
戻り値:	なし
説明:	Gameでのアドバイス画像更新
*******************************************************************************/
void UpdateUIHomeAdvice(void)
{
}
/*******************************************************************************
関数名:	void SetTextureUIHomeAdvice(void)
引数:	なし
戻り値:	なし
説明:	アドバイス画像の選択
*******************************************************************************/
void SetTextureUIHomeAdvice(void)
{
	// クラゲ情報を取得
	JELLY_FISH *gameJellyfish = GetJellyfishStatus();

	// 頂点バッファの中身を埋める
	VERTEX_2D *pVtx;
	{
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_homeAdvice.pD3DVtxBuff -> Lock(0,0,(void**)&pVtx,0);

		// クラゲの状態によってアドバイスを選択する/*選択の仕方要検討(ランダム性を持たせる)*/
		if(gameJellyfish->nFoodFull > 10)
		{
			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.f,ADIVCE_FINE/ADVICE_TYPE_MAX);
			pVtx[1].tex = D3DXVECTOR2(1.f,ADIVCE_FINE/ADVICE_TYPE_MAX);
			pVtx[2].tex = D3DXVECTOR2(0.f,(ADIVCE_FINE+1/ADVICE_TYPE_MAX));
			pVtx[3].tex = D3DXVECTOR2(1.f,(ADIVCE_FINE+1/ADVICE_TYPE_MAX));
		}

		// 頂点データをアンロックする
		g_homeAdvice.pD3DVtxBuff -> Unlock();
	}
}
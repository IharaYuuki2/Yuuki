/*******************************************************************************
* タイトル:		プレイヤー処理
* プログラム名:	Player.cpp
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2016/02/01
********************************************************************************
* 更新履歴:		- 2016/02/25	伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "XFile.h"
#include "Player.h"
#include "Input.h"
#include "Camera.h"
#include "DebugProc.h"
#include "Object.h"
#include "Shadow.h"
#include "UI.h"
#include "Effect.h"
#include "Sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PLAYER (1)

#define VALUE_MOVE (32.0f)							// 移動量
#define VALUE_CARRIER_SPEED (24.0f)
#define GRAVITY_ACCELERATION (-0.8f)				// 重力係数
#define COEFFICIENT_OF_REBOUND (-0.85f)				// 反発係数
#define COEFFICIENT_OF_FRICTION (0.30f)				// 摩擦係数
#define COEFFICIENT_OF_RESISTANCE (0.005f)			// 空気抵抗による抗力係数
#define COEFFICIENT_OF_ROT_INERTIA (0.20f)			// 回転慣性係数
#define	SHADOW_SIZE_X		(50.0f)					// 影の幅
#define	SHADOW_SIZE_Z		(50.0f)					// 影の高さ

// アニメーション用マクロ定義
#define	NUM_ANIM_PATTERN			(3)	
#define	FRAME_CHANGE_PATTERN_PLAYER	(7)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
PLAYER		g_aPlayer[MAX_PLAYER];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	
	return S_OK;
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	
}
/*******************************************************************************
関数名:	PLAYER *GetpPlayer(int Team, int PlayerID)
引数:	なし
戻り値:	なし
説明:	TeamのPlayerID番目のプレイヤー構造体ワークのアドレスを取得
*******************************************************************************/
PLAYER *GetpPlayer(int nPlayer)
{
	return &g_aPlayer[nPlayer];
}
/*******************************************************************************
* タイトル:		3D空間内のオブジェクト・ポリゴンの処理
* プログラム名:	Object.h
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2016/01/24
********************************************************************************
* 更新履歴:		- 2016/01/24	伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 列挙体
//*****************************************************************************
// クラゲのステータスタイプ
typedef enum
{
	INTELLIGENCE = 0,
	MOBILLITY,
	SENSIBILLITY,
	JUSTICE,
	FOODFULL,
	MOTIVATION,
	MAX_TYPE
} JELLYFISH_STATUS_TYPE;
//*****************************************************************************
// 構造体
//*****************************************************************************
// クラゲ用の構造体
typedef class
{
	public:
		D3DXMATRIX	mtxWorld;		// ワールドマトリックス
		D3DXVECTOR3 pos;			// ワールド空間内におけるローカル座標の原点の座標
		D3DXVECTOR3 rot;			// 回転角
		D3DXVECTOR3 scl;			// 大きさ(スケール)
		float		radius;			// 半径
		bool		bUse;			// 使用中かどうか
		int			nIntelligence;	// 知力/*各パラメータ値MAXは100*/
		int			nMobility;		// 体力
		int			nSensibility;	// 感性
		int			nJustice;		// 正義感
		int			nFoodFull;		// 満腹
		int			nMotivation;	// やる気
		int			nEmpty[5];		// 今後追加のステータス
} JELLY_FISH;

// オブジェクト用の構造体
typedef struct
{
	D3DXMATRIX	mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 pos;		// ワールド空間内におけるローカル座標の原点の座標
	D3DXVECTOR3 rot;		// 回転角
	D3DXVECTOR3 scl;		// 大きさ(スケール)
	float		radius;		// 半径
	bool		bUse;		// 使用中かどうか
} OBJECT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitObject(void);
void UpdateObject(void);
void DrawObject(void);
JELLY_FISH *GetJellyfishStatus(void);
void ChangeJellyfishStatus(JELLYFISH_STATUS_TYPE statusType, int valu);

#endif

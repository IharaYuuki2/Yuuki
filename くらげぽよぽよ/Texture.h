/*******************************************************************************
* タイトル:		Textureヘッダーファイル
* プログラム名:	Texture.h
* 作成者:		GP11A331 4 伊原佑稀
* 作成日:		2016/01/29
********************************************************************************
* 更新履歴:		- 2016/02/23	GP11A331 4 伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "Main.h"

/*******************************************************************************
* 構造体定義
*******************************************************************************/

/*******************************************************************************
* 列挙体定義
*******************************************************************************/
typedef enum
{TEX_SHADOW = 0,
	SUNSET,
	NOTE1,
	NOTE2,
	WALL,
	ROAD,
	MAX_SPACE_TEXTURE
} SPACE_TEXTURE;

typedef enum
{
	UI_MOHE_MENW_ICON_TEXTURE = 0,
	UI_MOHE_TRAINING_TEXTURE,
	UI_MOHE_ADVICE_TEXTURE,
	MAX_UI_TEXTURE
} UI_TEXTURE, USER_INTERFACE_TEXTURE;

typedef enum
{
	MAX_UTILITY_TEXTURE = 1
} UTILITY_TEXTURE;

typedef enum
{
	KURAGEPOYOPOYO = 0,
	TITLE_START,
	MAX_TITLE_TEXTURE
} TITLE_TEXTURE;

typedef enum
{
	MAX_RESULT_TEXTURE = 1
} RESULT_TEXTURE;

//*****************************************************************************
// マクロ定義
//*****************************************************************************

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
HRESULT InitTexture(void);
void UninitTexture(void);
LPDIRECT3DTEXTURE9 *GetTitleTexture(void);
LPDIRECT3DTEXTURE9 *GetResultTexture(void);
LPDIRECT3DTEXTURE9 *GetSpaceTexture(void);
LPDIRECT3DTEXTURE9 *GetUITexture(void);
LPDIRECT3DTEXTURE9 *GetUtilityTexture(void);

LPDIRECT3DVERTEXBUFFER9 *GetTitleTextureVertexBuffer(void);
LPDIRECT3DVERTEXBUFFER9 *GetUITextureVertexBuffer(void);
#endif
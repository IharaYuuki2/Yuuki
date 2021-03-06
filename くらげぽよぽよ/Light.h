/*******************************************************************************
* タイトル:		ライト処理
* プログラム名:	Light.h
* 作成者:		GP11A331 4番 伊原佑稀
* 作成日:		2015/10/22
********************************************************************************
* 更新履歴:		- 2015/10/22	伊原佑稀
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitLight(void);
void UninitLight(void);
void UpdateLight(void);

#endif

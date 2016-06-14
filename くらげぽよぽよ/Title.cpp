/*******************************************************************************
* �^�C�g��:		Title����
* �v���O������:	Title.cpp
* �쐬��:		GP11A331 4 �Ɍ��C�H
* �쐬��:		2016/02/23
********************************************************************************
* �X�V����:		- 2016/02/23	 �Ɍ�
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "Title.h"
#include "Texture.h"
#include "input.h"
#include "Light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define POLYGON_POS_X_GAMENAME	(SCREEN_WIDTH/2)//�|���S�����S��X
#define POLYGON_POS_Y_GAMENAME	(200)//�|���S���̒��S��Y
#define POLYGON_SIZE_X_GAMENAME	(800)//�|���S����SIZE X
#define POLYGON_SIZE_Y_GAMENAME	(400)//�|���S����SIZE Y
//#define POLYGON_TEXTURENAME_GAMENAME "data/TEXTURE/TitleGameName.png"

#define POLYGON_POS_X_GAMESTART	(SCREEN_WIDTH/2)//�|���S�����S��X
#define POLYGON_POS_Y_GAMESTART	(800)//�|���S���̒��S��Y
#define POLYGON_SIZE_X_GAMESTART	(400)//�|���S����SIZE X
#define POLYGON_SIZE_Y_GAMESTART	(200)//�|���S����SIZE Y
//#define POLYGON_TEXTURENAME_GAMESTART "data/TEXTURE/TitleIconStart.png"


/*******************************************************************************
* �\���̒�`
*******************************************************************************/

/*******************************************************************************
* �v���g�^�C�v�錾
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
* �O���[�o���ϐ�
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

	//���_���̍쐬
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

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBufferTitleGameName, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTitleTex[KURAGEPOYOPOYO]);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,						//���[�h����ŏ��̒��_�C���f�b�N�X
		NUM_POLYGON				//�|���S���̐�
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
		sizeof(VERTEX_2D)*NUM_VERTEX,	//���_�f�[�^�̃o�b�t�@�T�C�Y 
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_2D,					//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED, 
		&g_pVtxBufferTitleGameName,			//���_�o�b�t�@�C���^�[�t�F�[�X�̃|�C���^
		NULL)))
	{
		return E_FAIL;
	}
	{
	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBufferTitleGameName->Lock( 0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
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


	//�e�N�X�`�����W�w��
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

	//���_���̍쐬
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

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBufferTitleGameStart, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTitleTex[TITLE_START]);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,						//���[�h����ŏ��̒��_�C���f�b�N�X
		NUM_POLYGON				//�|���S���̐�
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
		sizeof(VERTEX_2D)*NUM_VERTEX,	//���_�f�[�^�̃o�b�t�@�T�C�Y 
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_2D,					//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED, 
		&g_pVtxBufferTitleGameStart,			//���_�o�b�t�@�C���^�[�t�F�[�X�̃|�C���^
		NULL)))
	{
		return E_FAIL;
	}
	{
	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBufferTitleGameStart->Lock( 0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
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


	//�e�N�X�`�����W�w��
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
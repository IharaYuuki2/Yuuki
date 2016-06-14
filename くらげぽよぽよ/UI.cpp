/*******************************************************************************
* �^�C�g��:		UI����
* �v���O������:	UI.cpp
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2016/02/01
********************************************************************************
* �X�V����:		- 2016/02/25	�Ɍ��C�H
*					- V1.00		Initial Version
*				- 2016/05/29	��ˌd
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "UI.h"
#include "DebugProc.h"
#include "Texture.h"
#include "Object.h"
#include "Game.h"

/*****************************************************************************
* �}�N����`
******************************************************************************/
// ���j���[�A�C�R���֌W
#define HOME_MENW_ICON_NUM	(7)		// ���j���[�A�C�R����(�c�̕�����)
#define HOME_MENW_ICON_POS_X	(500.0f)		// ���j���[�A�C�R���ʒuX(1���ڂ̒��S���WX)
#define HOME_MENW_ICON_POS_Y	(80.0f)			// ���j���[�A�C�R���ʒuY(1���ڂ̒��S���WY)
#define HOME_MENW_ICON_OUT_POS	(2000.0f)		// ���j���[�A�C�R���ʒu(��\��)
#define HOME_MENW_ICON_IN_POS	(1000.0f)		// ���j���[�A�C�R���ʒu(�\��)
#define HOME_MENW_ICON_SIZE_X	(300.0f)		// ���j���[�A�C�R��1�̑傫��X����
#define HOME_MENW_ICON_SIZE_Y	(140.0f)		// ���j���[�A�C�R��1�̑傫��Y����
#define HOME_MENW_ICON_INTERVAL_HEIGHT	(0.0f)	// ���j���[�A�C�R�����������̕�

// �g���[�j���O�A�C�R���֌W
#define HOME_TRAINING_ICON_NUM	(4)		// �g���[�j���O�A�C�R��(�c�̕�����)
#define HOME_TRAINING_ICON_POS_X	(500.0f)		// ���j���[�A�C�R���ʒuX(1���ڂ̒��S���WX)
#define HOME_TRAINING_ICON_POS_Y	(80.0f)			// ���j���[�A�C�R���ʒuY(1���ڂ̒��S���WY)
#define HOME_TRAINING_ICON_OUT_POS	(2000.0f)		// ���j���[�A�C�R���ʒu(��\��)		/*�ʒu�͗v����*/
#define HOME_TRAINING_ICON_IN_POS	(1000.0f)		// ���j���[�A�C�R���ʒu(�\��)
#define HOME_TRAINING_ICON_SIZE_X	(300.0f)		// ���j���[�A�C�R��1�̑傫��X����
#define HOME_TRAINING_ICON_SIZE_Y	(140.0f)		// ���j���[�A�C�R��1�̑傫��Y����
#define HOME_TRAINING_ICON_INTERVAL_HEIGHT	(0.0f)	// ���j���[�A�C�R�����������̕�

// �A�h�o�C�X�֌W
#define HOME_ADVICE_NUM	(3)		// �A�h�o�C�X�R�����g(�c�̕�����)
#define HOME_ADVICE_POS_X	(500.0f)	// �A�h�o�C�X�R�����g�ʒuX(�����l,���ۂ̓N���Q�̈ʒu����`��ꏊ�����߂�)
#define HOME_ADVICE_POS_Y	(500.0f)	// �A�h�o�C�X�R�����g�ʒuY(�����l,���ۂ̓N���Q�̈ʒu����`��ꏊ�����߂�)
#define HOME_ADVICE_SIZE_X	(100.0f)	// �A�h�o�C�X�R�����g1�̃T�C�YX
#define HOME_ADVICE_SIZE_Y	(50.0f)		// �A�h�o�C�X�R�����g1�̃T�C�YY

/*****************************************************************************
* �O���[�o���ϐ�
*****************************************************************************/
// �z�[�����j���[�A�C�R��
bool g_bHomeMenwIconMoveFlage = false;		// �A�C�R����true:�����Ă�Afalse:�~�܂��Ă�
UI_2D g_homeMenwIcon[HOME_MENW_ICON_NUM];	// ���j���[�A�C�R���\����
// �g���[�j���O�A�C�R��
UI_2D g_homeTrainingIcon[HOME_TRAINING_ICON_NUM];	// �g���[�j���O�A�C�R���\����
// �z�[���A�h�o�C�X
UI_2D g_homeAdvice;							// �A�h�o�C�X

/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
// �z�[�����j���[�A�C�R��
HRESULT InitUIHomeMenwIcon(void);
void UninitUIHomeMenwIcon(void);
HRESULT MakeVertexUIHomeMenwIcon(LPDIRECT3DDEVICE9 pDevice);
void DrawGameUIHomeMenwIcon(void);
void UpdateUIHomeMenwIcon(void);
void SetTextureUIHomeMenwIcon(int nCnt);		//	���j���[�A�C�R���ʒu�ύX

// �g���[�j���O�A�C�R��
HRESULT InitUIHomeTrainingIcon(void);
void UninitUIHomeTrainingIcon(void);
HRESULT MakeVertexUIHomeTrainingIcon(LPDIRECT3DDEVICE9 pDevice);
void DrawGameUIHomeTrainingIcon(void);
void UpdateUIHomeTrainingIcon(void);
void SetTextureUIHomeTrainingIcon(int nCnt);	//	�g���[�j���O�A�C�R���ʒu�ύX

// �z�[���A�h�o�C�X
HRESULT InitUIHomeAdvice(void);
void UninitUIHomeAdvice(void);
HRESULT MakeVertexUIHomeAdvice(LPDIRECT3DDEVICE9 pDevice);
void DrawGameUIHomeAdvice(void);
void UpdateUIHomeAdvice(void);
void SetTextureUIHomeAdvice(void);		//	�A�h�o�C�X�R�����g�������x�ύX

/*******************************************************************************
�֐���:	HRESULT InitUI(void)
����:	�Ȃ�
�߂�l:	����I��: int�^�� 0
����:	Game�̏�����
*******************************************************************************/
HRESULT InitUI(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	switch(GetMainMode())
	{
		// �^�C�g�����[�h�ł̏�����
		case MODE_TITLE:
			break;
		// �Q�[�����[�h�ł̏���������
		case MODE_GAME:
			// ���j���[�A�C�R���̏�����
			InitUIHomeMenwIcon();
			// �g���A�C�R��������
			InitUIHomeTrainingIcon();
			// �A�h�o�C�X������
			InitUIHomeAdvice();
			break;
		// ���U���g���[�h�ł̏�����
		case MODE_RESULT:
			break;
	}

	return S_OK;
}
/*******************************************************************************
�֐���:	void UninitUI(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	Game�̏I������
*******************************************************************************/
void UninitUI(void)
{
	switch(GetMainMode())
	{
		// �^�C�g�����[�h�ł̏I������
		case MODE_TITLE:
			break;
		// �Q�[�����[�h�̏I������
		case MODE_GAME:
			// ���j���[�A�C�R��
			UninitUIHomeMenwIcon();
			UninitUIHomeTrainingIcon();
			break;
		// ���U���g���[�h�ł̏I������
		case MODE_RESULT:
			break;
	}

}
/*******************************************************************************
�֐���:	void UpdateUI(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	Game�̍X�V����
*******************************************************************************/
void UpdateUI(void)
{
	switch(GetMainMode())
	{
		// �^�C�g�����[�h�ł̍X�V����
		case MODE_TITLE:
			break;
		// �Q�[�����[�h�ł̍X�V����
		case MODE_GAME:
			switch(GetGameMode())
			{
				case GAME_MODE_HOME:
					// �摜�̍X�V����
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
		// ���U���g���[�h�ł̍X�V����
		case MODE_RESULT:
			break;
	}
}
/*******************************************************************************
�֐���:	void DrawUI(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	Game�̕`��
*******************************************************************************/
void DrawUI(void)
{
	switch(GetMainMode())
	{
		// �^�C�g�����[�h�ł̕`�揈��
		case MODE_TITLE:
			break;
		// �Q�[�����[�h�ł̕`�揈��
		case MODE_GAME:
			switch(GetGameMode())
			{
				case GAME_MODE_HOME:		// �z�[�����
					DrawGameUIHomeMenwIcon();
					DrawGameUIHomeAdvice();
					break;
				case GAME_MODE_TRAINING:	// �g���[�j���O���
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
				case GAME_MODE_REST:		// �x�e���
					break;
				case GAME_MODE_FOOD:		// �G�T�グ
					break;
				case GAME_MODE_CAMERA:		// �J�����̐؂�ւ�
					break;
				case GAME_MODE_HISTORY:		// �N���Q�}��
					break;
				case GAME_MODE_OPTION:		// �I�v�V�����؂�ւ�
					break;
			}
		// ���U���g���[�h�ł̕`�揈��
		case MODE_RESULT:
			break;
	}
}

/*******************************************************************************
�֐���:	HRESULT InitUIHomeMenwIcon(void)
����:	�Ȃ�
�߂�l:	����I��: int�^�� 0
����:	�z�[�����j���[�̏�����
*******************************************************************************/
HRESULT InitUIHomeMenwIcon(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// �e�p�����[�^�̏�����
	for(int nCnt=0;nCnt<HOME_MENW_ICON_NUM;nCnt++)
	{
		g_homeMenwIcon[nCnt].bChoice = false;
		g_homeMenwIcon[nCnt].pD3DVtxBuff = NULL;
		g_homeMenwIcon[nCnt].vPos = D3DXVECTOR3(HOME_MENW_ICON_OUT_POS,HOME_MENW_ICON_POS_Y+((HOME_MENW_ICON_SIZE_Y+HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt),0.0f);
	}
	//���_���̍쐬
	if(FAILED(MakeVertexUIHomeMenwIcon(pDevice)))
	{
		return E_FAIL;
	}
	return S_OK;
}
/*******************************************************************************
�֐���:	void UninitUIHomeMenwIcon(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�z�[�����j���[�̏I������
*******************************************************************************/
void UninitUIHomeMenwIcon(void)
{
	// ���_�̏I������
	for(int nCnt=0;nCnt<HOME_MENW_ICON_NUM;nCnt++)
	{
		if(g_homeMenwIcon[nCnt].pD3DVtxBuff != NULL)
		{	//�o�b�t�@�[�̉��
			g_homeMenwIcon[nCnt].pD3DVtxBuff -> Release();
			g_homeMenwIcon[nCnt].pD3DVtxBuff = NULL;
		}
	}
}
/*******************************************************************************
�֐���:	HRESULT MakeVertexUIMenwTexture(LPDIRECT3DDEVICE9 pDevice)
����:	LPDIRECT3DDEVICE9�^ pDevice
�߂�l:	�Ȃ�
����:	Game�ł̃��j���[�A�C�R���摜���_�쐬
*******************************************************************************/
HRESULT MakeVertexUIHomeMenwIcon(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@���쐬
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

	{// ���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		for(int nCnt=0;nCnt<HOME_MENW_ICON_NUM;nCnt++)
		{
			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			g_homeMenwIcon[nCnt].pD3DVtxBuff -> Lock(0,0,(void**)&pVtx,0);

			//���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(g_homeMenwIcon[nCnt].vPos.x - HOME_MENW_ICON_SIZE_X/2,g_homeMenwIcon[nCnt].vPos.y - HOME_MENW_ICON_SIZE_Y/2 + (HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
			pVtx[1].vtx = D3DXVECTOR3(g_homeMenwIcon[nCnt].vPos.x + HOME_MENW_ICON_SIZE_X/2,g_homeMenwIcon[nCnt].vPos.y - HOME_MENW_ICON_SIZE_Y/2 + (HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
			pVtx[2].vtx = D3DXVECTOR3(g_homeMenwIcon[nCnt].vPos.x - HOME_MENW_ICON_SIZE_X/2,g_homeMenwIcon[nCnt].vPos.y + HOME_MENW_ICON_SIZE_Y/2 + (HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
			pVtx[3].vtx = D3DXVECTOR3(g_homeMenwIcon[nCnt].vPos.x + HOME_MENW_ICON_SIZE_X/2,g_homeMenwIcon[nCnt].vPos.y + HOME_MENW_ICON_SIZE_Y/2 + (HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
	
			// rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
	
			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
			pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
			pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
			pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);
	
			// �e�N�X�`�����W�w��
			pVtx[0].tex = D3DXVECTOR2(0.0f,(1.0f/HOME_MENW_ICON_NUM)*nCnt);
			pVtx[1].tex = D3DXVECTOR2(1.0f,(1.0f/HOME_MENW_ICON_NUM)*nCnt);
			pVtx[2].tex = D3DXVECTOR2(0.0f,(1.0f/HOME_MENW_ICON_NUM)*(nCnt+1));
			pVtx[3].tex = D3DXVECTOR2(1.0f,(1.0f/HOME_MENW_ICON_NUM)*(nCnt+1));

			// ���_�f�[�^���A�����b�N����
			g_homeMenwIcon[nCnt].pD3DVtxBuff -> Unlock();
		}
	}
	return S_OK;
}
/*******************************************************************************
�֐���:	void DrawGameUIHomeMenwIcon(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	Game�ł̃��j���[�A�C�R���摜�\��
*******************************************************************************/
void DrawGameUIHomeMenwIcon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 *pTex = GetUITexture();

	for(int nCnt=0;nCnt<HOME_MENW_ICON_NUM;nCnt++)
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice -> SetStreamSource(0,g_homeMenwIcon[nCnt].pD3DVtxBuff,0,sizeof(VERTEX_2D));
		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice -> SetFVF(FVF_VERTEX_2D);
		//�e�N�X�`���̐ݒ�
		pDevice -> SetTexture(0,pTex[UI_MOHE_MENW_ICON_TEXTURE]);
		//�|���S���`��
		pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,0,NUM_POLYGON);
	}

}
/*******************************************************************************
�֐���:	void UpdateUIHomeMenwIcon(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	Game�ł̃��j���[�A�C�R���摜�X�V
*******************************************************************************/
void UpdateUIHomeMenwIcon(void)
{
	POINT gameUIMouseClientPos = GetMouseClientPos();
	JELLY_FISH *gameUIJellyfish = GetJellyfishStatus();

	// �N���b�N���ꂽ��\��/��\��
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

	// �e�A�C�R���̃N���b�N����
	if(GetMouseLeftTrigger() && g_homeMenwIcon[0].bUse)		// ���g���K�[����������
	{
		// �ǂ̃A�C�R���N���b�N����������
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

	// �I�΂ꂽ�A�C�R���ɂ���Ă̏���
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
�֐���:	void SetTextureUIHomeMenwIcon(int nCnt)
����:	int nCnt:�ǂ̃��j���[�A�C�R���𓮂�����
�߂�l:	
����:	���j���[�A�C�R���̈ʒu�ύX
*******************************************************************************/
void SetTextureUIHomeMenwIcon(int nCnt)
{
	// ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;
	{
		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_homeMenwIcon[nCnt].pD3DVtxBuff -> Lock(0,0,(void**)&pVtx,0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(g_homeMenwIcon[nCnt].vPos.x - HOME_MENW_ICON_SIZE_X/2,g_homeMenwIcon[nCnt].vPos.y - HOME_MENW_ICON_SIZE_Y/2 + (HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
		pVtx[1].vtx = D3DXVECTOR3(g_homeMenwIcon[nCnt].vPos.x + HOME_MENW_ICON_SIZE_X/2,g_homeMenwIcon[nCnt].vPos.y - HOME_MENW_ICON_SIZE_Y/2 + (HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
		pVtx[2].vtx = D3DXVECTOR3(g_homeMenwIcon[nCnt].vPos.x - HOME_MENW_ICON_SIZE_X/2,g_homeMenwIcon[nCnt].vPos.y + HOME_MENW_ICON_SIZE_Y/2 + (HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
		pVtx[3].vtx = D3DXVECTOR3(g_homeMenwIcon[nCnt].vPos.x + HOME_MENW_ICON_SIZE_X/2,g_homeMenwIcon[nCnt].vPos.y + HOME_MENW_ICON_SIZE_Y/2 + (HOME_MENW_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);

		// ���_�f�[�^���A�����b�N����
		g_homeMenwIcon[nCnt].pD3DVtxBuff -> Unlock();
	}
}

/*******************************************************************************
�֐���:	HRESULT InitUIHomeTrainingIcon(void)
����:	�Ȃ�
�߂�l:	����I��: int�^�� 0
����:	�g���[�j���O�̏�����
*******************************************************************************/
HRESULT InitUIHomeTrainingIcon(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// �e�p�����[�^�̏�����
	for(int nCnt=0;nCnt<HOME_TRAINING_ICON_NUM;nCnt++)
	{
		g_homeTrainingIcon[nCnt].bChoice = false;
		g_homeTrainingIcon[nCnt].bUse = false;
		g_homeTrainingIcon[nCnt].pD3DVtxBuff = NULL;
		g_homeTrainingIcon[nCnt].vPos = D3DXVECTOR3(HOME_TRAINING_ICON_IN_POS,HOME_TRAINING_ICON_POS_Y+((HOME_TRAINING_ICON_SIZE_Y+HOME_TRAINING_ICON_INTERVAL_HEIGHT)*nCnt),0.0f);
	}
	// �g���A�C�R�����_���̍쐬
	if(FAILED(MakeVertexUIHomeTrainingIcon(pDevice)))
	{
		return E_FAIL;
	}
	return S_OK;
}
/*******************************************************************************
�֐���:	void UninitUIHomeTrainingIcon(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�z�[�����j���[�̏I������
*******************************************************************************/
void UninitUIHomeTrainingIcon(void)
{
	// ���_�̏I������
	for(int nCnt=0;nCnt<HOME_TRAINING_ICON_NUM;nCnt++)
	{
		if(g_homeTrainingIcon[nCnt].pD3DVtxBuff != NULL)
		{	//�o�b�t�@�[�̉��
			g_homeTrainingIcon[nCnt].pD3DVtxBuff -> Release();
			g_homeTrainingIcon[nCnt].pD3DVtxBuff = NULL;
		}
	}
}
/*******************************************************************************
�֐���:	HRESULT MakeVertexUIHomeTrainingIcon(LPDIRECT3DDEVICE9 pDevice)
����:	LPDIRECT3DDEVICE9�^ pDevice
�߂�l:	�Ȃ�
����:	Game�ł̃g���[�j���O�A�C�R���摜���_�쐬
*******************************************************************************/
HRESULT MakeVertexUIHomeTrainingIcon(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@���쐬
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

	{// ���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		for(int nCnt=0;nCnt<HOME_TRAINING_ICON_NUM;nCnt++)
		{
			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			g_homeTrainingIcon[nCnt].pD3DVtxBuff -> Lock(0,0,(void**)&pVtx,0);

			//���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(g_homeTrainingIcon[nCnt].vPos.x - HOME_TRAINING_ICON_SIZE_X/2,g_homeTrainingIcon[nCnt].vPos.y - HOME_TRAINING_ICON_SIZE_Y/2 + (HOME_TRAINING_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
			pVtx[1].vtx = D3DXVECTOR3(g_homeTrainingIcon[nCnt].vPos.x + HOME_TRAINING_ICON_SIZE_X/2,g_homeTrainingIcon[nCnt].vPos.y - HOME_TRAINING_ICON_SIZE_Y/2 + (HOME_TRAINING_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
			pVtx[2].vtx = D3DXVECTOR3(g_homeTrainingIcon[nCnt].vPos.x - HOME_TRAINING_ICON_SIZE_X/2,g_homeTrainingIcon[nCnt].vPos.y + HOME_TRAINING_ICON_SIZE_Y/2 + (HOME_TRAINING_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
			pVtx[3].vtx = D3DXVECTOR3(g_homeTrainingIcon[nCnt].vPos.x + HOME_TRAINING_ICON_SIZE_X/2,g_homeTrainingIcon[nCnt].vPos.y + HOME_TRAINING_ICON_SIZE_Y/2 + (HOME_TRAINING_ICON_INTERVAL_HEIGHT)*nCnt,0.0f);
	
			// rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
	
			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
			pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
			pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
			pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);
	
			// �e�N�X�`�����W�w��
			pVtx[0].tex = D3DXVECTOR2(0.0f,(1.0f/HOME_TRAINING_ICON_NUM)*nCnt);
			pVtx[1].tex = D3DXVECTOR2(1.0f,(1.0f/HOME_TRAINING_ICON_NUM)*nCnt);
			pVtx[2].tex = D3DXVECTOR2(0.0f,(1.0f/HOME_TRAINING_ICON_NUM)*(nCnt+1));
			pVtx[3].tex = D3DXVECTOR2(1.0f,(1.0f/HOME_TRAINING_ICON_NUM)*(nCnt+1));

			// ���_�f�[�^���A�����b�N����
			g_homeTrainingIcon[nCnt].pD3DVtxBuff -> Unlock();
		}
	}
	return S_OK;
}
/*******************************************************************************
�֐���:	void DrawGameUIHomeTrainingIcon(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	Game�ł̃��j���[�A�C�R���摜�\��
*******************************************************************************/
void DrawGameUIHomeTrainingIcon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 *pTex = GetUITexture();

	for(int nCnt=0;nCnt<HOME_TRAINING_ICON_NUM;nCnt++)
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice -> SetStreamSource(0,g_homeTrainingIcon[nCnt].pD3DVtxBuff,0,sizeof(VERTEX_2D));
		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice -> SetFVF(FVF_VERTEX_2D);
		//�e�N�X�`���̐ݒ�
		pDevice -> SetTexture(0,pTex[UI_MOHE_TRAINING_TEXTURE]);
		//�|���S���`��
		pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,0,NUM_POLYGON);
	}

}
/*******************************************************************************
�֐���:	void UpdateUIHomeTrainingIcon(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	Game�ł̃��j���[�A�C�R���摜�X�V
*******************************************************************************/
void UpdateUIHomeTrainingIcon(void)
{
	// �}�E�X�̏����󂯎��
	POINT gameUIMouseClientPos = GetMouseClientPos();

	// �e�A�C�R���̃N���b�N����
	if(GetMouseLeftTrigger())		// �E�g���K�[����������
	{
		// �ǂ̃A�C�R���N���b�N����������
		for(int nCnt=0;nCnt<HOME_MENW_ICON_NUM;nCnt++)
		{
			if( g_homeTrainingIcon[nCnt].vPos.y - HOME_TRAINING_ICON_SIZE_Y/2.0f < gameUIMouseClientPos.y &&
				g_homeTrainingIcon[nCnt].vPos.y + HOME_TRAINING_ICON_SIZE_Y/2.0f > gameUIMouseClientPos.y &&
				g_homeTrainingIcon[nCnt].vPos.x - HOME_TRAINING_ICON_SIZE_X/2.0f < gameUIMouseClientPos.x &&
				g_homeTrainingIcon[nCnt].vPos.x + HOME_TRAINING_ICON_SIZE_X/2.0f > gameUIMouseClientPos.x)
			{
				// �N���b�N���ꂽ�A�C�R����I����
				g_homeTrainingIcon[nCnt].bChoice = true;
				break;
			}
			// �A�C�R���O���N���b�N�Ńz�[�����j���[�ɖ߂�
			else
			{
				SetGameMode(GAME_MODE_HOME);
				InitUIHomeTrainingIcon();
			}
		}
	}
	// �I�΂ꂽ�A�C�R���ɂ�鏈��
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

	// �E�N���b�N�L�����Z��
	if(GetMouseRightTrigger())
	{
		SetGameMode(GAME_MODE_HOME);
		InitUIHomeTrainingIcon();
	}

}
/*******************************************************************************
�֐���:	void SetTextureUIHomeTrainingIcon(int nCnt)
����:	int nCnt:�ǂ̃��j���[�A�C�R���𓮂�����
�߂�l:	
����:	���j���[�A�C�R���̈ʒu�ύX
*******************************************************************************/
void SetTextureUIHomeTrainingIcon(int nCnt)
{
}

/*******************************************************************************
�֐���:	HRESULT InitUIHomeAdvice(void)
����:	�Ȃ�
�߂�l:	����I��: int�^�� 0
����:	�g���[�j���O�̏�����
*******************************************************************************/
HRESULT InitUIHomeAdvice(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// �e�p�����[�^�̏�����
	g_homeAdvice.bChoice = false;
	g_homeAdvice.bUse = false;
	g_homeAdvice.pD3DVtxBuff = NULL;
	g_homeAdvice.vPos = D3DXVECTOR3(HOME_ADVICE_POS_X,HOME_ADVICE_POS_Y,0.0f);

	// �A�h�o�C�X���_���̍쐬
	if(FAILED(MakeVertexUIHomeAdvice(pDevice)))
	{
		return E_FAIL;
	}

	return S_OK;
}
/*******************************************************************************
�֐���:	void UninitUIHomeAdvice(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�z�[�����j���[�̏I������
*******************************************************************************/
void UninitUIHomeAdvice(void)
{
	// ���_�̏I������
	if(g_homeAdvice.pD3DVtxBuff != NULL)
	{	//�o�b�t�@�[�̉��
		g_homeAdvice.pD3DVtxBuff -> Release();
		g_homeAdvice.pD3DVtxBuff = NULL;
	}
}
/*******************************************************************************
�֐���:	HRESULT MakeVertexUIHomeAdvice(LPDIRECT3DDEVICE9 pDevice)
����:	LPDIRECT3DDEVICE9�^ pDevice
�߂�l:	�Ȃ�
����:	Game�ł̃��j���[�A�C�R���摜���_�쐬
*******************************************************************************/
HRESULT MakeVertexUIHomeAdvice(LPDIRECT3DDEVICE9 pDevice) 
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@���쐬
	if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_2D,
											D3DPOOL_MANAGED,
											&g_homeAdvice.pD3DVtxBuff,
											NULL)))
	{
		return E_FAIL;
	}

	{// ���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_homeAdvice.pD3DVtxBuff -> Lock(0,0,(void**)&pVtx,0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(g_homeAdvice.vPos.x - HOME_ADVICE_SIZE_X/2.0f,g_homeAdvice.vPos.y - HOME_ADVICE_SIZE_Y/2.0f,0.0f);
		pVtx[1].vtx = D3DXVECTOR3(g_homeAdvice.vPos.x + HOME_ADVICE_SIZE_X/2.0f,g_homeAdvice.vPos.y - HOME_ADVICE_SIZE_Y/2.0f,0.0f);
		pVtx[2].vtx = D3DXVECTOR3(g_homeAdvice.vPos.x - HOME_ADVICE_SIZE_X/2.0f,g_homeAdvice.vPos.y + HOME_ADVICE_SIZE_Y/2.0f,0.0f);
		pVtx[3].vtx = D3DXVECTOR3(g_homeAdvice.vPos.x + HOME_ADVICE_SIZE_X/2.0f,g_homeAdvice.vPos.y + HOME_ADVICE_SIZE_Y/2.0f,0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
		pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
		pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
		pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

		// �e�N�X�`�����W�w��
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f,(1.0f/ADVICE_TYPE_MAX));
		pVtx[3].tex = D3DXVECTOR2(1.0f,(1.0f/ADVICE_TYPE_MAX));

		// ���_�f�[�^���A�����b�N����
		g_homeAdvice.pD3DVtxBuff -> Unlock();
	}
	return S_OK;
}
/*******************************************************************************
�֐���:	void DrawGameUIHomeAdvice(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	Game�ł̃A�h�o�C�X�摜�\��
*******************************************************************************/
void DrawGameUIHomeAdvice(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 *pTex = GetUITexture();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice -> SetStreamSource(0,g_homeAdvice.pD3DVtxBuff,0,sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture(0,pTex[UI_MOHE_ADVICE_TEXTURE]);
	//�|���S���`��
	pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,0,NUM_POLYGON);
}
/*******************************************************************************
�֐���:	void UpdateUIHomeAdvice(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	Game�ł̃A�h�o�C�X�摜�X�V
*******************************************************************************/
void UpdateUIHomeAdvice(void)
{
}
/*******************************************************************************
�֐���:	void SetTextureUIHomeAdvice(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�A�h�o�C�X�摜�̑I��
*******************************************************************************/
void SetTextureUIHomeAdvice(void)
{
	// �N���Q�����擾
	JELLY_FISH *gameJellyfish = GetJellyfishStatus();

	// ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;
	{
		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_homeAdvice.pD3DVtxBuff -> Lock(0,0,(void**)&pVtx,0);

		// �N���Q�̏�Ԃɂ���ăA�h�o�C�X��I������/*�I���̎d���v����(�����_��������������)*/
		if(gameJellyfish->nFoodFull > 10)
		{
			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.f,ADIVCE_FINE/ADVICE_TYPE_MAX);
			pVtx[1].tex = D3DXVECTOR2(1.f,ADIVCE_FINE/ADVICE_TYPE_MAX);
			pVtx[2].tex = D3DXVECTOR2(0.f,(ADIVCE_FINE+1/ADVICE_TYPE_MAX));
			pVtx[3].tex = D3DXVECTOR2(1.f,(ADIVCE_FINE+1/ADVICE_TYPE_MAX));
		}

		// ���_�f�[�^���A�����b�N����
		g_homeAdvice.pD3DVtxBuff -> Unlock();
	}
}
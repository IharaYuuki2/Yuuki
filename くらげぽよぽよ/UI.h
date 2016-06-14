/*******************************************************************************
* �^�C�g��:		UI����
* �v���O������:	UI.h
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2016/02/01
********************************************************************************
* �X�V����:		- 2016/02/25	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _UI_H_
#define _UI_H_

#include "Main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

/*******************************************************************************
* �񋓑̒�`
*******************************************************************************/
// �A�h�o�C�X�̎��
typedef enum
{
	ADIVCE_FINE = 0,
	ADVICE_DYING,
	ADVICE_TIRED,
	ADVICE_TYPE_MAX
} ADVICE_TYPE;

/*****************************************************************************
* �\����
*****************************************************************************/
// �e�N�X�`���̏��
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9	pD3DVtxBuff;	//���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	D3DXVECTOR3 vPos;						
	D3DXVECTOR3 vScl;
	D3DXCOLOR	col;
	int			nCnt;
	bool		bUse;
	bool		bChoice;
	D3DXVECTOR2 vTexPatSize;					//�e�N�X�`���̂ǂ̕������|���S���ɓ\�邩���߂�ϐ�
}UI_2D;

// �e�N�X�`��3D�ł�UI
typedef struct
{
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9	pD3DVtxBuff;	//���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vRot;
	D3DXVECTOR3 vScl;
	D3DXCOLOR	col;
	int			nCnt;
	bool		bUse;
	bool		bChoice;
	D3DXVECTOR2 vTexPatSize;				
	D3DXVECTOR3 vVtxPos[4];					//�r���{�[�h�����蔻��p�̒��_���W
}UI_3D;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);

#endif

/*******************************************************************************
* �^�C�g��:		3D��ԓ��̃I�u�W�F�N�g�E�|���S���̏���
* �v���O������:	Object.cpp
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2016/01/24
********************************************************************************
* �X�V����:		- 2016/01/24	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "Object.h"
#include "XFile.h"
#include "DebugProc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define KURAGEMOVE					(0.50f)			// ���炰�̈ړ����x
#define KURAGEROTATE				(0.20f)			// ���炰�̉�]���x
#define KURAGESIZEX					(1.0f)			// ���炰�̃T�C�Y(X����)
#define KURAGESIZEY					(1.0f)			// ���炰�̃T�C�Y(Y����)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitJellyfish(void);
void UninitJellyfish(void);
void UpdateJellyfish(void);
void DrawJellyfish(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
JELLY_FISH g_Jellyfish;

/*******************************************************************************
�֐���:	void InitObject(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�I�u�W�F�N�g�̏���������
*******************************************************************************/
void InitObject(void)
{
	InitJellyfish();
}
/*******************************************************************************
�֐���:	void UpdateObject(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�I�u�W�F�N�g�̍X�V����
*******************************************************************************/
void UpdateObject(void)
{
	UpdateJellyfish();
}
/*******************************************************************************
�֐���:	void DrawObject(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�I�u�W�F�N�g�̕`��
*******************************************************************************/
void DrawObject(void)
{
	DrawJellyfish();
}

/*******************************************************************************
�֐���:	void InitJellyfish(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�N���Q���f���̏���������
*******************************************************************************/
void InitJellyfish(void)
{
	// �ʒu��ݒ�
	g_Jellyfish.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	// ������ݒ�
	g_Jellyfish.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �X�P�[����ݒ�
	g_Jellyfish.scl = D3DXVECTOR3(20.0f,20.0f,20.0f);
	// �g�p���ɕύX
	g_Jellyfish.bUse = true;
	// �p�����[�^�̏�����(�e�p�����[�^��MAX�l��100)
	g_Jellyfish.nIntelligence = 5;		// �m��/*�e�p�����[�^�lMAX��100*/
	g_Jellyfish.nMobility = 5;			// �̗�
	g_Jellyfish.nSensibility = 5;		// ����
	g_Jellyfish.nJustice = 5;			// ���`��
	g_Jellyfish.nFoodFull = 50;			// ����
	g_Jellyfish.nMotivation = 50;		// ���C


}
/*******************************************************************************
�֐���:	void UninitJellyfish(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�N���Q���f���̏I������
*******************************************************************************/
void UninitJellyfish(void)
{
	
}
/*******************************************************************************
�֐���:	void UpdateJellyfish(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�N���Q���f���̍X�V����
*******************************************************************************/
void UpdateJellyfish(void)
{
	PrintDebugProc("[�N���QX���W : (%d)]\n",g_Jellyfish.pos.x);
	PrintDebugProc("[�N���QY���W : (%d)]\n\n",g_Jellyfish.pos.y);

}
/*******************************************************************************
�֐���:	void DrawJellyfish(void)
����:	�Ȃ�
�߂�l:	�Ȃ�
����:	�N���Q���f���̕`�揈��
*******************************************************************************/
void DrawJellyfish(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	XFILE *pJellyfishXFile = GetpJellyfishXFile();
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Jellyfish.mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl,g_Jellyfish.scl.x,g_Jellyfish.scl.y,g_Jellyfish.scl.z);
	D3DXMatrixMultiply(&g_Jellyfish.mtxWorld,&g_Jellyfish.mtxWorld,&mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_Jellyfish.rot.y,g_Jellyfish.rot.x,g_Jellyfish.rot.z);
	D3DXMatrixMultiply(&g_Jellyfish.mtxWorld,&g_Jellyfish.mtxWorld,&mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate,g_Jellyfish.pos.x,g_Jellyfish.pos.y,g_Jellyfish.pos.z);
	D3DXMatrixMultiply(&g_Jellyfish.mtxWorld,&g_Jellyfish.mtxWorld,&mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice -> SetTransform(D3DTS_WORLD,&g_Jellyfish.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice -> GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL * )pJellyfishXFile[XFILE_TEST_FILE].pD3DXBuffMate -> GetBufferPointer();

	// �}�e���A���̐ݒ�
	pDevice -> SetMaterial(&pD3DXMat[XFILE_TEST_FILE].MatD3D);

	// �e�N�X�`���̐ݒ�
	pDevice -> SetTexture(0,pJellyfishXFile[XFILE_TEST_FILE].pD3DTexture);

	// �`��
	pJellyfishXFile[XFILE_TEST_FILE].pD3DXMesh -> DrawSubset(0);

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice -> SetMaterial(&matDef);
}
/*******************************************************************************
�֐���:	void ChangeJellyfishStatus(JELLYFISH_STATUS_TYPE statusType, int valu)
����:	JELLYFISH_STATUS_TYPE statusType:	�ύX�������X�e�[�^�X�I��,
		int valu:							�ύX���������l
�߂�l:	�Ȃ�
����:	�N���Q�̃X�e�[�^�X�ύX
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
�֐���:	JELLY_FISH *GetJellyfishStatus(void)
����:	�Ȃ�
�߂�l:	�N���Q�̃X�e�[�^�X
����:	�N���Q�̍\���̂̃A�h���X
*******************************************************************************/
JELLY_FISH *GetJellyfishStatus(void)
{
	return &g_Jellyfish;
}
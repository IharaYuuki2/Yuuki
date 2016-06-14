/*******************************************************************************
* �^�C�g��:		3D��ԓ��̃I�u�W�F�N�g�E�|���S���̏���
* �v���O������:	Object.h
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2016/01/24
********************************************************************************
* �X�V����:		- 2016/01/24	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �񋓑�
//*****************************************************************************
// �N���Q�̃X�e�[�^�X�^�C�v
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
// �\����
//*****************************************************************************
// �N���Q�p�̍\����
typedef class
{
	public:
		D3DXMATRIX	mtxWorld;		// ���[���h�}�g���b�N�X
		D3DXVECTOR3 pos;			// ���[���h��ԓ��ɂ����郍�[�J�����W�̌��_�̍��W
		D3DXVECTOR3 rot;			// ��]�p
		D3DXVECTOR3 scl;			// �傫��(�X�P�[��)
		float		radius;			// ���a
		bool		bUse;			// �g�p�����ǂ���
		int			nIntelligence;	// �m��/*�e�p�����[�^�lMAX��100*/
		int			nMobility;		// �̗�
		int			nSensibility;	// ����
		int			nJustice;		// ���`��
		int			nFoodFull;		// ����
		int			nMotivation;	// ���C
		int			nEmpty[5];		// ����ǉ��̃X�e�[�^�X
} JELLY_FISH;

// �I�u�W�F�N�g�p�̍\����
typedef struct
{
	D3DXMATRIX	mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// ���[���h��ԓ��ɂ����郍�[�J�����W�̌��_�̍��W
	D3DXVECTOR3 rot;		// ��]�p
	D3DXVECTOR3 scl;		// �傫��(�X�P�[��)
	float		radius;		// ���a
	bool		bUse;		// �g�p�����ǂ���
} OBJECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitObject(void);
void UpdateObject(void);
void DrawObject(void);
JELLY_FISH *GetJellyfishStatus(void);
void ChangeJellyfishStatus(JELLYFISH_STATUS_TYPE statusType, int valu);

#endif

/*******************************************************************************
* �^�C�g��:		Game�w�b�_�[�t�@�C��
* �v���O������:	Game.h
* �쐬��:		GP11A331 4 �Ɍ��C�H
* �쐬��:		2016/02/23
********************************************************************************
* �X�V����:		- 2016/02/23	GP11A331 4 �Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
#ifndef _GAME_H_
#define _GAME_H_

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "Main.h"

/*******************************************************************************
* �\���̒�`
*******************************************************************************/

/*******************************************************************************
* �񋓑̒�`
*******************************************************************************/
// �Q�[�����[�h
typedef enum
{
	GAME_MODE_HOME = 0,
	GAME_MODE_TRAINING,	// �g���[�j���O
	GAME_MODE_REST,		// �x�e
	GAME_MODE_CONTACT,	// �G�ꍇ��
	GAME_MODE_FOOD,		// �G�T����
	GAME_MODE_CAMERA,	// �J�����؂�ւ�
	GAME_MODE_HISTORY,	// �N���Q�}��
	GAME_MODE_OPTION,	// �I�v�V�����؂�ւ�
	GAME_MODE_MAX
} GAME_MODE;
// �g���[�j���O���[�h
typedef enum
{
	TRAINING_MODE_INTELLIGENCE = 0,		// �m���g���[�j���O
	TRAINING_MODE_MOBILITY,				// �̗̓g���[�j���O
	TRAINING_MODE_SENSIBILLITY,			// �����g���[�j���O
	TRAINING_MODE_JUSTICE,				// ���`���g���[�j���O
	TRAINING_MODE_MAX
} TRAINING_MODE;
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameMode(int mode);
GAME_MODE GetGameMode(void);
void SetTraningMode(int mode);
TRAINING_MODE GetTraningMode(void);

#endif
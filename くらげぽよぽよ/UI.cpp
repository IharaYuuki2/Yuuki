/*******************************************************************************
* �^�C�g��:		UI����
* �v���O������:	UI.cpp
* �쐬��:		GP11A331 4�� �Ɍ��C�H
* �쐬��:		2016/02/01
********************************************************************************
* �X�V����:		- 2016/02/25	�Ɍ��C�H
*					- V1.00		Initial Version
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "UI.h"
#include "Texture.h"
#include "Camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	SIZE_X		(25.0f)							// �r���{�[�h�̕�
#define SIZE_Y		(25.0f)							// �r���{�[�h�̍���
/*******************************************************************************
* �\���̒�`
*******************************************************************************/
typedef struct
{
	LPDIRECT3DTEXTURE9		pD3DTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
																
	D3DXMATRIX				mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3             pos;					// �ʒu
	D3DXVECTOR3				truePos[4];
	D3DXVECTOR3             scl; 						// �X�P�[��
	int						alphatest;
	int						mode;
	bool					bUse;

}STATUSUPTEXTURE;
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
STATUSUPTEXTURE g_statusUpTexture;
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
HRESULT MakeVertexStatusUpTexture(LPDIRECT3DDEVICE9 pDevice);
void SetVertexStatusUpTexture(float fSizeX, float fSizeY);
void InitStatusUpTexture(void);
void UpdateStatusUpTexture(void);
void UninitStatusUpTexture(void);
void DrawStatusUpTexture(void);


void InitUI()
{
	InitStatusUpTexture();
}
void UpdateUI()
{
	UpdateStatusUpTexture();

	//POINT mouseClientPos = GetMouseClientPos();

	//if(image.pos.x - image.size.x / 2 < mouseClientPos.x &&
	//	image.pos.x + image.size.x / 2 > mos\useCLientPos.x&&&&&&&)
	//{
	//	if(GetMousePressRight())
	//	{
	//		if(bPressed)
	//		{

	//		}
	//		
	//	}
	//}
}
void UninitUI()
{
	UninitStatusUpTexture();
}

void DrawUI()
{
	DrawStatusUpTexture();
}


//--------------------------------------------------------------------
void InitStatusUpTexture(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ʒu�̏�����(D3DXVECTOR3���g�p)
	 g_statusUpTexture.pos = D3DXVECTOR3(200.0f,20.0f,200.0f);

	
	// �X�P�[���̏�����(D3DXVECTOR3���g�p)
	 g_statusUpTexture.scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//
	 g_statusUpTexture.bUse = false;
	 g_statusUpTexture.mode = STATUS_UP_NONE;

	// ���_���̍쐬
	MakeVertexStatusUpTexture(pDevice);

	

}

void UninitStatusUpTexture(void)
{


	//if(g_pD3DVtxBuffBillboard != NULL)
	//{// ���_�o�b�t�@�̊J��
	//	g_pD3DVtxBuffBillboard->Release();
	//	g_pD3DVtxBuffBillboard = NULL;
	//}
}

void UpdateStatusUpTexture(void)
{

}

void DrawStatusUpTexture(void)
{
	LPDIRECT3DTEXTURE9 *pUITexture  = GetUITexture();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;
	CAMERA *pCamera;
	

	// �J�����̎擾
	pCamera = GetCamera();
	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);

	//VERTEX_3D  *pVtx;

	//// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	//g_statusUpTexture.pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(& g_statusUpTexture.mtxWorld);
	// �|���S���𐳖ʂɌ�����(�t�s������߂�)
	 g_statusUpTexture.mtxWorld._11 = pCamera->mtxView._11;
	 g_statusUpTexture.mtxWorld._22 = pCamera->mtxView._22;
	 g_statusUpTexture.mtxWorld._33 = pCamera->mtxView._33;

	 g_statusUpTexture.mtxWorld._32 = pCamera->mtxView._23;
	 g_statusUpTexture.mtxWorld._23 = pCamera->mtxView._32;
	 g_statusUpTexture.mtxWorld._31 = pCamera->mtxView._13;

	 g_statusUpTexture.mtxWorld._13 = pCamera->mtxView._31;
	 g_statusUpTexture.mtxWorld._12 = pCamera->mtxView._21;
	 g_statusUpTexture.mtxWorld._21 = pCamera->mtxView._12;
	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScale, g_statusUpTexture.scl.x, g_statusUpTexture.scl.y,  g_statusUpTexture.scl.z);
	
	D3DXMatrixMultiply(&g_statusUpTexture.mtxWorld,&g_statusUpTexture.mtxWorld,&mtxScale);
	
	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate,g_statusUpTexture.pos.x,g_statusUpTexture.pos.y,g_statusUpTexture.pos.z);

	D3DXMatrixMultiply(&g_statusUpTexture.mtxWorld,&g_statusUpTexture.mtxWorld,&mtxTranslate);

	//// ���_���W�̌v�Z

	//D3DXVec3TransformCoord(&g_statusUpTexture.truePos[0],&pVtx[0].vtx,&g_statusUpTexture.mtxWorld);
	//D3DXVec3TransformCoord(&g_statusUpTexture.truePos[1],&pVtx[1].vtx,&g_statusUpTexture.mtxWorld);
	//D3DXVec3TransformCoord(&g_statusUpTexture.truePos[2],&pVtx[2].vtx,&g_statusUpTexture.mtxWorld);
	//D3DXVec3TransformCoord(&g_statusUpTexture.truePos[3],&pVtx[3].vtx,&g_statusUpTexture.mtxWorld);

	//// ���_�f�[�^���A�����b�N����
	//g_statusUpTexture.pD3DVtxBuff->Unlock();


	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice -> SetTransform(D3DTS_WORLD,&g_statusUpTexture.mtxWorld);
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0,g_statusUpTexture.pD3DVtxBuff,0,sizeof(VERTEX_3D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	// �e�N�X�`���̐ݒ�

	switch(g_statusUpTexture.mode)
	{
		case STATUS_INTELLIGENCE_UP :
			pDevice->SetTexture(0,pUITexture[UI_INTELLIGENCEUP]);
			break;
		case STATUS_MOBILITY_UP:
			pDevice->SetTexture(0,pUITexture[UI_MOTILITYUP]);
			break;
		case STATUS_JUSTICE_UP:
			pDevice->SetTexture(0,pUITexture[UI_JUSTICEUP]);
			break;
		case STATUS_SENSIBILITY_UP:
			pDevice->SetTexture(0,pUITexture[UI_SENSIBILITYUP]);
			break;
	}
	// �A���t�@ �e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);

	pDevice->SetRenderState(D3DRS_ALPHAREF,g_statusUpTexture.alphatest);

	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);


	// �|���S���̕`��
	if(g_statusUpTexture.bUse == true)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,NUM_VERTEX);
	}
		//
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
	// ���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);


}


//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexStatusUpTexture(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&g_statusUpTexture.pD3DVtxBuff,
											NULL)))
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D  *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_statusUpTexture.pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-SIZE_X / 2.0f,+SIZE_Y / 2.0f,0.0f);
			pVtx[1].vtx = D3DXVECTOR3(+SIZE_X / 2.0f,+SIZE_Y / 2.0f,0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-SIZE_X / 2.0f,-SIZE_Y / 2.0f,0.0f);
			pVtx[3].vtx = D3DXVECTOR3(+SIZE_X / 2.0f,-SIZE_Y / 2.0f,0.0f);
			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

		// ���_�f�[�^���A�����b�N����
		g_statusUpTexture.pD3DVtxBuff->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexStatusUpTexture(float fSizeX, float fSizeY)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_statusUpTexture.pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-SIZE_X / 2.0f,+SIZE_Y / 2.0f,0.0f);
		pVtx[1].vtx = D3DXVECTOR3(+SIZE_X / 2.0f,+SIZE_Y / 2.0f,0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-SIZE_X / 2.0f,-SIZE_Y / 2.0f,0.0f);
		pVtx[3].vtx = D3DXVECTOR3(+SIZE_X / 2.0f,-SIZE_Y / 2.0f,0.0f);
		
		// ���_�f�[�^���A�����b�N����
		g_statusUpTexture.pD3DVtxBuff->Unlock();
	}
}

void SetStatusUpTexture(D3DXVECTOR3 pos,STATUSUPMODE statusMode)
{
	g_statusUpTexture.bUse = true;
	g_statusUpTexture.pos = pos;
	g_statusUpTexture.pos.y += 30.0f;
	g_statusUpTexture.mode = statusMode;
}

//=============================================================================
//
// �J�������� [camera.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "inputx.h"	//XINPUT�p
#include "camera.h"
#include "keyboard.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//�J�����s��̃p�����[�^�[
#define	POS_X_CAM		(0.0f)		// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM		(4.0f)		// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM		(-6.0f)	// �J�����̏����ʒu(Z���W)
#define	AT_X_CAM		(0.0f)		//�@�����_	
#define	AT_Y_CAM		(2.0f)	
#define	AT_Z_CAM		(0.0f)	

//�v���W�F�N�V�����s��̃p�����[�^�[
#define	VIEW_ANGLE		(60.0f)											// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(1.0f)											// �߂�����������E����NearZ�l
#define	VIEW_FAR_Z		(10000.0f)										// �����̌�������E����FarZ�l


#define	VALUE_MOVE_CAMERA	(20.0f)										// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// �J�����̉�]��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static CAMERA			g_Camera;		// �J�����f�[�^

//=============================================================================
// ����������
//=============================================================================
void InitCamera(void)
{
	g_Camera.pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);//�J�����̍��W
	g_Camera.at = D3DXVECTOR3(AT_X_CAM, AT_Y_CAM, AT_Z_CAM);//�J�����̒����_
	g_Camera.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//�J�����̏�x�N�g��

	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�ƒ����_�̋������v�Z
	float vx, vz;
	vx = g_Camera.pos.x - g_Camera.at.x;
	vz = g_Camera.pos.z - g_Camera.at.z;
	g_Camera.len = sqrtf(vx * vx + vz * vz);

	g_Camera.fov = VIEW_ANGLE;	//����p�̏�����


}


//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{

}


//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{

	if (Keyboard_IsKeyDown(KK_Z))
	{// ���_����u���v
		g_Camera.rot.y += VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y -= D3DX_PI * 2.0f;
		}

		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_C))
	{// ���_����u�E�v
		g_Camera.rot.y -= VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y < -D3DX_PI)
		{
			g_Camera.rot.y += D3DX_PI * 2.0f;
		}

		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_Y))
	{// ���_�ړ��u��v
		g_Camera.pos.y += VALUE_MOVE_CAMERA;
	}

	if (Keyboard_IsKeyDown(KK_N))
	{// ���_�ړ��u���v
		g_Camera.pos.y -= VALUE_MOVE_CAMERA;
	}

	if (Keyboard_IsKeyDown(KK_Q))
	{// �����_����u���v
		g_Camera.rot.y -= VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y < -D3DX_PI)
		{
			g_Camera.rot.y += D3DX_PI * 2.0f;
		}

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_E))
	{// �����_����u�E�v
		g_Camera.rot.y += VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y -= D3DX_PI * 2.0f;
		}

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_T))
	{// �����_�ړ��u��v
		g_Camera.at.y += VALUE_MOVE_CAMERA;
	}

	if (Keyboard_IsKeyDown(KK_B))
	{// �����_�ړ��u���v
		g_Camera.at.y -= VALUE_MOVE_CAMERA;
	}

	if (Keyboard_IsKeyDown(KK_U))
	{// �߂Â�
		g_Camera.len -= VALUE_MOVE_CAMERA;
		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_M))
	{// �����
		g_Camera.len += VALUE_MOVE_CAMERA;
		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	// �J�����������ɖ߂�
	if (Keyboard_IsKeyDown(KK_P))
	{
		UninitCamera();
		InitCamera();
	}

	////����p��ύX����
	//if (Keyboard_IsKeyDown(KK_A))
	//{// �p�x��傫�����遁�������\��
	//	g_Camera.fov += 1.0f;
	//}
	//else if (Keyboard_IsKeyDown(KK_S))
	//{// �p�x�����������遁�傫���\��
	//	g_Camera.fov += -1.0f;
	//}




}


//=============================================================================
// �J�����̍X�V
//=============================================================================
void SetCamera(void) 
{
	// �r���[�}�g���b�N�X�ݒ�
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.pos, &g_Camera.at, &g_Camera.up);
	//DirectX�փJ�����s����Z�b�g
	SetViewMatrix(&g_Camera.mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�ݒ�
//	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, 1.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, VIEW_FAR_Z);
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, D3DXToRadian(g_Camera.fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, VIEW_FAR_Z);
	//DiectX�փv���W�F�N�V�����s����Z�b�g
	SetProjectionMatrix(&g_Camera.mtxProjection);


	//�J�����s��̋t�s����쐬
	float det;
	D3DXMatrixInverse(&g_Camera.mtxInvView, &det, &g_Camera.mtxView);


}


//=============================================================================
// �J�����̎擾
//=============================================================================
CAMERA *GetCamera(void) 
{
	return &g_Camera;
}


// �J�����̎��_�ƒ����_���Z�b�g
void SetCameraAT(D3DXVECTOR3 pos)
{
	// �J�����̒����_���v���C���[�̍��W�ɂ��Ă݂�
	g_Camera.at = pos;

	// �J�����̎��_���J������Y����]�ɑΉ������Ă���
	g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
	g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
}


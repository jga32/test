//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "inputx.h"	//XINPUT用
#include "camera.h"
#include "keyboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//カメラ行列のパラメーター
#define	POS_X_CAM		(0.0f)		// カメラの初期位置(X座標)
#define	POS_Y_CAM		(4.0f)		// カメラの初期位置(Y座標)
#define	POS_Z_CAM		(-6.0f)	// カメラの初期位置(Z座標)
#define	AT_X_CAM		(0.0f)		//　注視点	
#define	AT_Y_CAM		(2.0f)	
#define	AT_Z_CAM		(0.0f)	

//プロジェクション行列のパラメーター
#define	VIEW_ANGLE		(60.0f)											// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(1.0f)											// 近くが見える限界距離NearZ値
#define	VIEW_FAR_Z		(10000.0f)										// 遠くの見える限界距離FarZ値


#define	VALUE_MOVE_CAMERA	(20.0f)										// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// カメラの回転量

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static CAMERA			g_Camera;		// カメラデータ

//=============================================================================
// 初期化処理
//=============================================================================
void InitCamera(void)
{
	g_Camera.pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);//カメラの座標
	g_Camera.at = D3DXVECTOR3(AT_X_CAM, AT_Y_CAM, AT_Z_CAM);//カメラの注視点
	g_Camera.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//カメラの上ベクトル

	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 視点と注視点の距離を計算
	float vx, vz;
	vx = g_Camera.pos.x - g_Camera.at.x;
	vz = g_Camera.pos.z - g_Camera.at.z;
	g_Camera.len = sqrtf(vx * vx + vz * vz);

	g_Camera.fov = VIEW_ANGLE;	//視野角の初期化


}


//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{

}


//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{

	if (Keyboard_IsKeyDown(KK_Z))
	{// 視点旋回「左」
		g_Camera.rot.y += VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y -= D3DX_PI * 2.0f;
		}

		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_C))
	{// 視点旋回「右」
		g_Camera.rot.y -= VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y < -D3DX_PI)
		{
			g_Camera.rot.y += D3DX_PI * 2.0f;
		}

		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_Y))
	{// 視点移動「上」
		g_Camera.pos.y += VALUE_MOVE_CAMERA;
	}

	if (Keyboard_IsKeyDown(KK_N))
	{// 視点移動「下」
		g_Camera.pos.y -= VALUE_MOVE_CAMERA;
	}

	if (Keyboard_IsKeyDown(KK_Q))
	{// 注視点旋回「左」
		g_Camera.rot.y -= VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y < -D3DX_PI)
		{
			g_Camera.rot.y += D3DX_PI * 2.0f;
		}

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_E))
	{// 注視点旋回「右」
		g_Camera.rot.y += VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y -= D3DX_PI * 2.0f;
		}

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_T))
	{// 注視点移動「上」
		g_Camera.at.y += VALUE_MOVE_CAMERA;
	}

	if (Keyboard_IsKeyDown(KK_B))
	{// 注視点移動「下」
		g_Camera.at.y -= VALUE_MOVE_CAMERA;
	}

	if (Keyboard_IsKeyDown(KK_U))
	{// 近づく
		g_Camera.len -= VALUE_MOVE_CAMERA;
		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_M))
	{// 離れる
		g_Camera.len += VALUE_MOVE_CAMERA;
		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	// カメラを初期に戻す
	if (Keyboard_IsKeyDown(KK_P))
	{
		UninitCamera();
		InitCamera();
	}

	////視野角を変更する
	//if (Keyboard_IsKeyDown(KK_A))
	//{// 角度を大きくする＝小さく表示
	//	g_Camera.fov += 1.0f;
	//}
	//else if (Keyboard_IsKeyDown(KK_S))
	//{// 角度を小さくする＝大きく表示
	//	g_Camera.fov += -1.0f;
	//}




}


//=============================================================================
// カメラの更新
//=============================================================================
void SetCamera(void) 
{
	// ビューマトリックス設定
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.pos, &g_Camera.at, &g_Camera.up);
	//DirectXへカメラ行列をセット
	SetViewMatrix(&g_Camera.mtxView);

	// プロジェクションマトリックス設定
//	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, 1.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, VIEW_FAR_Z);
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, D3DXToRadian(g_Camera.fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, VIEW_FAR_Z);
	//DiectXへプロジェクション行列をセット
	SetProjectionMatrix(&g_Camera.mtxProjection);


	//カメラ行列の逆行列を作成
	float det;
	D3DXMatrixInverse(&g_Camera.mtxInvView, &det, &g_Camera.mtxView);


}


//=============================================================================
// カメラの取得
//=============================================================================
CAMERA *GetCamera(void) 
{
	return &g_Camera;
}


// カメラの視点と注視点をセット
void SetCameraAT(D3DXVECTOR3 pos)
{
	// カメラの注視点をプレイヤーの座標にしてみる
	g_Camera.at = pos;

	// カメラの視点をカメラのY軸回転に対応させている
	g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
	g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
}


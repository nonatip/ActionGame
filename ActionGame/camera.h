#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

#include "DirectX11Manager.h"
#include "DX11MathUtil.h"
#include "Define.h"

class CScene;

using namespace DirectX;

class CCamera
{
private:
	CScene*			m_scene = nullptr;	// シーンへのポインタ
	int				m_mode;

	XMFLOAT4X4		m_projectionMatrix;		// プロジェクション行列
	XMFLOAT4X4		m_cameraMatrix;			// ビュー行列
	XMFLOAT3		m_eyePosition;			// カメラ座標
	XMFLOAT3		m_lookatPosition;		// 注視点座標
	XMFLOAT3		m_upVector;				// 上向きベクトル

	float			m_nearClip;				// ニアクリップ
	float			m_farClip;				// ファークリップ
	float			m_aspectRatio;			// アスペクト比
	float			m_fov;					// 視野

	float			m_look = 10.0f;			// 各モードの注視点調整用

	XMFLOAT3		m_pos = { 0,0,0 };		// FPSカメラ位置調整用

	float			m_distance = -10;		// TPSカメラの高さ調整用
	float			m_height = 10;			// TPSカメラの距離調整用

	float			m_sensitivity = 50;		// FREEカメラの感度調整用
	XMFLOAT2		m_beforeMouse;			// FREEカメラ用直前のマウス座標

	void CreateCameraMatrix() {
		XMVECTOR vectorEye = XMVectorSet(m_eyePosition.x, m_eyePosition.y, m_eyePosition.z, 0.0f);
		XMVECTOR vectorLookAt = XMVectorSet(m_lookatPosition.x, m_lookatPosition.y, m_lookatPosition.z, 0.0f);
		XMVECTOR vectorUp = XMVectorSet(m_upVector.x, m_upVector.y, m_upVector.z, 0.0f);
		XMMATRIX camera = XMMatrixLookAtLH(vectorEye, vectorLookAt, vectorUp);
		XMStoreFloat4x4(&m_cameraMatrix, camera);
	}
	void CreateProjectionMatrix() {
		XMMATRIX projection = XMMatrixPerspectiveFovLH(m_fov, m_aspectRatio, m_nearClip, m_farClip);
		XMStoreFloat4x4(&m_projectionMatrix, projection);
	}

	void UpdateDEFAULT();
	void UpdateFPS();
	void UpdateTPS();
	void UpdateFREE();
public:
	enum CameraMode {
		DEFAULT,
		FPS,
		TPS,
		FREE,
	};
	CCamera(CScene* scene) { m_scene = scene; Init(); }
	~CCamera() { Uninit(); }
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// アクセサ
	const XMFLOAT4X4& GetCameraMatrix() { return m_cameraMatrix; }
	const XMFLOAT4X4& GetProjectionMatrix() { return m_projectionMatrix; }
	const XMFLOAT3&	GetEye() { return m_eyePosition; }
	const XMFLOAT3& GetLookat() { return m_lookatPosition; }
	const XMFLOAT3& GetUp() { return m_upVector; }
	const int&		GetMode() { return m_mode; }
	void SetCameraMatrix(const XMFLOAT3& eye, const XMFLOAT3& lookat, const XMFLOAT3& up) {
		m_eyePosition = eye;
		m_lookatPosition = lookat;
		m_upVector = up;

		// カメラ行列を生成
		CreateCameraMatrix();
	}
	void SetProjectionMatrix(float nearClip, float farClip, float fov, float width, float height) {
		m_nearClip = nearClip;
		m_farClip = farClip;
		m_fov = fov;
		m_aspectRatio = width / height;
		// プロジェクション行列を生成
		CreateProjectionMatrix();
	}
};
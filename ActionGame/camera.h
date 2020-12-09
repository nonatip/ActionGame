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
	CScene*			m_scene = nullptr;	// �V�[���ւ̃|�C���^
	int				m_mode;

	XMFLOAT4X4		m_projectionMatrix;		// �v���W�F�N�V�����s��
	XMFLOAT4X4		m_cameraMatrix;			// �r���[�s��
	XMFLOAT3		m_eyePosition;			// �J�������W
	XMFLOAT3		m_lookatPosition;		// �����_���W
	XMFLOAT3		m_upVector;				// ������x�N�g��

	float			m_nearClip;				// �j�A�N���b�v
	float			m_farClip;				// �t�@�[�N���b�v
	float			m_aspectRatio;			// �A�X�y�N�g��
	float			m_fov;					// ����

	float			m_look = 10.0f;			// �e���[�h�̒����_�����p

	XMFLOAT3		m_pos = { 0,0,0 };		// FPS�J�����ʒu�����p

	float			m_distance = -10;		// TPS�J�����̍��������p
	float			m_height = 10;			// TPS�J�����̋��������p

	float			m_sensitivity = 50;		// FREE�J�����̊��x�����p
	XMFLOAT2		m_beforeMouse;			// FREE�J�����p���O�̃}�E�X���W

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

	// �A�N�Z�T
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

		// �J�����s��𐶐�
		CreateCameraMatrix();
	}
	void SetProjectionMatrix(float nearClip, float farClip, float fov, float width, float height) {
		m_nearClip = nearClip;
		m_farClip = farClip;
		m_fov = fov;
		m_aspectRatio = width / height;
		// �v���W�F�N�V�����s��𐶐�
		CreateProjectionMatrix();
	}
};
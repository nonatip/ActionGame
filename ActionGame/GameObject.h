#pragma once
#include "DirectX11Manager.h"
#include "dx11mathutil.h"
#include "UnityExportModel.h"
#include "UnityExportSkinnedModel.h"

#include <list>

class CScene;

class GameObject
{
protected:
	int			m_type = GameObject::Other;	// �I�u�W�F�N�g�^�C�v
	CScene*		m_scene = nullptr;	// �V�[���ւ̃|�C���^

	XMFLOAT4X4	m_world;		// ���[���h�ϊ��p�s��
	XMFLOAT3	m_pos;			// ���݈ʒu
	XMFLOAT3	m_beforePos;	// ���O���W
	XMFLOAT3	m_dir;			// �i�s����

	XMFLOAT3	vecX;		// x���x�N�g��
	XMFLOAT3	vecY;		// y���x�N�g��
	XMFLOAT3	vecZ;		// z���x�N�g��

	XMFLOAT3	m_trans;	// ���s�ړ��s��쐬�p
	XMFLOAT3	m_angle;	// ��]�s��쐬�p

	// ���f���͎�ނ���������̂Ŕh���N���X���e�X��������
	//UnityExportModel *model;
	//UnityExportSkinnedModel *skinnedModel;
	//std::list<uem::SkinnedAnimation*> animList;

	// �ړ���̏��X�V
	void UpdateInfo();
public:
	enum ObjectType {
		Player,
		Enemy,
		Other
	};

	GameObject() {};
	virtual ~GameObject() {};

	// ���������Ďg�p
	virtual void Update() {};
	virtual void Draw() {};

	// �A�N�Z�T
	const XMFLOAT4X4&	GetMtx()	{ return m_world; }
	const XMFLOAT3&		GetPos()	{ return m_pos; }
	const XMFLOAT3&		GetDir()	{ return m_dir; }
	const XMFLOAT3&		GetVecX()	{ return vecX; }
	const XMFLOAT3&		GetVecY()	{ return vecY; }
	const XMFLOAT3&		GetVecZ()	{ return vecZ; }
	const int&			GetType()	{ return m_type; }
};
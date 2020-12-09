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
	int			m_type = GameObject::Other;	// オブジェクトタイプ
	CScene*		m_scene = nullptr;	// シーンへのポインタ

	XMFLOAT4X4	m_world;	// ワールド変換用行列
	XMFLOAT3	m_pos;		// 現在位置
	XMFLOAT3	m_dir;		// 進行方向

	XMFLOAT3	vecX;		// x軸ベクトル
	XMFLOAT3	vecY;		// y軸ベクトル
	XMFLOAT3	vecZ;		// z軸ベクトル

	XMFLOAT3	m_trans;	// 平行移動行列作成用
	XMFLOAT3	m_angle;	// 回転行列作成用

	// モデルは種類が複数あるので派生クラスが各々所持する
	//UnityExportModel *model;
	//UnityExportSkinnedModel *skinnedModel;
	//std::list<uem::SkinnedAnimation*> animList;

	// 移動後の情報更新
	void UpdateInfo();
public:
	enum ObjectType {
		Player,
		Enemy,
		Other
	};

	GameObject() {};
	virtual ~GameObject() {};

	// 書き換えて使用
	virtual void Update() {};
	virtual void Draw() {};

	// アクセサ
	const XMFLOAT4X4&	GetMtx()	{ return m_world; }
	const XMFLOAT3&		GetPos()	{ return m_pos; }
	const XMFLOAT3&		GetDir()	{ return m_dir; }
	const XMFLOAT3&		GetVecX()	{ return vecX; }
	const XMFLOAT3&		GetVecY()	{ return vecY; }
	const XMFLOAT3&		GetVecZ()	{ return vecZ; }
	const int&			GetType()	{ return m_type; }
};
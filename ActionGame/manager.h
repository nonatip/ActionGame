#pragma once
#include "DirectX11Manager.h"

// �N���X�̃v���g�^�C�v�錾
class CManager;

// �V�[���̊��N���X
class CScene
{
protected:
	CManager* manager;
public:
	CScene(CManager* pManager) { manager = pManager; };
	virtual ~CScene() {};

	virtual void Update() {};
	virtual void Draw() {};
	virtual void Initialize() {};
	virtual void Finalize() {};
};

// �V�[���Ǘ��N���X
class CManager
{
public:
	// ���̃V�[���̃|�C���^
	CScene* scene;
	CManager() {};
	~CManager() { delete scene; };

	// �`��
	void Update() { scene->Update(); };
	// �X�V
	void Draw() { scene->Draw(); };
};
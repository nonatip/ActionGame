#pragma once

#include "manager.h"

// �^�C�g���S�̂̊Ǘ�
class CTitle :public CScene
{
	bool isChange = false;
	// �R���X�^���g�o�b�t�@
	ConstantBufferMatrix m_constantBuffer;
	ConstantBuffer m_cb;
	ID3D11Buffer* tmpCb[];
public:
	CTitle(CManager *pManager);
	~CTitle();
	void Update();
	void Draw();
};
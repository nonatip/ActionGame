#pragma once

#include "manager.h"

// タイトル全体の管理
class CTitle :public CScene
{
	bool isChange = false;
	// コンスタントバッファ
	ConstantBufferMatrix m_constantBuffer;
	ConstantBuffer m_cb;
	ID3D11Buffer* tmpCb[];
public:
	CTitle(CManager *pManager);
	~CTitle();
	void Update();
	void Draw();
};
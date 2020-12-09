#pragma once
#include "manager.h"

// GameObject
#include <list>
#include "GameObject.h"
#include "CPlayer.h"

#include "camera.h"

class CGame :public CScene
{
public:
	CGame(CManager *pManager);
	~CGame();
	void Update();
	void Draw();
	void Initialize();
	void Finalize();

	// オブジェクト
	CCamera* camera;
	std::list<GameObject*> objList;
private:
	bool isTransition = false;
	// コンスタントバッファ
	ConstantBufferMatrix m_constantBuffer;
	ConstantBuffer m_cb;
	ID3D11Buffer* tmpCb[];
};
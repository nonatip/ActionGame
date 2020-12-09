#pragma once
#include "DirectX11Manager.h"

// クラスのプロトタイプ宣言
class CManager;

// シーンの基底クラス
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

// シーン管理クラス
class CManager
{
public:
	// 今のシーンのポインタ
	CScene* scene;
	CManager() {};
	~CManager() { delete scene; };

	// 描画
	void Update() { scene->Update(); };
	// 更新
	void Draw() { scene->Draw(); };
};
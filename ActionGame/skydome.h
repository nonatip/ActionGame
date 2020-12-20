#pragma once
#include "GameObject.h"

class CSkydome :
	public GameObject
{
	// モデルは種類が複数あるので派生クラスが各々所持する
	UnityExportModel *model;
public:
	CSkydome(CScene* scene);
	~CSkydome();
	void Update();
	void Draw();
};
#pragma once
#include "GameObject.h"

class CStage:
	public GameObject
{
	// モデルは種類が複数あるので派生クラスが各々所持する
	UnityExportModel *model;
public:
	CStage(CScene* scene);
	~CStage();
	void Update();
	void Draw();
};
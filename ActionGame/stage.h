#pragma once
#include "GameObject.h"

class CStage:
	public GameObject
{
	// ���f���͎�ނ���������̂Ŕh���N���X���e�X��������
	UnityExportModel *model;
public:
	CStage(CScene* scene);
	~CStage();
	void Update();
	void Draw();
};
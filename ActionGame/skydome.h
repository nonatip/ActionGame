#pragma once
#include "GameObject.h"

class CSkydome :
	public GameObject
{
	// ���f���͎�ނ���������̂Ŕh���N���X���e�X��������
	UnityExportModel *model;
public:
	CSkydome(CScene* scene);
	~CSkydome();
	void Update();
	void Draw();
};
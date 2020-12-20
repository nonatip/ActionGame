#include "skydome.h"

CSkydome::CSkydome(CScene * scene)
{
	m_scene = scene;
	m_type = GameObject::Other;

	DX11MtxIdentity(m_world);
	model = new UnityExportModel();
	model->LoadBinary("Assets/Models/Skydome.umb");
}

CSkydome::~CSkydome()
{
	delete model;
}

void CSkydome::Update()
{
}

void CSkydome::Draw()
{
	model->Draw();
}
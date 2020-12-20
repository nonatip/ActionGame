#include "stage.h"

CStage::CStage(CScene * scene)
{
	m_scene = scene;
	m_type = GameObject::Other;
	DX11MtxIdentity(m_world);
	model = new UnityExportModel();
	model->LoadBinary("Assets/Models/Map.umb");
}

CStage::~CStage()
{
	delete model;
}

void CStage::Update()
{

}

void CStage::Draw()
{
	model->Draw();
}
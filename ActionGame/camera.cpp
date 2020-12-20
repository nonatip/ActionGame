#include "camera.h"
#include "game.h"

void CCamera::Init()
{
	m_eyePosition = { 0,0,-10 };
	m_lookatPosition = { 0,0,0 };
	m_upVector = { 0,1,0 };
	SetCameraMatrix(m_eyePosition, m_lookatPosition, m_upVector);
	SetProjectionMatrix(1.0f, 10000.0f, XM_PIDIV2 / 2, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void CCamera::Uninit()
{
}

void CCamera::Update()
{
	switch (m_mode)
	{
	case CCamera::CameraMode::GAME:
		UpdateGameCamera();
		break;
	default:
		// カメラを初期設定のまま採用する
		break;
	}
}

// ゲーム内カメラ：TPS
void CCamera::UpdateGameCamera()
{
	XMFLOAT4X4 targetMtx;
	CGame* scene = (CGame*)m_scene;
	for (auto &obj : scene->objList)
	{
		if (obj->GetType() == GameObject::Player)
		{
			targetMtx = obj->GetMtx();
		}
	}

	m_eyePosition.x = targetMtx._41 + targetMtx._31*m_distance;
	m_eyePosition.y = targetMtx._42 + m_height;
	m_eyePosition.z = targetMtx._43 + targetMtx._33*m_distance;

	m_lookatPosition.x = targetMtx._41 + targetMtx._31*m_look;
	m_lookatPosition.y = targetMtx._42 + targetMtx._32*m_look;
	m_lookatPosition.z = targetMtx._43 + targetMtx._33*m_look;

	m_upVector.x = targetMtx._21;
	m_upVector.y = targetMtx._22;
	m_upVector.z = targetMtx._23;

	CreateCameraMatrix();
}

void CCamera::Draw()
{
	std::string str;

	// imGuiの描画
	ImGui::Begin(u8"Camera");
	if (m_mode == CCamera::CameraMode::GAME)
	{
		if (ImGui::TreeNode("GameCamera"))
		{
			if (ImGui::TreeNode("distance"))
			{
				ImGui::SliderFloat("posX", &m_distance, -100.0f, 0.0f);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("height"))
			{
				ImGui::SliderFloat("posX", &m_height, 0.0f, 50.0f);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("test"))
			{
				ImGui::SliderFloat("look", &m_look, 0.0f, 100.0f);
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
	}
	str = "Pos:(" + std::to_string(m_eyePosition.x) + ","
		+ std::to_string(m_eyePosition.y) + ","
		+ std::to_string(m_eyePosition.z) + ")";
	ImGui::Text(str.c_str());
	str = "LookAt:(" + std::to_string(m_lookatPosition.x) + ","
		+ std::to_string(m_lookatPosition.y) + ","
		+ std::to_string(m_lookatPosition.z) + ")";
	ImGui::Text(str.c_str());
	str = "UpVec:(" + std::to_string(m_upVector.x) + ","
		+ std::to_string(m_upVector.y) + ","
		+ std::to_string(m_upVector.z) + ")";
	ImGui::Text(str.c_str());
	ImGui::End();
}
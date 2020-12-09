#include "camera.h"
#include "game.h"

void CCamera::Init()
{
	m_mode = CCamera::DEFAULT;
	m_eyePosition = { 0,0,-10 };
	m_lookatPosition = { 0,0,0 };
	m_upVector = { 0,1,0 };
	SetCameraMatrix(m_eyePosition, m_lookatPosition, m_upVector);
	SetProjectionMatrix(1.0f, 1000.0f, XM_PIDIV2 / 2, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void CCamera::Uninit()
{
}

void CCamera::Update()
{
	switch (m_mode)
	{
	case CCamera::DEFAULT:
		UpdateDEFAULT();
		break;
	case CCamera::FPS:
		UpdateFPS();
		break;
	case CCamera::TPS:
		UpdateTPS();
		break;
	case CCamera::FREE:
		UpdateFREE();
		break;
	default:
		break;
	}
}

void CCamera::Draw()
{
	std::string str;

	// imGui‚Ì•`‰æ
	ImGui::Begin(u8"Camera");
	ImGui::InputInt("Mode", &m_mode);
	if (ImGui::TreeNode("DEFAULT"))
	{
		if (ImGui::TreeNode("pos"))
		{
			ImGui::SliderFloat("posX", &m_eyePosition.x, -256.0f, 256.0f);
			ImGui::SliderFloat("posY", &m_eyePosition.y, -256.0f, 256.0f);
			ImGui::SliderFloat("posZ", &m_eyePosition.z, -256.0f, 256.0f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("look"))
		{
			ImGui::SliderFloat("lookX", &m_lookatPosition.x, -256.0f, 256.0f);
			ImGui::SliderFloat("lookY", &m_lookatPosition.y, -256.0f, 256.0f);
			ImGui::SliderFloat("lookZ", &m_lookatPosition.z, -256.0f, 256.0f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("up"))
		{
			ImGui::SliderFloat("upX", &m_upVector.x, -256.0f, 256.0f);
			ImGui::SliderFloat("upY", &m_upVector.y, -256.0f, 256.0f);
			ImGui::SliderFloat("upZ", &m_upVector.z, -256.0f, 256.0f);
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("FPS"))
	{
		if (ImGui::TreeNode("pos"))
		{
			ImGui::SliderFloat("posX", &m_pos.x, -256.0f, 256.0f);
			ImGui::SliderFloat("posY", &m_pos.y, -256.0f, 256.0f);
			ImGui::SliderFloat("posZ", &m_pos.z, -256.0f, 256.0f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("look"))
		{
			ImGui::SliderFloat("look", &m_look, -256.0f, 256.0f);
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("TPS"))
	{
		if (ImGui::TreeNode("distance"))
		{
			ImGui::SliderFloat("posX", &m_distance, -256.0f, 256.0f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("height"))
		{
			ImGui::SliderFloat("posX", &m_height, -256.0f, 256.0f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("look"))
		{
			ImGui::SliderFloat("look", &m_look, -256.0f, 256.0f);
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("FREE"))
	{
		str = "LookAt:(" + std::to_string(m_lookatPosition.x) + ","
			+ std::to_string(m_lookatPosition.y) + ","
			+ std::to_string(m_lookatPosition.z) + ")";
		ImGui::Text(str.c_str());
		if (ImGui::TreeNode("sensitivity"))
		{
			ImGui::SliderFloat("sensitivity", &m_sensitivity, 10.0f, 100.0f);
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	ImGui::End();
}

void CCamera::UpdateDEFAULT()
{
	CreateCameraMatrix();
}

void CCamera::UpdateFPS()
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

	m_eyePosition.x = targetMtx._41 + m_pos.x;
	m_eyePosition.y = targetMtx._42 + m_pos.y;
	m_eyePosition.z = targetMtx._43 + m_pos.z;

	m_lookatPosition.x = targetMtx._41 + targetMtx._31*m_look;
	m_lookatPosition.y = targetMtx._42 + targetMtx._32*m_look;
	m_lookatPosition.z = targetMtx._43 + targetMtx._33*m_look;

	m_upVector.x = targetMtx._21;
	m_upVector.y = targetMtx._22;
	m_upVector.z = targetMtx._23;

	CreateCameraMatrix();
}

void CCamera::UpdateTPS()
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

void CCamera::UpdateFREE()
{
	if (GetMouseRightTrigger())
	{
		m_beforeMouse.x = GetMouseX();
		m_beforeMouse.y = GetMouseY();
	}
	if (GetMouseRightPress())
	{
		m_lookatPosition.x += (GetMouseX() - m_beforeMouse.x)/m_sensitivity;
		m_lookatPosition.y += -(GetMouseY() - m_beforeMouse.y)/m_sensitivity;

		m_beforeMouse.x = GetMouseX();
		m_beforeMouse.y = GetMouseY();
	}
	CreateCameraMatrix();
}
#include "CSlime.h"
#include "game.h"

CSlime::CSlime(CScene* scene)
{
	m_scene = scene;
	m_type = GameObject::Enemy;
	DX11MtxIdentity(m_world);
	// �e�X�g�p
	m_world._41 = 100;
	m_world._42 = 0;
	m_world._43 = 100;
	Generate();
	skinnedModel = new UnityExportSkinnedModel();
	skinnedModel->LoadBinary("Assets/Models/Slime.usb");
	for (int i = 0; i < AnimMax; i++)
	{
		animation[i].LoadBinary(animData[i], skinnedModel->uemData.m_root.get());
	}
}

CSlime::~CSlime()
{
	delete skinnedModel;
}

void CSlime::Update()
{
	switch (action)
	{
	case SlimeAction::Search:
		break;
	case SlimeAction::Fight:
		break;
	default:
		break;
	}

#pragma region AnimationTest
	if (animCnt > animation[anim].GetMaxAnimationTime())
	{
		animCnt = 0;
	}
	animation[anim].SetTransform(animCnt);
#pragma endregion

	animCnt += 1.0f / 60.0f;
}

void CSlime::AnimUpdate()
{
}

void CSlime::Draw()
{
	//CGame* scene = (CGame*)m_scene;

	// ���f���̕`��
	if (isDraw())
	{
		skinnedModel->Draw();
	}

	std::string str;

	// imGui�̕`��
	ImGui::Begin(u8"Slime");
	ImGui::Checkbox("Attack", &isAttack);
	ImGui::InputInt("Animation", &anim);
	if (anim < 0)
	{
		anim = SlimeAnimation::AnimMax - 1;
	}
	if (anim >= SlimeAnimation::AnimMax)
	{
		anim = 0;
	}
	if (ImGui::TreeNode("AnimData"))
	{
		for (int i = 0; i < SlimeAnimation::AnimMax; i++)
		{
			ImGui::Text(animData[i]);
		}
		ImGui::TreePop();
	}
	ImGui::End();
}

bool CSlime::isDraw()
{
	CGame* scene = (CGame*)m_scene;

	return true;
}

void CSlime::Generate()
{
	CGame* scene = (CGame*)m_scene;
}
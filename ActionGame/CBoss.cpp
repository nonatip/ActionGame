#include "CBoss.h"
#include "game.h"

CBoss::CBoss(CScene* scene)
{
	m_scene = scene;
	m_type = GameObject::Enemy;
	DX11MtxIdentity(m_world);
	// テスト用
	m_world._41 = 0;
	m_world._42 = 0;
	m_world._43 = 100;
	Generate();
	skinnedModel = new UnityExportSkinnedModel();
	skinnedModel->LoadBinary("Assets/Models/Boss.usb");
	for (int i = 0; i < AnimMax; i++)
	{
		animation[i].LoadBinary(animData[i], skinnedModel->uemData.m_root.get());
	}
}

CBoss::~CBoss()
{
	delete skinnedModel;
}

void CBoss::Update()
{
	switch (action)
	{
	case BossAction::Search:
		break;
	case BossAction::Fight:
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

void CBoss::AnimUpdate()
{
}

void CBoss::Draw()
{
	//CGame* scene = (CGame*)m_scene;

	// モデルの描画
	skinnedModel->Draw();

	std::string str;

	// imGuiの描画
	ImGui::Begin(u8"Boss");
	ImGui::Checkbox("Attack", &isAttack);
	ImGui::InputInt("Animation", &anim);
	if (anim < 0)
	{
		anim = BossAnimation::AnimMax - 1;
	}
	if (anim >= BossAnimation::AnimMax)
	{
		anim = 0;
	}
	if (ImGui::TreeNode("AnimData"))
	{
		for (int i = 0; i < BossAnimation::AnimMax; i++)
		{
			ImGui::Text(animData[i]);
		}
		ImGui::TreePop();
	}
	ImGui::End();
}

bool CBoss::isDraw()
{
	CGame* scene = (CGame*)m_scene;

	return true;
}

void CBoss::Generate()
{
	CGame* scene = (CGame*)m_scene;
}
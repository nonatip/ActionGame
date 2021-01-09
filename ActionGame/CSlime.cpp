#include "CSlime.h"
#include "game.h"

CSlime::CSlime(CScene* scene)
{
	m_scene = scene;
	m_type = GameObject::Enemy;
	DX11MtxIdentity(m_world);
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
	if (animCnt > animation[anim].GetMaxAnimationTime())
	{
		animCnt = 0;
	}
	animation[anim].SetTransform(animCnt);

	animCnt += 1.0f / 60.0f;
}

void CSlime::AnimUpdate()
{
}

void CSlime::Draw()
{
	//CGame* scene = (CGame*)m_scene;

	// ƒ‚ƒfƒ‹‚Ì•`‰æ
	skinnedModel->Draw();

	std::string str;

	// imGui‚Ì•`‰æ
	ImGui::Begin(u8"Slime");
	ImGui::Checkbox("Attack", &isAttack);
	ImGui::InputInt("Animation", &anim);
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

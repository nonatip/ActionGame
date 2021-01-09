#include "CTurtle.h"
#include "game.h"

CTurtle::CTurtle(CScene* scene)
{
	m_scene = scene;
	m_type = GameObject::Enemy;
	DX11MtxIdentity(m_world);
	skinnedModel = new UnityExportSkinnedModel();
	skinnedModel->LoadBinary("Assets/Models/Turtle.usb");
	for (int i = 0; i < AnimMax; i++)
	{
		animation[i].LoadBinary(animData[i], skinnedModel->uemData.m_root.get());
	}
}

CTurtle::~CTurtle()
{
	delete skinnedModel;
}

void CTurtle::Update()
{
	if (animCnt > animation[anim].GetMaxAnimationTime())
	{
		animCnt = 0;
	}
	animation[anim].SetTransform(animCnt);

	animCnt += 1.0f / 60.0f;
}

void CTurtle::AnimUpdate()
{
}

void CTurtle::Draw()
{
	//CGame* scene = (CGame*)m_scene;

	// ƒ‚ƒfƒ‹‚Ì•`‰æ
	skinnedModel->Draw();

	std::string str;

	// imGui‚Ì•`‰æ
	ImGui::Begin(u8"Turtle");
	ImGui::Checkbox("Attack", &isAttack);
	ImGui::InputInt("Animation", &anim);
	if (ImGui::TreeNode("AnimData"))
	{
		for (int i = 0; i < TurtleAnimation::AnimMax; i++)
		{
			ImGui::Text(animData[i]);
		}
		ImGui::TreePop();
	}
	ImGui::End();
}

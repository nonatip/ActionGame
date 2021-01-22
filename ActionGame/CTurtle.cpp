#include "CTurtle.h"
#include "game.h"

CTurtle::CTurtle(CScene* scene)
{
	m_scene = scene;
	m_type = GameObject::Enemy;
	DX11MtxIdentity(m_world);
	// テスト用
	m_world._41 = -100;
	m_world._42 = 0;
	m_world._43 = 100;
	Generate();
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
	switch (action)
	{
	case TurtleAction::Search:
		break;
	case TurtleAction::Fight:
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

void CTurtle::AnimUpdate()
{
}

void CTurtle::Draw()
{
	//CGame* scene = (CGame*)m_scene;

	// モデルの描画
	if (isDraw())
	{
		skinnedModel->Draw();
	}

	std::string str;

	// imGuiの描画
	ImGui::Begin(u8"Turtle");
	ImGui::Checkbox("Attack", &isAttack);
	ImGui::InputInt("Animation", &anim);
	if (anim < 0)
	{
		anim = TurtleAnimation::AnimMax - 1;
	}
	if (anim >= TurtleAnimation::AnimMax)
	{
		anim = 0;
	}
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

bool CTurtle::isDraw()
{
	CGame* scene = (CGame*)m_scene;

	// playerとplayerの進行方向ベクトル
	// playerと敵の位置の差ベクトル
	// 内積の結果が90度以上なら後ろにいる
	// 一定距離離れていて後ろにいる場合は描画しないようにする

	return true;
}

void CTurtle::Generate()
{
	CGame* scene = (CGame*)m_scene;


}
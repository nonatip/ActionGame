#include "CSlime.h"
#include "game.h"

CSlime::CSlime(CScene* scene)
{
	m_scene = scene;
	m_type = GameObject::Enemy;
	DX11MtxIdentity(m_world);
	// テスト用
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

	UpdateInfo();

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

	// モデルの描画
	if (isDraw())
	{
		skinnedModel->Draw();
	}

	std::string str;

	// imGuiの描画
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
	XMFLOAT3 pos, dir;
	float dot;

	CGame* scene = (CGame*)m_scene;
	for (auto obj : scene->objList)
	{
		if (obj->GetType() == ObjectType::Player)
		{
			pos = obj->GetPos();
			dir = obj->GetDir();
		}
	}

	// playerと敵の位置の差ベクトル：dif_pos
	XMFLOAT3 dif_pos = { m_pos.x - pos.x,m_pos.y - pos.y, m_pos.z - pos.z, };

	// 正規化
	DX11Vec3Normalize(dir, dir);
	DX11Vec3Normalize(dif_pos, dif_pos);

	// 内積の結果が90度以上なら後ろにいる
	DX11Vec3Dot(dot, dir, dif_pos);

	// 一定距離離れているかつ、後ろにいる場合は描画しないようにする
	if (dot < 0)
	{
		return false;
	}

	return true;
}

void CSlime::Generate()
{
	CGame* scene = (CGame*)m_scene;
}
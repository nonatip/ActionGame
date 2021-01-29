#include "CTurtle.h"
#include "game.h"

CTurtle::CTurtle(CScene* scene)
{
	m_scene = scene;
	m_type = GameObject::Enemy;
	DX11MtxIdentity(m_world);
	// �e�X�g�p
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

void CTurtle::AnimUpdate()
{
}

void CTurtle::Draw()
{
	//CGame* scene = (CGame*)m_scene;

	// ���f���̕`��
	if (isDraw())
	{
		skinnedModel->Draw();
	}

	std::string str;

	// imGui�̕`��
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

	// player�ƓG�̈ʒu�̍��x�N�g���Fdif_pos
	XMFLOAT3 dif_pos = { m_pos.x - pos.x,m_pos.y - pos.y, m_pos.z - pos.z, };

	// ���K��
	DX11Vec3Normalize(dir, dir);
	DX11Vec3Normalize(dif_pos, dif_pos);

	// ���ς̌��ʂ�90�x�ȏ�Ȃ���ɂ���
	DX11Vec3Dot(dot, dir, dif_pos);

	// ��苗������Ă��邩�A���ɂ���ꍇ�͕`�悵�Ȃ��悤�ɂ���
	if (dot < 0)
	{
		return false;
	}

	return true;
}

void CTurtle::Generate()
{
	CGame* scene = (CGame*)m_scene;


}
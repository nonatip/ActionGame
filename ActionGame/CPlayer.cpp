#include "CPlayer.h"
#include "game.h"

CPlayer::CPlayer(CScene* scene)
{
	m_scene = scene;
	m_type = GameObject::Player;
	DX11MtxIdentity(m_world);
	skinnedModel = new UnityExportSkinnedModel();
	skinnedModel->LoadBinary("Assets/Models/UnityChan.usb");
	for (int i = 0; i < AnimMax; i++)
	{
		animation[i].LoadBinary(animData[i], skinnedModel->uemData.m_root.get());
	}
	m_beforeMouse.x = GetMouseX();
	m_beforeMouse.y = GetMouseY();
}

CPlayer::~CPlayer()
{
	delete skinnedModel;
}

void CPlayer::Update()
{
	if (!isJump && !isAttack)
	{
		// 向きの変更
		m_angle.y += (GetMouseX() - m_beforeMouse.x) / m_sensitivity;
		m_beforeMouse.x = GetMouseX();
		if (GetKeyboardPress(DIK_W))	// 前進キー入力
		{
			if (GetKeyboardPress(DIK_LSHIFT))
			{
				if (anim != CPlayer::PlayerAnimation::Run)
				{
					anim = CPlayer::PlayerAnimation::Run;
					animCnt = 0;
					m_trans.x += m_dir.x * 2.0f;
					m_trans.y += m_dir.y * 2.0f;
					m_trans.z += m_dir.z * 2.0f;
				}
			}
			else
			{
				if (anim != CPlayer::PlayerAnimation::Walk)
				{
					anim = CPlayer::PlayerAnimation::Walk;
					animCnt = 0;
					m_trans.x += m_dir.x * 1.0f;
					m_trans.y += m_dir.y * 1.0f;
					m_trans.z += m_dir.z * 1.0f;
				}
			}
		}
		if (GetMouseLeftPress())	// 左クリック：パンチ
		{
			anim = CPlayer::PlayerAnimation::Punch;
			isAttack = true;
			animCnt = 0;
		}
		if (GetMouseRightPress())	//右クリック：キック
		{
			anim = CPlayer::PlayerAnimation::Kick;
			isAttack = true;
			animCnt = 0;
		}
		if (GetKeyboardPress(DIK_SPACE))	// ジャンプキー入力
		{
			anim = CPlayer::PlayerAnimation::Jump;
			isJump = true;
			animCnt = 0;
		}
		if (!GetKeyboardAnyKey() && !GetMouseAnyBotton())	// 何も操作されてないとき
		{
			if (anim != CPlayer::PlayerAnimation::Idle)
			{
				anim = CPlayer::PlayerAnimation::Idle;
				animCnt = 0;
			}
		}
	}

	DX11MakeWorldMatrix(m_world, m_angle, m_trans);
	UpdateInfo();

	// アニメーションの更新
	AnimUpdate();
}

void CPlayer::AnimUpdate()
{
	switch (anim)
	{
	case CPlayer::PlayerAnimation::Idle:
		if (animCnt > animation[Idle].GetMaxAnimationTime())
		{
			animCnt = 0;
		}
		animation[Idle].SetTransform(animCnt);
		break;
	case CPlayer::PlayerAnimation::Walk:
		if (animCnt > animation[Walk].GetMaxAnimationTime())
		{
			animCnt = 0;
		}
		animation[Walk].SetTransform(animCnt);
		break;
	case CPlayer::PlayerAnimation::Run:
		if (animCnt > animation[Run].GetMaxAnimationTime())
		{
			animCnt = 0;
		}
		animation[Run].SetTransform(animCnt);
		break;
	case CPlayer::PlayerAnimation::Jump:
		if (animCnt > animation[Jump].GetMaxAnimationTime())
		{
			isJump = false;
		}
		animation[Jump].SetTransform(animCnt);
		break;
	case CPlayer::PlayerAnimation::Punch:
		if (animCnt > animation[Punch].GetMaxAnimationTime())
		{
			isAttack = false;
		}
		animation[Punch].SetTransform(animCnt);
		break;
	case CPlayer::PlayerAnimation::Kick:
		if (animCnt > animation[Kick].GetMaxAnimationTime())
		{
			isAttack = false;
		}
		animation[Kick].SetTransform(animCnt);
		break;
	default:
		break;
	}

	animCnt += 1.0f / 60.0f;
}

void CPlayer::Draw()
{
	CGame* scene = (CGame*)m_scene;

	// モデルの描画
	skinnedModel->Draw();

	std::string str;

	// imGuiの描画
	ImGui::Begin(u8"Player");
	ImGui::SliderFloat("sensitivity", &m_sensitivity, 10.0f, 100.0f);
	ImGui::Checkbox("Jump", &isJump);
	ImGui::Checkbox("Attack", &isAttack);
	str = "Anim:(" + std::to_string(anim) + ")";
	ImGui::Text(str.c_str());
	ImGui::End();
}
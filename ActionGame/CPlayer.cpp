#include "CPlayer.h"
#include "game.h"

CPlayer::CPlayer(CScene* scene)
{
	m_scene = scene;
	m_type = GameObject::Player;
	DX11MtxIdentity(m_world);
	skinnedModel = new UnityExportSkinnedModel();
	skinnedModel->LoadBinary("Assets/Models/Unitychan.usb");
	for (int i = 0; i < AnimMax; i++)
	{
		animation[i].LoadBinary(animData[i], skinnedModel->uemData.m_root.get());
	}
}

CPlayer::~CPlayer()
{
	delete skinnedModel;
}

void CPlayer::Update()
{
	if (!isLand && !isAttack)
	{
		// 向きの変更
		m_angle.y += GetMouseAxisX() / m_sensitivity;
		if (GetKeyboardPress(DIK_W))	// 前進キー入力
		{
			if (GetKeyboardPress(DIK_LSHIFT))
			{
				if (anim != CPlayer::PlayerAnimation::Run)
				{
					anim = CPlayer::PlayerAnimation::Run;
					animCnt = 0;
				}
				m_trans.x += m_dir.x * 1.0f;
				m_trans.y += m_dir.y * 1.0f;
				m_trans.z += m_dir.z * 1.0f;
			}
			else
			{
				if (anim != CPlayer::PlayerAnimation::Walk)
				{
					anim = CPlayer::PlayerAnimation::Walk;
					animCnt = 0;
				}
				m_trans.x += m_dir.x * 0.5f;
				m_trans.y += m_dir.y * 0.5f;
				m_trans.z += m_dir.z * 0.5f;
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
		if (GetKeyboardPress(DIK_SPACE))	// 回避キー入力
		{
			if (GetKeyboardPress(DIK_W))
			{
				m_trans.x += m_dir.x * 10.0f;
				m_trans.y += m_dir.y * 10.0f;
				m_trans.z += m_dir.z * 10.0f;
			}
			if (GetKeyboardPress(DIK_S))
			{
				m_trans.x += m_dir.x * -10.0f;
				m_trans.y += m_dir.y * -10.0f;
				m_trans.z += m_dir.z * -10.0f;
			}
			if (GetKeyboardPress(DIK_A))
			{
				m_trans.x += m_world._11 * -10.0f;
				m_trans.y += m_world._21 * -10.0f;
				m_trans.z += m_world._31 * -10.0f;
			}
			if (GetKeyboardPress(DIK_D))
			{
				m_trans.x += m_world._11 * 10.0f;
				m_trans.y += m_world._21 * 10.0f;
				m_trans.z += m_world._31 * 10.0f;
			}
			anim = CPlayer::PlayerAnimation::Land;
			isLand = true;
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

	// ワールド変換行列作成
	DX11MakeWorldMatrix(m_world, m_angle, m_trans);
	// 位置補正
	if (m_world._41 < -STAGE_SIZE || m_world._41 > STAGE_SIZE)
	{
		m_world._41 = m_beforePos.x;
	}
	if (m_world._43 < -STAGE_SIZE || m_world._43 > STAGE_SIZE)
	{
		m_world._43 = m_beforePos.z;
	}
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
	case CPlayer::PlayerAnimation::Land:
		if (animCnt > animation[Land].GetMaxAnimationTime())
		{
			isLand = false;
		}
		animation[Land].SetTransform(animCnt);
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
	//CGame* scene = (CGame*)m_scene;

	// モデルの描画
	skinnedModel->Draw();

	std::string str;

	// imGuiの描画
	ImGui::Begin(u8"Player");
	ImGui::SliderFloat("sensitivity", &m_sensitivity, 10.0f, 100.0f);
	ImGui::Checkbox("Land", &isLand);
	ImGui::Checkbox("Attack", &isAttack);
	str = "Anim:(" + std::to_string(anim) + ")";
	ImGui::Text(str.c_str());
	ImGui::End();
}
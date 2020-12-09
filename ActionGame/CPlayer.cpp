#include "CPlayer.h"
#include "game.h"
CPlayer::CPlayer(CScene* scene)
{
	m_scene = scene;
	m_type = GameObject::Player;
	DX11MtxIdentity(m_world);
	skinnedModel = new UnityExportSkinnedModel();
	skinnedModel->LoadBinary("Assets/Models/SkinnedMeshData.usb");
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
	if (GetKeyboardPress(DIK_W))
	{
		if (anim != CPlayer::Run)
		{
			anim = CPlayer::Run;
			animCnt = 0;
		}
		m_trans.x += m_dir.x * 1.0f;
		m_trans.y += m_dir.y * 1.0f;
		m_trans.z += m_dir.z * 1.0f;
	}
	if (GetKeyboardPress(DIK_D))
	{
		m_angle.y += 1.0f;
	}
	if (GetKeyboardPress(DIK_A))
	{
		m_angle.y -= 1.0f;
	}
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		if (anim != CPlayer::Jump)
		{
			anim = CPlayer::Jump;
			animCnt = 0;
		}
	}
	if (GetKeyboardAnyKey())
	{
		if (anim != CPlayer::Idle)
		{
			anim = CPlayer::Idle;
			animCnt = 0;
		}
	}

	DX11MakeWorldMatrix(m_world, m_angle, m_trans);
	UpdateInfo();

	switch (anim)
	{
	case CPlayer::Idle:
		if (animCnt > animation[Idle].GetMaxAnimationTime())
		{
			animCnt = 0;
		}
		animation[Idle].SetTransform(animCnt);
		break;
	case CPlayer::Run:
		if (animCnt > animation[Run].GetMaxAnimationTime())
		{
			animCnt = 0;
		}
		animation[Run].SetTransform(animCnt);
		break;
	case CPlayer::Jump:
		if (animCnt > animation[Jump].GetMaxAnimationTime())
		{
			animCnt = 0;
		}
		animation[Jump].SetTransform(animCnt);
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
	if (!(scene->camera->GetMode() == CCamera::FPS))
	{
		skinnedModel->Draw();
	}

	// imGuiの描画
	ImGui::Begin(u8"Player");
#pragma region Operation
	ImGui::Text("W:GoStraight");
	ImGui::Text("Space:Jump");
#pragma endregion
#pragma region Anim
	//// 状態
	//static bool isJump;
	//ImGui::Checkbox("jump", &isJump);
	//static bool isRun;
	//ImGui::Checkbox("run", &isRun);
	//static bool isSlide;
	//ImGui::Checkbox("slide", &isSlide);
	//// アニメーション
	//static float jumpTime = 0.0f;
	//ImGui::SliderFloat("JumpAnim", &jumpTime, 0.0f, animation[Jump].GetMaxAnimationTime());
	//static float runTime = 0.0f;
	//ImGui::SliderFloat("RunAnim", &runTime, 0.0f, animation[Run].GetMaxAnimationTime());
	//static float slideTime = 0.0f;
	//ImGui::SliderFloat("SlideAnim", &slideTime, 0.0f, animation[Idle].GetMaxAnimationTime());
	//// セット
	//if (isJump)
	//{
	//	animation[Jump].SetTransform(jumpTime);
	//}
	//if (isRun)
	//{
	//	animation[Run].SetTransform(runTime);
	//}
	//if (isSlide)
	//{
	//	animation[Idle].SetTransform(slideTime);
	//}
#pragma endregion
	ImGui::End();
}
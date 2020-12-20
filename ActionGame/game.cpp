#include "game.h"
#include "title.h"

#include <DirectXMath.h>
#include "DirectX11Manager.h"

CGame::CGame(CManager *pManager) : CScene(pManager)
{
	Initialize();
}

void CGame::Initialize()
{
	//�R���X�^���g�o�b�t�@�̍쐬
	DirectX11Manager::CreateConstantBuffer(sizeof(ConstantBufferMatrix), &m_cb);
	// �I�u�W�F�N�g�̐���
	CPlayer* player = new CPlayer(this);
	objList.emplace_back(player);
	CSkydome* skydome = new CSkydome(this);
	objList.emplace_back(skydome);
	CStage* stage = new CStage(this);
	objList.emplace_back(stage);
	// �J�����̍쐬
	camera = new CCamera(this);
	camera->SetMode(CCamera::CameraMode::GAME);
	m_constantBuffer.proj = XMMatrixTranspose(XMLoadFloat4x4(&camera->GetProjectionMatrix()));
	m_constantBuffer.view = XMMatrixTranspose(XMLoadFloat4x4(&camera->GetCameraMatrix()));
}

CGame::~CGame()
{
	Finalize();
}

void CGame::Finalize()
{
	// �I�u�W�F�N�g�̏I������
	for (auto &obj : objList)
	{
		if (obj != nullptr)//nullptr�̃��c��delete�����痎����
		{
			delete(obj);
		}
	}

	delete camera;
}

void CGame::Update()
{
	UpdateInput();

	for (auto &obj : objList)
	{
		obj->Update();
	}

	// �J�����̍X�V
	camera->Update();

	// �Ƃ肠�����̎���
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		//�}�l�[�W���[�̃A�h���X�������p��
		manager->scene = new CTitle(manager);
		delete this;
	}
}

void CGame::Draw()
{
	// �`��O
	DirectX11Manager::DrawBegin();

	// proj&view�̃Z�b�g
	m_constantBuffer.proj = XMMatrixTranspose(XMLoadFloat4x4(&camera->GetProjectionMatrix()));
	m_constantBuffer.view = XMMatrixTranspose(XMLoadFloat4x4(&camera->GetCameraMatrix()));

	// �I�u�W�F�N�g�`�揈��
	for (auto &obj : objList)
	{
		m_constantBuffer.world = XMMatrixTranspose(XMLoadFloat4x4(&obj->GetMtx()));
		DirectX11Manager::UpdateConstantBuffer(m_cb.Get(), m_constantBuffer);
		*tmpCb = { m_cb.Get() };
		DirectX11Manager::m_pImContext->VSSetConstantBuffers(0, 1, tmpCb);
		obj->Draw();
	}

	// �J�����̕`��
	camera->Draw();

	// ImGui
	ImGui::Begin(u8"game");
	ImGui::Text("FPS %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("TitleScene:PushEnter");
	ImGui::End();

	// �`���
	DirectX11Manager::DrawEnd();
}
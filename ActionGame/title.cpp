#include "title.h"
#include "game.h"

CTitle::CTitle(CManager *pManager) :CScene(pManager)
{
	//�R���X�^���g�o�b�t�@�̍쐬
	DirectX11Manager::CreateConstantBuffer(sizeof(ConstantBufferMatrix), &m_cb);
}

CTitle::~CTitle()
{

}

void CTitle::Update()
{
	UpdateInput();

	if (!GetKeyboardAnyKey())
	{
		isChange = true;
	}

	// �Ƃ肠�����̎���
	if (isChange&&GetKeyboardAnyKey())
	{
		//�}�l�[�W���[�̃A�h���X�������p��
		manager->scene = new CGame(manager);
		delete this;
	}
}

void CTitle::Draw()
{
	// �`��O
	DirectX11Manager::DrawBegin();

	// �I�u�W�F�N�g�`�揈��


	// ImGui
	ImGui::Begin(u8"title");
	ImGui::Text("FPS %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("GameScene:PushAnyKey");
	ImGui::End();

	// �`���
	DirectX11Manager::DrawEnd();
}
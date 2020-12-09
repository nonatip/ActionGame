#include "title.h"
#include "game.h"

CTitle::CTitle(CManager *pManager) :CScene(pManager)
{
	//コンスタントバッファの作成
	DirectX11Manager::CreateConstantBuffer(sizeof(ConstantBufferMatrix), &m_cb);
}

CTitle::~CTitle()
{

}

void CTitle::Update()
{
	UpdateInput();

	// とりあえずの実装
	if (isTransition)
	{
		//マネージャーのアドレスを引き継ぐ
		manager->scene = new CGame(manager);
		delete this;
	}
}

void CTitle::Draw()
{
	// 描画前
	DirectX11Manager::DrawBegin();

	// オブジェクト描画処理


	// ImGui
	ImGui::Begin(u8"title");
	ImGui::Text("FPS %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Checkbox("transition", &isTransition);
	ImGui::End();

	// 描画後
	DirectX11Manager::DrawEnd();
}
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
	//コンスタントバッファの作成
	DirectX11Manager::CreateConstantBuffer(sizeof(ConstantBufferMatrix), &m_cb);
	// オブジェクトの生成
	CPlayer* player = new CPlayer(this);
	objList.emplace_back(player);
	CStage* stage = new CStage(this);
	objList.emplace_back(stage);
	// 敵のテスト生成
	CSlime* slime = new CSlime(this);
	objList.emplace_back(slime);
	CTurtle* turtle = new CTurtle(this);
	objList.emplace_back(turtle);
	CBoss *boss = new CBoss(this);
	objList.emplace_back(boss);
	// カメラの作成
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
	// オブジェクトの終了処理
	for (auto &obj : objList)
	{
		if (obj != nullptr)//nullptrのヤツをdeleteしたら落ちる
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

	// カメラの更新
	camera->Update();

	// とりあえずの実装
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		//マネージャーのアドレスを引き継ぐ
		manager->scene = new CTitle(manager);
		delete this;
	}
}

void CGame::Draw()
{
	// 描画前
	DirectX11Manager::DrawBegin();

	// proj&viewのセット
	m_constantBuffer.proj = XMMatrixTranspose(XMLoadFloat4x4(&camera->GetProjectionMatrix()));
	m_constantBuffer.view = XMMatrixTranspose(XMLoadFloat4x4(&camera->GetCameraMatrix()));

	// オブジェクト描画処理
	for (auto &obj : objList)
	{
		m_constantBuffer.world = XMMatrixTranspose(XMLoadFloat4x4(&obj->GetMtx()));
		DirectX11Manager::UpdateConstantBuffer(m_cb.Get(), m_constantBuffer);
		*tmpCb = { m_cb.Get() };
		DirectX11Manager::m_pImContext->VSSetConstantBuffers(0, 1, tmpCb);
		obj->Draw();
	}

	// カメラの描画
	camera->Draw();

	// ImGui
	ImGui::Begin(u8"game");
	ImGui::Text("FPS %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("TitleScene:PushEnter");
	ImGui::End();

	// 描画後
	DirectX11Manager::DrawEnd();
}
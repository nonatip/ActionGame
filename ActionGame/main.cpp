#include "DirectX11Manager.h"

#include "manager.h"
#include "title.h"

int g_nCountFPS = 0;	// FPSカウンタ

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DWORD dwExecLastTime;		// 最後に実行した時間		
	DWORD dwFPSLastTime;		// 最後に計測した時間
	DWORD dwCurrentTime;		// 現在時刻
	DWORD dwFrameCount;			// フレーム数
	timeBeginPeriod(1);			// タイマの分解能力を1msにする
	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;

	if (FAILED(DirectX11Manager::Init(hInstance, nCmdShow)))
		return -1;

	//管理システムを動的確保
	CManager *p_manager;
	p_manager = new CManager();
	//タイトルを動的確保
	p_manager->scene = new CTitle(p_manager);

	MSG msg = { 0 };
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (WM_QUIT == msg.message) break;

		// 現在時間を取得
		dwCurrentTime = timeGetTime();

		// 0.5秒ごとに実行
		if ((dwCurrentTime - dwFPSLastTime) > 500) {

			// FPSを計算
			g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

			// FPS計測時間に現座時間をセット
			dwFPSLastTime = dwCurrentTime;

			// フレーム数をゼロクリア
			dwFrameCount = 0;
		}

		// 16ミリ秒経過したら
		if ((dwCurrentTime - dwExecLastTime) >= (1000.0f / 60.0f)) {

			// 最終実行時間に現在時間をセット
			dwExecLastTime = dwCurrentTime;

			// マネージャーからシーンの更新、描画を呼び出す
			p_manager->Update();
			p_manager->Draw();

			// フレーム数カウントアップ
			dwFrameCount++;
		}
	}

	DirectX11Manager::Cleanup();
	return 0;
}
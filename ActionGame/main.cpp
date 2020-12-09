#include "DirectX11Manager.h"

#include "manager.h"
#include "title.h"

int g_nCountFPS = 0;	// FPS�J�E���^

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DWORD dwExecLastTime;		// �Ō�Ɏ��s��������		
	DWORD dwFPSLastTime;		// �Ō�Ɍv����������
	DWORD dwCurrentTime;		// ���ݎ���
	DWORD dwFrameCount;			// �t���[����
	timeBeginPeriod(1);			// �^�C�}�̕���\�͂�1ms�ɂ���
	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;

	if (FAILED(DirectX11Manager::Init(hInstance, nCmdShow)))
		return -1;

	//�Ǘ��V�X�e���𓮓I�m��
	CManager *p_manager;
	p_manager = new CManager();
	//�^�C�g���𓮓I�m��
	p_manager->scene = new CTitle(p_manager);

	MSG msg = { 0 };
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (WM_QUIT == msg.message) break;

		// ���ݎ��Ԃ��擾
		dwCurrentTime = timeGetTime();

		// 0.5�b���ƂɎ��s
		if ((dwCurrentTime - dwFPSLastTime) > 500) {

			// FPS���v�Z
			g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

			// FPS�v�����ԂɌ������Ԃ��Z�b�g
			dwFPSLastTime = dwCurrentTime;

			// �t���[�������[���N���A
			dwFrameCount = 0;
		}

		// 16�~���b�o�߂�����
		if ((dwCurrentTime - dwExecLastTime) >= (1000.0f / 60.0f)) {

			// �ŏI���s���ԂɌ��ݎ��Ԃ��Z�b�g
			dwExecLastTime = dwCurrentTime;

			// �}�l�[�W���[����V�[���̍X�V�A�`����Ăяo��
			p_manager->Update();
			p_manager->Draw();

			// �t���[�����J�E���g�A�b�v
			dwFrameCount++;
		}
	}

	DirectX11Manager::Cleanup();
	return 0;
}
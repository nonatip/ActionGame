#pragma once
#include	<d3d11.h>
#include	<DirectXMath.h>
#include	<math.h>
#include	<vector>
#include	"DirectX11Manager.h"
#include	"Define.h"

class CBox {
private:
	ID3D11Buffer*		m_pVertexBuffer;	// ���_�o�b�t�@
	ID3D11Buffer*		m_pIndexBuffer;		// �C���f�b�N�X�o�b�t�@
	ID3D11VertexShader* m_pVertexShader;	// ���_�V�F�[�_�[
	ID3D11PixelShader*  m_pPixelShader;		// �s�N�Z���V�F�[�_�[
	ID3D11InputLayout*  m_pVertexLayout;	// ���_���C�A�E�g
	float				m_lengthx;			// ����(X)
	float				m_lengthy;			// ����(Y)
	float				m_lengthz;			// ���s��(Z)

	struct Vertex {
		DirectX::XMFLOAT3	Pos;
	};

	struct Face {
		unsigned int idx[3];
	};

	Vertex					m_vertex[8];		// ���_���W

	Face					m_face[12];			// �ʃC���f�b�N�X�f�[�^
	unsigned int			m_facenum = 12;		// �ʐ�

	// �C���f�b�N�X�f�[�^���쐬����
	void CreateIndex();
	// ���_�f�[�^���쐬����
	void CreateVertex();

public:

	void Draw();

	// ������
	bool Init(
		float width,						// ��
		float height,						// ����
		float depth);						// ���s��

	// �I������
	void Exit();
};
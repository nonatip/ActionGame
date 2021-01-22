#pragma once
#include	<d3d11.h>
#include	<DirectXMath.h>
#include	<math.h>
#include	<vector>
#include	"DirectX11Manager.h"
#include	"Define.h"

class CSphere {
private:
	ID3D11Buffer*		m_pVertexBuffer;	// ���_�o�b�t�@
	ID3D11Buffer*		m_pIndexBuffer;		// �C���f�b�N�X�o�b�t�@
	ID3D11VertexShader* m_pVertexShader;	// ���_�V�F�[�_�[
	ID3D11PixelShader*  m_pPixelShader;		// �s�N�Z���V�F�[�_�[
	ID3D11InputLayout*  m_pVertexLayout;	// ���_���C�A�E�g
	unsigned int		m_divX;				// ���������̕�����
	unsigned int		m_divY;				// ���������̕�����
	float				m_radius;			// ���a

	struct Vertex {
		DirectX::XMFLOAT3	Pos;
		DirectX::XMFLOAT3	Normal;
	};

	struct Face {
		unsigned int idx[3];
	};

	Vertex*					m_vertex;			// ���_���W

	Face*					m_face;				// �ʃC���f�b�N�X�f�[�^
	unsigned int			m_facenum;			// �ʐ�

	// �C���f�b�N�X�f�[�^���쐬����
	void CreateIndex();
	// ���_�f�[�^���쐬����
	void CreateVertex();

public:

	void Normalize(XMFLOAT3 vector, XMFLOAT3& Normal);

	void Draw(ID3D11DeviceContext* device);

	// ������
	bool Init(float r,						// ���a
		int division_horizontal,			// ���������̕�����
		int division_vertical,				// ���������̕�����
		ID3D11Device* device);

	// �I������
	void Exit();
};
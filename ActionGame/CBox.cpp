#include	"CBox.h"

// �C���f�b�N�X�f�[�^���쐬
void CBox::CreateIndex() {
	m_face[0].idx[0] = 0;		// ��O  ok
	m_face[0].idx[1] = 1;
	m_face[0].idx[2] = 2;

	m_face[1].idx[0] = 2;
	m_face[1].idx[1] = 3;
	m_face[1].idx[2] = 0;

	m_face[2].idx[0] = 5;		// ��  ok
	m_face[2].idx[1] = 4;
	m_face[2].idx[2] = 7;

	m_face[3].idx[0] = 7;
	m_face[3].idx[1] = 6;
	m_face[3].idx[2] = 5;

	m_face[4].idx[0] = 4;		// ���� ok
	m_face[4].idx[1] = 0;
	m_face[4].idx[2] = 7;

	m_face[5].idx[0] = 0;
	m_face[5].idx[1] = 3;
	m_face[5].idx[2] = 7;

	m_face[6].idx[0] = 1;		// �E�� ok
	m_face[6].idx[1] = 5;
	m_face[6].idx[2] = 6;

	m_face[7].idx[0] = 1;
	m_face[7].idx[1] = 6;
	m_face[7].idx[2] = 2;

	m_face[8].idx[0] = 0;		// �㑤 ok
	m_face[8].idx[1] = 4;
	m_face[8].idx[2] = 1;

	m_face[9].idx[0] = 4;
	m_face[9].idx[1] = 5;
	m_face[9].idx[2] = 1;

	m_face[10].idx[0] = 3;		// ����
	m_face[10].idx[1] = 2;
	m_face[10].idx[2] = 7;

	m_face[11].idx[0] = 6;
	m_face[11].idx[1] = 7;
	m_face[11].idx[2] = 2;
}

// ���_�f�[�^���쐬
void CBox::CreateVertex() {

	m_vertex[0].Pos.x = -(m_lengthx / 2.0f);
	m_vertex[0].Pos.y = (m_lengthy / 2.0f);
	m_vertex[0].Pos.z = -(m_lengthz / 2.0f);

	m_vertex[1].Pos.x = (m_lengthx / 2.0f);
	m_vertex[1].Pos.y = (m_lengthy / 2.0f);
	m_vertex[1].Pos.z = -(m_lengthz / 2.0f);

	m_vertex[2].Pos.x = (m_lengthx / 2.0f);
	m_vertex[2].Pos.y = -(m_lengthy / 2.0f);
	m_vertex[2].Pos.z = -(m_lengthz / 2.0f);

	m_vertex[3].Pos.x = -(m_lengthx / 2.0f);
	m_vertex[3].Pos.y = -(m_lengthy / 2.0f);
	m_vertex[3].Pos.z = -(m_lengthz / 2.0f);

	m_vertex[4].Pos.x = -(m_lengthx / 2.0f);
	m_vertex[4].Pos.y = (m_lengthy / 2.0f);
	m_vertex[4].Pos.z = (m_lengthz / 2.0f);

	m_vertex[5].Pos.x = (m_lengthx / 2.0f);
	m_vertex[5].Pos.y = (m_lengthy / 2.0f);
	m_vertex[5].Pos.z = (m_lengthz / 2.0f);

	m_vertex[6].Pos.x = (m_lengthx / 2.0f);
	m_vertex[6].Pos.y = -(m_lengthy / 2.0f);
	m_vertex[6].Pos.z = (m_lengthz / 2.0f);

	m_vertex[7].Pos.x = -(m_lengthx / 2.0f);
	m_vertex[7].Pos.y = -(m_lengthy / 2.0f);
	m_vertex[7].Pos.z = (m_lengthz / 2.0f);

}

// �`��
void CBox::Draw() {
	// ���_�o�b�t�@���Z�b�g����
	unsigned int stride = sizeof(Vertex);
	unsigned  offset = 0;

	DirectX11Manager::m_pImContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);		// �o�[�e�b�N�X�o�b�t�@���Z�b�g
	DirectX11Manager::m_pImContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);			// �C���f�b�N�X�o�b�t�@���Z�b�g
	DirectX11Manager::m_pImContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);		// �g�|���W�[���Z�b�g�i���v���~�e�B�u�^�C�v�j
	DirectX11Manager::m_pImContext->IASetInputLayout(m_pVertexLayout);									// ���_���C�A�E�g�Z�b�g

	DirectX11Manager::m_pImContext->VSSetShader(m_pVertexShader, nullptr, 0);			// ���_�V�F�[�_�[���Z�b�g
	DirectX11Manager::m_pImContext->PSSetShader(m_pPixelShader, nullptr, 0);			// �s�N�Z���V�F�[�_�[���Z�b�g

	DirectX11Manager::m_pImContext->DrawIndexed(m_facenum * 3,		// �`�悷��C���f�b�N�X���i�ʐ��~�R�j
															0,		// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
															0);		// ���_�o�b�t�@�̍ŏ�����g��
}

bool CBox::Init(
	float width,
	float height,
	float depth) {

	bool sts;

	// �a�a�n�w�T�C�Y���Z�b�g
	m_lengthx = width;
	m_lengthy = height;
	m_lengthz = depth;

	// BOX�̃C���f�b�N�X�f�[�^���쐬
	CreateIndex();

	// BOX�̒��_�f�[�^���쐬
	CreateVertex();

	// ���_�o�b�t�@�쐬
	m_pVertexBuffer = DirectX11Manager::CreateVertexBuffer(m_vertex, 8);
	// �C���f�b�N�X�o�b�t�@�쐬
	m_pIndexBuffer = DirectX11Manager::CreateIndexBuffer(m_face, 12 * 3);

	// ���_�V�F�[�_�[�𐶐�
	m_pVertexShader = DirectX11Manager::CreateVertexShader("Assets/Shaders/3DPipeLine.hlsl", "vsHit");
	// �s�N�Z���V�F�[�_�[�𐶐�
	m_pPixelShader = DirectX11Manager::CreatePixelShader("Assets/Shaders/3DPipeLine.hlsl", "psHit");

	// ���_�f�[�^�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	unsigned int numElements = ARRAYSIZE(layout);
	m_pVertexLayout = DirectX11Manager::CreateInputLayout(layout, numElements, "Assets/Shaders/3DPipeLine.hlsl", "vsHit");

	return true;
}

void CBox::Exit() {

	// �s�N�Z���V�F�[�_�[���
	if (m_pPixelShader) {
		m_pPixelShader->Release();
		m_pPixelShader = nullptr;
	}

	// ���_�V�F�[�_�[���
	if (m_pVertexShader) {
		m_pVertexShader->Release();
		m_pVertexShader = nullptr;
	}

	if (m_pVertexLayout) {
		m_pVertexLayout->Release();
		m_pVertexLayout = nullptr;
	}

	if (m_pIndexBuffer) {
		m_pIndexBuffer->Release();
		m_pIndexBuffer = nullptr;
	}

	if (m_pVertexBuffer) {
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
	}
}
#include	"CSphere.h"
// �@���x�N�g�����v�Z
// �m�[�}���C�Y
void CSphere::Normalize(XMFLOAT3 vector, XMFLOAT3& Normal) {

	DirectX::XMVECTOR v;
	v = XMLoadFloat3(&vector);			// XMFLOAT3=>XMVECTOR
	v = XMVector3Normalize(v);			// ���K��
	XMStoreFloat3(&Normal, v);			// XMVECTOR=>XMFLOAT3
}

// �C���f�b�N�X�f�[�^���쐬
void CSphere::CreateIndex() {

	// �ʐ��Z�b�g
	m_facenum = m_divY * m_divX * 2;

	m_face = new Face[m_facenum];

	Face* pface = m_face;

	// �C���f�b�N�X����
	for (unsigned int y = 0; y < m_divY; y++) {
		for (unsigned int x = 0; x < m_divX; x++) {
			int count = (m_divX + 1)*y + x;			// ������W�̃C���f�b�N�X

			// �㔼��
			pface->idx[0] = count;
			pface->idx[1] = count + 1;
			pface->idx[2] = count + 1 + (m_divX + 1);

			pface++;

			// ������
			pface->idx[0] = count;
			pface->idx[1] = count + (m_divX + 1) + 1;
			pface->idx[2] = count + (m_divX + 1);

			pface++;
		}
	}
}

// ���_�f�[�^���쐬
void CSphere::CreateVertex() {

	float azimuth = 0.0f;			// ���ʊp
	float elevation = 0.0f;			// �p

	m_vertex = new Vertex[(m_divX + 1) * (m_divY + 1)];
	Vertex* pvtx = m_vertex;

	XMFLOAT3	Normal;
	// ���ʊp�Ƌp���狅���b�V���̒��_�f�[�^���쐬
	for (unsigned int y = 0; y <= m_divY; y++) {
		elevation = (PI * (float)y) / (float)m_divY;    // �p���Z�b�g
		float r = m_radius * sinf(elevation);					// �p�ɉ��������a���v�Z

		for (unsigned int x = 0; x <= m_divX; x++) {
			azimuth = (2 * PI * (float)x) / (float)m_divX;	// ���ʊp���Z�b�g

			// ���_���W�Z�b�g
			pvtx->Pos.x = r * cosf(azimuth);
			pvtx->Pos.y = m_radius * cosf(elevation);
			pvtx->Pos.z = r * sinf(azimuth);

			// �@���x�N�g���Z�b�g
			Normalize(pvtx->Pos, Normal);		// �@�����v�Z
			pvtx->Normal = Normal;				// �@�����Z�b�g

			// ����
			pvtx++;
		}
	}
}

// �`��
void CSphere::Draw(ID3D11DeviceContext* device) {

	// ���_�o�b�t�@���Z�b�g����
	unsigned int stride = sizeof(Vertex);
	unsigned  offset = 0;
	device->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	device->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);			// �C���f�b�N�X�o�b�t�@���Z�b�g
	device->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);		// �g�|���W�[���Z�b�g�i���v���~�e�B�u�^�C�v�j
	device->IASetInputLayout(m_pVertexLayout);					// ���_���C�A�E�g�Z�b�g

	device->VSSetShader(m_pVertexShader, nullptr, 0);			// ���_�V�F�[�_�[���Z�b�g
	device->PSSetShader(m_pPixelShader, nullptr, 0);			// �s�N�Z���V�F�[�_�[���Z�b�g

	device->DrawIndexed(m_facenum * 3,		// �`�悷��C���f�b�N�X���i�ʐ��~�R�j
		0,									// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
		0);									// ���_�o�b�t�@�̍ŏ�����g��
}

bool CSphere::Init(float r,				// ���a
	int division_horizontal,			// ���������̕�����
	int division_vertical,				// ���������̕�����
	ID3D11Device* device) {
	bool sts;
	// ��������ۑ�
	m_divX = division_horizontal;
	m_divY = division_vertical;

	// ���a��ۑ�
	m_radius = r;

	// ���̃C���f�b�N�X�f�[�^���쐬
	CreateIndex();

	// ���̒��_�f�[�^���쐬
	CreateVertex();

	// ���_�o�b�t�@�쐬
	m_pVertexBuffer = DirectX11Manager::CreateVertexBuffer(m_vertex, (m_divY + 1)*(m_divX + 1));

	// �C���f�b�N�X�o�b�t�@�쐬
	m_pIndexBuffer = DirectX11Manager::CreateIndexBuffer(m_face, (m_divY)*(m_divX) * 2 * 3);

	// ���_�V�F�[�_�[�𐶐�
	m_pVertexShader = DirectX11Manager::CreateVertexShader("Assets/Shaders/3DPipeLine.hlsl", "vsHit");
	// �s�N�Z���V�F�[�_�[�𐶐�
	m_pPixelShader = DirectX11Manager::CreatePixelShader("Assets/Shaders/3DPipeLine.hlsl", "psHit");

	// ���_�f�[�^�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	unsigned int numElements = ARRAYSIZE(layout);
	m_pVertexLayout = DirectX11Manager::CreateInputLayout(layout, numElements, "Assets/Shaders/3DPipeLine.hlsl", "vsHit");


	return true;
}

void CSphere::Exit() {

	if (m_vertex) {
		delete[] m_vertex;
	}

	if (m_face) {
		delete[] m_face;
	}

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
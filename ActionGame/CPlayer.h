#pragma once
#include "GameObject.h"

class CPlayer :
	public GameObject
{
	// �A�j���[�V�����̎��
	enum PlayerAnimation {
		Idle,
		Walk,
		Run,
		Jump,
		Punch,
		Kick,
		SpinKick,
		AnimMax
	};
	// �A�j���[�V�����f�[�^�̃p�X
	const char* animData[AnimMax]
	{
		"Assets/Models/Idleanim.usab",
		"Assets/Models/WALK00_Fanim.usab",
		"Assets/Models/RUN00_Fanim.usab",
		"Assets/Models/JUMP00anim.usab",
		"Assets/Models/Jabanim.usab",
		"Assets/Models/Hikickanim.usab",
		"Assets/Models/Spinkickanim.usab",
	};

	UnityExportSkinnedModel *skinnedModel;
	uem::SkinnedAnimation animation[AnimMax];

	int		anim = CPlayer::Idle;
	float	animCnt = 0;
	bool	isJump = false;
	bool	isAttack = false;

	float			m_sensitivity = 50;		// ��]���x
	XMFLOAT2		m_beforeMouse;			// ���O�̃}�E�X���W

	void AnimUpdate();
public:
	CPlayer(CScene* scene);
	~CPlayer();
	void Update();
	void Draw();
};
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
		Gethit,
		AnimMax
	};
	// �A�j���[�V�����f�[�^�̃p�X
	const char* animData[AnimMax]
	{
		"Assets/Models/U_Idleanim.usab",
		"Assets/Models/U_WALK00_Fanim.usab",
		"Assets/Models/U_RUN00_Fanim.usab",
		"Assets/Models/U_JUMP00anim.usab",
		"Assets/Models/U_Jabanim.usab",
		"Assets/Models/U_Hikickanim.usab",
		"Assets/Models/U_Spinkickanim.usab",
		"Assets/Models/U_GetHitanim.usab",
	};

	UnityExportSkinnedModel *skinnedModel;
	uem::SkinnedAnimation animation[AnimMax];

	int		anim = CPlayer::Idle;
	float	animCnt = 0;
	bool	isJump = false;
	bool	isAttack = false;

	float			m_sensitivity = 50;		// ��]���x

	void AnimUpdate();
public:
	CPlayer(CScene* scene);
	~CPlayer();
	void Update();
	void Draw();
};
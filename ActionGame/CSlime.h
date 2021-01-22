#pragma once
#include "GameObject.h"

class CSlime :
	public GameObject
{
	// �A�j���[�V�����̎��
	enum SlimeAnimation {
		Idle,
		Walk,
		Run,
		Attack01,
		Attack02,
		GetHit,
		Die,
		AnimMax
	};
	// �A�j���[�V�����f�[�^�̃p�X
	const char* animData[AnimMax]
	{
		"Assets/Models/S_IdleBattleanim.usab",
		"Assets/Models/S_WalkFWDanim.usab",
		"Assets/Models/S_RunFWDanim.usab",
		"Assets/Models/S_Attack01anim.usab",
		"Assets/Models/S_Attack02anim.usab",
		"Assets/Models/S_GetHitanim.usab",
		"Assets/Models/S_Dieanim.usab",
	};
	// �s���̃p�^�[��
	enum SlimeAction {
		Search,
		Fight,
	};

	UnityExportSkinnedModel *skinnedModel;
	uem::SkinnedAnimation animation[AnimMax];

	int		anim = SlimeAnimation::Idle;
	int		action = SlimeAction::Search;
	float	animCnt = 0;
	bool	isAttack = false;

	void AnimUpdate();
	bool isDraw();
	void Generate();
public:
	CSlime(CScene* scene);
	~CSlime();
	void Update();
	void Draw();
};
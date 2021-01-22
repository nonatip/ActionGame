#pragma once
#include "GameObject.h"

class CBoss :
	public GameObject
{
	// �A�j���[�V�����̎��
	enum BossAnimation {
		Idle,
		Walk,
		Run,
		Attack01,
		Attack02,
		GetHit,
		Die,
		Scream,
		AnimMax
	};
	// �A�j���[�V�����f�[�^�̃p�X
	const char* animData[AnimMax]
	{
		"Assets/Models/B_Idleanim.usab",
		"Assets/Models/B_Walkanim.usab",
		"Assets/Models/B_Runanim.usab",
		"Assets/Models/B_Attack01anim.usab",
		"Assets/Models/B_Attack02anim.usab",
		"Assets/Models/B_GetHitanim.usab",
		"Assets/Models/B_Dieanim.usab",
		"Assets/Models/B_Screamanim.usab",
	};
	// �s���̃p�^�[��
	enum BossAction {
		Search,
		Fight,
	};

	UnityExportSkinnedModel *skinnedModel;
	uem::SkinnedAnimation animation[AnimMax];

	int		anim = BossAnimation::Idle;
	int		action = BossAction::Search;
	float	animCnt = 0;
	bool	isAttack = false;

	void AnimUpdate();
	bool isDraw();
	void Generate();
public:
	CBoss(CScene* scene);
	~CBoss();
	void Update();
	void Draw();
};
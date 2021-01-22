#pragma once
#include "GameObject.h"

class CTurtle :
	public GameObject
{
	// �A�j���[�V�����̎��
	enum TurtleAnimation {
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
		"Assets/Models/T_IdleBattleanim.usab",
		"Assets/Models/T_WalkFWDanim.usab",
		"Assets/Models/T_RunFWDanim.usab",
		"Assets/Models/T_Attack01anim.usab",
		"Assets/Models/T_Attack02anim.usab",
		"Assets/Models/T_GetHitanim.usab",
		"Assets/Models/T_Dieanim.usab",
	};
	// �s���̃p�^�[��
	enum TurtleAction {
		Search,
		Fight,
	};

	UnityExportSkinnedModel *skinnedModel;
	uem::SkinnedAnimation animation[AnimMax];

	int		anim = TurtleAnimation::Idle;
	int		action = TurtleAction::Search;
	float	animCnt = 0;
	bool	isAttack = false;

	void AnimUpdate();
	bool isDraw();
	void Generate();
public:
	CTurtle(CScene* scene);
	~CTurtle();
	void Update();
	void Draw();
};
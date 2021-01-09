#pragma once
#include "GameObject.h"

class CTurtle :
	public GameObject
{
	// アニメーションの種類
	enum TurtleAnimation {
		Idle,
		WalkF,
		Run,
		Attack01,
		Attack02,
		GetHit,
		Die,
		AnimMax
	};
	// アニメーションデータのパス
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

	UnityExportSkinnedModel *skinnedModel;
	uem::SkinnedAnimation animation[AnimMax];

	int		anim = CTurtle::Idle;
	float	animCnt = 0;
	bool	isJump = false;
	bool	isAttack = false;

	void AnimUpdate();
public:
	CTurtle(CScene* scene);
	~CTurtle();
	void Update();
	void Draw();
};
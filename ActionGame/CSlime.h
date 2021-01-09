#pragma once
#include "GameObject.h"

class CSlime :
	public GameObject
{
	// アニメーションの種類
	enum SlimeAnimation {
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
		"Assets/Models/S_IdleBattleanim.usab",
		"Assets/Models/S_WalkFWDanim.usab",
		"Assets/Models/S_RunFWDanim.usab",
		"Assets/Models/S_Attack01anim.usab",
		"Assets/Models/S_Attack02anim.usab",
		"Assets/Models/S_GetHitanim.usab",
		"Assets/Models/S_Dieanim.usab",
	};

	UnityExportSkinnedModel *skinnedModel;
	uem::SkinnedAnimation animation[AnimMax];

	int		anim = CSlime::Idle;
	float	animCnt = 0;
	bool	isAttack = false;

	void AnimUpdate();
public:
	CSlime(CScene* scene);
	~CSlime();
	void Update();
	void Draw();
};
#pragma once
#include "GameObject.h"

class CPlayer :
	public GameObject
{
	// アニメーションの種類
	enum PlayerAnimation {
		Idle,
		Walk,
		Run,
		Land,
		Punch,
		Kick,
		SpinKick,
		Gethit,
		Down,
		AnimMax
	};
	// アニメーションデータのパス
	const char* animData[AnimMax]
	{
		"Assets/Models/U_Idleanim.usab",
		"Assets/Models/U_WALK00_Fanim.usab",
		"Assets/Models/U_RUN00_Fanim.usab",
		"Assets/Models/U_Landanim.usab",
		"Assets/Models/U_Jabanim.usab",
		"Assets/Models/U_Hikickanim.usab",
		"Assets/Models/U_Spinkickanim.usab",
		"Assets/Models/U_GetHitanim.usab",
		"Assets/Models/U_DamageDownanim.usab",
	};

	UnityExportSkinnedModel *skinnedModel;
	uem::SkinnedAnimation animation[AnimMax];

	int		anim = PlayerAnimation::Idle;
	float	animCnt = 0;
	bool	isLand = false;
	bool	isAttack = false;
	int		comboCnt = 0;

	float	m_sensitivity = 50;

	void AnimUpdate();
public:
	CPlayer(CScene* scene);
	~CPlayer();
	void Update();
	void Draw();
};
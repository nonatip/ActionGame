#pragma once
#include "GameObject.h"

class CPlayer :
	public GameObject
{
	// �A�j���[�V�����̎��
	enum PlayerAnimation {
		Idle,
		Run,
		Jump,
		AnimMax
	};
	// �A�j���[�V�����f�[�^�̃p�X
	const char* animData[AnimMax]
	{
		"Assets/Models/SLIDE00anim.usab",
		"Assets/Models/RUN00_Fanim.usab",
		"Assets/Models/JUMP00anim.usab",
	};

	UnityExportSkinnedModel *skinnedModel;
	uem::SkinnedAnimation animation[AnimMax];

	int anim = CPlayer::Idle;
	float animCnt;
public:
	CPlayer(CScene* scene);
	~CPlayer();
	void Update();
	void Draw();
};
/*!
@file Boss.cpp
@brief �{�X����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//�@�{�X
	//--------------------------------------------------------------------------------------
	Boss::Boss(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void Boss::OnCreate() {
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.75f, 0.25f);
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(0.0f, 0.375f, -5.0f);

		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, 1.0f));

	}

	void Boss::OnUpdate() {
	}

}
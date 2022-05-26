/*!
@file Wall.cpp
@brief �J�x�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	Wall::Wall(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const int HP

	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_HP(HP)
	{}


	void Wall::OnCreate() {
		
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.2f, 0.1f, 0.06f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI * -0.5f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		
		//�I�u�W�F�N�g�̃O���[�v�𓾂�
		auto group = GetStage()->GetSharedObjectGroup(L"Wall_Group");
		//�O���[�v�Ɏ������g��ǉ�
		group->IntoGroup(GetThis<Wall>());

		//�e������
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"UNBREAKWALL_MESH");
		//�e������i�V���h�E�}�b�v��`�悷��j
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto WallHP = GetHP();
		auto ptrDraw1 = AddComponent<PNTStaticModelDraw>();
		if (WallHP >= 4)
		{
			ptrDraw1->SetMeshResource(L"UNBREAKWALL_MESH");
		}
		//�ǂ̎c��ϋv�l�ɂ��Ă̏���
		if (WallHP >= 4)
		{
			ptrDraw1->SetMeshResource(L"UNBREAKWALL_MESH");
		}
		else if (WallHP >= 3)
		{
			ptrDraw1->SetMeshResource(L"DAMAGEWALL1_MESH");
		}
		else if (WallHP >= 2)
		{
			ptrDraw1->SetMeshResource(L"DAMAGEWALL2_MESH");
		}
		else if (WallHP >= 1)
		{
			ptrDraw1->SetMeshResource(L"DAMAGEWALL3_MESH");
		}

		ptrDraw1->SetMeshToTransformMatrix(spanMat);
		//auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		/*ptrDraw->SetFogEnabled(false);
		ptrDraw->SetOwnShadowActive(true);*/

		//auto ptrDraw2 = AddComponent<BcPNTStaticDraw>();
		//ptrDraw2->SetFogEnabled(true);
		//ptrDraw2->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw2->SetOwnShadowActive(true);
		//ptrDraw2->SetTextureResource(L"WALL_TX");
		//PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		//auto PsPtr = AddComponent<RigidbodyBox>(param);
		//PsPtr->SetDrawActive(false);

		//Obb�̏Փ˔��������
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(true);
		//auto obb = ptrColl->GetObb();
		//GetStage()->SetSharedGameObject(L"Wall_Group",GetThis<Wall>());
				//�ǂݍ��݂̐ݒ������
		//GetStage()->SetSharedGameObject(L"BREAKWALL", GetThis<Wall>());
			//�ق��̃I�u�W�F�N�g�̉e�����󂯂Ȃ��i��v���C���[�ɓ��������������Ȃǂ̏����j
		ptrColl->SetFixed(true);
	}
	void Wall::OnUpdate()
	{
		m_InputHandler.PushHandle(GetThis<Wall>());

		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//B�{�^����������Ă���Ƃ�
		if (cntlVec[0].wButtons & XINPUT_GAMEPAD_B) {
			//�\��
			SetDrawActive(false);
		}
		//B�{�^����������Ă��Ȃ��Ƃ�
		else {
			SetDrawActive(true);
		}
	}


	void  Wall::OnPushB() {
	}

	//X�{�^������������
	void Wall::OnPushX()
	{
		
	}

	//�ǂɓ���������
	void Wall::OnCollisionEnter(shared_ptr<GameObject>& Other) {
				}
			
}
//end basecross

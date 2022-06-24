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
			Vec3(0.09f, 0.095f, 0.3f),  //�X�P�[��kabe
			Vec3(0.0f, 5.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),     //��]
			Vec3(-0.1f, -0.7f, 0.3f)    //�|�W�V����
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

		
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"UNBREAKWALL_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		
		//Obb�̏Փ˔��������
		auto ptrColl = AddComponent<CollisionObb>();
		
	
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
		
		
		
		auto WallHP = GetHP();
		auto ptrDraw = GetComponent<PNTStaticModelDraw>();
		
		//�ǂ̎c��ϋv�l�ɂ��Ă̏���
		if (WallHP >= 4)
		{
			ptrDraw->SetMeshResource(L"UNBREAKWALL_MESH");

		}
		else if (WallHP >= 3)
		{
			Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
			spanMat.affineTransformation(
				Vec3(1.0f, 0.3f, 0.1f),//Scale
				Vec3(0.0f, 5.0f, 0.0f),//Position
				Vec3(0.0f, 0.0f, 0.0f),//��]
				Vec3(-0.5f, -0.6f, 0.0f)//Position
			);
			ptrDraw->SetMeshResource(L"DAMAGEWALL2_MESH");
			ptrDraw->SetMeshToTransformMatrix(spanMat);
			
		}
		else if (WallHP <= 1)
		{
		
			Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
			spanMat.affineTransformation(
				Vec3(1.0f, 0.1f, 0.1f),//Scale
				Vec3(0.0f, 5.0f, 0.0f),//Position
				Vec3(0.0f,0.0f, 0.0f),//��]
				Vec3(1.0f, -0.6f, 0.0f)//Position
			);
			ptrDraw->SetMeshResource(L"DAMAGEWALL1_MESH");
			ptrDraw->SetMeshToTransformMatrix(spanMat);
		}
		else if (WallHP >= 1)
		{
			Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
			spanMat.affineTransformation(
				Vec3(1.0f, 0.1f, 0.1f),//Scale
				Vec3(0.0f, 5.0f, 0.0f),//Position
				Vec3(0.0f, 0.0f, 0.0f),//��]
				Vec3(-0.2f, -0.6f, 0.0f)//Position
			);
			ptrDraw->SetMeshResource(L"DAMAGEWALL3_MESH");
		
			ptrDraw->SetMeshToTransformMatrix(spanMat);
			
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

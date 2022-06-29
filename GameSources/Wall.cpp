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
		//�����ʒu�̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

        // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		Mat4x4 spanMat;                 
		spanMat.affineTransformation(
			Vec3(0.3f, 0.095f, 0.09f),    //�傫��
			Vec3(0.0f, 5.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),       //��]
			Vec3(-0.4f, -0.7f, 0.0f)      //�ʒu
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

		//�`��R���|�[�l���g
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();

		//���b�V���̐ݒ�
		ptrDraw->SetMeshResource(L"UNBREAKWALL_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//Obb�̏Փ˔��������
		auto ptrColl = AddComponent<CollisionObb>();

		//�ق��̃I�u�W�F�N�g�̉e�����󂯂Ȃ�
		ptrColl->SetFixed(true);
	}

	void Wall::OnUpdate()
	{
		m_InputHandler.PushHandle(GetThis<Wall>());

		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//B�{�^����������Ă���Ƃ�
		if (cntlVec[0].wButtons & XINPUT_GAMEPAD_B) {
			//�ǂ̕`��̕\�������Ȃ�
			SetDrawActive(false);
		}

		//B�{�^����������Ă��Ȃ��Ƃ�
		else {
			//�ǂ̕`��̏���������
			SetDrawActive(true);
		}
		
		auto WallHP = GetHP();                            //�ǂ�HP�擾
		auto ptrDraw = GetComponent<PNTStaticModelDraw>();//�ǂ̕`��R���|�[�l���g
		
		//�ǂ̎c��ϋv�l�ɂ��Ă̏���
		
		//HP��4��������
		if (WallHP >= 4)
		{
			ptrDraw->SetMeshResource(L"UNBREAKWALL_MESH");

		}

		//HP��3��������
		else if (WallHP >= 3)
		{
			Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
			spanMat.affineTransformation(
				Vec3(0.3f, 0.095f, 0.09f),//�傫��
				Vec3(0.0f, 5.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),   //��]
				Vec3(-0.4f, -0.7f, 0.0f)  //�ʒu
			);
			ptrDraw->SetMeshResource(L"DAMAGEWALL1_MESH");
			ptrDraw->SetMeshToTransformMatrix(spanMat);
			
		}

		//HP��2��������
		else if (WallHP >=2)
		{
		
			Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
			spanMat.affineTransformation(
				Vec3(0.3f, 0.095f, 0.09f),//�傫��
				Vec3(0.0f, 5.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),   //��]
				Vec3(-0.4f, -0.7f, 0.0f)  //�ʒu
			);
			ptrDraw->SetMeshResource(L"DAMAGEWALL2_MESH");
			ptrDraw->SetMeshToTransformMatrix(spanMat);
		}

		//HP��1��������
		else if (WallHP >= 1)
		{
			Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
			spanMat.affineTransformation(
				Vec3(0.3f, 0.095f, 0.09f),//�傫��
				Vec3(0.0f, 5.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),   //��]
				Vec3(-0.4f, -0.7f, 0.0f)  //�ʒu
			);
			ptrDraw->SetMeshResource(L"DAMAGEWALL3_MESH");
		
			ptrDraw->SetMeshToTransformMatrix(spanMat);
			
		}

	}

}
//end basecross

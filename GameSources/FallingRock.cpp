/*!
@file FallingRock.cpp
@brief ���Ύ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�\�z�Ɣj��
	FallingRock::FallingRock(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Falling(0)
	{}


	//������
	void FallingRock::OnCreate() {
		//�����ʒu�̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);



		//���f���̌����ڂ����߂�
		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.2f, 0.2f, 0.2f),//�傫��
			Vec3(0.0f, 5.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),//��]
			Vec3(0.0f, -0.5f, 0.5f)//�ʒu
		);

		//�I�u�W�F�N�g�̃O���[�v�𓾂�
		auto group3 = GetStage()->GetSharedObjectGroup(L"FallingRock_Group1");

		//�O���[�v�Ɏ������g��ǉ�
		group3->IntoGroup(GetThis < FallingRock > ());

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();

		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"IWA_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//�`��R���|�[�l���g
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();

		//���b�V���̐ݒ�
		ptrDraw->SetMeshResource(L"IWA_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		
		//�L���[�u�^�̓����蔻��
		auto Coll = AddComponent<CollisionObb>();
		
		//�ق��̃I�u�W�F�N�g�̉e�����󂯂Ȃ�
		Coll->SetFixed(true);
        
		//�ǂݍ��݂̐ݒ������
		GetStage()->SetSharedGameObject(L"FallingRock", GetThis<FallingRock>());
	}

	void FallingRock::OnUpdate()
	{
		//������ꂽ��
		if (m_Falling==1)
		{
			//�d�͂�����
			auto ptrGra = AddComponent<Gravity>();
		}
	}
}
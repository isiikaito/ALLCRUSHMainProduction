/*!
@file Obstacle1.cpp
@brief ��Q������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�\�z�Ɣj��
	Obstacle1::Obstacle1(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{}


	//������
	void Obstacle1::OnCreate() {
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

	

		//���f���̌����ڂ����߂�
		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		Mat4x4 spanMat; 
		spanMat.affineTransformation(
			Vec3(0.5f, 0.5f, 0.5f),  //�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),  //��]
			Vec3(-0.4f, -0.5f, -0.6f)//�ʒu
		);
		
		//�I�u�W�F�N�g�̃O���[�v�𓾂�
		auto group1 = GetStage()->GetSharedObjectGroup(L"Obstacle1_Group1");

		//�O���[�v�Ɏ������g��ǉ�
		group1->IntoGroup(GetThis<Obstacle1>());

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();

		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"OBSTACLE1_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//�`��R���|�[�l���g
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();

		//���b�V���̓ǂݍ���
		ptrDraw->SetMeshResource(L"OBSTACLE1_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//RigidbodyBox�̒ǉ�
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		
		//�L���[�u�^�̓����蔻��̒ǉ�
		auto Coll = AddComponent<CollisionObb>();
       
		//�ق��̃I�u�W�F�N�g�̉e�����󂯂Ȃ�
		Coll->SetFixed(true);


	}

}
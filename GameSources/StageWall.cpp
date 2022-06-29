/*!
@file StageWall.cpp
@brief�X�e�[�W�̕ǂ̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�\�z�Ɣj��
	StageWall::StageWall(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{}


	//������
	void StageWall::OnCreate() {
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		Mat4x4 spanMat; 
		spanMat.affineTransformation(
			Vec3(0.01956f, 0.02f, 0.2),//�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //��]
			Vec3(0.0f, -0.1f, -1.5f)  //�ʒu
		);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();

		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"STAGEWALL_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//�`��R���|�[�l���g
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();

		//���b�V���̓ǂݍ���
		ptrDraw->SetMeshResource(L"STAGEWALL_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//RigidbodyBox�̒ǉ�
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		
		//�L���[�u�^�̓����蔻��̒ǉ�
		auto Coll = AddComponent<CollisionObb>();
		
		//���̃I�u�W�F�N�g�̉e�����󂯂Ȃ�
		Coll->SetFixed(true);
	}
}
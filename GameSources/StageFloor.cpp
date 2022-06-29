/*!
@file StageFloor.cpp
@brief�X�e�[�W�̏�����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�\�z�Ɣj��
	StageFloor::StageFloor(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{}


	//������
	void StageFloor::OnCreate() {
		//�����ʒu�̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		//���f���̌����ڂ����߂�
		// ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		Mat4x4 spanMat; 
		spanMat.affineTransformation(
			Vec3(0.045f, 1.0f, 0.13f),//�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),   //��]
			Vec3(0.0f, 0.0f, -0.05f)  //�ʒu
		);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();

		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"STAGEFLOOR_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//�`��R���|�[�l���g
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();

		//���b�V���̐ݒ�
		ptrDraw->SetMeshResource(L"STAGEFLOOR_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//RigidbodyBox�̒ǉ�
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);

		//�L���[�u�^�̓����蔻��̒ǉ�
		auto Coll = AddComponent<CollisionObb>();

		//�ق��̃I�u�W�F�N�g�̉e�����󂯂Ȃ��i��v���C���[�ɓ��������������Ȃǂ̏����j
		Coll->SetFixed(true);
	}

}
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
		//�Փ˔���G���A�����߂�
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		//���f���ƏՓ˔�������킹�Ȃ���΂Ȃ�Ȃ�

		//���f���̌����ڂ����߂�
		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.045f, 1.0f, 0.13f),//�X�P�[��yuka
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),//��]
			Vec3(0.0f, 0.0f, -0.05f)//�|�W�V����yuka
		);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"STAGEFLOOR_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();

		ptrDraw->SetMeshResource(L"STAGEFLOOR_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		//RigidbodyBox�̒ǉ�
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		//�����蔻���������
		/*PsPtr->SetDrawActive(true);*/

		auto Coll = AddComponent<CollisionObb>();

		Coll->SetFixed(true);


	}

}
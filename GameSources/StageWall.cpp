/**
*@file StageWall.cpp
*@brief �X�e�[�W�̕ǂ̎��̂���������Ă���\�[�X�t�@�C��
*@author Kaito Isii
*@details �X�e�[�W�̕ǂ̎��̂̎���
*/

#include "stdafx.h"
#include "Project.h"

/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross {
	//!�p�����[�^�̏�����
	StageWall::StageWall(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{}

	void StageWall::OnCreate() {
		//!�����ʒu�Ȃǂ̐ݒ�

		//!�Փ˔���̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!�傫��
		ptrTrans->SetRotation(m_Rotation);//!��]
		ptrTrans->SetPosition(m_Position);//!�ʒu

		//!���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		Mat4x4 spanMat; 
		spanMat.affineTransformation(
			Vec3(0.01956f, 0.02f, 0.2), //!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),     //!��]
			Vec3(0.0f, -0.1f, -1.5f)    //!�ʒu
		);

		
		auto ptrShadow = AddComponent<Shadowmap>();//!�e������i�V���h�E�}�b�v��`�悷��j
        auto Coll = AddComponent<CollisionObb>();//!�L���[�u�^�̓����蔻��̒ǉ�
		Coll->SetFixed(true);//!���̃I�u�W�F�N�g�̉e�����󂯂Ȃ�
        auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g

		//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"STAGEWALL_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//!���b�V���̓ǂݍ���
		ptrDraw->SetMeshResource(L"STAGEWALL_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//!RigidbodyBox�̒ǉ�
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		
	}
}
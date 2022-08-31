/**
*@file Trap.cpp
*@brief�g���b�v����������Ă���\�[�X�t�@�C��
*@author Kaito Isii
*@details �g���b�v�̎��̂̎���
*/

#include "stdafx.h"
#include "Project.h"

/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross {
	//!�p�����[�^�̏�����
	Trap::Trap(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{}



	void Trap::OnCreate() {
		//!�����ʒu�Ȃǂ̐ݒ�

		//!�Փ˔���̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!�傫��
		ptrTrans->SetRotation(m_Rotation);//!��]
		ptrTrans->SetPosition(m_Position);//!�ʒu

		//!���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.3f, 0.07f, 0.07f),//!�傫��
			Vec3(0.0f, 5.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f), //!��]
			Vec3(-0.4f, -0.55f, -0.09f) //!�ʒu

		);

		auto ptrShadow = AddComponent<Shadowmap>();       //!�e������i�V���h�E�}�b�v��`�悷��j
		auto Coll = AddComponent<CollisionObb>();         //!�L���[�u�^�̓����蔻��
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();//!�`��R���|�[�l���g
		Coll->SetFixed(true);                             //!���̃I�u�W�F�N�g�̉e�����󂯂Ȃ�

		//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"KUMONOSU_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//!���b�V���̐ݒ�
		ptrDraw->SetMeshResource(L"KUMONOSU_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//!RigidbodyBox�̒ǉ�
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);

	}

}
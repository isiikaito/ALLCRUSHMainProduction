/**
*@file Obstacle1.cpp
*@brief ��Q���I�u�W�F�N�g����������Ă���\�[�X�t�@�C��
*@author Kaito Isii
*@details ��Q���I�u�W�F�N�g�̎���
*/
#include "stdafx.h"
#include "Project.h"

/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross {
	//!�p�����[�^�̏�����
	Obstacle1::Obstacle1(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{}


	
	void Obstacle1::OnCreate() {
		//!�����ʒu�Ȃǂ̐ݒ�

		//!�Փ˔���̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		//!���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		Mat4x4 spanMat; 
		spanMat.affineTransformation(
			Vec3(0.5f, 0.5f, 0.5f),  //!�傫��
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),  //!��]
			Vec3(-0.4f, -0.5f, -0.6f)//!�ʒu
		);
		
		
		auto group1 = GetStage()->GetSharedObjectGroup(L"Obstacle1_Group1");//!�I�u�W�F�N�g�̃O���[�v�𓾂�
		group1->IntoGroup(GetThis<Obstacle1>());                            //!�O���[�v�Ɏ������g��ǉ�
		auto ptrShadow = AddComponent<Shadowmap>();                         //!�e������i�V���h�E�}�b�v��`�悷��j
        auto ptrDraw = AddComponent<PNTStaticModelDraw>();                  //!�`��R���|�[�l���g
        auto Coll = AddComponent<CollisionObb>();                           //!�L���[�u�^�̓����蔻��̒ǉ�
		Coll->SetFixed(true);                                               //!�ق��̃I�u�W�F�N�g�̉e�����󂯂Ȃ�

		//!�e�̌`�i���b�V���j��ݒ� 
		ptrShadow->SetMeshResource(L"OBSTACLE1_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//!���b�V���̓ǂݍ���
		ptrDraw->SetMeshResource(L"OBSTACLE1_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//!RigidbodyBox�̒ǉ�
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
	}

}
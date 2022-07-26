/**
*@file FallingRock.cpp
*@brief���Ύ��̂���������Ă���\�[�X�t�@�C��
*@author Kaito Isii
*@details ���Ύ��̂̎���
*/

#include "stdafx.h"
#include "Project.h"

/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross {
	//!�p�����[�^�̏�����
	FallingRock::FallingRock(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Falling(0)
	{}


	
	void FallingRock::OnCreate() {
		//!�����ʒu�Ȃǂ̐ݒ�
		
		//!�Փ˔���̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);      //!�傫��
		ptrTrans->SetRotation(m_Rotation);//!��]
		ptrTrans->SetPosition(m_Position);//!�ʒu

		//!���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		Mat4x4 spanMat; 
		spanMat.affineTransformation(
			Vec3(0.2f, 0.2f, 0.2f),//!�傫��
			Vec3(0.0f, 5.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),//!��]
			Vec3(0.0f, -0.5f, 0.5f)//!�ʒu
		);

		
		auto group3 = GetStage()->GetSharedObjectGroup(L"FallingRock_Group1");  //!�I�u�W�F�N�g�̃O���[�v�𓾂�
        group3->IntoGroup(GetThis < FallingRock > ());                          //!�O���[�v�Ɏ������g��ǉ�
		auto ptrShadow = AddComponent<Shadowmap>();                             //!�e������i�V���h�E�}�b�v��`�悷��j
		auto Coll = AddComponent<CollisionObb>();                               //!�L���[�u�^�̓����蔻��
		Coll->SetFixed(true);                                                   //!�ق��̃I�u�W�F�N�g�̉e�����󂯂Ȃ�
		GetStage()->SetSharedGameObject(L"FallingRock", GetThis<FallingRock>());//!�ǂݍ��݂̐ݒ������
        auto ptrDraw = AddComponent<PNTStaticModelDraw>();                      //!�`��R���|�[�l���g
		
		//!�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"IWA_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//!���b�V���̐ݒ�
		ptrDraw->SetMeshResource(L"IWA_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		
	}

	void FallingRock::OnUpdate()
	{
		//!������ꂽ��
		if (m_Falling==1)
		{
			auto ptrGra = AddComponent<Gravity>();//!�d�͂�����
		}
	}
}
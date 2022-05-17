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
		//�Փ˔���G���A�����߂�
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);



		//���f���̌����ڂ����߂�
		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.2f, 0.3f, 0.3f),//�X�P�[��
			Vec3(0.0f, 5.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),//��]
			Vec3(0.0f, -0.5f, -0.7f)//�|�W�V����
		);

		

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"IWA_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();

		ptrDraw->SetMeshResource(L"IWA_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		//RigidbodyBox�̒ǉ�
		/*PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);*/
		////�����蔻���������
		//PsPtr->SetDrawActive(true);

		auto Coll = AddComponent<CollisionObb>();
		
		//�Փ˔����\��
		Coll->SetDrawActive(true);
		//�ق��̃I�u�W�F�N�g�̉e�����󂯂Ȃ��i��v���C���[�ɓ��������������Ȃǂ̏����j
		Coll->SetFixed(true);
        
		//�ǂݍ��݂̐ݒ������
		GetStage()->SetSharedGameObject(L"FallingRock", GetThis<FallingRock>());
	}

	void FallingRock::OnUpdate()
	{
		if (m_Falling==1)
		{
			//�d�͂�����
			auto ptrGra = AddComponent<Gravity>();
		}

	}

	
		
}
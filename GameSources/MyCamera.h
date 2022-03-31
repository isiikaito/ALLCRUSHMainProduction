#pragma once
#include "stdafx.h"

namespace basecross {

	class MyCamera : public Camera
	{
		float angleY; // Y�����S�̉�荞�݁i���W�A���p�j
		float distance; // �����Ώۂ���̋���

		weak_ptr<GameObject> m_TargetObject;	//�ڕW�ƂȂ�I�u�W�F�N�g
		bsm::Vec3 m_TargetToAt;	//�ڕW���王�_�𒲐�����ʒu�x�N�g��
		float m_ToTargetLerp;	//�ڕW��ǂ�������ۂ̕�Ԓl

	public:
		void SetTargetObject(const shared_ptr<GameObject>& Obj);

		shared_ptr<GameObject> GetTargetObject() const;
		float GetToTargetLerp() const;
		void SetToTargetLerp(float f);

		MyCamera()
			: angleY(0.0f), distance(10.0f)
		{
			//void SetTargetObject(const shared_ptr<GameObject>&Obj);
			//weak_ptr<GameObject> m_TargetObject;	//�ڕW�ƂȂ�I�u�W�F�N�g
			//float m_ToTargetLerp;	//�ڕW��ǂ�������ۂ̕�Ԓl
			//void SetToTargetLerp(float f);

		}

		void OnUpdate() override;

		float GetAngleY() const
		{
			return angleY;
		}

	};
	class ObjCamera : public Camera {
		weak_ptr<GameObject> m_TargetObject;	//�ڕW�ƂȂ�I�u�W�F�N�g
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		ObjCamera();
		//--------------------------------------------------------------------------------------
/*!
@brief	�f�X�g���N�^
*/
//--------------------------------------------------------------------------------------
		virtual ~ObjCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�J�����̖ڕW�I�u�W�F�N�g��ݒ肷��
		@param[in]	Obj	�J�����̖ڕW�I�u�W�F�N�g
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void SetTargetObject(const shared_ptr<GameObject>& Obj);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;

	};

}
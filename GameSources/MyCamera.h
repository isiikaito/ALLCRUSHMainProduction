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
		float PPdistance;
		float m_TurnTime;
		float m_Turn;
	public:
		void SetTargetObject(const shared_ptr<GameObject>& Obj);

		shared_ptr<GameObject> GetTargetObject() const;
		float GetToTargetLerp() const;
		void SetToTargetLerp(float f);
		//B�{�^���J�����̕ύX
		void OnPushB();


		MyCamera()
			: angleY(0.0f), distance(5.0f)
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
}
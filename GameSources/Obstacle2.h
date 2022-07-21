/**
*@file Obstacle2.h
*@brief ��Q���I�u�W�F�N�g�̎�������`����Ă���w�b�_�[�t�@�C��
*@author Kaito Isii
*@details ��Q���I�u�W�F�N�g�̎���
*/
#pragma once
#include "stdafx.h"

/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross {

	class Obstacle2 : public GameObject {
		Vec3 m_Scale;    //!�傫��
		Vec3 m_Rotation; //!��]
		Vec3 m_Position; //!�ʒu
	public:
		/**
	    * �R���X�g���N�^
	    */
		Obstacle2(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
�@�@�@�@* �f�X�g���N�^
�@�@�@�@*/
		virtual ~Obstacle2() {}

		/**
		* ��Q���I�u�W�F�N�g�̏����p�����[�^������������֐�
		*/
		virtual void OnCreate() override;

	};
}

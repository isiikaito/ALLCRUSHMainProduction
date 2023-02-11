/**
*@file Trap.h
*@brief�g���b�v����`����Ă���w�b�_�[�t�@�C��
*@author Kaito Isii
*@details �g���b�v�̎���
*/

#pragma once
#include "stdafx.h"

/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross {

	class Trap : public GameObject {
		Vec3 m_Scale;   //!�傫��
		Vec3 m_Rotation;//!��]
		Vec3 m_Position;//!�ʒu
	public:

		/**
		* �R���X�g���N�^
		*/
		Trap(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
�@�@�@�@* �f�X�g���N�^
�@�@�@�@*/
		virtual ~Trap() {}

		/**
		* �o���̕ǂ̏����p�����[�^������������֐�
		*/
		virtual void OnCreate() override;

	};
}

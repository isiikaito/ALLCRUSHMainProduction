/**
*@file StageWall.h
*@brief �X�e�[�W�̕ǂ̎�������`����Ă���w�b�_�[�t�@�C��
*@author Kaito Isii
*@details �X�e�[�W�̕ǂ̎���
*/

#pragma once
#include "stdafx.h"

/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross {

	class StageWall : public GameObject {
		Vec3 m_Scale;   //!�傫��
		Vec3 m_Rotation;//!��]
		Vec3 m_Position;//!�ʒu
	public:
		/**
		* �R���X�g���N�^
		*/
		StageWall(const shared_ptr<Stage>& StagePtr, const Vec3& Scale,const Vec3& Rotation,const Vec3& Position);

		/**
�@�@�@�@* �f�X�g���N�^
�@�@�@�@*/
		virtual ~StageWall() {}
		
		/**
		* �X�e�[�W�̕ǂ̏����p�����[�^������������֐�
		*/
		virtual void OnCreate() override;

	};
}


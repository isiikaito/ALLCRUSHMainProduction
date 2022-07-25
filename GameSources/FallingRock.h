/**
*@file FallingRock.h
*@brief ���΃I�u�W�F�N�g�̎�������`����Ă���w�b�_�[�t�@�C��
*@author Kaito Isii
*@details ���΃I�u�W�F�N�g�̎���
*/
#pragma once
#include "stdafx.h"

/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross {

	class FallingRock : public GameObject {
		Vec3 m_Scale;    //!�傫��
		Vec3 m_Rotation; //!��]
		Vec3 m_Position; //!�ʒu
		int m_Falling;   //!�����j�󂳂ꂽ���ǂ���
	public:

		/**
		* �R���X�g���N�^
		*/
		FallingRock(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

        /**
�@�@�@�@* �f�X�g���N�^
�@�@�@�@*/
		virtual ~FallingRock() {}

		
		/**
		* ���΃I�u�W�F�N�g�̏����p�����[�^������������֐�
		*/
		virtual void OnCreate() override;

		/**
		* ���I�u�W�F�N�g���j�󂳂ꂽ�Ƃ��ɗ��΂�������֐�
		*/
		virtual void OnUpdate() override;
		
		/**
         * ���I�u�W�F�N�g���j�󂳂ꂽ���ǂ���
         * @return int ���I�u�W�F�N�g���X�e�[�W��ɑ��݂��邩�ǂ������Ԃ��Ă���
         */
		int GetFalling()const {
			return m_Falling;
		}

		/**
		 * ���I�u�W�F�N�g���j�󂳂ꂽ���ǂ���
		 * @param[in] int  Falling �X�e�[�W��Ŕj�󂳂�t���ǂ���
		 */
		void SetFalling(int Falling) {
			m_Falling = Falling;
		}
	};
}

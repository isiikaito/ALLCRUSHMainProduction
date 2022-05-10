/*!
@file GameOverStage.h
@brief �Q�[���I�[�o�[�X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���I�[�o�[�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameOverStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();

		//���̓n���h���[
		InputHandler2<GameOverStage> m_InputHandler;

	public:
		//�\�z�Ɣj��
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		//���̓C�x���g�ɉ�������֐�
		void OnPushB();
		void OnPushX(){}
		//�\���L�[��
		void OnPushUP() {}
		//�\���L�[��
		void OnPushDOUN() {}
	};
}
//end namespace basecross



/*!
@file ClearStage.h
@brief �Q�[���N���A�X�e�[�W
*/



#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�N���A�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class ClearStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();

		//���̓n���h���[
		InputHandler2<ClearStage> m_InputHandler;

	public:
		//�\�z�Ɣj��
		ClearStage() :Stage() {}
		virtual ~ClearStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		//���̓C�x���g�ɉ�������֐�
		void OnPushA(){}
		void OnPushB();
		void OnPushX(){}
		//�\���L�[��
		void OnPushUP() {}
		//�\���L�[��
		void OnPushDOWN() {}
	};
}
//end namespace basecross



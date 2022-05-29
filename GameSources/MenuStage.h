/*!
@file menuStage.h
@brief ���j���[�X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���j���[�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class MenuStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();

		//Stage1�X�v���C�g�쐬
		void CreateMenuSprite1();
		//Stage2�v���C�g�쐬
		void CreateMenuSprite2();

		void CerateFadeOutBlack1();
		//���̓n���h���[
		InputHandler2<MenuStage> m_InputHandler;
		float m_idleTime;
		int num = 0;


	public:
		
		//�\�z�Ɣj��
		MenuStage() :Stage() {}
		virtual ~MenuStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		//���̓C�x���g�ɉ�������֐�
		void OnPushB();
		void OnPushX() {}
		//Y�{�^��
		void OnPushY() {}
		//�\���L�[��
		void OnPushUP();
		//�\���L�[��
		void OnPushDOWN();
	};
}
//end namespace basecross

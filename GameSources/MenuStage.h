/*!
@file MenuStage.h
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
		
		//B�{�^���������Ă��邩
		bool m_OnPushB = true;
		//���̓n���h���[
		InputHandler2<MenuStage> m_InputHandler;

		float m_idleTime;
		int StageNum ;
		bool  OnPushBCheck = false;
		bool  OnPushBCheck1 = false;


	public:
		
		//�\�z�Ɣj��
		MenuStage() :Stage() , m_idleTime(0.0f),StageNum(1){}
		virtual ~MenuStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		//�X�e�[�W�I��
		void SelectStage();
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

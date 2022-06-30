/*!
@file TitleStage.h
@brief �^�C�g���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�^�C�g���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
	
		bool  OnPushBCheck; //B�{�^���̔���1
		bool  OnPushBCheck1;//B�{�^���̔���2
		bool m_OnPushB;     //B�{�^���������ꂽ���ǂ���
		//���̓n���h���[
		InputHandler2<TitleStage> m_InputHandler;

	public:
		//�\�z�Ɣj��
		TitleStage() :Stage(),
			OnPushBCheck(false),
			OnPushBCheck1(false),
			m_OnPushB(true)
		{}
		virtual ~TitleStage() {}


		virtual void OnCreate()override;//������
		virtual void OnUpdate()override;//�X�V
		//���̓C�x���g�ɉ�������֐�
		void OnPushX() {}               //�R���g���[���[�̃{�^������X
		void OnPushUP() {}              //�R���g���[���[�̃{�^������\���L�[��
		void OnPushDOWN(){}             //�R���g���[���[�̃{�^������\���L�[��
		void OnPushY() {}               //�R���g���[���[�̃{�^������Y
		void OnPushB();                 //�R���g���[���[�̃{�^������B
	};
}
//end namespace basecross

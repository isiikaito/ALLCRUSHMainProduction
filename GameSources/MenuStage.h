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
		
		void CreateViewLight();  //�r���[�̍쐬
		void CreateMenuSprite1();//Stage1�X�v���C�g�쐬
		void CreateMenuSprite2();//Stage2�v���C�g�쐬

       float m_idleTime;    //����
		bool m_OnPushB;     //B�{�^���������Ă��邩
		bool OnPushBCheck;  //B�{�^���̔���
		bool OnPushBCheck1; //B�{�^���̔���
		int m_UPlimit;      //�X�e�[�W�I���̏��(��)
		int m_DOWNlimit;    //�X�e�[�W���(��)
        int StageNum ;      //�X�e�[�W�̔ԍ�

		InputHandler2<MenuStage> m_InputHandler;//���̓n���h���[

	public:
		
		//�\�z�Ɣj��
		MenuStage() :Stage() ,
			OnPushBCheck(false),
			OnPushBCheck1(false),
			m_OnPushB(true),
			m_idleTime(0.0f),
			StageNum(0),
		    m_UPlimit(0),
		    m_DOWNlimit(1){}
			
		virtual ~MenuStage() {}
		
		virtual void OnCreate()override;//������
		virtual void OnUpdate()override;//�X�V
		void StageSprite1();            //�X�e�[�W�X�v���C�g1�̏���
		void StageSprite2();            //�X�e�[�W�X�v���C�g2�̏���
		void SelectStage();             //�X�e�[�W�I��
		void OnPushX() {}               //�R���g���[���[�̃{�^������X
		void OnPushA() {}               //�R���g���[���[�̃{�^������A
		void OnPushUP();                //�R���g���[���[�̃{�^������\���L�[��
		void OnPushDOWN();              //�R���g���[���[�̃{�^������\���L�[��
		void OnPushY() {}               //�R���g���[���[�̃{�^������Y
		void OnPushB();                 //�R���g���[���[�̃{�^������B
	};
}
//end namespace basecross

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
	
		int SceneCountbakc;
		bool  OnPushBCheck = false;
		bool  OnPushBCheck1 = false;
		bool m_OnPushB=true;
		//���̓n���h���[
		InputHandler2<TitleStage> m_InputHandler;

	public:
		//�\�z�Ɣj��
		TitleStage() :Stage(),SceneCountbakc(0) {}
		virtual ~TitleStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		//���̓C�x���g�ɉ�������֐�
		void OnPushB();
		void OnPushX(){}
		void OnPushY(){}
		void OnPushUP() {}
		void OnPushDOWN() {}

		
	};
}
//end namespace basecross

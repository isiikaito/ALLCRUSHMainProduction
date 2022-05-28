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
		void CerateFadeOutBlack();
		int SceneCountbakc;
		//���̓n���h���[
		InputHandler2<TitleStage> m_InputHandler;

	public:
		//�\�z�Ɣj��
		TitleStage() :Stage() {}
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

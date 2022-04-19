/*!
@file MyMovieStage.h
@brief  Q [   X e [ W
*/

#pragma once
#include "stdafx.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���[�r�[�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class MyMovieStage : public MovieStage {
		//���̓n���h���[
		InputHandler<MyMovieStage> m_InputHandler;
	public:
		//�\�z�Ɣj��
		MyMovieStage() :MovieStage() {}
		virtual ~MyMovieStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		//A�{�^��
		void OnPushA();
		//B�{�^��
		void OnPushB();
	};
}
//end namespace basecross
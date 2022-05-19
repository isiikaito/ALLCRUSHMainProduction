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
	class MyClearStage : public MovieStage {
		//���̓n���h���[
		InputHandler<MyMovieStage> m_InputHandler;
		float MovieTime = 0.0f;
	public:
		//�\�z�Ɣj��
		MyClearStage() :MovieStage() {}
		virtual ~MyClearStage() {}
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


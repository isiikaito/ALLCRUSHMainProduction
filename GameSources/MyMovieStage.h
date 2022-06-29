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
		float MovieTime;
		float m_Time;
	public:
		//�\�z�Ɣj��
		MyMovieStage() :MovieStage(),
		MovieTime(43.6f),
		m_Time(0.0f){}
		virtual ~MyMovieStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
	};
}
//end namespace basecross

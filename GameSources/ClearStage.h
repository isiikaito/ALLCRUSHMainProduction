/*!
@file ClearStage.h
@brief �Q�[���N���A�X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class ClearStage : public Stage {

		//�r���[�̍쐬
		void CreateViewLight();

	public:
		//�\�z�Ɣj��
		ClearStage() :Stage() {}
		virtual ~ClearStage() {}
		//������
		virtual void OnCreate()override;

	};
}
//end namespace basecross


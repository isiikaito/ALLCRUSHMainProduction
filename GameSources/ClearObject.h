/*!
@file ClearObject.h
@brief �Q�[���N���A�I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ClearObject : public GameObject {
	public:
		//�\�z�Ɣj��
		//�R���X�g���N�^
		ClearObject(const shared_ptr<Stage>& StagePtr);
		//�f�X�g���N�^
		virtual ~ClearObject() {}
		virtual void OnCreate() override;
	};


}
//end namespace basecross


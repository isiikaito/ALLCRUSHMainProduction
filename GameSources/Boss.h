/*!
@file Bos.h
@brief �{�X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Boss : public GameObject {
	public:
		Boss(const shared_ptr<Stage>& StagePtr);
		virtual ~Boss() {}
		//�A�N�Z�T
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
	};
}
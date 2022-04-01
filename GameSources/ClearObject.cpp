/*!
@file ClearObject.cpp
@brief �N���A��m�点��I�u�W�F�N�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�N���A��m�点��I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	ClearObject::ClearObject(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void ClearObject::OnCreate() {
		//�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"�N���A");
		ptrString->SetTextRect(Rect2D<float>(300.0f, 64.0f, 640.0f, 480.0f));
	}



}
//endnamespace basecross
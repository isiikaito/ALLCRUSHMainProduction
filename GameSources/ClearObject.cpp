/*!
@file ClearObject.cpp
@brief クリアを知らせるオブジェクト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	クリアを知らせるオブジェクト
	//--------------------------------------------------------------------------------------
	ClearObject::ClearObject(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void ClearObject::OnCreate() {
		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"クリア");
		ptrString->SetTextRect(Rect2D<float>(300.0f, 64.0f, 640.0f, 480.0f));
	}



}
//endnamespace basecross
/*!
@file ProjectBehavior.h
@brief プロジェク定義の行動クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	コントローラのボタンのハンドラ
	//--------------------------------------------------------------------------------------
	template<typename T>
	struct InputHandler {
		void PushHandle(const shared_ptr<T>& Obj) {
			////キーボードの取得（優先）
			//const auto& KeyState = App::GetApp()->GetInputDevice().GetKeyState();
			//if (KeyState.m_bPressedKeyTbl[VK_SPACE]) {
			//	Obj->OnPushA();
			//	return;
			//}
			//if (KeyState.m_bPressedKeyTbl['B']) {
			//	Obj->OnPushB();
			//	return;
			//}
			//コントローラの取得
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				////Aボタン
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
					Obj->OnPushA();
				}
				//Bボタン
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
					Obj->OnPushB();
				}
				
			}
		}
	};

	template<typename T>
	struct InputHandler2 {
		void PushHandle(const shared_ptr<T>& Obj) {
			//コントローラの取得
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				//Bボタン
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
					Obj->OnPushB();
				}
				//Xボタン
				 if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) {
					Obj->OnPushX();
				}
				 //十字キーの上
				 if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_UP) {
					Obj->OnPushUP();
				}
				 //十字キーの下
				 if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
					 Obj->OnPushDOWN();
				 }
			}
		}
	};

}

//end basecross
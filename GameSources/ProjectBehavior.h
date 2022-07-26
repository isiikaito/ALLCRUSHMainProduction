/*!
@file ProjectBehavior.h
@brief �v���W�F�N��`�̍s���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�R���g���[���̃{�^���̃n���h��
	//--------------------------------------------------------------------------------------
	template<typename T>
	struct InputHandler {
		void PushHandle(const shared_ptr<T>& Obj) {
			//�R���g���[���̎擾
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				//A�{�^��
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
					Obj->OnPushA();
				}			
			}
		}
	};

	template<typename T>
	struct InputHandler2 {
		void PushHandle(const shared_ptr<T>& Obj) {
			//�R���g���[���̎擾
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				//B�{�^��
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
					Obj->OnPushB();
				}
				//X�{�^��
				 if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) {
					Obj->OnPushX();
				}
				 //Y�{�^��
				 if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y) {
					 Obj->OnPushY();
				 }
				 //�\���L�[�̏�
				 if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_UP) {
					Obj->OnPushUP();
				}
				 //�\���L�[�̉�
				 if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
					 Obj->OnPushDOWN();
				 }
			}
		}
	};

	template<typename T>
	struct ResetHandler {
		void ResetHandle(const shared_ptr<T>& Obj) {
			//�R���g���[���̎擾
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				//���Z�b�g�R�}���h
				if ((cntlVec[0].wButtons & XINPUT_GAMEPAD_START) && (cntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
					&&(cntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER))
				{
					Obj->OnPushReset();
				}
				//�X�L�b�v�R�}���h
				if (cntlVec[0].wButtons & XINPUT_GAMEPAD_START) {
					Obj->OnPushSkip();
				}
			}
		}
	};
}

//end basecross
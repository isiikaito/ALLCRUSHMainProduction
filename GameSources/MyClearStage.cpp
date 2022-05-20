/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���[�r�[�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	//������
	void MyClearStage::OnCreate() {
		MovieStage::OnCreate();
		wstring dataDir;
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		App::GetApp()->GetAssetsDirectory(dataDir);
		wstring strMovie = dataDir + L"GameClear1.mp4";
		SetMovieFileName(strMovie);
		//�Đ�
		Play();
	}

	void MyClearStage::OnUpdate() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		//m_InputHandler.PushHandle(GetThis<MyClearStage>());
		auto elps = App::GetApp()->GetElapsedTime();
		MovieTime += elps;
		if (MovieTime >= 19.0f) {
			SetAutoRepeat(true);
			PostEvent(0.0f, GetThis<ObjectInterface>(),
				App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			return;
		}

	}


	//A�{�^��
	void MyClearStage::OnPushA() {
		//�������Ȃ�
	}
	//B�{�^��
	void MyClearStage::OnPushB() {
		//�Q�[���X�e�[�W�Ɉڍs
		//PostEvent(0.0f, GetThis<ObjectInterface>(),
		//	App::GetApp()->GetScene<Scene>(), L"ToGameStage");
	}
}
//end basecross

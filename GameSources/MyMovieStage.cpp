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
	void MyMovieStage::OnCreate() {
		MovieStage::OnCreate();
		wstring dataDir;
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		App::GetApp()->GetAssetsDirectory(dataDir);
		wstring strMovie = dataDir + L"kari.mp4";
		SetMovieFileName(strMovie);
		//�Đ�
		Play();
	}

	void MyMovieStage::OnUpdate() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<MyMovieStage>());
	}

	//A�{�^��
	void MyMovieStage::OnPushA() {
		//�������Ȃ�
	}
	//B�{�^��
	void MyMovieStage::OnPushB() {
		//�Q�[���X�e�[�W�Ɉڍs
		PostEvent(0.0f, GetThis<ObjectInterface>(),
			App::GetApp()->GetScene<Scene>(), L"ToGameStage");
	}
}
//end basecross

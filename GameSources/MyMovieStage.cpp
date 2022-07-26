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
		wstring strMovie = dataDir + L"BOSU WALK TRUE.mp4";
		SetMovieFileName(strMovie);
		//�Đ�
		Play();
	}

	void MyMovieStage::OnUpdate() {
		ResetHandler.ResetHandle(GetThis<MyMovieStage>());//�R���g���[���[�̃`�F�b�N
		auto elps = App::GetApp()->GetElapsedTime();
		m_Time += elps;
		//���掞�Ԃ̐ݒ�
		if (m_Time >= MovieTime) {
			SetAutoRepeat(false);
			//�V�[���̐؂�ւ�
			PostEvent(0.0f, GetThis<ObjectInterface>(),
				App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			return;
		}

	}
	void MyMovieStage::OnPushSkip()
	{
		MovieSkip();
	}
	void MyMovieStage::MovieSkip()
	{
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
	}
}
//end basecross

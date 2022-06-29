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
		auto elps = App::GetApp()->GetElapsedTime();
		m_Time += elps;
		//����̎��Ԓ���
		if ( m_Time>= MovieTime) {
			SetAutoRepeat(true);
			//�V�[���̐؂�ւ�
			PostEvent(0.0f, GetThis<ObjectInterface>(),
				App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			return;
		}

	}


	
}
//end basecross

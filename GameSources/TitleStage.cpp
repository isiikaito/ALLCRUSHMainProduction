/*!
@file TitleStage.cpp
@brief �^�C�g���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�^�C�g���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight() {

		auto ptrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto ptrCamera = ObjectFactory::Create<Camera>();
		ptrView->SetCamera(ptrCamera);

		//�}���`���C�g�̍쐬
		auto ptrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		ptrMultiLight->SetDefaultLighting();
	}

	
	//������
	void TitleStage::OnCreate() {
		CreateViewLight();
		AddGameObject<TitleSprite>(L"TITLLE_TX", false,
			Vec2(256.0f, 64.0f), Vec2(0.0f, 100.0f));

	
		
	}
	//�X�V
	void TitleStage::OnUpdate() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<TitleStage>());
		if (OnPushBCheck) {
			if (!OnPushBCheck1)
			{
			auto WalkSound = App::GetApp()->GetXAudio2Manager();
			WalkSound->Start(L"WalkSound", 0, 0.5f);
			OnPushBCheck1 = true;
			}			
		}
		
	}
	void TitleStage::OnPushB() {	

		if (m_OnPushB)
		{
			//�t�F�[�h�A�E�g�̍쐬
			AddGameObject<FadeOut>( true,
				Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f,0.0f));
			PostEvent(XM_PI / 2, GetThis<TitleStage>(), App::GetApp()->GetScene<Scene>(), L"ToMenuStage");
			m_OnPushB = false;
		}
	
			OnPushBCheck = true;
	}
	
}

//end namespace basecross
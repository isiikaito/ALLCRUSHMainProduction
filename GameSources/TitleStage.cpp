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

	void TitleStage::CerateFadeOutBlack()
	{		
		AddGameObject<FadeOutBlack>(true,
			Vec2(1300.0f, 800.0f), Vec3(0.0f, 0.0f, 0.0f));
		
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
		
		
	}
	void TitleStage::OnPushB() {	
		auto WalkSound = App::GetApp()->GetXAudio2Manager();
		WalkSound->Start(L"WalkSound", 0, 0.5f);

			CerateFadeOutBlack();
	}
}

//end namespace basecross
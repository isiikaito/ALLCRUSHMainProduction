/*!
@file GameOverStage.cpp
@brief �Q�[���I�[�o�[�X�e�[�W
*/



#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�^�C�g���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameOverStage::CreateViewLight() {

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
	void GameOverStage::OnCreate() {
		CreateViewLight();
		AddGameObject<GameOverSprite>(L"GAMEOVER_TX", false,
			Vec2(1300.0f, 800.0f), Vec2(0.0f, 0.0f));
	}
	////�X�V
	//void GameOverStage::OnUpdate() {
	//	//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
	//	m_InputHandler.PushHandle(GetThis<GameOverStage>());

	//}
	/*void GameOverStage::OnPushB() {
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");

	}*/
}

//end namespace basecross
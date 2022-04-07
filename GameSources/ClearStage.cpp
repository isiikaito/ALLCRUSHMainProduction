/*!
@file ClearStage.cpp
@brief �N���A�X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�N���A�X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void ClearStage::CreateViewLight() {

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
	void ClearStage::OnCreate() {
		CreateViewLight();
		AddGameObject<ClearSprite>(L"GAMECREA_TX", false,
			Vec2(1300.0f, 800.0f), Vec2(0.0f, 0.0f));
	}
	//�X�V
	void ClearStage::OnUpdate() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<ClearStage>());

	}
	void ClearStage::OnPushB() {
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");

	}
}

//end namespace basecross

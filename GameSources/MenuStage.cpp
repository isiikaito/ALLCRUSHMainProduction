/*!
@file MenuStage.cpp
@brief ���j���[�X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���j���[�X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void MenuStage::CreateViewLight() {

		auto ptrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto ptrCamera = ObjectFactory::Create<Camera>();
		ptrView->SetCamera(ptrCamera);
		//�}���`���C�g�̍쐬
		auto ptrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		ptrMultiLight->SetDefaultLighting();
	}

//�A�C�e���X�v���C�g�쐬
	void MenuStage::CreatemenuSprite1() {
		AddGameObject<memuSprite1>(L"STAGE1_TX", true,
			//�e�N�X�`���̑傫���@�@�@�@�ʒu
			Vec2(180.0f, 180.0f), Vec3(-130.0f, 210.0f, 0.0f));
	}

	//������
	void MenuStage::OnCreate() {
		CreateViewLight();
		AddGameObject<TitleSprite>(L"MEMU_TX", false,
			Vec2(256.0f, 64.0f), Vec2(0.0f, 100.0f));
		//�A�C�e���X�v���C�g
		CreatemenuSprite1();
	}
	//�\���L�[��
	void MenuStage:: OnPushUP() {
		num--;
		if (num < 0)
		{
			num = 0;
		}
	}
	//�\���L�[��
	void MenuStage::OnPushDOUN() {
		num++;
		if (num > 2)
		{
			num = 2;
		}
	}
	//�X�V
	void MenuStage::OnUpdate() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<MenuStage>());
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0];
          //�R���g���[���̎擾
				auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto ptrStage1 = GetSharedGameObject<memuSprite1>(L"memuSprite1");
				float elapsedTime = App::GetApp()->GetElapsedTime();
				m_idleTime += elapsedTime;
				if (num == 0)
				{
					if (m_idleTime >= 1.0f)
					{
						
                        ptrStage1->SetDrawActive(false);
						if (m_idleTime >= 1.5f)
						{
						ptrStage1->SetDrawActive(true);
							m_idleTime = 0;
						}

						return;
					}
				}
				else{ ptrStage1->SetDrawActive(true); }


				
				
				
	}

	
	
	void MenuStage::OnPushB() {
		
		switch (num)
		{
			case 0:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToMovieStage");
				break;
			case 1:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
				break;
			case 2:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage2");
				break;
		
		}
		
	}
}

//end namespace basecross
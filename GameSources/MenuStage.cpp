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
	void MenuStage::CreateMenuSprite1() {
		AddGameObject<MenuSprite1>(L"STAGE1_TX", true,
			//�e�N�X�`���̑傫���@�@�@�@�ʒu
			Vec2(180.0f, 180.0f), Vec3(-130.0f, 210.0f, 0.0f));
	}

	//�A�C�e���X�v���C�g�쐬
	void MenuStage::CreateMenuSprite2() {
		AddGameObject<MenuSprite2>(L"STAGE2_TX", true,
			//�e�N�X�`���̑傫���@�@�@�@�ʒu
			Vec2(200.0f, 200.0f), Vec3(-130.0f, 110.0f, 0.0f));
	}

	//������
	void MenuStage::OnCreate() {
		CreateViewLight();
		AddGameObject<TitleSprite>(L"MEMU_TX", false,
			Vec2(256.0f, 64.0f), Vec2(0.0f, 100.0f));
		//Stage1�X�v���C�g
		CreateMenuSprite1();

		//Stage2�X�v���C�g
		CreateMenuSprite2();
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
	void MenuStage::OnPushDOWN() {
		num++;
		if (num > 1)
		{
			num = 1;
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

		//�X�e�[�W�I������

		//menuSprite1���擾����
		auto ptrStage1 = GetSharedGameObject<MenuSprite1>(L"MenuSprite1");
		//elapsedTime���擾���邱�Ƃɂ�莞�Ԃ��g����
		float elapsedTime = App::GetApp()->GetElapsedTime();
		//���Ԃ�ϐ��ɑ���
		m_idleTime += elapsedTime;
		//�\���L�[�𗘗p����num���O�̎�
		 if (num == 0)
		    {   //���Ԃ�1�b��ɕ\�����I�t�ɂȂ�
				if (m_idleTime >= 1.0f)
				  {
                     ptrStage1->SetDrawActive(false);
					  //���Ԃ�1.5�b��ɃI���ɂȂ�
					  if (m_idleTime >= 1.5f)
					   {
						 ptrStage1->SetDrawActive(true);
						 //m_idleTime��0�ɂ��邱�Ƃɂ�茳�ɖ߂��ă��[�v����B
						 m_idleTime = 0;
					   }
						return;
				  }
		   }
		 //�I������ĂȂ��Ƃ��͕\�����ꂽ�܂�
		else{ ptrStage1->SetDrawActive(true); }


		 //menuSprite1���擾����
		 auto ptrStage2 = GetSharedGameObject<MenuSprite2>(L"MenuSprite2");
		
		 //���Ԃ�ϐ��ɑ���
		
		 //�\���L�[�𗘗p����num���O�̎�
		 if (num == 1)
		 {   //���Ԃ�1�b��ɕ\�����I�t�ɂȂ�
			 if (m_idleTime >= 1.0f)
			 {
				 ptrStage2->SetDrawActive(false);
				 //���Ԃ�1.5�b��ɃI���ɂȂ�
				 if (m_idleTime >= 1.5f)
				 {
					 ptrStage2->SetDrawActive(true);
					 //m_idleTime��0�ɂ��邱�Ƃɂ�茳�ɖ߂��ă��[�v����B
					 m_idleTime = 0;
				 }
				 return;
			 }
		 }
		 //�I������ĂȂ��Ƃ��͕\�����ꂽ�܂�
		 else { ptrStage2->SetDrawActive(true); }
				
				
				
	}

	
	
	void MenuStage::OnPushB() {
		
		switch (num)
		{
			case 0:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
				break;
			case 1:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage2");
				break;
			/*case 2:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage2");
				break;*/
		
		}
		
	}
}

//end namespace basecross
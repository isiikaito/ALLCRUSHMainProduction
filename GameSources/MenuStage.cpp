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
		AddGameObject<MenuSprite1>(L"Stage1_TX", true,
			//�e�N�X�`���̑傫���@�@�@�@�ʒu
			Vec2(200.0f, 100.0f), Vec3(-50.0f, 50.0f, 0.0f));
	}

	//�A�C�e���X�v���C�g�쐬
	void MenuStage::CreateMenuSprite2() {
		AddGameObject<MenuSprite2>(L"Stage2_TX", true,
			//�e�N�X�`���̑傫���@�@�@�@�ʒu
			Vec2(200.0f, 100.0f), Vec3(-50.0f, -100.0f, 0.0f));
	}
	
	
	//������
	void MenuStage::OnCreate() {
		CreateViewLight();
		AddGameObject<TitleSprite>(L"MenuSelect_TX", false,
			Vec2(256.0f, 64.0f), Vec2(0.0f, 100.0f));
		CreateMenuSprite1();//Stage1�X�v���C�g
		CreateMenuSprite2();//Stage2�X�v���C�g
	}
	
	void MenuStage::SelectStage()
	{
		//scene�̎擾
		auto scene = App::GetApp()->GetScene<Scene>();
		//�X�e�[�W�ԍ��̎擾
		auto Select = scene->GetStageSelect();
		//���I��ł���X�e�[�W�ԍ���n��
		Select = StageNum;
		scene->SetStageSelect(Select);
	}

	//�\���L�[��
	void MenuStage:: OnPushUP() {

		StageNum--;
		if (StageNum <= m_UPlimit)
		{
			StageNum = m_UPlimit;
		}
	}
	//�\���L�[��
	void MenuStage::OnPushDOWN() {
		StageNum++;
		if (StageNum >= m_DOWNlimit)
		{
			StageNum = m_DOWNlimit;
		}
	}

	
	void MenuStage::StageSprite1()
	{
	    //menuSprite1���擾����
		auto ptrStage1 = GetSharedGameObject<MenuSprite1>(L"MenuSprite1");
		//elapsedTime���擾���邱�Ƃɂ�莞�Ԃ��g����
		float elapsedTime = App::GetApp()->GetElapsedTime();
		if (OnPushBCheck) {
			if (!OnPushBCheck1)
			{
				auto WalkSound = App::GetApp()->GetXAudio2Manager();
				WalkSound->Start(L"WalkSound", 0, 0.4f);
				OnPushBCheck1 = true;
			}
		}
		//���Ԃ�ϐ��ɑ���
		m_idleTime += elapsedTime;
		//�\���L�[�𗘗p����num���O�̎�
		 if (StageNum == m_UPlimit)
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

	}

	//�X�e�[�W�X�v���C�g�Q�̏���
	void MenuStage::StageSprite2()
	{
         //menuSprite1���擾����
		 auto ptrStage2 = GetSharedGameObject<MenuSprite2>(L"MenuSprite2");
		
		 //���Ԃ�ϐ��ɑ���
		
		 //�\���L�[�𗘗p����num���O�̎�
		 if (StageNum == m_DOWNlimit)
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
	//�X�V
	void MenuStage::OnUpdate() {
		SelectStage();
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<MenuStage>());

		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0];
        //�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		StageSprite1();
		StageSprite2();	
		
	}

	
	//B�{�^����������Ă�����
	void MenuStage::OnPushB() {
		
		wstring stagename[]
		{  
			L"ToMovieStage",
			L"ToGameStage"
		};
		if (m_OnPushB==true)
		{
         //�t�F�[�h�A�E�g�̍쐬
		AddGameObject<FadeOut>(true,
			Vec2(1290.0f, 960.0f), Vec3(0.0f, 0.0f, 0.0f));
		SelectStage();
		//���̃X�e�[�W�ֈڍs
		PostEvent(XM_PI / 2, GetThis<MenuStage>(), App::GetApp()->GetScene<Scene>(), stagename[StageNum]);
		m_OnPushB = false;
		}
		
		OnPushBCheck = true;
	}
}

//end namespace basecross
/*!
@file GameStage.cpp
@brief�N���A�X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�N���A�X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void ClearStage::CreateViewLight() {
		const Vec3 eye(0.0f, 20.0f, -10.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}



	void ClearStage::OnCreate() {
		try {

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			AddGameObject<ClearObject>();

		}
		catch (...) {
			throw;
		}
	}


}
//end basecross

/*!
@file GameStage.h
@brief  Q [   X e [ W
*/

#pragma once
#include "stdafx.h"


namespace basecross {
	//enum class CameraSelect {
	//	//openingCamera,
	//	myCamera,
	//	objCamera,
	//  mainCamera,
	//  backCamera
	//};
	//--------------------------------------------------------------------------------------
	// �Q�[���X�e�[�W2�N���X
	//--------------------------------------------------------------------------------------
	class GameStage2 : public Stage {
		//CSV�t�@�C������C
		CsvFile m_CsvC;
		//�r���[�̍쐬
		void CreateViewLight();
		
		//��
		void CreatePillar();
		
		//�}���ɂ��X�e�[�W�̕Ǎ쐬
		void CreateStageWall();
		//�}���ɂ��X�e�[�W�̏��쐬
		void CreateStageFloor();
		//�J�x�̍쐬
		void CreateWall();
		//��Q���P
		void CreateObstacle1();
		//��Q��2
		void CreateObstacle2();
		//�A�C�e���X�v���C�g�쐬
		void CreateMyitem1();
		//�Q�[�W�̒ǉ�
		void CreateMygage();
		void CreateExitWall();
		//����
		void CreateFallingRock();
		//�^�C���쐬
		void CreateTime();
		//�g�[�^������
		float m_TotalTime;

		//OpeningCamera�p�̃r���[
		shared_ptr<SingleView> m_OpeningCameraView;
		//MyCamera�p�̃r���[
		shared_ptr<SingleView> m_MyCameraView;
		//ObjCamera�p�̃r���[
		//shared_ptr<SingleView> m_ObjCameraView;
		CameraSelect m_CameraSelect;

		//���̓n���h���[
		InputHandler<GameStage> m_InputHandler;
		//BGM
		shared_ptr<SoundItem> m_BGM;
		//�G�̍쐬
		void CreateEnemy();
		//�L�����N�^�[�̍쐬
		void CreateChara();
		//�v���C���[�̍쐬
		void CreatePlayer();
		//BGM�̍Đ�
		void BGM();
		void OnDestroy();
		//�J�����}���̍쐬
		void CreateCameraman();
	public:
		//�\�z�Ɣj��
		GameStage2() :Stage(), m_TotalTime(0) {}
		virtual ~GameStage2() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		//A�{�^���Ȃɂ����Ȃ�
		void OnPushA();
		//B�{�^���J�����̕ύX
		void OnPushB();
		CameraSelect GetCameraSelect() const {
			return m_CameraSelect;
		}
		void ToMyCamera();
		void ToObjCamera();
	};

}
//end basecross

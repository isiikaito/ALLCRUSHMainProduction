/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player : public GameObject
	{

		//������̕\��
		void DrawStrings();

		const float MaxMoveSpeed; // �ړ��̍ő呬

		bool moveStop;//Player�̈ړ���~�̔���

		Vec3 moveDir; // �ړ������x�N�g���i�P�ʃx�N�g���j
		Vec3 at1;
		float speed; // �ړ��̑���

		float accel; // �����x

		//�A�C�e���̏�����
		float itemCount;
		//�p���[�A�b�v�A�C�e��
		int PowerCount;
		//�v���C���[�̃X�s�[�h
		float speed2;
		//���΂̃J�E���g
		float FallingCount;

		//���J�E���g
		int PillarCount;
		float SoundTime;


		//�v���C���[�ƃ{�X�Ƃ̋���
		float PBdistance;

		//�v���C���[�ƒ��̏���
		float PPdistance;


		//�U������J�E���g�^�C��
		float m_TurnTime;

		//�p���[�A�b�v�����邩�Ȃ���
		int Power;
		
		
		// �e���b�v
		void CreateTelop();
		float m_TelopTime;

		// �e���b�v2
		void CreateTelop2();
		float m_Telop2Time;

		// �e���b�v3
		void CreateTelop3();
		float m_Telop3Time;

		// �e���b�v4
		void CreateTelop4();
		float m_Telop4Time;


		Vec3 GetMoveVector() const;

		InputHandler<Player> m_InputHandler;
		//void MovePlayer();
		InputHandler2<Player> m_InputHandler2;
		shared_ptr<SoundItem> m_BGM;
		void OnDestroy();

		// �G�t�F�N�g�֘A
		float m_TotalTime;
		bool m_isPlay;
		Effekseer::Handle m_handle;
		Effekseer::ManagerRef m_manager;
		EffekseerRendererDX11::RendererRef m_renderer;
		Effekseer::EffectRef m_effect;

		// �G�t�F�N�g�֘A1
		float m_TotalTime1;
		bool m_isPlay1;
		Effekseer::Handle m_handle1;
		Effekseer::ManagerRef m_manager1;
		EffekseerRendererDX11::RendererRef m_renderer1;
		Effekseer::EffectRef m_effect1;

		void CreateEffect();
		void CreateEffect1();

	public:
		//Player(const shared_ptr<Stage>& StagePtr);

		// �X�e�[�W��n����R���X�g���N�^���K�{
		Player(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), // �X�e�[�W�͐e�N���X�ɓ�����
			MaxMoveSpeed(6.0f),
			moveStop(1.0f),	
			moveDir(0.0f, 0.0f, 0.0f),
			at1(0.0f,0.0f,0.0f),
			speed(0.0f),
			speed2(5.0f),
			accel(0.0f),
			itemCount(0),
			PowerCount(0),
			Power(1),
			SoundTime(0.0f),
			m_TotalTime(0.0f), m_isPlay(false),m_handle(0),
			m_manager(nullptr), m_renderer(nullptr), m_effect(nullptr),
			m_TotalTime1(0.0f), m_isPlay1(false),m_handle1(0),
			m_manager1(nullptr), m_renderer1(nullptr), m_effect1(nullptr)
		{
		}
		virtual void OnDraw() override;

		//A�{�^��
		void OnPushA();
		//B�{�^��
		void OnPushB(){}
		//�\���L�[��
		void OnPushUP() {}
		//�\���L�[��
		void OnPushDOWN() {}
		//X�{�^��
		void OnPushX();
		//�G�̍U��(/)�ɂԂ������Ƃ�
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
		void OnCreate() override; // �I�u�W�F�N�g�̏������p�֐��iUnity��Start�֐��j
		void OnUpdate() override; // �I�u�W�F�N�g�̃t���[�����Ƃ̏����iUnity��Update�֐��j
		void OnUpdate2() override; // �I�u�W�F�N�g�̃t���[�����Ƃ̏����iUnity��Update�֐��j
		void OnAttack();

		int GetPillarCount()const {
			return PillarCount;
		}
		void SetPillarCount(int PillarCount) {
			PillarCount = PillarCount;
		}
		int GetPower()const {
			return Power;
		}
		void SetPower(int Power)
		{
			Power = Power;
		}
	};
}
//end basecross


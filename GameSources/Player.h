/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player : public GameObject
	{
		const float MaxMoveSpeed; // �ړ��̍ő呬

		bool moveStop;//Player�̈ړ���~�̔���

		Vec3 moveDir; // �ړ������x�N�g���i�P�ʃx�N�g���j
		float speed; // �ړ��̑���

		float accel; // �����x

		//�A�C�e���̏�����
		float itemCount;
		//�v���C���[�̃X�s�[�h
		float speed2;
		//���΂̃J�E���g
		float FallingCount;

		//�v���C���[�ƃ{�X�Ƃ̋���
		float PBdistance;

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

		void CreateEffect();

	public:
		//Player(const shared_ptr<Stage>& StagePtr);

		// �X�e�[�W��n����R���X�g���N�^���K�{
		Player(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), // �X�e�[�W�͐e�N���X�ɓ�����
			MaxMoveSpeed(6.0f),
			moveStop(1.0f),	
			moveDir(0.0f, 0.0f, 0.0f),
			speed(0.0f),
			speed2(1.0f),
			accel(0.0f),
			itemCount(0),
			m_TotalTime(0.0f), m_isPlay(false), m_handle(0),
			m_manager(nullptr), m_renderer(nullptr), m_effect(nullptr)

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
	};
}
//end basecross


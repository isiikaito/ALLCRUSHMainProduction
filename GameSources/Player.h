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

		Vec3 moveDir; // �ړ������x�N�g���i�P�ʃx�N�g���j
		float speed; // �ړ��̑���

		float accel; // �����x

		Vec3 GetMoveVector() const;

		InputHandler<Player> m_InputHandler;
		//void MovePlayer();


	public:
		// �X�e�[�W��n����R���X�g���N�^���K�{
		Player(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), // �X�e�[�W�͐e�N���X�ɓ�����
			MaxMoveSpeed(6.0f),
			moveDir(0.0f, 0.0f, 0.0f),
			speed(0.0f),
			accel(0.0f)
		{
		}
		//A�{�^��
		void OnPushA();
		//B�{�^���Ȃɂ����Ȃ�
		void OnPushB() {}


		void OnCreate() override; // �I�u�W�F�N�g�̏������p�֐��iUnity��Start�֐��j
		void OnUpdate() override; // �I�u�W�F�N�g�̃t���[�����Ƃ̏����iUnity��Update�֐��j
		void OnUpdate2() override; // �I�u�W�F�N�g�̃t���[�����Ƃ̏����iUnity��Update�֐��j
	};


}
//end basecross


/*!
@file TitleStage.h
@brief �^�C�g���X�v���C�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���I�[�o�[�e���b�v�X�v���C�g�N���X
	//--------------------------------------------------------------------------------------
	class GameOverTelop : public GameObject {
		bool m_Trace;//�����ɂȂ邩�ǂ���
		Vec2 m_StartScale;//�X�P�[�����O
		Vec2 m_StartPos;//�ꏊ
		wstring m_TextureKey;//�e�N�X�`���̖��O
		float m_idleTime;
	public:
		GameOverTelop(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			bool Trace,
			const Vec2& StartScale,
			const Vec2& StartPos);
		//�j��
		virtual ~GameOverTelop();
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override {}
	};
}
//end namespace basecross

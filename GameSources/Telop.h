/*!
@file TitleStage.h
@brief �^�C�g���X�v���C�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�e���b�v�X�v���C�g�N���X
	//--------------------------------------------------------------------------------------
	class Telop : public GameObject {
		bool m_Trace;//�����ɂȂ邩�ǂ���
		Vec2 m_StartScale;//�X�P�[�����O
		Vec2 m_StartPos;//�ꏊ
		wstring m_TextureKey;//�e�N�X�`���̖��O
		float m_idleTime;
	public:
		Telop(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			bool Trace,
			const Vec2& StartScale,
			const Vec2& StartPos);
		//�j��
		virtual ~Telop();
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override {}
	};
}
//end namespace basecross

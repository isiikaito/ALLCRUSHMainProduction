/*!
@file menuSprite1.h
@brief ����
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	
	class memuSprite1 : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_idleTime;
		
		//�o�b�N�A�b�v���_�f�[�^
		vector< VertexPositionColorTexture> m_BackupVertices;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	TextureKey	�e�N�X�`���L�[
		@param[in]	Trace	�����������邩�ǂ���
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		memuSprite1(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		
		virtual ~memuSprite1();
		
		virtual void OnCreate() override;
		
		virtual void OnUpdate()override;

		////���̓C�x���g�ɉ�������֐�
		//void OnPushB();
		//void OnPushX(){}
		////�\���L�[��
		//void OnPushUP();
		////�\���L�[��
		//void OnPushDOUN();
	
	};
}

/*!
@file Time.h
@brief �^�C���Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
		///	�X�R�A�\���̃X�v���C�g
		//--------------------------------------------------------------------------------------
	class MyTime : public GameObject {
		bool m_Trace;         //����
		Vec2 m_StartScale;    //�傫��
		Vec3 m_StartPos;      //�ʒu
		wstring m_TextureKey; //�e�N�X�`��
		float m_Score;        //����
		//����
		UINT m_NumberOfDigits;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		
		MyTime(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		
		virtual ~MyTime() {}
		
		void SetScore(float f) {
			m_Score = f;
		}
		
		virtual void OnCreate() override;
		
		virtual void OnUpdate()override;
	};


}
//end basecross


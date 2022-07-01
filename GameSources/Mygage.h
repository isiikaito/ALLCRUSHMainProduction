/*!
@file Mygage.h
@brief �Q�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Mygage : public GameObject {
		bool m_Trace;        //����
		Vec2 m_StartScale;   //�傫��
		Vec3 m_StartPos;     //�ʒu
		wstring m_TextureKey;//�e�N�X�`��
		float m_TotalTime;   //���Ԃ̎擾
		vector<VertexPositionTexture> m_BackupVertices;//�o�b�N�A�b�v���_�f�[�^
	public:
	
		Mygage(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		
		virtual ~Mygage();
		
		virtual void OnCreate() override;
		
	};
}

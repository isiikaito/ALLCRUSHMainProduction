/*!
@file Myitem1.h
@brief �A�C�e��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Myitem1 : public GameObject {
		bool m_Trace;        //����
		Vec2 m_StartScale;   //�傫��
		Vec3 m_StartPos;     //�ʒu
		wstring m_TextureKey;//�e�N�X�`��
		float m_TotalTime;   //����
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		
		Myitem1(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		
		virtual ~Myitem1();
		
		virtual void OnCreate() override;
		
	};
}

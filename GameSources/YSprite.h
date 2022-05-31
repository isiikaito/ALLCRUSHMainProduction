/*!
@file YSprite.h
@brief �p���[
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class YSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_TotalTime;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionTexture> m_BackupVertices;
	public:

		YSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		virtual ~YSprite();

		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate()override;

	};
}
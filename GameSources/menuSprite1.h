/*!
@file MenuSprite1.h
@brief 文字
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	
	class MenuSprite1 : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_idleTime;
		
		//バックアップ頂点データ
		vector< VertexPositionColorTexture> m_BackupVertices;
	public:
		
		MenuSprite1(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		
		virtual ~MenuSprite1();
		
		virtual void OnCreate() override;
		
		
	
	};
}

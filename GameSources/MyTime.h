/*!
@file Time.h
@brief タイムなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
		///	スコア表示のスプライト
		//--------------------------------------------------------------------------------------
	class MyTime : public GameObject {
		bool m_Trace;         //透明
		Vec2 m_StartScale;    //大きさ
		Vec3 m_StartPos;      //位置
		wstring m_TextureKey; //テクスチャ
		float m_Score;        //数字
		//桁数
		UINT m_NumberOfDigits;
		//バックアップ頂点データ
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


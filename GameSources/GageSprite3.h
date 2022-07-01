/*!
@file GageSprite3.h
@brief ゲージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//ゲージ
	class GageSprite3 : public GameObject
	{
		bool m_Trace;       //透明
		Vec2 m_StartScale;  //大きい
		Vec3 m_StartPos;    //位置
		float m_TotalTime;  //時間の取得
		int m_BreakCount;   //壁を壊した回数
		int m_PowerON;      //パワーアップ中
		int m_PowerOFF;     //パワーアップしてない
		vector<VertexPositionColor>m_BackupVertices;//バックアップ頂点データ


	public:
		GageSprite3(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		virtual ~GageSprite3();

		virtual void OnCreate() override;//初期化
		virtual void OnUpdate()override; //更新

		
	};
}

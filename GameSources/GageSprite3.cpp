/*!
@file GageSprite2.cpp
@brief ゲージの実体a
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//ゲージ

	GageSprite3::GageSprite3(const shared_ptr<Stage>& StagePtr, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0),
		m_ColwUP(0),
		m_ColwDOWN(0)
	{}

	GageSprite3::~GageSprite3() {}
	void GageSprite3::OnCreate() {


		float helfSize = 0.5f;
		//頂点配列
		m_BackupVertices = {
			//カラー　透明度
{ VertexPositionColor(Vec3(-helfSize, helfSize, 0),Col4(1.0f,0.0f,0.0f,1.0f)) },
{ VertexPositionColor(Vec3(helfSize, helfSize, 0), Col4(1.0f, 0.0f, 0.0f, 1.0f)) },
{ VertexPositionColor(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 0.0f, 0.0f, 1.0f)) },
{ VertexPositionColor(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 0.0f, 0.0f,1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		//頂点とインデックスを指定してスプライト作成

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		auto ptrDraw = AddComponent<PCSpriteDraw>(m_BackupVertices, indices);
		SetAlphaActive(true);

		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.0f));
		//頂点とインデックスを指定してスプライト作成
		AddComponent<PCSpriteDraw>(m_BackupVertices, indices);




	}
	//点滅処理（Elapsedtimeを利用している）
	void GageSprite3::OnUpdate() {




		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto PowerCount = ptrPlayer->GetPowerCount();
		ptrPlayer->SetPowerCount(PowerCount);

		if (PowerCount == 3)


		{ //プレイヤーの座標取得

			auto ptrDraw = GetComponent<PCSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0f, 0.0, 0.0f, 1.0f));




		}
	}
}
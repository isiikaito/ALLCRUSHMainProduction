/*!
@file FadeOutEnd.cpp
@brief フェードアウト実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	FadeOutEnd::FadeOutEnd(const shared_ptr<Stage>& StagePtr, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0)
	{}

	FadeOutEnd::~FadeOutEnd() {}
	void FadeOutEnd::OnCreate() {

		float helfSize = 0.5f;
		//頂点配列
		m_BackupVertices = {
			//カラー　透明度
		{ VertexPositionColor(Vec3(-helfSize, helfSize, 0),Col4(0.0f,0.0f,0.0f,0.0f)) },
		{ VertexPositionColor(Vec3(helfSize, helfSize, 0), Col4(0.0f,0.0f,0.0f,0.0f)) },
		{ VertexPositionColor(Vec3(-helfSize, -helfSize, 0), Col4(0.0f,0.0f,0.0f,0.0f)) },
		{ VertexPositionColor(Vec3(helfSize, -helfSize, 0), Col4(0.0f,0.0f,0.0f,0.0f)) },
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

		//頂点とインデックスを指定してスプライト作成
		AddComponent<PCSpriteDraw>(m_BackupVertices, indices);
	}

	//点滅処理（Elapsedtimeを利用している）
	void FadeOutEnd::OnUpdate() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;

		if (m_TotalTime >= XM_PI) {
			m_TotalTime = 0;
		}

		vector<VertexPositionColor> newVertices;
		for (size_t i = 0; i < m_BackupVertices.size(); i++) {
			Col4 col = m_BackupVertices[i].color;
			//sinで0〜１までにして0の時は透明１の時は表示としている
			col.w = sin(m_TotalTime);
			auto v = VertexPositionColor(
				m_BackupVertices[i].position,
				col
			);
			newVertices.push_back(v);
				if (m_TotalTime >= 1)
				{
					auto ptrGMOStage = GetStage()->GetSharedGameObject<GMOTelop>(L"GMOTelop");
					ptrGMOStage->SetDrawActive(true);
					// 時間の変数に足す
					//m_GMOTelopTime += elapsedTime;
					//if (m_GMOTelopTime >= 5.0f)
					//{
					//1秒後に表示がオフになる
					//	ptrGMOStage->SetDrawActive(false);
					//}
				//PostEvent(0.0f, GetThis<FadeOutEnd>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
				}

			}
		}
	}
/*!
@file GageSprite.cpp
@brief ゲージの実体a
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//ゲージ

	GageSprite::GageSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0),
		m_BreakCount(2),
		m_PowerON(0),
		m_PowerOFF(1)

	{}

	GageSprite::~GageSprite() {}
	void GageSprite::OnCreate() {


		float helfSize = 0.5f;
		//頂点配列
		m_BackupVertices = 
		{
			                                                                           //カラー　透明度
                           { VertexPositionColor(Vec3(-helfSize, helfSize, 0),Col4(1.0f,0.0f,0.0f,1.0f)) },
                           { VertexPositionColor(Vec3(helfSize, helfSize, 0), Col4(1.0f, 0.0f, 0.0f, 1.0f)) },
                           { VertexPositionColor(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 0.0f, 0.0f, 1.0f)) },
                           { VertexPositionColor(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 0.0f, 0.0f,1.0f)) },
	    };
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		
		//初期位置の設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);

        //頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCSpriteDraw>(m_BackupVertices, indices);
		SetAlphaActive(true);

		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.0f));
		//頂点とインデックスを指定してスプライト作成
		AddComponent<PCSpriteDraw>(m_BackupVertices, indices);




	}

	//点滅処理（Elapsedtimeを利用している）
	void GageSprite::OnUpdate() {

	//プレイヤーの取得
	auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
	auto PowerCount = ptrPlayer->GetPowerCount();
		//壁を殴った回数
		ptrPlayer->SetPowerCount(PowerCount);
		//パワーアップしているかどうか
		auto Power = ptrPlayer->GetPower();
		ptrPlayer->SetPower(Power);
		//アイテムを使ったかどうか
		auto Gageflash = ptrPlayer->GetGageflash();
		ptrPlayer->SetGageflash(Gageflash);
		//壁を１回殴ったら
		if (PowerCount == 1)


		{
			//ゲージの表示
			auto ptrDraw = GetComponent<PCSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0f, 0.0, 0.0f, 1.0f));

		}



		//パワーアップした時
		if (Power == m_PowerON)
		{
			//点滅

			//時間の取得
			float elapsedTime = App::GetApp()->GetElapsedTime();
			m_TotalTime += elapsedTime;
			if (m_TotalTime >= XM_PI) {
				m_TotalTime = 0;
			}
			//頂点の取得
			vector<VertexPositionColor> newVertices;
			for (size_t i = 0; i < m_BackupVertices.size(); i++) {
				Col4 col = m_BackupVertices[i].color;
				//sinで0～１までにして0の時は透明１の時は表示としている
				col.w = sin(m_TotalTime);
				auto v = VertexPositionColor(
					m_BackupVertices[i].position,
					col
				);
				newVertices.push_back(v);
			}
			auto ptrDraw = GetComponent<PCSpriteDraw>();
			ptrDraw->UpdateVertices(newVertices);

		}
		//アイテムを使った後
		if (Gageflash == m_PowerOFF)
		{
			//ゲージを消す
			auto ptrDraw = GetComponent<PCSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0f, 0.0, 0.0f, 0.0f));
			Gageflash = m_PowerON;
		}

	}

}

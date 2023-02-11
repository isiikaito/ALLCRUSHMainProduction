/*!
@file YSprite.cpp
@brief　パワーボタン
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	constexpr int m_powerMax = 3;
	constexpr int m_gageflashTrue = 1;
	YSprite::YSprite(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0)
	{}

	YSprite::~YSprite() {}
	void YSprite::OnCreate() {
		float helfSize = 0.5f;
		//頂点配列
		m_BackupVertices = {
			{ VertexPositionTexture(Vec3(-helfSize, helfSize, 0), Vec2(0.0f, 0.0f)) },
			{ VertexPositionTexture(Vec3(helfSize, helfSize, 0), Vec2(1.0f, 0.0f)) },
			{ VertexPositionTexture(Vec3(-helfSize, -helfSize, 0), Vec2(0.0f, 1.0f)) },
			{ VertexPositionTexture(Vec3(helfSize, -helfSize, 0), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };

		//透明処理
		SetAlphaActive(m_Trace);

		//初期位置の設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);

		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

		//テクスチャの読み込み
		ptrDraw->SetTextureResource(m_TextureKey);

		//テクスチャの表示をしない
		SetDrawActive(false);

		//読み込みの設定をする
		GetStage()->SetSharedGameObject(L"YSprite", GetThis<YSprite>());
	}

	void YSprite::OnUpdate() 
	{
		//プレイヤーの取得
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");

		//壁を壊した回数
		auto PowerCount = ptrPlayer->GetPowerCount();
		ptrPlayer->SetPowerCount(PowerCount);

		//使い終わってるかどうか
		auto Gageflash = ptrPlayer->GetGageflash();
		ptrPlayer->SetGageflash(Gageflash);
		if (PowerCount == m_powerMax)
		{
			//テクスチャを表示する
			SetDrawActive(true);
		}
		//ゲージを使い終わったら
		if (Gageflash == m_gageflashTrue)
		{
			//テクスチャの表示をしない
			SetDrawActive(false);
			Gageflash = 0;
		}
	}
}
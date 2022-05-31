/*!
@file XSprite.cpp
@brief �A�C�e���e�N�X�`��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

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
		//���_�z��
		m_BackupVertices = {
			{ VertexPositionTexture(Vec3(-helfSize, helfSize, 0), Vec2(0.0f, 0.0f)) },
			{ VertexPositionTexture(Vec3(helfSize, helfSize, 0), Vec2(1.0f, 0.0f)) },
			{ VertexPositionTexture(Vec3(-helfSize, -helfSize, 0), Vec2(0.0f, 1.0f)) },
			{ VertexPositionTexture(Vec3(helfSize, -helfSize, 0), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_TextureKey);
		SetDrawActive(false);
		//�ǂݍ��݂̐ݒ������
		GetStage()->SetSharedGameObject(L"YSprite", GetThis<YSprite>());
	}

	void YSprite::OnUpdate() 
	{
		//�v���C���[�̎擾
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		//�ǂ��󂵂���
		auto PowerCount = ptrPlayer->GetPowerCount();
		ptrPlayer->SetPowerCount(PowerCount);
		//�g���I����Ă邩�ǂ���
		auto Gageflash = ptrPlayer->GetGageflash();
		ptrPlayer->SetGageflash(Gageflash);
		if (PowerCount == 3)
		{
			SetDrawActive(true);
		}
		//�Q�[�W���g���I�������
		if (Gageflash == 1)
		{
			SetDrawActive(false);
			Gageflash = 0;
		}
	}
}
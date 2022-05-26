/*!
@file GageSprite2.cpp
@brief �Q�[�W�̎���a
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�Q�[�W

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
		//���_�z��
		m_BackupVertices = {
			//�J���[�@�����x
{ VertexPositionColor(Vec3(-helfSize, helfSize, 0),Col4(1.0f,0.0f,0.0f,1.0f)) },
{ VertexPositionColor(Vec3(helfSize, helfSize, 0), Col4(1.0f, 0.0f, 0.0f, 1.0f)) },
{ VertexPositionColor(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 0.0f, 0.0f, 1.0f)) },
{ VertexPositionColor(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 0.0f, 0.0f,1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		auto ptrDraw = AddComponent<PCSpriteDraw>(m_BackupVertices, indices);
		SetAlphaActive(true);

		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.0f));
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		AddComponent<PCSpriteDraw>(m_BackupVertices, indices);




	}
	//�_�ŏ����iElapsedtime�𗘗p���Ă���j
	void GageSprite3::OnUpdate() {




		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto PowerCount = ptrPlayer->GetPowerCount();
		ptrPlayer->SetPowerCount(PowerCount);

		if (PowerCount == 3)


		{ //�v���C���[�̍��W�擾

			auto ptrDraw = GetComponent<PCSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0f, 0.0, 0.0f, 1.0f));




		}
	}
}
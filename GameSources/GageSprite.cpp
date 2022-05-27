/*!
@file GageSprite.cpp
@brief �Q�[�W�̎���a
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�Q�[�W

	GageSprite::GageSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0),
		m_ColwUP(0),
		m_ColwDOWN(0)
	{}

	GageSprite::~GageSprite() {}
	void GageSprite::OnCreate() {
		float helfSize = 0.5f;
		//���_�z��
		m_BackupVertices = {
			                                                             //�J���[�@�����x
			{ VertexPositionColor(Vec3(-helfSize, helfSize, 0),Col4(2.0f,0.0f,0.0f,m_ColwUP)) },
			{ VertexPositionColor(Vec3(helfSize, helfSize, 0), Col4(2.0f, 0.0f, 0.0f, m_ColwUP)) },
			{ VertexPositionColor(Vec3(-helfSize, -helfSize, 0), Col4(2.0f, 0.0f, 0.0f, m_ColwDOWN)) },
			{ VertexPositionColor(Vec3(helfSize, -helfSize, 0), Col4(2.0f, 0.0f, 0, m_ColwDOWN)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		AddComponent<PCSpriteDraw>(m_BackupVertices, indices);
		//�ǂݍ��݂̐ݒ������
		GetStage()->SetSharedGameObject(L"GageSprite", GetThis<GageSprite>());
	}
	//�_�ŏ����iElapsedtime�𗘗p���Ă���j
	void GageSprite::OnUpdate() {
		////���Ԃ̎擾
		//float elapsedTime = App::GetApp()->GetElapsedTime();
		//m_TotalTime += elapsedTime;
		//if (m_TotalTime >= XM_PI) {
		//	m_TotalTime = 0;
		//}
		//
		//vector<VertexPositionColor> newVertices;
		//for (size_t i = 0; i < m_BackupVertices.size(); i++) {
		//	Col4 col = m_BackupVertices[i].color;
		//	//sin��0�`�P�܂łɂ���0�̎��͓����P�̎��͕\���Ƃ��Ă���
		//	col.w = sin(m_TotalTime);
		//	auto v = VertexPositionColor(
		//		m_BackupVertices[i].position,
		//		col
		//	);
		//	newVertices.push_back(v);
		//}
		//auto ptrDraw = GetComponent<PCSpriteDraw>();
		//ptrDraw->UpdateVertices(newVertices);

		
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto itemCount = ptrPlayer->GetPower();
		ptrPlayer->SetPower(itemCount);
		
		if (itemCount==0)


		{ //�v���C���[�̍��W�擾
		
			m_ColwUP = 1.0f;
			m_ColwDOWN = 1.0f;
			
		}
		 
	}
}
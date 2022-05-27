/*!
@file GageSprite.h
@brief �Q�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//�Q�[�W
	class GageSprite : public GameObject
	{
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		float m_TotalTime;
		float m_ColwUP;//�Q�[�W��̓����x
		float m_ColwDOWN;//�Q�[�W���̓����x
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionColor>m_BackupVertices;

		
	public:
		GageSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		virtual ~GageSprite();

		virtual void OnCreate() override;

		virtual void OnUpdate()override;

		////�Q�[�W��̓����x�擾
		//float GetColwUP()const {
		//	return m_ColwUP;
		//}
		//void SetColwUP(float ColwUP) {
		//	m_ColwUP = ColwUP;
		//}

		////�Q�[�W���̓����x�擾
		//float GetColwDOWN()const {
		//	return m_ColwDOWN;
		//}
		//void SetColwDOWN(float ColwDOWN) {
		//	m_ColwDOWN = ColwDOWN;
		//}
	};
}
/*!
@file GageSprite.h
@brief �Q�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//�Q�[�W
	class GageSpriteWhite : public GameObject
	{
		bool m_Trace;       //����
		Vec2 m_StartScale;  //�傫��
		Vec3 m_StartPos;    //�ʒu
		float m_TotalTime;  //���Ԃ̎擾
		vector<VertexPositionColor>m_BackupVertices;//�o�b�N�A�b�v���_�f�[�^
	public:
		GageSpriteWhite(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		virtual ~GageSpriteWhite();

		virtual void OnCreate() override;

		
	};

	
}
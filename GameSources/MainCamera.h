#pragma once
#include "stdafx.h"

namespace basecross {

	class MainCamera : public Camera
	{
		float angleY; // Y�����S�̉�荞�݁i���W�A���p�j
		float distance; // �����Ώۂ���̋���

	public:
		MainCamera()
			: angleY(0.0f), distance(5.0f)
		{
		}

		void OnUpdate() override;

		float GetAngleY() const
		{
			return angleY;
		}
	};
}
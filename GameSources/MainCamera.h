#pragma once
#include "stdafx.h"

namespace basecross {

	class MainCamera : public Camera
	{
		float angleY; // Y軸中心の回り込み（ラジアン角）
		float distance; // 注視対象からの距離

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
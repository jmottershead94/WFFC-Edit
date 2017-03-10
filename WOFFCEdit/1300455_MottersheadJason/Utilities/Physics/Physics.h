#pragma once

#include "../Maths/Maths.h"

class Physics
{
	friend class ToolMain;

	private:
		Physics();

	public:
		struct AABB
		{
			DirectX::SimpleMath::Vector3 left;
			DirectX::SimpleMath::Vector3 right;
			DirectX::SimpleMath::Vector3 top;
			DirectX::SimpleMath::Vector3 bottom;
			DirectX::SimpleMath::Vector3 front;
			DirectX::SimpleMath::Vector3 back;
		};

		~Physics();
		static bool PointToAABB(const AABB& box, DirectX::SimpleMath::Vector3& point);
};
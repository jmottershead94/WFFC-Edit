#pragma once

#include "../Maths/Maths.h"

/*
 * Provides access to common physics functionality.
 */
class Physics
{
	friend class ToolMain;

	private:
		Physics();

	public:
		/*
		 * A struct of data for an axis aligned bounding box.
		 */
		struct AABB
		{
			DirectX::SimpleMath::Vector3 vecMax;
			DirectX::SimpleMath::Vector3 vecMin;
		};

		~Physics();
		static bool PointToAABB(const AABB& box, DirectX::SimpleMath::Vector3& point);
		static bool Ray(DirectX::SimpleMath::Vector3& start, DirectX::SimpleMath::Vector3& end, const AABB& box, bool returnFirstHit = true);
};
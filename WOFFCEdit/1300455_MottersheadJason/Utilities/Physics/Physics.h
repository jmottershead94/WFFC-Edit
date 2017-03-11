#pragma once

#include "../Maths/Maths.h"

/*
 * Provides access to common physics functionality.
 */
class Physics
{
	friend class ToolMain;

	private:
		/*
		 * Constructs this instance.
		 */
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

		/*
		 * Destructs this instance.
		 */
		~Physics();

		/*
		 * Checks to see if the point lies within the bounding box.
		 * @param box the bounding box to check for points inside.
		 * @param point the point to check inside of the bounding box.
		 * @return bool if the point lies inside of the bounding box.
		 */
		static bool PointToAABB(const AABB& box, DirectX::SimpleMath::Vector3& point);

		/*
		 * Casts a ray from a start point to an end point and checks for AABB-point collisions.
		 * @param start where to draw the ray FROM.
		 * @param end where the ray should END.
		 * @param box the bounding box to test this ray against.
		 * @param returnFirstHit if this function should return after the first collision has been detected.
		 * @return bool if this ray has hit something.
		 */
		static bool Ray(DirectX::SimpleMath::Vector3& start, DirectX::SimpleMath::Vector3& end, const AABB& box, bool returnFirstHit = true);
};
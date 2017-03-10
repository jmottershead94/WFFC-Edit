#include "Physics.h"

std::unique_ptr<Physics> instance = nullptr;

/*
 * Constructs this instance.
 */
Physics::Physics()
{
	if (instance == nullptr)
		instance = std::make_unique<Physics>(*this);
}

/*
 * Destructs this instance.
 */
Physics::~Physics()
{}

/*
 * Checks to see if the point lies within the bounding box.
 * @param box the bounding box to check for points inside.
 * @param point the point to check inside of the bounding box.
 * @return bool if the point lies inside of the bounding box.
 */
bool Physics::PointToAABB(const AABB& box, DirectX::SimpleMath::Vector3& point)
{
	if ((point.x > box.left.x && point.x < box.right.x)
		&& (point.y > box.bottom.y && point.y < box.top.y)
		&& (point.z > box.back.z && point.z < box.front.z))
	{
		return true;
	}

	return false;
}

/*
 * Casts a ray from a start point to an end point and checks for AABB-point collisions.
 * @param start where to draw the ray FROM.
 * @param end where the ray should END.
 * @param box the bounding box to test this ray against.
 * @param returnFirstHit if this function should return after the first collision has been detected.
 * @return bool if this ray has hit something.
 */
bool Physics::Ray(DirectX::SimpleMath::Vector3& start, DirectX::SimpleMath::Vector3& end, const AABB& box, bool returnFirstHit)
{
	std::vector<DirectX::SimpleMath::Vector3> points = Maths::BresenhamsLine(start, end);

	if (points.size() <= 0)
		return false;

	for (size_t i = 0; i < points.size(); ++i)
	{
		if (Physics::PointToAABB(box, points[i]))
		{
			if(returnFirstHit)
				return true;
		}
	}

	return false;
}
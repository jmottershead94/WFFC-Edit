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
		&& (point.z > box.front.z && point.z < box.back.z))
	{
		return true;
	}

	return false;
}
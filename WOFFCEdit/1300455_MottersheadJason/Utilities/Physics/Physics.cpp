#include "Physics.h"

std::unique_ptr<Physics> instance = nullptr;

Physics::Physics()
{
	if (instance == nullptr)
		instance = std::make_unique<Physics>(*this);
}

Physics::~Physics()
{}

bool Physics::PointToAABB(const AABB& box, DirectX::SimpleMath::Vector3& point)
{
	return
	(
		((point.x > box.vecMin.x && point.x <= box.vecMax.x) &&
		(point.y > box.vecMin.y && point.y <= box.vecMax.y) &&
		(point.z > box.vecMin.z && point.z <= box.vecMax.z))
	);
}

bool Physics::Ray(DirectX::SimpleMath::Vector3& start, DirectX::SimpleMath::Vector3& end, const AABB& box, bool returnFirstHit)
{
	std::vector<DirectX::SimpleMath::Vector3> points = Maths::BresenhamsLine(start, end);

	// No points to test!
	if (points.size() <= 0)
		return false;

	bool result = true;

	// Loop through each of the points and compare them to the AABB.
	for (size_t i = 0; i < points.size(); ++i)
	{
		if (Physics::PointToAABB(box, points[i]))
		{
			result &= true;

			if (returnFirstHit)
				return true;
		}
		else
			result &= false;
	}

	return false;
}
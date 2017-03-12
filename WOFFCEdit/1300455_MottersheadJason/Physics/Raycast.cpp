#include "Raycast.h"

Raycast::Raycast() :
	_start(DirectX::SimpleMath::Vector3::Zero),
	_end(DirectX::SimpleMath::Vector3::Zero),
	_direction(DirectX::SimpleMath::Vector3::Zero)
{}

Raycast::~Raycast()
{}

bool Raycast::Hit(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& direction, const float distance, Collider& collider, const bool& returnFirstHit)
{
	// Calculate the end point of the ray.
	DirectX::SimpleMath::Vector3 testEnd;
	testEnd = start + (direction * distance);

	// Obtain a list of points on the ray.
	std::vector<DirectX::SimpleMath::Vector3> points = Maths::BresenhamsLine(start, Maths::RoundVector3(testEnd));

	// No points to test!
	if (points.size() <= 0)
		return false;

	bool result = true;

	// Loop through each of the points and compare them to the collider.
	for (size_t i = 0; i < points.size(); ++i)
	{
		if (collider.PointCollision(points[i]))
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
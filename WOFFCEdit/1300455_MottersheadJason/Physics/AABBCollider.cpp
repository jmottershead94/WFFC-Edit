#include "AABBCollider.h"

AABBCollider::AABBCollider()
	: Collider()
{}

AABBCollider::AABBCollider(const bool isKinematic, const DirectX::SimpleMath::Vector3& newPosition, const DirectX::SimpleMath::Vector3& newRotation, const DirectX::SimpleMath::Vector3& newScale, const DirectX::SimpleMath::Vector3& newOffset) 
	: Collider::Collider(isKinematic, newPosition, newRotation, newScale, newOffset)
{}

AABBCollider::~AABBCollider()
{}

void AABBCollider::Update(const DirectX::SimpleMath::Vector3& newPosition, const DirectX::SimpleMath::Vector3& newRotation, const DirectX::SimpleMath::Vector3& newScale)
{
	scale = newScale;
	rotation = newRotation;
	position = newPosition;	

	SetBounds();
}

bool const AABBCollider::PointCollision(const DirectX::SimpleMath::Vector3& point)
{
	return
	(
		(point.x >= _vecMin.x && point.x <= _vecMax.x) &&
		(point.y >= _vecMin.y && point.y <= _vecMax.y) &&
		(point.z >= _vecMin.z && point.z <= _vecMax.z)
	);
}

bool const AABBCollider::AABBCollision(const Collider& collider)
{
	return false;
}

void AABBCollider::SetBounds()
{
	// Setting up the maximum and minimum positions for the collider.
	halfScale = (scale * 0.5f);
	DirectX::SimpleMath::Vector3 objectMax(offset.x + position.x + halfScale.x, offset.y + position.y + halfScale.y, offset.z + position.z + halfScale.z);
	DirectX::SimpleMath::Vector3 objectMin(offset.x + position.x - scale.x, offset.y + position.y - scale.y, offset.z + position.z - scale.z);

	// Setting the AABB maximum and minimum points.
	_vecMax = objectMax;
	_vecMin = objectMin;
}
#include "AABBCollider.h"

AABBCollider::AABBCollider()
	: Collider()
{
	SetBounds(position, scale);
}

AABBCollider::AABBCollider(const bool isKinematic, const DirectX::SimpleMath::Vector3& newPosition, const DirectX::SimpleMath::Vector3& newRotation, const DirectX::SimpleMath::Vector3& newScale, const DirectX::SimpleMath::Vector3& newOffset) 
	: Collider::Collider(isKinematic, newPosition, newRotation, newScale, newOffset)
{
	SetBounds(newPosition, newScale);
}

AABBCollider::~AABBCollider()
{}

void AABBCollider::Update(const DirectX::SimpleMath::Vector3& newPosition, const DirectX::SimpleMath::Vector3& newRotation, const DirectX::SimpleMath::Vector3& newScale)
{
	position = newPosition;
	rotation = newRotation;
	scale = newScale;

	SetBounds(newPosition, newScale);
}

bool const AABBCollider::PointCollision(const DirectX::SimpleMath::Vector3& point)
{
	return
	(
		(point.x > _vecMin.x && point.x <= _vecMax.x) &&
		(point.y > _vecMin.y && point.y <= _vecMax.y) &&
		(point.z > _vecMin.z && point.z <= _vecMax.z)
	);
}

bool const AABBCollider::AABBCollision(const Collider& collider)
{
	return false;
}

void AABBCollider::SetBounds(const DirectX::SimpleMath::Vector3& newPosition, const DirectX::SimpleMath::Vector3& newScale)
{
	// Setting up the maximum and minimum positions for the collider.	
	DirectX::SimpleMath::Vector3 objectMax(newPosition.x + newScale.x, newPosition.y + newScale.y, newPosition.z + newScale.z);
	DirectX::SimpleMath::Vector3 objectMin(newPosition.x - newScale.x, newPosition.y - newScale.y, newPosition.z - newScale.z);

	// Setting the AABB maximum and minimum points.
	_vecMax = objectMax;
	_vecMin = objectMin;
}
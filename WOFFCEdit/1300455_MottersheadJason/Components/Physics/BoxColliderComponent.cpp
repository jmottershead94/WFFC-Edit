#include "BoxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent()
{
	SetKinematic(true);
	SetPosition(DirectX::SimpleMath::Vector3::Zero);
	SetRotation(DirectX::SimpleMath::Vector3::Zero);
	SetScale(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
	SetHalfScale();
	SetOffset(DirectX::SimpleMath::Vector3::Zero);
	SetBounds();
}

BoxColliderComponent::BoxColliderComponent(const BoxColliderComponent* collider)
{
	SetKinematic(collider->Kinematic());
	SetPosition(collider->Position());
	SetRotation(collider->Rotation());
	SetScale(collider->Scale());
	SetHalfScale();
	SetOffset(collider->Offset());
	SetBounds();
}

BoxColliderComponent::BoxColliderComponent(const bool isKinematic, const DirectX::SimpleMath::Vector3& newPosition, const DirectX::SimpleMath::Vector3& newRotation, const DirectX::SimpleMath::Vector3& newScale, const DirectX::SimpleMath::Vector3& newOffset)
{
	SetKinematic(isKinematic);
	SetPosition(newPosition);
	SetRotation(newRotation);
	SetScale(newScale);
	SetHalfScale();
	SetOffset(newOffset);
	SetBounds();
}

BoxColliderComponent::~BoxColliderComponent()
{}

void BoxColliderComponent::Update(const double & dt, const DirectX::SimpleMath::Vector3 & newPosition, const DirectX::SimpleMath::Vector3 & newRotation, const DirectX::SimpleMath::Vector3 & newScale)
{
	if (!Enabled())
		return;

	UNUSED(dt);
	position = newPosition;
	rotation = newRotation;
	scale = newScale;
	SetBounds();
}

bool const BoxColliderComponent::PointCollision(const DirectX::SimpleMath::Vector3 & point)
{
	if (!Enabled())
		return false;

	return
	(
		(point.x >= _vecMin.x && point.x <= _vecMax.x) &&
		(point.y >= _vecMin.y && point.y <= _vecMax.y) &&
		(point.z >= _vecMin.z && point.z <= _vecMax.z)
	);
}

bool const BoxColliderComponent::AABBCollision(const ColliderComponent & collider)
{
	if (!Enabled())
		return false;

	return false;
}

void BoxColliderComponent::SetBounds()
{
	if (!Enabled())
		return;

	// Setting up the maximum and minimum positions for the collider.
	halfScale = (scale * 0.5f);
	DirectX::SimpleMath::Vector3 objectMax(offset.x + position.x + halfScale.x, offset.y + position.y + halfScale.y, offset.z + position.z + halfScale.z);
	DirectX::SimpleMath::Vector3 objectMin(offset.x + position.x - scale.x, offset.y + position.y - scale.y, offset.z + position.z - scale.z);

	// Setting the AABB maximum and minimum points.
	_vecMax = objectMax;
	_vecMin = objectMin;
}
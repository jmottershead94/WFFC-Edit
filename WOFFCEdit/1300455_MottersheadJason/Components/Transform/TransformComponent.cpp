#include "TransformComponent.h"

TransformComponent::TransformComponent() :
	_position(DirectX::SimpleMath::Vector3::Zero),
	_rotation(DirectX::SimpleMath::Vector3::Zero),
	_scale(1.0f, 1.0f, 1.0f),
	_lookAt(DirectX::SimpleMath::Vector3::Zero),
	_right(DirectX::SimpleMath::Vector3::UnitX),
	_up(DirectX::SimpleMath::Vector3::UnitY),
	_forward(DirectX::SimpleMath::Vector3::UnitZ)
{}

TransformComponent::~TransformComponent()
{}

void TransformComponent::CalculateVectors()
{
	// Calculating the forward vector.
	_forward.x = sin(Maths::DegreesToRadians(_rotation.y));
	_forward.y = tan(Maths::DegreesToRadians(_rotation.x));
	_forward.z = cos(Maths::DegreesToRadians(_rotation.y));
	_forward.Normalize();

	// Calculating the right and up vectors.
	_forward.Cross(DirectX::SimpleMath::Vector3::UnitY, _right);
	_forward.Cross(_right, _up);
}

void TransformComponent::CalculateLookAt()
{
	_lookAt = _position + _forward;
}
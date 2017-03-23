#include "TransformComponent.h"

TransformComponent::TransformComponent() :
	_position(0.0f, 0.0f, 0.0f),
	_rotation(0.0f, 0.0f, 0.0f),
	_scale(1.0f, 1.0f, 1.0f)
{}

TransformComponent::~TransformComponent()
{}
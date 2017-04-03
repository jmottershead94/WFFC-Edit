#include "Camera.h"

Camera::Camera(const DirectX::SimpleMath::Vector3 position, const float speed, const float rotateRate) :
	_speed(speed),
	_rotateRate(rotateRate)
{
	_transform.SetPosition(position);
	_transform.SetLookAt(DirectX::SimpleMath::Vector3::Zero);
}

Camera::~Camera()
{}

void Camera::Controls(const double& dt)
{
	UNUSED(dt);

#if TOOL_EDITOR
	if(CrossPlatformInput::CameraActivationPressed())
	{
		// Rotating the camera right and left.
		if (CrossPlatformInput::RotateRight())
			_transform.Rotate(0.0f, -_rotateRate, 0.0f);
		else if (CrossPlatformInput::RotateLeft())
			_transform.Rotate(0.0f, _rotateRate, 0.0f);

		_transform.SetRotationX(Maths::ClampFloat(_transform.Rotation().x, -_rotationXClamp, _rotationXClamp));

		// Rotating the camera up and down.
		if (Utils::InvertCamera())
		{
			if (CrossPlatformInput::RotateDown() && _transform.Rotation().x < 90.0f)
				_transform.Rotate(_rotateRate, 0.0f, 0.0f);
			if (CrossPlatformInput::RotateUp() && _transform.Rotation().x > -90.0f)
				_transform.Rotate(-_rotateRate, 0.0f, 0.0f);
		}
		else
		{
			if (CrossPlatformInput::RotateUp() && _transform.Rotation().x < 90.0f)
				_transform.Rotate(_rotateRate, 0.0f, 0.0f);
			if (CrossPlatformInput::RotateDown() && _transform.Rotation().x > -90.0f)
				_transform.Rotate(-_rotateRate, 0.0f, 0.0f);
		}
	}
#endif

	// Setup the right, up and forward vectors for this transform.
	_transform.CalculateVectors();

#if TOOL_EDITOR
	if (CrossPlatformInput::CameraActivationPressed())
	{
		// Moving forward and backward.
		if (CrossPlatformInput::MoveForward())
			_transform.Translate(_transform.Forward() * _speed);
		if (CrossPlatformInput::MoveBack())
			_transform.Translate(_transform.Forward() * -_speed);

		// Moving right and left.
		if (CrossPlatformInput::MoveRight())
			_transform.Translate(_transform.Right() * _speed);
		if (CrossPlatformInput::MoveLeft())
			_transform.Translate(_transform.Right() * -_speed);

		// Moving up and down.
		if (CrossPlatformInput::MoveUp())
			_transform.Translate(DirectX::SimpleMath::Vector3::UnitY * _speed);
		if (CrossPlatformInput::MoveDown())
			_transform.Translate(DirectX::SimpleMath::Vector3::UnitY * -_speed);
	}
#endif

	// Update the look at point with the new position and forward vector.
	_transform.CalculateLookAt();
}

void Camera::Update(const double& dt)
{
	Controls(dt);
}
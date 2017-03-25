#include "Camera.h"

Camera::Camera(const DirectX::SimpleMath::Vector3 position, InputCommands& input, const float speed, const float rotateRate) :
	_speed(speed),
	_rotateRate(rotateRate),
	_input(&input)
{
	_transform.SetPosition(position);
	_transform.SetLookAt(DirectX::SimpleMath::Vector3::Zero);
}

Camera::~Camera()
{}

void Camera::Controls(const double& dt)
{
	UNUSED(dt);

	if (_input->rightMouseDown)
	{
		// Rotating the camera right and left.
		if (_input->rightMouseDragRight || _input->rotRight)
			_transform.Rotate(0.0f, -_rotateRate, 0.0f);
		else if (_input->rightMouseDragLeft || _input->rotLeft)
			_transform.Rotate(0.0f, _rotateRate, 0.0f);

		// Clamping the x rotation.
		if (_transform.Rotation().x >= _rotationXClamp)
			_transform.SetRotation(_rotationXClamp - _rotateRate, _transform.Rotation().y, _transform.Rotation().z);
		if (_transform.Rotation().x <= -_rotationXClamp)
			_transform.SetRotation(-_rotationXClamp + _rotateRate, _transform.Rotation().y, _transform.Rotation().z);

		// Rotating the camera up and down.
		if ((_input->rotUp || _input->rightMouseDragUp) && _transform.Rotation().x < 90.0f)
			_transform.Rotate(_rotateRate, 0.0f, 0.0f);
		if ((_input->rotDown || _input->rightMouseDragDown) && _transform.Rotation().x > -90.0f)
			_transform.Rotate(-_rotateRate, 0.0f, 0.0f);
	}

	// Setup the right, up and forward vectors for this transform.
	_transform.CalculateVectors();

	if (_input->rightMouseDown)
	{
		// Moving forward and backward.
		if (_input->forward)
			_transform.Translate(_transform.Forward() * _speed);
		if (_input->back)
			_transform.Translate(_transform.Forward() * -_speed);

		// Moving right and left.
		if (_input->right)
			_transform.Translate(_transform.Right() * _speed);
		if (_input->left)
			_transform.Translate(_transform.Right() * -_speed);

		// Moving up and down.
		if (_input->up)
			_transform.Translate(DirectX::SimpleMath::Vector3::UnitY * _speed);
		if (_input->down)
			_transform.Translate(DirectX::SimpleMath::Vector3::UnitY * -_speed);
	}

	// Update the look at point with the new position and forward vector.
	_transform.CalculateLookAt();
}

void Camera::Update(const double& dt)
{
	Controls(dt);
}
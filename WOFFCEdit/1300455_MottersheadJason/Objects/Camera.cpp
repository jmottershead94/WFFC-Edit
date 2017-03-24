#include "Camera.h"

Camera::Camera() :
	_speed(0.0f),
	_rotateRate(0.0f),
	_position(0.0f, 3.7f, -3.5f),
	_rotation(DirectX::SimpleMath::Vector3::Zero),
	_lookAt(DirectX::SimpleMath::Vector3::Zero),
	_right(DirectX::SimpleMath::Vector3::UnitX),
	_up(DirectX::SimpleMath::Vector3::UnitY),
	_forward(DirectX::SimpleMath::Vector3::UnitZ),
	_input(nullptr)
{}

Camera::~Camera()
{}

void Camera::Init(InputCommands& input, const float speed, const float rotateRate)
{
	_input = &input;
	_speed = speed;
	_rotateRate = rotateRate;
}

void Camera::Controls(const double & dt)
{
	UNUSED(dt);

	// Rotating left and right.
	if (/*_input->rightMouseDown && */_input->rotRight)
		_rotation.y -= _rotateRate;
	if (/*_input->rightMouseDown && */_input->rotLeft)
		_rotation.y += _rotateRate;

	// Calculate the forward vector.
	_forward.x = sin(Maths::DegreesToRadians(_rotation.y));
	_forward.z = cos(Maths::DegreesToRadians(_rotation.y));

	// Calculating the right and up vectors from the forward vector.
	// right = forward: (x, y, z) cross unit y: (0, 1, 0)
	// up = forward: (x, y, z) cross right: (x, y, z)
	_forward.Cross(DirectX::SimpleMath::Vector3::UnitY, _right);
	_forward.Cross(_right, _up);

	// Moving forward and backward.
	if (/*_input->rightMouseDown && */_input->forward)
		_position += (_forward * _speed);
	if (/*_input->rightMouseDown && */_input->back)
		_position -= (_forward * _speed);

	// Moving right and left.
	if (/*_input->rightMouseDown && */_input->right)
		_position += (_right * _speed);
	if (/*_input->rightMouseDown && */_input->left)
		_position -= (_right * _speed);

	// Moving up and down.
	if (/*_input->rightMouseDown && */_input->up)
		_position += (_up * _speed);
	if (/*_input->rightMouseDown && */_input->down)
		_position -= (_up * _speed);

	// Update the look at point.
	_lookAt = _position + _forward;
}

void Camera::Update(const double& dt)
{
	Controls(dt);
}
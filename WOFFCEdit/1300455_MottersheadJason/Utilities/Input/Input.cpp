#include "Input.h"

static std::unique_ptr<Input> instance = nullptr;

Input::Input()
{
	if (instance == nullptr)
		instance = std::make_unique<Input>(*this);
}

Input::~Input()
{}

void Input::SetKeyDown(const int key)
{
	instance->_pc._keyboard._keys[key] = true;
}

void Input::SetKeyUp(const int key)
{
	instance->_pc._keyboard._keys[key] = false;
}

void Input::SetLeftMousePressed(const bool value)
{
	instance->_pc._mouse._left = value;
}

void Input::SetRightMousePressed(const bool value)
{
	instance->_pc._mouse._right = value;
}

void Input::SetLeftMouseReleased(const bool value)
{
	instance->_pc._mouse._leftRelease = value;
}

void Input::SetRightMouseReleased(const bool value)
{
	instance->_pc._mouse._rightRelease = value;
}

void Input::SetLeftMouseDrag(const bool value)
{
	instance->_pc._mouse._leftDrag = value;
}

void Input::SetRightMouseDrag(const bool value)
{
	instance->_pc._mouse._rightDrag = value;
}

void Input::SetLeftMouseDouble(const bool value)
{
	instance->_pc._mouse._leftDoubleClick = value;
}

void Input::SetRightMouseDouble(const bool value)
{
	instance->_pc._mouse._rightDoubleClick = value;
}

void Input::SetLeftDragAxis(const float drag)
{
	instance->_pc._mouse._leftDragAxis = drag;
}

void Input::SetRightDragAxis(const float drag)
{
	instance->_pc._mouse._rightDragAxis = drag;
}

void Input::SetMouseX(const int x)
{
	instance->_pc._mouse._x = x;
}

void Input::SetMouseY(const int y)
{
	instance->_pc._mouse._y = y;
}

bool Input::LeftMousePressed()
{
	return instance->_pc._mouse._left;
}

bool Input::RightMousePressed()
{
	return instance->_pc._mouse._right;
}

bool Input::LeftMouseReleased()
{
	return instance->_pc._mouse._leftRelease;
}

bool Input::RightMouseReleased()
{
	return instance->_pc._mouse._rightRelease;
}

bool Input::LeftMouseDrag()
{
	return instance->_pc._mouse._leftDrag;
}

bool Input::RightMouseDrag()
{
	return instance->_pc._mouse._rightDrag;
}

bool Input::LeftMouseDouble()
{
	return instance->_pc._mouse._leftDoubleClick;
}

bool Input::RightMouseDouble()
{
	return instance->_pc._mouse._rightDoubleClick;
}

float Input::LeftMouseDragAxis()
{
	return instance->_pc._mouse._leftDragAxis;
}

float Input::RightMouseDragAxis()
{
	return instance->_pc._mouse._rightDragAxis;
}

bool Input::IsKeyDown(WPARAM key)
{
	return instance->_pc._keyboard._keys[key];
}

int Input::GetMouseX()
{
	return instance->_pc._mouse._x;
}

int Input::GetMouseY()
{
	return instance->_pc._mouse._y;
}
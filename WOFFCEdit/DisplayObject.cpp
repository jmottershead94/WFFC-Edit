#include "DisplayObject.h"

DisplayObject::DisplayObject() : BaseObject()
{
	m_model = NULL;
	m_texture_diffuse = NULL;
	m_render = true;
	m_wireframe = false;
}

DisplayObject::~DisplayObject()
{}

void DisplayObject::OnLeftMouseClick()
{
	// Reverse the focus of this object.
	inFocus = !inFocus;
}

void DisplayObject::OnLeftMouseDoubleClick()
{
	// Move the camera to the position of this object.
	// We need a pointer to the main camera.
	// Make a camera class...
}
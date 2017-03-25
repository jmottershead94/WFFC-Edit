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
	// Move the camera over to this object.
	camera->Transform().SetPosition(Maths::Lerp(camera->Transform().Position(), transform->Position(), 0.2f));
}
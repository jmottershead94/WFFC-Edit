#include "PrimitiveObject.h"

PrimitiveObject::PrimitiveObject() : BaseObject()
{
	_primitive = nullptr;
	_texture_diffuse = nullptr;
	_render = true;
	_wireframe = false;
}

PrimitiveObject::~PrimitiveObject()
{}

void PrimitiveObject::OnLeftMouseClick()
{
	// Reverse the focus of this object.
	inFocus = !inFocus;
}

void PrimitiveObject::OnLeftMouseDoubleClick()
{
	// Move the camera over to this object.
	camera->Transform().SetPosition(Maths::Lerp(camera->Transform().Position(), transform->Position(), 0.2f));
}
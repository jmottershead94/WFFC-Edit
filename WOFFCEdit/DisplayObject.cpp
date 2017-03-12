#include "DisplayObject.h"

DisplayObject::DisplayObject()
{
	m_model = NULL;
	m_texture_diffuse = NULL;
	m_orientation.x = 0.0f;
	m_orientation.y = 0.0f;
	m_orientation.z = 0.0f;
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
	m_scale.x = 0.0f;
	m_scale.y = 0.0f;
	m_scale.z = 0.0f;
	m_render = true;
	m_wireframe = false;
}

DisplayObject::~DisplayObject()
{
	//if (_collider)
	//{
	//	delete _collider;
	//}
}

void DisplayObject::AddCollider()
{
	_collider = new AABBCollider();
	_collider->Update(m_position, m_orientation, m_scale);
}

void DisplayObject::Update()
{
	_collider->Update(m_position, m_orientation, m_scale);
}
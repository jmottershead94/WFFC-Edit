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

bool DisplayObject::ClickedOn(DirectX::SimpleMath::Matrix& worldMatrix, DirectX::SimpleMath::Vector3& camPosition, DirectX::SimpleMath::Vector3& camForward)
{
	// Make sure the collider is with this object.
	_collider->Update(m_position, m_orientation, m_scale);

	DirectX::SimpleMath::Vector3 start(Utils::GetCursorPositionInWorld(worldMatrix, camPosition));
	DirectX::SimpleMath::Vector3 end(start.x, start.y, camPosition.z);
	
	// Cast a ray from the cursor to this object and see if it hits.
	bool rayHit = _ray.Hit(start, end, *_collider, true);

	if (rayHit)
		_inFocus = true;

	return rayHit;
}

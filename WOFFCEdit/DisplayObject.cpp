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
}

DisplayObject::~DisplayObject()
{
//	delete m_texture_diffuse;
}

void DisplayObject::AddCollider()
{
	_position.x = m_position.x;
	_position.y = m_position.y;
	_position.z = m_position.z;

	// Setting up the maximum and minimum positions for the collider.	
	DirectX::SimpleMath::Vector3 objectMax(_position.x + m_scale.x, _position.y + m_scale.y, _position.z + m_scale.z);
	DirectX::SimpleMath::Vector3 objectMin(_position.x - m_scale.x, _position.y - m_scale.y, _position.z - m_scale.z);

	// Setting up the AABB for this display object.
	_aabb.vecMax = objectMax;
	_aabb.vecMin = objectMin;
}

bool DisplayObject::ClickedOn(DirectX::SimpleMath::Matrix& worldMatrix, DirectX::SimpleMath::Vector3& camPosition, DirectX::SimpleMath::Vector3& camForward)
{
	DirectX::SimpleMath::Vector3 start(Utils::GetCursorPositionInWorld(worldMatrix, camPosition));
	DirectX::SimpleMath::Vector3 end(start.x, start.y, camPosition.z);

	bool rayHit = Physics::Ray(start, end, _aabb, true);

	// Cast a ray from the cursor to this object and see if it hits.
	if (rayHit)
		_inFocus = true;

	return rayHit;
}
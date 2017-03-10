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

/*
 * Adds a collider to this object.
 */
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

/*
 * Provides a way to check if this scene object has been clicked on.
 * @param worldMatrix used to help calculate the cursor position in the world.
 * @param camPosition used to help determine the cursor position in the world.
 * @param camForward the direction the camera is looking.
 * @return bool if this object has been clicked on.
 */
bool DisplayObject::ClickedOn(DirectX::SimpleMath::Matrix& worldMatrix, DirectX::SimpleMath::Vector3& camPosition, DirectX::SimpleMath::Vector3& camForward)
{
	float rayDistance = 3.0f;
	DirectX::SimpleMath::Vector3 start(Utils::GetCursorPositionInWorld(worldMatrix, camPosition));
	DirectX::SimpleMath::Vector3 roundedStart(Maths::RoundVector3(start));

	// Setup the rounded ending distance for the ray.
	DirectX::SimpleMath::Vector3 end(start.x, start.y, start.z);
	end = end.Cross(camForward);
	end.z *= rayDistance;
	DirectX::SimpleMath::Vector3 roundedEnd(Maths::RoundVector3(end));

	bool rayHit = Physics::Ray(roundedStart, roundedEnd, _aabb, true);

	// Cast a ray from the cursor to this object and see if it hits.
	if (rayHit)
		_inFocus = true;

	return rayHit;
}

///*
// * Called every frame.
// * @param camForward the direction the camera is looking.
// */
//void DisplayObject::Update(DirectX::SimpleMath::Matrix& worldMatrix, DirectX::SimpleMath::Vector3& camPosition, DirectX::SimpleMath::Vector3& camForward)
//{
//	ClickedOn(worldMatrix, camPosition, camForward);
//}
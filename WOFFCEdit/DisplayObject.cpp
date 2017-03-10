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

	DirectX::SimpleMath::Vector3 objectLeft(_position.x - m_scale.x, _position.y, _position.z);
	DirectX::SimpleMath::Vector3 objectRight(_position.x + m_scale.x, _position.y, _position.z);
	DirectX::SimpleMath::Vector3 objectUp(_position.x, _position.y + m_scale.y, _position.z);
	DirectX::SimpleMath::Vector3 objectDown(_position.x, _position.y - m_scale.y, _position.z);
	DirectX::SimpleMath::Vector3 objectFront(_position.x, _position.y, _position.z + m_scale.z);
	DirectX::SimpleMath::Vector3 objectBack(_position.x, _position.y, _position.z - m_scale.z);

	// Setting up the AABB collider for the display object.
	_aabb.back = objectBack;
	_aabb.front = objectFront;
	_aabb.top = objectUp;
	_aabb.bottom = objectDown;
	_aabb.left = objectLeft;
	_aabb.right = objectRight;
}

/*
 * Provides a way to check if this scene object has been clicked on.
 * @param camForward the direction the camera is looking.
 * @return bool if this object has been clicked on.
 */
bool DisplayObject::ClickedOn(DirectX::SimpleMath::Matrix& worldMatrix, DirectX::SimpleMath::Vector3& camPosition, DirectX::SimpleMath::Vector3& camForward)
{
	float rayDistance = 10.0f;
	DirectX::SimpleMath::Vector3 start(Utils::GetCursorPositionInWorld(worldMatrix, camPosition));
	DirectX::SimpleMath::Vector3 roundedStart(Maths::RoundVector3(start));

	DirectX::SimpleMath::Vector3 end(start.x, start.y, start.z + rayDistance);
	end = end.Cross(camForward);
	DirectX::SimpleMath::Vector3 roundedEnd(Maths::RoundVector3(end));

	std::vector<DirectX::SimpleMath::Vector3> points = Maths::BresenhamsLine(start, end);

	bool objectFocus = false;
	
	/*for (size_t i = 0; i < points.size(); ++i)
	{
		if (Physics::PointToAABB(_aabb, points[i]))
		{
			objectFocus = true;
			break;
		}
	}*/

	return objectFocus;
}

/*
 * Called every frame.
 * @param camForward the direction the camera is looking.
 */
void DisplayObject::Update(DirectX::SimpleMath::Matrix& worldMatrix, DirectX::SimpleMath::Vector3& camPosition, DirectX::SimpleMath::Vector3& camForward)
{
	ClickedOn(worldMatrix, camPosition, camForward);
}
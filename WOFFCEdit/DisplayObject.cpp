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
 * Provides a way to check if this scene object has been clicked on.
 * @param camForward the direction the camera is looking.
 * @return bool if this object has been clicked on.
 */
bool DisplayObject::ClickedOn(DirectX::SimpleMath::Vector3& camForward)
{
	_position.x = m_position.x;
	_position.y = m_position.y;
	_position.z = m_position.z;

	float rayDistance = 10.0f;
	DirectX::SimpleMath::Vector3 start(Utils::GetCursorPositionInWindow() / 512.0f);
	DirectX::SimpleMath::Vector3 end(start.x, start.y, start.z + rayDistance);		// SIDE NOTE: This end needs manipulating based on the camera forward vector i.e multiply by the camera forward.
	end *= camForward;

	DirectX::SimpleMath::Vector3 objectLeft(_position.x - m_scale.x, _position.y, _position.z);
	DirectX::SimpleMath::Vector3 objectRight(_position.x + m_scale.x, _position.y, _position.z);
	DirectX::SimpleMath::Vector3 objectUp(_position.x, _position.y + m_scale.y, _position.z);
	DirectX::SimpleMath::Vector3 objectDown(_position.x, _position.y - m_scale.y, _position.z);

	bool objectFocus = true;

	//objectFocus &= Maths::IsPointBetween(start, end, _position);

	objectFocus &= Maths::IsPointBetween(start, end, objectLeft);
	objectFocus &= Maths::IsPointBetween(start, end, objectRight);
	objectFocus &= Maths::IsPointBetween(start, end, objectUp);
	objectFocus &= Maths::IsPointBetween(start, end, objectDown);

	return objectFocus;
}

/*
 * Called every frame.
 * @param camForward the direction the camera is looking.
 */
void DisplayObject::Update(DirectX::SimpleMath::Vector3& camForward)
{
	//_inFocus = ClickedOn(camForward);
	if (ClickedOn(camForward))
	{
		_inFocus = !_inFocus;
	}
}
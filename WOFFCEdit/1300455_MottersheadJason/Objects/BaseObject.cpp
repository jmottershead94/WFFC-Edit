#include "BaseObject.h"

BaseObject::BaseObject() :
	_inFocus(false),
	_collider(nullptr)
{}

BaseObject::~BaseObject()
{}

void BaseObject::AddCollider()
{
	_collider = new AABBCollider();
	_collider->Update(m_position, m_orientation, m_scale);
}

void BaseObject::Update()
{
	_collider->Update(m_position, m_orientation, m_scale);
}

void BaseObject::OnNotify(const EventType currentEvent)
{}

void BaseObject::OnNotify(const EventType currentEvent, const DirectX::SimpleMath::Vector3& cursorPosition, const DirectX::SimpleMath::Vector3& cameraLookDirection)
{
	bool rayHit = _ray.Hit(Maths::RoundVector3(cursorPosition), cameraLookDirection, 10.0f, *_collider);

	// If the cursor is "looking" at this object.
	if (!rayHit)
		return;

	// Process each event.
	switch (currentEvent)
	{
		// If the user has left clicked on this object.
		case (EventType::EVENT_LEFT_MOUSE_CLICK) :
		{
			OnLeftMouseClick();
			break;
		}
		// If the user has clicked and is dragging their mouse on this object.
		case (EventType::EVENT_LEFT_MOUSE_DRAG) :
		{
			OnLeftMouseDrag();
			break;
		}
		// If the user is holding the left mouse button down on this object.
		case (EventType::EVENT_LEFT_MOUSE_HOLD) :
		{
			OnLeftMouseHeld();
			break;
		}
		// If the user has released the left mouse on this object.
		case (EventType::EVENT_LEFT_MOUSE_RELEASE) :
		{
			OnLeftMouseReleased();
			break;
		}
		// If the user has right clicked on this object.
		case (EventType::EVENT_RIGHT_MOUSE_CLICK) :
		{
			OnRightMouseClick();
			break;
		}
	}
}
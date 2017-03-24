#include "BaseObject.h"

BaseObject::BaseObject() :
	inFocus(false)
{
	// Adding a standard transform component.
	transform = AddComponent<TransformComponent>();
	transform->SetPosition(DirectX::SimpleMath::Vector3::Zero);
	transform->SetRotation(DirectX::SimpleMath::Vector3::Zero);
	transform->SetScale(DirectX::SimpleMath::Vector3::Zero);

	// Adding standard collider components for editor and "game" use.
	collider = AddComponent<BoxColliderComponent>();
	editorCollider = new BoxColliderComponent(dynamic_cast<BoxColliderComponent*>(collider));

	// Components can be enabled/disabled.
	//collider->SetEnabled(true);
	//editorCollider->SetEnabled(false);
	//editorCollider->Enabled();
}

BaseObject::~BaseObject()
{}

void BaseObject::Update(const double& dt)
{
	collider->Update(dt, transform->GetPosition(), transform->GetRotation(), transform->GetScale());
	editorCollider->Update(dt, transform->GetPosition(), transform->GetRotation(), transform->GetScale());
}

void BaseObject::CleanUpComponents()
{
	if (components.size() > 0)
	{
		for (size_t i = 0; i < components.size(); ++i)
			delete components[i];

		components.clear();
	}

	if (editorCollider)
	{
		delete editorCollider;
	}
}

void BaseObject::OnNotify(const EventType currentEvent)
{}

void BaseObject::OnNotify(const EventType currentEvent, const DirectX::SimpleMath::Vector3& cursorPosition, const DirectX::SimpleMath::Vector3& cameraLookDirection)
{
	bool rayHit = ray.Hit(Maths::RoundVector3(cursorPosition), cameraLookDirection, 10.0f, *editorCollider);

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

Component* BaseObject::SearchForComponent(const int id) const
{
	Component* result = nullptr;

	if (components.size() <= 0)
		return result;

	// Loop through all of the components and check for any matching IDs.
	for (size_t i = 0; i < components.size(); ++i)
	{
		Component* currentComponent = components.at(i);

		if (currentComponent->GetID() == id)
			result = currentComponent;
	}

	return result;
}
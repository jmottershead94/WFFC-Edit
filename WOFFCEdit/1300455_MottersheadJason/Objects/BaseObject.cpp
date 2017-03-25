#include "BaseObject.h"

BaseObject::BaseObject() :
	inFocus(false),
	transform(nullptr),
	collider(nullptr),
	editorCollider(nullptr),
	camera(nullptr)
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
	//editorCollider->SetEnabled(true);
	//editorCollider->Enabled();
}

BaseObject::~BaseObject()
{}

void BaseObject::Update(const double& dt)
{
	// Updating the object transform.
	transform->CalculateVectors();
	transform->CalculateLookAt();

	// Updating the object colliders.
	collider->Update(dt, transform->Position(), transform->Rotation(), transform->Scale());
	editorCollider->Update(dt, transform->Position(), transform->Rotation(), transform->Scale());
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
		delete editorCollider;
}

void BaseObject::OnNotify(EventType& currentEvent)
{}

void BaseObject::OnNotify(EventType& currentEvent, const DirectX::SimpleMath::Vector3& cursorPosition, const DirectX::SimpleMath::Vector3& cameraLookDirection)
{
	bool rayHit = ray.Hit(Maths::RoundVector3(cursorPosition), cameraLookDirection, 50.0f, *editorCollider);

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
			currentEvent = EventType::EVENT_NULL;
			break;
		}
		// If the user has clicked and is dragging their mouse on this object.
		case (EventType::EVENT_LEFT_MOUSE_DRAG) :
		{
			OnLeftMouseDrag();
			currentEvent = EventType::EVENT_NULL;
			break;
		}
		// If the user is holding the left mouse button down on this object.
		case (EventType::EVENT_LEFT_MOUSE_HOLD) :
		{
			OnLeftMouseHeld();
			currentEvent = EventType::EVENT_NULL;
			break;
		}
		// If the user has released the left mouse on this object.
		case (EventType::EVENT_LEFT_MOUSE_RELEASE) :
		{
			OnLeftMouseReleased();
			currentEvent = EventType::EVENT_NULL;
			break;
		}
		case (EventType::EVENT_LEFT_MOUSE_CLICK_DOUBLE) :
		{
			OnLeftMouseDoubleClick();
			currentEvent = EventType::EVENT_NULL;
			break;
		}
		// If the user has right clicked on this object.
		case (EventType::EVENT_RIGHT_MOUSE_CLICK) :
		{
			OnRightMouseClick();
			currentEvent = EventType::EVENT_NULL;
			break;
		}
		// If the user has right clicked and dragged the mouse on this object.
		case (EventType::EVENT_RIGHT_MOUSE_DRAG) :
		{
			OnRightMouseDrag();
			currentEvent = EventType::EVENT_NULL;
			break;
		}
		case (EventType::EVENT_NULL):
		{
			break;
		}
		default:
		{
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
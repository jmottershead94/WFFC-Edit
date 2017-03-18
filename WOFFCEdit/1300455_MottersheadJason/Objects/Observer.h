#pragma once

#include "../Utilities/Maths/Maths.h"
#include "../Events/EventTypes.h"

/*
 * Provides a base class that can interact with the event system.
 */
class Observer
{
	public:
		/*
		 * Destructs this instance.
		 */
		virtual ~Observer() {};

		/*
		 * Notifies this object about an event.
		 * @param currentEvent what event has occured (i.e. left mouse click).
		 */
		virtual void OnNotify(const EventType currentEvent) = 0;

		/*
		 * Notifies this object about an event.
		 * @param currentEvent what event has occured (i.e. left mouse click).
		 * @param cursorPosition the position of the cursor in the world.
		 * @param cameraLookDirection the direction the camera is facing.
		 */
		virtual void OnNotify(const EventType currentEvent, const DirectX::SimpleMath::Vector3& cursorPosition, const DirectX::SimpleMath::Vector3& cameraLookDirection) = 0;
};
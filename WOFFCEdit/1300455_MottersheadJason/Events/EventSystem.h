#pragma once

#include "../Objects/Observer.h"

/**
 * A system for notifying observers (basically the subject).
 */
class EventSystem
{
	friend class Editor;

	private:
		bool _enabled;
		std::vector<Observer*> _observers;

		/**
		 * Constructs this instance.
		 */
		explicit EventSystem();

		/**
		 * Destructs this instance.
		 */
		~EventSystem();

		/**
		 * Notifies the event system that something interesting has happened, notify all of the observers.
		 * @param currentEvent what event has occured (i.e. left mouse click).
		 */
		void Notify(EventType currentEvent);

		/**
		 * Notifies the event system that something interesting has happened, notify all of the observers.
		 * @param currentEvent what event has occured (i.e. left mouse click).
		 * @param cursorPosition the position of the cursor in the world.
		 * @param cameraLookDirection the direction the camera is facing.
		 */
		void Notify(EventType currentEvent, const DirectX::SimpleMath::Vector3& cursorPosition, const DirectX::SimpleMath::Vector3& cameraLookDirection);

	public:
		/**
		 * Allows other classes to add new observers to the event system for notifications.
		 * @param observer the new observer to add to the event system.
		 */
		void AddObserver(Observer* observer);

		/**
		 * Allows other classes to remove observers from the event system.
		 * @param observer the observer to remove from the event system.
		 */
		void RemoveObserver(Observer* observer);

		/**
		 * If the event system should be enabled or not.
		 * @param value the current enabled status of the event system.
		 */
		inline void IsEnabled(const bool value) { _enabled = value; }
};
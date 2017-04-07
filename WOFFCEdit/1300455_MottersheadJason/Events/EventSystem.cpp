#include "EventSystem.h"

EventSystem::EventSystem() :
	_enabled(true)
{}

EventSystem::~EventSystem()
{}

void EventSystem::Notify(EventType currentEvent)
{
	// If there are no observers in our event system, or if the event system is disabled, just return.
	if (_observers.empty() || !_enabled)
		return;

	// Loop through each of the observers and notify them of the event.
	for (size_t i = 0; i < _observers.size(); ++i)
		_observers.at(i)->OnNotify(currentEvent);
}

void EventSystem::Notify(EventType currentEvent, const DirectX::SimpleMath::Vector3 & cursorPosition, const DirectX::SimpleMath::Vector3 & cameraLookDirection)
{
	// If there are no observers in our event system, or if the event system is disabled, just return.
	if (_observers.empty() || !_enabled)
		return;

	// Loop through each of the observers and notify them of the event.
	for (size_t i = 0; i < _observers.size(); ++i)
		_observers.at(i)->OnNotify(currentEvent, cursorPosition, cameraLookDirection);
}

void EventSystem::AddObserver(Observer* observer)
{
	// If the specified observer is null, or if the event system is disabled, just return.
	if (!observer || !_enabled)
		return;

	// If the observer is valid, add it to our event system.
	_observers.push_back(observer);
}

void EventSystem::RemoveObserver(Observer* observer)
{
	// If there are currently no observers, or if the specified observer is null, or if the event system is disabled, just return.
	if (_observers.empty() || !observer || !_enabled)
		return;

	// Loop through the observers.
	for (size_t i = 0; i < _observers.size(); ++i)
	{
		// If the specified observer is in our event system, remove it.
		if (observer == _observers[i])
			_observers.erase(_observers.begin() + i);
	}

	_observers.clear();
}
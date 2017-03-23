#pragma once

#include "../Physics/AABBCollider.h"
#include "../Physics/Raycast.h"
#include "../Objects/Observer.h"
#include "../Components/Transform/TransformComponent.h"

/**
 * A base object to be used for providing an interactable object
 * with event system interaction, and also expandable components.
 */
class BaseObject : public Observer
{
	public:
		int m_ID;

		/**
		 * Constructs this instance.
		 */
		explicit BaseObject();

		/**
		 * Destructs this instance.
		 */
		~BaseObject();

		/**
		 * Adds a collider to this object.
		 */
		void AddCollider();

		/**
		 * Called every frame.
		 * @param dt the time passed since the last frame update.
		 */
		void Update(const double& dt);

		/**
		 * Removes all of the components.
		 */
		void RemoveAllComponents();

		/**
		 * Gets a requested component from this object with a given type.
		 * @return const Component* the requested component.
		 */
		template <class T>
		T* GetComponent() const
		{
			T* result = nullptr;

			// If class T doesn't inherit from component, return a nullptr.
			if (!std::is_base_of<Component, T>::value)
				return result;

			// Search for the desired component in our components data structure.
			Component* component = SearchForComponent(T::IDNumber);

			// Cast and return the component.
			result = (T*)(component);
			return result;
		}

		/**
		 * Adds a new component for this object.
		 * @return Component* the new component.
		 */
		template <class T>
		T* AddComponent()
		{
			T* result = nullptr;

			// If class T doesn't inherit from component, return a nullptr.
			if (!std::is_base_of<Component, T>::value)
				return result;

			// If there are components.
			if (components.size() > 0)
			{
				// Obtain the current component we should check for.
				T* componentCheck = (T*)(SearchForComponent(T::IDNumber));

				// If the component doesn't already exist, we should continue on as normal.
				if (componentCheck != nullptr)
					return result;
			}

			// We can now add the new component.
			Component* newComponent = new T();
			components.push_back(newComponent);
			
			// Cast and return the component.
			result = (T*)(newComponent);
			return result;
		}

		/**
		 * Notifies this object about an event.
		 * @param currentEvent what event has occured (i.e. left mouse click).
		 */
		void OnNotify(const EventType currentEvent) override;

		/**
		 * Notifies this object about an event.
		 * @param currentEvent what event has occured (i.e. left mouse click).
		 * @param cursorPosition the position of the cursor in the world.
		 * @param cameraLookDirection the direction the camera is facing.
		 */
		void OnNotify(const EventType currentEvent, const DirectX::SimpleMath::Vector3& cursorPosition, const DirectX::SimpleMath::Vector3& cameraLookDirection) override;

		/**
		 * Allows us to set this object being in focus.
		 * @param value if this object is in focus or not.
		 */
		inline void const SetFocus(const bool value) { _inFocus = value; }

		/**
		 * Allows us to see if this object is in focus.
		 * @return const bool if the object is in focus.
		 */
		inline bool const InFocus() { return _inFocus; }

		/**
		 * Provides access to the collider of this object.
		 * @return const AABBCollider* the collider of this object.
		 */
		inline AABBCollider* const GetCollider() const { return static_cast<AABBCollider*>(_collider); }

		/**
		 * Gets the transform component of this object.
		 * @return TransformComponent& the transform associated with this object.
		 */
		inline TransformComponent& Transform() { return *transform; }

	protected:
		bool _inFocus;
		Collider* _collider;
		Raycast _ray;
		TransformComponent* transform;
		std::vector<Component*> components;

	private:
		/**
		 * Provides a way to get a specific component from this object.
		 * @param id the ID of the component.
		 * @return const Component* the desired component.
		 */
		Component* SearchForComponent(const int id) const;

		/**
		 * Virtual private methods, indicating that inheriting classes CAN 
		 * override these methods if they want to implement the functionality.
		 *
		 * This sort of setup provides a Unity-esque OnMouse event system 
		 * for any inheriting classes.
		 */

		/**
		 * What happens when the user left clicks on this object.
		 */
		virtual void OnLeftMouseClick() {};

		/**
		 * What happens when the user left clicks and drags the mouse on this object.
		 */
		virtual void OnLeftMouseDrag() {};

		/**
		 * What happens when the user left clicks and holds the mouse on this object.
		 */
		virtual void OnLeftMouseHeld() {};

		/**
		 * What happens when the user has released the left mouse button on this object.
		 */
		virtual void OnLeftMouseReleased() {};

		/**
		 * What happens when the user has pressed the right mouse button on this object.
		 */
		virtual void OnRightMouseClick() {};
};
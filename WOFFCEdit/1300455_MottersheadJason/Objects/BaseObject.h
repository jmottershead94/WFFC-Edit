#pragma once

#include "../Physics/AABBCollider.h"
#include "../Physics/Raycast.h"
#include "../Objects/Observer.h"

/*
 * A base object to be used for providing an interactable object
 * with event system interaction.
 */
class BaseObject : public Observer
{
	public:
		int m_ID;
		DirectX::SimpleMath::Vector3			m_position;
		DirectX::SimpleMath::Vector3			m_orientation;
		DirectX::SimpleMath::Vector3			m_scale;

		/*
		 * Constructs this instance.
		 */
		explicit BaseObject();

		/*
		 * Destructs this instance.
		 */
		~BaseObject();

		/*
		 * Adds a collider to this object.
		 */
		void AddCollider();

		/*
		 * Called every frame.
		 */
		void Update();

		/*
		 * Notifies this object about an event.
		 * @param currentEvent what event has occured (i.e. left mouse click).
		 */
		void OnNotify(const EventType currentEvent) override;

		/*
		 * Notifies this object about an event.
		 * @param currentEvent what event has occured (i.e. left mouse click).
		 * @param cursorPosition the position of the cursor in the world.
		 * @param cameraLookDirection the direction the camera is facing.
		 */
		void OnNotify(const EventType currentEvent, const DirectX::SimpleMath::Vector3& cursorPosition, const DirectX::SimpleMath::Vector3& cameraLookDirection) override;

		/*
		 * Allows us to set this object being in focus.
		 * @param value if this object is in focus or not.
		 */
		inline void const SetFocus(const bool value) { _inFocus = value; }

		/*
		 * Allows us to see if this object is in focus.
		 * @return const bool if the object is in focus.
		 */
		inline bool const InFocus() { return _inFocus; }

		/*
		 * Provides access to the collider of this object.
		 * @return const AABBCollider* the collider of this object.
		 */
		inline AABBCollider* const GetCollider() const { return static_cast<AABBCollider*>(_collider); }

	protected:
		bool _inFocus;
		Collider* _collider;
		Raycast _ray;

	private:
		/*
		 * Virtual private methods, indicating that inheriting classes CAN 
		 * override these methods if they want to implement the functionality.
		 *
		 * This sort of setup provides a Unity-esque OnMouse event system 
		 * for any inheriting classes.
		 */

		/*
		 * What happens when the user left clicks on this object.
		 */
		virtual void OnLeftMouseClick() {};

		/*
		 * What happens when the user left clicks and drags the mouse on this object.
		 */
		virtual void OnLeftMouseDrag() {};

		/*
		 * What happens when the user left clicks and holds the mouse on this object.
		 */
		virtual void OnLeftMouseHeld() {};

		/*
		 * What happens when the user has released the left mouse button on this object.
		 */
		virtual void OnLeftMouseReleased() {};

		/*
		 * What happens when the user has pressed the right mouse button on this object.
		 */
		virtual void OnRightMouseClick() {};
};
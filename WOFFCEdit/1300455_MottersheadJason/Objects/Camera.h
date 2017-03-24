#pragma once

#include "../Utilities/Maths/Maths.h"
#include "../../InputCommands.h"

/**
 * A class to store camera functionality.
 */
class Camera
{
	public:
		/**
		 * Constructs this instance.
		 */
		explicit Camera();

		/**
		 * Destructs this instance.
		 */
		~Camera();

		/**
		 * Initialises this instance.
		 * @param input the main input for the tool.
		 * @param speed how fast the camera moves.
		 * @param rotateRate how fast the camera rotates.
		 */
		void Init(InputCommands& input, const float speed, const float rotateRate);

		/**
		 * Provides controls for this object.
		 * @param dt the time passed since the last frame update.
		 */
		void Controls(const double& dt);

		/**
		 * Called every frame.
		 * @param dt the time passed since the last frame update.
		 */
		void Update(const double& dt);

		// This could be optimised by setting up transform components to have look at and up, right, forward etc.
		// Maybe when there is more will power?
		inline void SetPosition(const DirectX::SimpleMath::Vector3& position)			{ _position = position; }
		inline void SetRotation(const DirectX::SimpleMath::Vector3& rotation)			{ _rotation = rotation; }
		inline void SetLookAt(const DirectX::SimpleMath::Vector3& lookAt)				{ _lookAt = lookAt; }
		inline void SetRightVector(const DirectX::SimpleMath::Vector3& right)			{ _right = right; }
		inline void SetUpVector(const DirectX::SimpleMath::Vector3& up)					{ _up = up; }
		inline void SetForwardVector(const DirectX::SimpleMath::Vector3& forward)		{ _forward = forward; }

		inline DirectX::SimpleMath::Vector3 const Position() const		{ return _position; }
		inline DirectX::SimpleMath::Vector3 const Rotation() const		{ return _rotation; }
		inline DirectX::SimpleMath::Vector3 const LookAt() const		{ return _lookAt; }
		inline DirectX::SimpleMath::Vector3 const Right() const			{ return _right; }
		inline DirectX::SimpleMath::Vector3 const Up() const			{ return _up; }
		inline DirectX::SimpleMath::Vector3 const Forward() const		{ return _forward; }

	private:
		float _speed, _rotateRate;
		DirectX::SimpleMath::Vector3 _position, _rotation;
		DirectX::SimpleMath::Vector3 _lookAt;
		DirectX::SimpleMath::Vector3 _right, _up, _forward;
		InputCommands* _input;
};
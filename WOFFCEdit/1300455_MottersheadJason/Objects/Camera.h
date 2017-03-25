#pragma once

#include "../Utilities/Maths/Maths.h"
#include "../Components/Transform/TransformComponent.h"
#include "../../InputCommands.h"

/**
 * A class to store camera functionality.
 */
class Camera
{
	public:
		/**
		 * Constructs this instance.
		 * @param position the starting position of the camera.
		 * @param input the main input for the tool.
		 * @param speed how fast the camera moves.
		 * @param rotateRate how fast the camera rotates.
		 */
		explicit Camera(const DirectX::SimpleMath::Vector3 position, InputCommands& input, const float speed, const float rotateRate);

		/**
		 * Destructs this instance.
		 */
		~Camera();

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

		/**
		 * Provides access to the transform of this object.
		 * @return TransformComponent& the transform.
		 */
		inline TransformComponent& Transform() { return _transform; }

	private:
		const float _rotationXClamp = 90.0f;
		float _speed, _rotateRate;
		TransformComponent _transform;
		InputCommands* _input;
};
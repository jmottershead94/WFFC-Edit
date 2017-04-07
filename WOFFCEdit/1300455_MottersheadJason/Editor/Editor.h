#pragma once

#include "../Utilities/Maths/Maths.h"
#include "../Utilities/Input/CrossPlatformInput.h"
#include "../Events/EventSystem.h"
#include "../Objects/Camera.h"
#include "../../SceneObject.h"
#include "../../Game.h"

/**
 * The editor used for this tool.
 */
class Editor
{
	public:
		enum State
		{
			TRANSLATE,
			ROTATE,
			SCALE
		};

		explicit Editor();
		~Editor();
		void Initialize(Game& game);
		void AddObjectsToEventSystem(std::vector<SceneObject>& sceneObjects);
		void RemoveObjectsFromEventSystem(std::vector<SceneObject>& sceneObjects);

		/**
		 * Provides a copy of all selected objects.
		 */
		void CopyObjects(std::vector<SceneObject>& sceneObjects);

		/**
		 * Provides a way to paste the copied objects into the scene.
		 */
		void PasteObjects(std::vector<SceneObject>& sceneObjects);

		/**
		 * Provides a way to toggle wireframe.
		 */
		void ToggleWireframe();

		/**
		 * Provides specific editor controls.
		 */
		void Controls();

		/**
		 * Provides specific editor updates.
		 */
		void Update(std::vector<SceneObject>& sceneObjects);

		inline void ToggleCopy(const bool value) { _copyEnabled = value; }
		inline void TogglePaste(const bool value) { _pasteEnabled = value; }
		inline void SetState(const State newState) { _editorState = newState; }

		inline std::shared_ptr<Camera>& MainCamera() { return _camera; }
		inline State const CurrentEditorState() const { return _editorState; }
		inline bool const IsCopyEnabled() const { return _copyEnabled; }
		inline bool const IsPasteEnabled() const { return _pasteEnabled; }

	private:
		bool _copyEnabled, _pasteEnabled;
		double _dt;
		DirectX::SimpleMath::Vector3 _translationSpeed, _rotationSpeed, _scaleSpeed;
		EventSystem _eventSystem;
		std::shared_ptr<Camera> _camera;
		std::vector<BaseObject*> _copiedObjects;
		Input _input;
		Utils _utilities;
		Maths _maths;
		State _editorState;
		Game* _renderer;

		/**
		 * Manipulates objects based on the current editor state.
		 * @param displayObject the current object to manipulate.
		 */
		void ObjectManipulation(SceneObject& displayObject);

		/**
		 * Provides a quick and easy way to manipulate vector3's based on the same control scheme.
		 * @param manipulationVector the current vector to manipulate.
		 */
		void Manipulate(DirectX::SimpleMath::Vector3& manipulationVector);


};
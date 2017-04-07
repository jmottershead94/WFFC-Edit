#include "Editor.h"

Editor::Editor()
{}

Editor::~Editor()
{}

void Editor::Initialize(Game& game)
{
	_renderer = &game;
	_camera = std::make_shared<Camera>(DirectX::SimpleMath::Vector3(30.0f, 10.0f, 10.0f), 0.3f, 1.5f);
	_camera->Transform().Rotate(0.0f, 180.0f, 0.0f);
	_editorState = State::TRANSLATE;
}

void Editor::AddObjectsToEventSystem(std::vector<SceneObject>& sceneObjects)
{
	for (size_t i = 0; i < sceneObjects.size(); ++i)
	{
		// Add this object into the event system to listen out for input.
		_eventSystem.AddObserver(&sceneObjects.at(i));
	}
}

void Editor::CopyObjects(std::vector<SceneObject>& sceneObjects)
{
	_pasteEnabled = false;

	for (size_t i = 0; i < sceneObjects.size(); ++i)
	{
		SceneObject currentObject = sceneObjects.at(i);

		if (currentObject.Focus())
		{
			SceneObject* newObject = currentObject.Copy();
			_copiedObjects.push_back(newObject);
			_pasteEnabled = true;
		}
	}
}

void Editor::PasteObjects(std::vector<SceneObject>& sceneObjects)
{
	if (!_pasteEnabled || _copiedObjects.size() < 1)
		return;

	// Deselecting all of the current display list objects.
	for (size_t i = 0; i < sceneObjects.size(); ++i)
	{
		SceneObject currentObject = sceneObjects.at(i);

		if (currentObject.Focus())
		{
			currentObject.SetFocus(false);
			currentObject.tex_diffuse_path = currentObject.OriginalTexturePath();
		}
	}

	// Pasting and selecting all of the new display list objects.
	for (size_t i = 0; i < _copiedObjects.size(); ++i)
	{
		SceneObject* currentObject = new SceneObject(*(SceneObject*)(_copiedObjects.at(i)));

		currentObject->m_ID = sceneObjects.size() + (i + 1);
		currentObject->tex_diffuse_path = currentObject->OriginalTexturePath();

		sceneObjects.push_back(*currentObject);
	}

	_copiedObjects.clear();

	_copyEnabled = true;
	_pasteEnabled = false;
}

void Editor::ToggleWireframe()
{
	Utils::SetWireframe(!Utils::WireframeMode());
}

void Editor::ObjectManipulation(SceneObject& displayObject)
{
	switch (_editorState)
	{
		case State::TRANSLATE:
		{
			DirectX::SimpleMath::Vector3 translation;
			Manipulate(translation);
			displayObject.Transform().Translate(translation);

			break;
		}
		case State::ROTATE:
		{
			DirectX::SimpleMath::Vector3 rotation;

			if (Input::IsKeyDown('D'))
				rotation += DirectX::SimpleMath::Vector3::UnitY;
			if (Input::IsKeyDown('A'))
				rotation -= DirectX::SimpleMath::Vector3::UnitY;

			if (Input::IsKeyDown('E'))
				rotation -= DirectX::SimpleMath::Vector3::UnitZ;
			if (Input::IsKeyDown('Q'))
				rotation += DirectX::SimpleMath::Vector3::UnitZ;

			if (Input::IsKeyDown('W'))
				rotation -= DirectX::SimpleMath::Vector3::UnitX;
			if (Input::IsKeyDown('S'))
				rotation += DirectX::SimpleMath::Vector3::UnitX;

			displayObject.Transform().Rotate(rotation);

			break;
		}
		case State::SCALE:
		{
			DirectX::SimpleMath::Vector3 scale = displayObject.Transform().Scale();
			Manipulate(scale);
			displayObject.Transform().SetScale(scale);

			break;
		}
		default:
			break;
	}
}

void Editor::Manipulate(DirectX::SimpleMath::Vector3& manipulationVector)
{
	if (Input::IsKeyDown('D'))
		manipulationVector += DirectX::SimpleMath::Vector3::UnitX;
	if (Input::IsKeyDown('A'))
		manipulationVector -= DirectX::SimpleMath::Vector3::UnitX;

	if (Input::IsKeyDown('E'))
		manipulationVector += DirectX::SimpleMath::Vector3::UnitY;
	if (Input::IsKeyDown('Q'))
		manipulationVector -= DirectX::SimpleMath::Vector3::UnitY;

	if (Input::IsKeyDown('W'))
		manipulationVector -= DirectX::SimpleMath::Vector3::UnitZ;
	if (Input::IsKeyDown('S'))
		manipulationVector += DirectX::SimpleMath::Vector3::UnitZ;
}

void Editor::Controls()
{
	if (CrossPlatformInput::GenerateTerrainPressed())
		_renderer->GenerateRandomTerrain();

	if (CrossPlatformInput::WireframeModePressed())
		ToggleWireframe();
	
	if (CrossPlatformInput::SelectPressed())
		_eventSystem.Notify(EventType::EVENT_LEFT_MOUSE_CLICK, Utils::GetCursorPositionInWorld(_renderer->WorldMatrix(), _renderer->ProjectionMatrix(), _renderer->ViewMatrix(), _renderer->DeviceResources()->GetScreenViewport()), Utils::GetCursorDirectionInWorld());

	if (CrossPlatformInput::SelectReleased())
		_eventSystem.Notify(EventType::EVENT_LEFT_MOUSE_RELEASE, Utils::GetCursorPositionInWorld(_renderer->WorldMatrix(), _renderer->ProjectionMatrix(), _renderer->ViewMatrix(), _renderer->DeviceResources()->GetScreenViewport()), Utils::GetCursorDirectionInWorld());

	if (CrossPlatformInput::SelectDoublePressed())
		_eventSystem.Notify(EventType::EVENT_LEFT_MOUSE_CLICK_DOUBLE, Utils::GetCursorPositionInWorld(_renderer->WorldMatrix(), _renderer->ProjectionMatrix(), _renderer->ViewMatrix(), _renderer->DeviceResources()->GetScreenViewport()), Utils::GetCursorDirectionInWorld());
}

void Editor::Update(std::vector<SceneObject>& sceneObjects)
{
	//TODO  any more complex than this, and the camera should be abstracted out to somewhere else
	//camera motion is on a plane, so kill the 7 component of the look direction
	DirectX::SimpleMath::Vector3 planarMotionVector = _camera->Transform().Forward();
	planarMotionVector.y = 0.0f;

	_camera->Update(_dt);

	if (sceneObjects.empty())
		return;

	// Resetting the enabled status for copy.
	_copyEnabled = false;

	for (size_t i = 0; i < sceneObjects.size(); ++i)
	{
		SceneObject sceneObject = sceneObjects.at(i);
		sceneObject.Update(_dt);

		if (sceneObject.Focus())
		{
			// The copy option for the menus should be available now.
			_copyEnabled = true;

			// If the user isn't moving the camera, assume they are manipulating an object for now.
			if (!Input::RightMousePressed())
				ObjectManipulation(sceneObject);
		}
	}
}
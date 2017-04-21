#include "Editor.h"

Editor::Editor() :
	_translationSpeed(1.0f, 1.0f, 1.0f),
	_rotationSpeed(1.0f, 1.0f, 1.0f),
	_scaleSpeed(1.0f, 1.0f, 1.0f)
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

void Editor::RemoveObjectsFromEventSystem(std::vector<SceneObject>& sceneObjects)
{
	for (size_t i = 0; i < sceneObjects.size(); ++i)
	{
		// Remove this object from the event system.
		_eventSystem.RemoveObserver(&sceneObjects.at(i));
	}
}

SceneObject* Editor::SpawnNewSceneObject(const int numberOfSceneObjects, const std::string modelFilePath, const std::string textureFilePath, DirectX::SimpleMath::Vector3 modelScale)
{
	SceneObject* newObject = new SceneObject();
	newObject->ID = numberOfSceneObjects + 1;
	newObject->chunk_ID = 0;
	newObject->model_path = modelFilePath;
	newObject->tex_diffuse_path = textureFilePath;
	newObject->Transform().SetPosition(_camera->Transform().Position());
	newObject->Transform().SetRotation(_camera->Transform().Rotation());
	newObject->Transform().SetScale(DirectX::SimpleMath::Vector3::One * modelScale);
	newObject->render = false;
	newObject->collision = false;
	newObject->collision_mesh = "";
	newObject->collectable = false;
	newObject->destructable = false;
	newObject->health_amount = 0;
	newObject->editor_render = true;
	newObject->editor_texture_vis = true;
	newObject->editor_normals_vis = false;
	newObject->editor_collision_vis = false;
	newObject->editor_pivot_vis = false;
	newObject->pivotX = 0.0f;
	newObject->pivotY = 0.0f;
	newObject->pivotZ = 0.0f;
	newObject->snapToGround = false;
	newObject->AINode = false;
	newObject->audio_path = "";
	newObject->volume = 0.0f;
	newObject->pitch = 0.0f;
	newObject->pan = 0.0f;
	newObject->one_shot = false;
	newObject->play_on_init = false;
	newObject->play_in_editor = false;
	newObject->min_dist = 0.0f;
	newObject->max_dist = 0.0f;
	newObject->camera = false;
	newObject->path_node = false;
	newObject->path_node_start = false;
	newObject->path_node_end = false;
	newObject->parent_id = 0;
	newObject->editor_wireframe = false;
	newObject->name = "Name";

	newObject->SetEditorCamera(_camera);
	newObject->SetOriginalTexturePath(textureFilePath);
	//_eventSystem.AddObserver(newObject);

	return newObject;
}

void Editor::SpawnTree(std::vector<SceneObject>& sceneObjects)
{
	// Removing observers because we are about to update the scene graph.
	RemoveObjectsFromEventSystem(sceneObjects);

	// Spawning in a new tree.
	SceneObject* newTree = SpawnNewSceneObject(sceneObjects.size(), "database/data/Lowpoly_tree_sample.cmo", "database/data/placeholder.dds", DirectX::SimpleMath::Vector3(3.0f, 3.0f, 3.0f));
	sceneObjects.push_back(*newTree);

	// Adding observers because we have updated the scene graph.
	AddObjectsToEventSystem(sceneObjects);

	// Rebuilding the display list to show changes via the renderer.
	_renderer->BuildDisplayList(&sceneObjects);
}

void Editor::CopyObjects(std::vector<SceneObject>& sceneObjects)
{
	_pasteEnabled = false;

	for (size_t i = 0; i < sceneObjects.size(); ++i)
	{
		SceneObject* currentObject = &sceneObjects.at(i);

		if (currentObject->Focus())
		{
			SceneObject* newObject = currentObject->Copy();
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
		SceneObject* currentObject = &sceneObjects.at(i);

		if (currentObject->Focus())
		{
			currentObject->SetFocus(false);
			currentObject->tex_diffuse_path = currentObject->OriginalTexturePath();
		}
	}

	// Pasting and selecting all of the new display list objects.
	for (size_t i = 0; i < _copiedObjects.size(); ++i)
	{
		SceneObject* currentObject = &sceneObjects.at(i);
		SceneObject* newObject = currentObject->Copy();

		newObject->m_ID = sceneObjects.size() + (i + 1);
		newObject->tex_diffuse_path = currentObject->OriginalTexturePath();

		sceneObjects.push_back(*newObject);
	}

	_renderer->BuildDisplayList(&sceneObjects);
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
			DirectX::SimpleMath::Vector3 translation(DirectX::SimpleMath::Vector3::Zero);
			
			Manipulate(translation);
			displayObject.Transform().Translate(translation * Utils::TranslationSpeed());

			if (translation != DirectX::SimpleMath::Vector3::Zero)
				displayObject.SetDirty(true);
			else
				displayObject.SetDirty(false);

			break;
		}
		case State::ROTATE:
		{
			DirectX::SimpleMath::Vector3 rotation(DirectX::SimpleMath::Vector3::Zero);

			if (Input::IsKeyDown('L'))
				rotation += DirectX::SimpleMath::Vector3::UnitY;
			if (Input::IsKeyDown('J'))
				rotation -= DirectX::SimpleMath::Vector3::UnitY;

			if (Input::IsKeyDown('O'))
				rotation -= DirectX::SimpleMath::Vector3::UnitZ;
			if (Input::IsKeyDown('U'))
				rotation += DirectX::SimpleMath::Vector3::UnitZ;

			if (Input::IsKeyDown('I'))
				rotation -= DirectX::SimpleMath::Vector3::UnitX;
			if (Input::IsKeyDown('K'))
				rotation += DirectX::SimpleMath::Vector3::UnitX;

			displayObject.Transform().Rotate(rotation * Utils::RotationRate());

			if (rotation != DirectX::SimpleMath::Vector3::Zero)
				displayObject.SetDirty(true);
			else
				displayObject.SetDirty(false);

			break;
		}
		case State::SCALE:
		{
			DirectX::SimpleMath::Vector3 originalScale = displayObject.Transform().Scale();
			DirectX::SimpleMath::Vector3 scale = originalScale;

			Manipulate(scale);
			displayObject.Transform().SetScale(scale);
			
			if(scale != originalScale)
				displayObject.SetDirty(true);
			else
				displayObject.SetDirty(false);

			break;
		}
		default:
		{
			displayObject.SetDirty(false);
			break;
		}
	}
}

void Editor::Manipulate(DirectX::SimpleMath::Vector3& manipulationVector)
{
	if (Input::IsKeyDown('L'))
		manipulationVector += DirectX::SimpleMath::Vector3::UnitX;
	if (Input::IsKeyDown('J'))
		manipulationVector -= DirectX::SimpleMath::Vector3::UnitX;

	if (Input::IsKeyDown('O'))
		manipulationVector += DirectX::SimpleMath::Vector3::UnitY;
	if (Input::IsKeyDown('U'))
		manipulationVector -= DirectX::SimpleMath::Vector3::UnitY;

	if (Input::IsKeyDown('I'))
		manipulationVector -= DirectX::SimpleMath::Vector3::UnitZ;
	if (Input::IsKeyDown('K'))
		manipulationVector += DirectX::SimpleMath::Vector3::UnitZ;
}

void Editor::Controls(std::vector<SceneObject>& sceneObjects)
{
	if (CrossPlatformInput::GenerateTerrainPressed())
		_renderer->GenerateRandomTerrain();

	if (CrossPlatformInput::WireframeModePressed())
		ToggleWireframe();
	
	if (CrossPlatformInput::SpawnTreePressed())
		SpawnTree(sceneObjects);

	if (CrossPlatformInput::TranslateHotKeyPressed())
		_editorState = Editor::State::TRANSLATE;

	if (CrossPlatformInput::RotateHotKeyPressed())
		_editorState = Editor::State::ROTATE;

	if (CrossPlatformInput::ScaleHotKeyPressed())
		_editorState = Editor::State::SCALE;

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
		SceneObject* sceneObject = &sceneObjects.at(i);
		sceneObject->Update(_dt);

		if (sceneObject->Focus())
		{
			// The copy option for the menus should be available now.
			_copyEnabled = true;

			// If the user isn't moving the camera, assume they are manipulating an object for now.
			if (!Input::RightMousePressed())
				ObjectManipulation(*sceneObject);
		}
	}
}
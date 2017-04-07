#include "ToolMain.h"
#include "resource.h"
#include <vector>
#include <sstream>

//ToolMain Class
ToolMain::ToolMain()
{
	m_currentChunk = 0;		//default value
	m_selectedObject = 0;	//initial selection ID
	m_sceneGraph.clear();	//clear the vector for the scenegraph
	m_databaseConnection = NULL;
}

ToolMain::~ToolMain()
{
	sqlite3_close(m_databaseConnection);		//close the database connection
}

int ToolMain::getCurrentSelectionID()
{

	return m_selectedObject;
}

void ToolMain::onActionInitialise(HWND handle, int width, int height)
{
	//window size, handle etc for directX
	m_width		= width;
	m_height	= height;
	m_d3dRenderer.GetDefaultSize(m_width, m_height);
	_editor.Initialize(m_d3dRenderer);
	m_d3dRenderer.Initialize(handle, m_width, m_height, _editor.MainCamera());
	Utils::Initialize(handle, width, height);

	//database connection establish
	int rc;
	rc = sqlite3_open("database/test.db", &m_databaseConnection);

	if (rc) 
	{
		TRACE("Can't open database");
		//if the database cant open. Perhaps a more catastrophic error would be better here
	}
	else 
	{
		TRACE("Opened database successfully");
	}	

	onActionLoad();
}

void ToolMain::onActionLoad()
{
	//load current chunk and objects into lists
	if (!m_sceneGraph.empty())		//is the vector empty
	{
		_editor.RemoveObjectsFromEventSystem(m_sceneGraph);
		m_sceneGraph.clear();		//if not, empty it
	}

	//SQL
	int rc;
	char *sqlCommand;
	char *ErrMSG = 0;
	sqlite3_stmt *pResults;								//results of the query
	sqlite3_stmt *pResultsChunk;

	//OBJECTS IN THE WORLD
	//prepare SQL Text
	sqlCommand = "SELECT * from Objects";				//sql command which will return all records from the objects table.
	//Send Command and fill result object
	rc = sqlite3_prepare_v2(m_databaseConnection, sqlCommand, -1, &pResults, 0 );
	
	//loop for each row in results until there are no more rows.  ie for every row in the results. We create and object
	while (sqlite3_step(pResults) == SQLITE_ROW)
	{	
		SceneObject newSceneObject;
		newSceneObject.ID = sqlite3_column_int(pResults, 0);
		newSceneObject.chunk_ID = sqlite3_column_int(pResults, 1);
		newSceneObject.model_path		= reinterpret_cast<const char*>(sqlite3_column_text(pResults, 2));
		newSceneObject.tex_diffuse_path = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 3));
		newSceneObject.Transform().SetPosition(sqlite3_column_double(pResults, 4), sqlite3_column_double(pResults, 5), sqlite3_column_double(pResults, 6));
		newSceneObject.Transform().SetRotation(sqlite3_column_double(pResults, 7), sqlite3_column_double(pResults, 8), sqlite3_column_double(pResults, 9));
		newSceneObject.Transform().SetScale(sqlite3_column_double(pResults, 10), sqlite3_column_double(pResults, 11), sqlite3_column_double(pResults, 12));
		newSceneObject.render = sqlite3_column_int(pResults, 13);
		newSceneObject.collision = sqlite3_column_int(pResults, 14);
		newSceneObject.collision_mesh = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 15));
		newSceneObject.collectable = sqlite3_column_int(pResults, 16);
		newSceneObject.destructable = sqlite3_column_int(pResults, 17);
		newSceneObject.health_amount = sqlite3_column_int(pResults, 18);
		newSceneObject.editor_render = sqlite3_column_int(pResults, 19);
		newSceneObject.editor_texture_vis = sqlite3_column_int(pResults, 20);
		newSceneObject.editor_normals_vis = sqlite3_column_int(pResults, 21);
		newSceneObject.editor_collision_vis = sqlite3_column_int(pResults, 22);
		newSceneObject.editor_pivot_vis = sqlite3_column_int(pResults, 23);
		newSceneObject.pivotX = sqlite3_column_double(pResults, 24);
		newSceneObject.pivotY = sqlite3_column_double(pResults, 25);
		newSceneObject.pivotZ = sqlite3_column_double(pResults, 26);
		newSceneObject.snapToGround = sqlite3_column_int(pResults, 27);
		newSceneObject.AINode = sqlite3_column_int(pResults, 28);
		newSceneObject.audio_path = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 29));
		newSceneObject.volume = sqlite3_column_double(pResults, 30);
		newSceneObject.pitch = sqlite3_column_double(pResults, 31);
		newSceneObject.pan = sqlite3_column_int(pResults, 32);
		newSceneObject.one_shot = sqlite3_column_int(pResults, 33);
		newSceneObject.play_on_init = sqlite3_column_int(pResults, 34);
		newSceneObject.play_in_editor = sqlite3_column_int(pResults, 35);
		newSceneObject.min_dist = sqlite3_column_double(pResults, 36);
		newSceneObject.max_dist = sqlite3_column_double(pResults, 37);
		newSceneObject.camera = sqlite3_column_int(pResults, 38);
		newSceneObject.path_node = sqlite3_column_int(pResults, 39);
		newSceneObject.path_node_start = sqlite3_column_int(pResults, 40);
		newSceneObject.path_node_end = sqlite3_column_int(pResults, 41);
		newSceneObject.parent_id = sqlite3_column_int(pResults, 42);
		newSceneObject.editor_wireframe = sqlite3_column_int(pResults, 43);
		newSceneObject.name = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 44));
		
		newSceneObject.SetEditorCamera(_editor.MainCamera());
		newSceneObject.SetOriginalTexturePath(newSceneObject.tex_diffuse_path);

		//send completed object to scenegraph
		m_sceneGraph.push_back(newSceneObject);
	}

	//THE WORLD CHUNK
	//prepare SQL Text
	sqlCommand = "SELECT * from Chunks";				//sql command which will return all records from  chunks table. There is only one tho.
														//Send Command and fill result object
	rc = sqlite3_prepare_v2(m_databaseConnection, sqlCommand, -1, &pResultsChunk, 0);
	
	sqlite3_step(pResultsChunk);
	m_chunk.ID = sqlite3_column_int(pResultsChunk, 0);
	m_chunk.name = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 1));
	m_chunk.chunk_x_size_metres = sqlite3_column_int(pResultsChunk, 2);
	m_chunk.chunk_y_size_metres = sqlite3_column_int(pResultsChunk, 3);
	m_chunk.chunk_base_resolution = sqlite3_column_int(pResultsChunk, 4);
	m_chunk.heightmap_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 5));
	m_chunk.tex_diffuse_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 6));
	m_chunk.tex_splat_alpha_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 7));
	m_chunk.tex_splat_1_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 8));
	m_chunk.tex_splat_2_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 9));
	m_chunk.tex_splat_3_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 10));
	m_chunk.tex_splat_4_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 11));
	m_chunk.render_wireframe = sqlite3_column_int(pResultsChunk, 12);
	m_chunk.render_normals = sqlite3_column_int(pResultsChunk, 13);
	m_chunk.tex_diffuse_tiling = sqlite3_column_int(pResultsChunk, 14);
	m_chunk.tex_splat_1_tiling = sqlite3_column_int(pResultsChunk, 15);
	m_chunk.tex_splat_2_tiling = sqlite3_column_int(pResultsChunk, 16);
	m_chunk.tex_splat_3_tiling = sqlite3_column_int(pResultsChunk, 17);
	m_chunk.tex_splat_4_tiling = sqlite3_column_int(pResultsChunk, 18);
	
	_editor.AddObjectsToEventSystem(m_sceneGraph);

	//Process REsults into renderable
	m_d3dRenderer.BuildDisplayList(&m_sceneGraph);
	//build the renderable chunk 
	m_d3dRenderer.BuildDisplayChunk(&m_chunk);
}

void ToolMain::onActionSave()
{
	//SQL
	int rc;
	char *sqlCommand;
	char *ErrMSG = 0;
	sqlite3_stmt *pResults;								//results of the query
	
	//OBJECTS IN THE WORLD Delete them all
	//prepare SQL Text
	sqlCommand = "DELETE FROM Objects";	 //will delete the whole object table.   Slightly risky but hey.
	rc = sqlite3_prepare_v2(m_databaseConnection, sqlCommand, -1, &pResults, 0);
	sqlite3_step(pResults);

	//Populate with our new objects
	std::wstring sqlCommand2;
	int numObjects = m_sceneGraph.size();	//Loop thru the scengraph.

	for (int i = 0; i < numObjects; i++)
	{
		m_sceneGraph.at(i).tex_diffuse_path = m_sceneGraph.at(i).OriginalTexturePath();

		std::stringstream command;
		command << "INSERT INTO Objects "
			<< "VALUES(" << m_sceneGraph.at(i).ID << ","
			<< m_sceneGraph.at(i).chunk_ID << ","
			<< "'" << m_sceneGraph.at(i).model_path << "'" << ","
			<< "'" << m_sceneGraph.at(i).tex_diffuse_path << "'" << ","
			<< m_sceneGraph.at(i).Transform().Position().x << ","
			<< m_sceneGraph.at(i).Transform().Position().y << ","
			<< m_sceneGraph.at(i).Transform().Position().z << ","
			<< m_sceneGraph.at(i).Transform().Rotation().x << ","
			<< m_sceneGraph.at(i).Transform().Rotation().y << ","
			<< m_sceneGraph.at(i).Transform().Rotation().z << ","
			<< m_sceneGraph.at(i).Transform().Scale().x << ","
			<< m_sceneGraph.at(i).Transform().Scale().y << ","
			<< m_sceneGraph.at(i).Transform().Scale().z << ","
			<< m_sceneGraph.at(i).render << ","
			<< m_sceneGraph.at(i).collision << ","
			<< "'" << m_sceneGraph.at(i).collision_mesh << "'" << ","
			<< m_sceneGraph.at(i).collectable << ","
			<< m_sceneGraph.at(i).destructable << ","
			<< m_sceneGraph.at(i).health_amount << ","
			<< m_sceneGraph.at(i).editor_render << ","
			<< m_sceneGraph.at(i).editor_texture_vis << ","
			<< m_sceneGraph.at(i).editor_normals_vis << ","
			<< m_sceneGraph.at(i).editor_collision_vis << ","
			<< m_sceneGraph.at(i).editor_pivot_vis << ","
			<< m_sceneGraph.at(i).pivotX << ","
			<< m_sceneGraph.at(i).pivotY << ","
			<< m_sceneGraph.at(i).pivotZ << ","
			<< m_sceneGraph.at(i).snapToGround << ","
			<< m_sceneGraph.at(i).AINode << ","
			<< "'" << m_sceneGraph.at(i).audio_path << "'" << ","
			<< m_sceneGraph.at(i).volume << ","
			<< m_sceneGraph.at(i).pitch << ","
			<< m_sceneGraph.at(i).pan << ","
			<< m_sceneGraph.at(i).one_shot << ","
			<< m_sceneGraph.at(i).play_on_init << ","
			<< m_sceneGraph.at(i).play_in_editor << ","
			<< m_sceneGraph.at(i).min_dist << ","
			<< m_sceneGraph.at(i).max_dist << ","
			<< m_sceneGraph.at(i).camera << ","
			<< m_sceneGraph.at(i).path_node << ","
			<< m_sceneGraph.at(i).path_node_start << ","
			<< m_sceneGraph.at(i).path_node_end << ","
			<< m_sceneGraph.at(i).parent_id << ","
			<< m_sceneGraph.at(i).editor_wireframe << ","
			<< "'" << m_sceneGraph.at(i).name << "'"
			<< ")";
		std::string sqlCommand2 = command.str();
		rc = sqlite3_prepare_v2(m_databaseConnection, sqlCommand2.c_str(), -1, &pResults, 0);
		sqlite3_step(pResults);
	}

	MessageBox(NULL, L"Objects Saved", L"Notification", MB_OK);
}

void ToolMain::onActionSaveTerrain()
{
	m_d3dRenderer.SaveDisplayChunk(&m_chunk);
}

void ToolMain::onActionExit(MSG* msg)
{
	int savingUserInput = MessageBoxW(msg->hwnd, L"Would you like to save before quitting?", L"Save and Exit", MB_YESNOCANCEL);

	if (savingUserInput == IDYES)
	{
		onActionSave();
		onActionSaveTerrain();

		SendMessage(msg->hwnd, WM_CLOSE, 0, 0);
		PostQuitMessage(0);
	}
	else if (savingUserInput == IDNO)
	{
		SendMessage(msg->hwnd, WM_CLOSE, 0, 0);
		PostQuitMessage(0);
	}
}

void ToolMain::Tick(MSG *msg)
{
	//do we have a selection
	//do we have a mode
	//are we clicking / dragging /releasing
	//has something changed
		//update Scenegraph
		//add to scenegraph
		//resend scenegraph to Direct X renderer

	//
	// Input Logic.
	//
	_editor.Controls();

	if (CrossPlatformInput::SavePressed())
	{
		onActionSave();
		onActionSaveTerrain();
	}

	//
	// Update Logic.
	//
	for (size_t i = 0; i < m_sceneGraph.size(); ++i)
	{
		SceneObject* currentObject = &m_sceneGraph.at(i);

		if (currentObject->Dirty())
		{
			_updateSceneGraph = true;
			currentObject->SetDirty(false);
		}
	}

	if (_updateSceneGraph)
	{
		m_d3dRenderer.BuildDisplayList(&m_sceneGraph);
		_updateSceneGraph = false;
	}

	_editor.Update(m_sceneGraph);
	
	//
	// Render Logic.
	//
	//Renderer Update Call
	m_d3dRenderer.Tick();
}

void ToolMain::UpdateInput(MSG * msg)
{
	switch (msg->message)
	{
		//Global inputs,  mouse position and keys etc
		case WM_KEYDOWN:
		{
			if (msg->wParam == VK_ESCAPE) 
				onActionExit(msg);

			Input::SetKeyDown(msg->wParam);
			break;
		}
		case WM_KEYUP:
		{
			Input::SetKeyUp(msg->wParam);
			break;
		}
		case WM_MOUSEMOVE:
		{
			onMouseMove(msg);
			break;
		}
		// Mouse clicks.
		case WM_LBUTTONDOWN:
		{
			onLeftMouseDown(msg);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			onRightMouseDown(msg);
			break;
		}
		// Mouse releases.
		case WM_LBUTTONUP:
		{
			onLeftMouseUp();
			break;
		}
		case WM_RBUTTONUP:
		{
			onRightMouseUp();
			break;
		}
		// Mouse double clicks.
		case WM_LBUTTONDBLCLK:
		{
			Input::SetLeftMouseDouble(true);
			Input::SetLeftMouseReleased(false);
			break;
		}
		case WM_RBUTTONDBLCLK:
		{
			PopUpMenu(msg);
			Input::SetRightMouseDouble(true);
			Input::SetRightMouseReleased(false);
			break;
		}
	}
}

SceneObject* ToolMain::SpawnNewSceneObject(DisplayObject* displayObject, const std::string modelFilePath, const std::string textureFilePath, DirectX::SimpleMath::Vector3 modelScale)
{
	SceneObject* newObject = new SceneObject();
	newObject->ID = displayObject->m_ID;
	newObject->chunk_ID = 0;
	newObject->model_path = modelFilePath;
	newObject->tex_diffuse_path = textureFilePath;
	newObject->Transform().SetPosition(displayObject->Transform().Position());
	newObject->Transform().SetRotation(displayObject->Transform().Rotation());
	newObject->Transform().SetScale(displayObject->Transform().Scale() + modelScale);
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
	return newObject;
}

void ToolMain::PopUpMenu(MSG* msg)
{
	int xPos = GET_X_LPARAM(msg->lParam);
	int yPos = GET_Y_LPARAM(msg->lParam);

	POINT cursorPoint;
	cursorPoint.x = xPos;
	cursorPoint.y = yPos;
	GetCursorPos(&cursorPoint);
	_previousMouse = cursorPoint;

	_popUpMenu = CreatePopupMenu();
	InsertMenu(_popUpMenu, 0, MF_BYPOSITION | MF_STRING, 0, L"Edit");

	//MENUITEMINFO subMenuInfo;
	//subMenuInfo = 
	//InsertMenuItem(_popUpMenu, 0, MF_BYPOSITION | MF_STRING, )
	//InsertMenu(_popUpMenu, 1, MF_BYPOSITION | MF_STRING, 1, L"Hello2");
	SetForegroundWindow(msg->hwnd);
	_popUpMenuResult = TrackPopupMenu(_popUpMenu, TPM_RETURNCMD | TPM_TOPALIGN | TPM_LEFTALIGN, cursorPoint.x, cursorPoint.y, 0, msg->hwnd, 0);
}

void ToolMain::onActionCopyItems()
{
	_editor.CopyObjects(m_sceneGraph);
}

void ToolMain::onActionPasteItems()
{
	_editor.PasteObjects(m_sceneGraph);
}

void ToolMain::onActionGenerateTerrain()
{
	m_d3dRenderer.GenerateRandomTerrain();
}

void ToolMain::onActionToggleWireframe()
{
	Utils::SetWireframe(!Utils::WireframeMode());
}

void ToolMain::onActionSpawnModel(const std::string modelFilePath, const std::string textureFilePath, DirectX::SimpleMath::Vector3 modelScale)
{
	m_sceneGraph.push_back(*SpawnNewSceneObject(m_d3dRenderer.SpawnNewDisplayObject(modelFilePath, textureFilePath, modelScale), modelFilePath, textureFilePath, modelScale));
}

void ToolMain::onActionChangeEditorState(const Editor::State newState)
{
	_editor.SetState(newState);
}

void ToolMain::onLeftMouseDown(MSG* msg)
{
	int xPos = GET_X_LPARAM(msg->lParam);
	int yPos = GET_Y_LPARAM(msg->lParam);

	Input::SetMouseX(xPos);
	Input::SetMouseY(yPos);

	POINT cursorPoint;
	cursorPoint.x = xPos;
	cursorPoint.y = yPos;
	_previousMouse = cursorPoint;

	Input::SetLeftMousePressed(true);
	Input::SetLeftMouseReleased(false);
}

void ToolMain::onLeftMouseUp()
{
	Input::SetLeftMouseReleased(true);
	Input::SetLeftMousePressed(false);
	Input::SetLeftMouseDrag(false);
	Input::SetLeftMouseDouble(false);
}

void ToolMain::onRightMouseDown(MSG* msg)
{
	int xPos = GET_X_LPARAM(msg->lParam);
	int yPos = GET_Y_LPARAM(msg->lParam);

	Input::SetMouseX(xPos);
	Input::SetMouseY(yPos);

	POINT cursorPoint;
	cursorPoint.x = xPos;
	cursorPoint.y = yPos;
	_previousMouse = cursorPoint;
	
	Input::SetRightMousePressed(true);
}

void ToolMain::onRightMouseUp()
{
	Input::SetRightMouseReleased(true);
	Input::SetRightMousePressed(false);
	Input::SetRightMouseDrag(false);
	Input::SetRightMouseDouble(false);
}

void ToolMain::onMouseMove(MSG* msg)
{
	int xPos = GET_X_LPARAM(msg->lParam);
	int yPos = GET_Y_LPARAM(msg->lParam);

	Input::SetMouseX(xPos);
	Input::SetMouseY(yPos);

	POINT deltaPosition;
	deltaPosition.x = xPos - _previousMouse.x;
	deltaPosition.y = yPos - _previousMouse.y;
	
	// Handles right mouse button drags.
	if (MK_RBUTTON & msg->wParam)
		onRightButtonMouseDrag(deltaPosition.x, deltaPosition.y);

	// Handles left mouse button drags.
	if (MK_LBUTTON & msg->wParam)
		onLeftButtonMouseDrag(deltaPosition.x, deltaPosition.y);
}

void ToolMain::onRightButtonMouseDrag(int mouseX, int mouseY)
{
	if (!Input::RightMousePressed())
		return;

	Input::SetRightMouseDrag(true);
	Input::SetRightMouseReleased(false);

	// Checking x axis drag.
	if (mouseX >= _mouseDragDeadCentre)
		Input::SetMouseDragAxisX(1.0f);
	else if (mouseX <= -_mouseDragDeadCentre)
		Input::SetMouseDragAxisX(-1.0f);
	else
		Input::SetMouseDragAxisX(0.0f);

	// Checking y axis drag.
	if (mouseY >= _mouseDragDeadCentre)
		Input::SetMouseDragAxisY(-1.0f);
	else if (mouseY <= -_mouseDragDeadCentre)
		Input::SetMouseDragAxisY(1.0f);
	else
		Input::SetMouseDragAxisY(0.0f);
}

void ToolMain::onLeftButtonMouseDrag(int mouseX, int mouseY)
{
	if (!Input::LeftMousePressed())
		return;

	Input::SetLeftMouseDrag(true);
	Input::SetLeftMouseReleased(false);

	// Checking x axis drag.
	if (mouseX >= _mouseDragDeadCentre)
		Input::SetMouseDragAxisX(1.0f);
	else if (mouseX <= -_mouseDragDeadCentre)
		Input::SetMouseDragAxisX(-1.0f);
	else
		Input::SetMouseDragAxisX(0.0f);

	// Checking y axis drag.
	if (mouseY >= _mouseDragDeadCentre)
		Input::SetMouseDragAxisY(-1.0f);
	else if (mouseY <= -_mouseDragDeadCentre)
		Input::SetMouseDragAxisY(1.0f);
	else
		Input::SetMouseDragAxisY(0.0f);
}
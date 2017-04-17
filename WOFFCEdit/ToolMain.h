#pragma once

#include <afxext.h>
#include "pch.h"
#include "1300455_MottersheadJason/Editor/Editor.h"
#include "sqlite3.h"
#include <vector>

class ToolMain
{
	public: //methods
		ToolMain();
		~ToolMain();

		//onAction - These are the interface to MFC
		int		getCurrentSelectionID();										//returns the selection number of currently selected object so that It can be displayed.
		void	onActionInitialise(HWND handle, int width, int height);			//Passes through handle and hieght and width and initialises DirectX renderer and SQL LITE
		void	onActionFocusCamera();
		void	onActionLoad();													//load the current chunk
		afx_msg	void	onActionSave();											//save the current chunk
		afx_msg void	onActionSaveTerrain();									//save chunk geometry
		void	Tick(MSG *msg);
		void	UpdateInput(MSG *msg);

	public:	//variables
		std::vector<SceneObject>    m_sceneGraph;	//our scenegraph storing all the objects in the current chunk
		ChunkObject					m_chunk;		//our landscape chunk
		int m_selectedObject;						//ID of current Selection

	private:	//methods
		void	onContentAdded();
		
	private:	//variables
		HWND	m_toolHandle;		//Handle to the  window
		Game	m_d3dRenderer;		//Instance of D3D rendering system for our tool
		CRect	WindowRECT;		//Window area rectangle. 
		sqlite3 *m_databaseConnection;	//sqldatabase handle

		int m_width;		//dimensions passed to directX
		int m_height;
		int m_currentChunk;			//the current chunk of thedatabase that we are operating on.  Dictates loading and saving. 
	
	// Jason's Added Work.
	private:
		const float _mouseDragDeadCentre = 100.0f;
		int _popUpMenuResult = -1;
		bool _updateSceneGraph = false;
		POINT _previousMouse;
		HMENU _topLevelMenu, _popUpMenu;
		Editor _editor;

		/**
		 * Creates a new pop up menu.
		 * @param msg the message with the lParam and wParam for windows parameters.
		 */
		void PopUpMenu(MSG* msg);

	public:
		/**
		 * Performs appropriate exit actions.
		 * @param msg the message with the lParam and wParam for windows parameters.
		 */
		void onActionExit(MSG* msg);

		/**
		 * Copies all of the selected items.
		 */
		void onActionCopyItems();

		/**
		 * Pastes all of the selected items.
		 */
		void onActionPasteItems();

		/**
		 * Provides a way to generate random terrain.
		 */
		void onActionGenerateTerrain();

		/**
		 * Provides a way to toggle wireframe.
		 */
		void onActionToggleWireframe();

		/**
		 * Spawns in a model.
		 * @param modelFilePath the file path to the model we want to spawn in.
		 * @param textureFilePath the file path to the texture for the model.
		 * @param modelScale the scale offset for the model size.
		 */
		void onActionSpawnModel(const std::string modelFilePath, const std::string textureFilePath, DirectX::SimpleMath::Vector3 modelScale);

		/**
		 * Changes the editor state.
		 * @param newState the new state to change to.
		 */
		void onActionChangeEditorState(const Editor::State newState);

	private:
		/**
		 * What happens when the left mouse has been pressed.
		 * @param msg the message with the lParam and wParam for windows parameters.
		 */
		void onLeftMouseDown(MSG* msg);

		/**
		 * What happens when the left mouse button has been released.
		 */
		void onLeftMouseUp();

		/**
		 * What happens when the right mouse has ben pressed.
		 * @param msg the message with the lParam and wParam for windows parameters.
		 */
		void onRightMouseDown(MSG* msg);

		/**
		 * What happens when the right mouse button has been released.
		 */
		void onRightMouseUp();

		/**
		 * Defines what happens when we move the mouse.
		 * @param msg the message with the lParam and wParam for windows parameters.
		 */
		void onMouseMove(MSG* msg);

		/**
		 * What happens when we hold down the right mouse button and drag the mouse.
		 * @param mouseX the delta x position of the mouse.
		 * @param mouseY the delta y position of the mouse.
		 */
		void onRightButtonMouseDrag(int mouseX, int mouseY);

		/**
		 * What happens when we hold down the left mouse button and drag the mouse.
		 * @param mouseX the delta x position of the mouse.
		 * @param mouseY the delta y position of the mouse.
		 */
		void onLeftButtonMouseDrag(int mouseX, int mouseY);
};
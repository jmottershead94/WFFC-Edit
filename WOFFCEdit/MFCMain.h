#pragma once

#include <afxwin.h> 
#include <afxext.h>
#include <afx.h>
#include "pch.h"
#include "Game.h"
#include "ToolMain.h"
#include "resource.h"
#include "MFCFrame.h"
#include "SelectDialogue.h"
#include "1300455_MottersheadJason/Settings.h"

class MFCMain : public CWinApp 
{
public:
	MFCMain();
	~MFCMain();
	BOOL InitInstance();
	int  Run();

private:

	CMyFrame * m_frame;	//handle to the frame where all our UI is
	HWND m_toolHandle;	//Handle to the MFC window
	ToolMain m_ToolSystem;	//Instance of Tool System that we interface to. 
	CRect WindowRECT;	//Window area rectangle. 
	SelectDialogue m_ToolSelectDialogue;			//for modeless dialogue, declare it here
	

	int m_width;		
	int m_height;
	
	//Interface funtions for menu and toolbar etc requires
	afx_msg void MenuFileQuit();
	afx_msg void MenuFileSaveTerrain();
	afx_msg void MenuEditSelect();
	afx_msg	void ToolBarButton1();

	// Jason's Added Work.
	//CDialogEx _editorSettings;
	CButton* _invertedCamCheckBox = nullptr;
	Settings _settings;

	/**
	 * Allows the user to save the scene.
	 */
	afx_msg void MenuSaveAll();

	/**
	 * Allows the user to copy selected items.
	 */
	afx_msg void MenuEditCopy();

	/**
	 * Allows the user to paste copied items.
	 */
	afx_msg void MenuEditPaste();

	/**
	 * Allows the user to edit tool settings.
	 */
	afx_msg void MenuEditSettings();

	/**
	 * Generates random terrain with the tool bar button.
	 */
	afx_msg void MenuGenerateRandomTerrain();

	/**
	 * Toggles wireframe mode.
	 */
	afx_msg void MenuToggleWireframe();

	/**
	 * Spawns in a tree model.
	 */
	afx_msg void MenuSpawnTree();

	/**
	 * Allows the user to translate selected objects.
	 */
	afx_msg void MenuTranslate();

	/**
	 * Allows the user to rotate selected objects.
	 */
	afx_msg void MenuRotate();

	/**
	 * Allows the user to scale selected objects.
	 */
	afx_msg void MenuScale();

	DECLARE_MESSAGE_MAP()	// required macro for message map functionality  One per class
};

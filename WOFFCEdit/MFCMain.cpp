#include "MFCMain.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(MFCMain, CWinApp)
	ON_COMMAND(ID_FILE_QUIT,	&MFCMain::MenuFileQuit)
	ON_COMMAND(ID_FILE_SAVEALL, &MFCMain::MenuSaveAll)
	ON_COMMAND(ID_EDIT_SELECT, &MFCMain::MenuEditSelect)
	ON_COMMAND(ID_EDIT_COPY40079, &MFCMain::MenuEditCopy)
	ON_COMMAND(ID_EDIT_PASTE40079, &MFCMain::MenuEditPaste)
	ON_COMMAND(ID_EDIT_SETTINGS, &MFCMain::MenuEditSettings)
	ON_COMMAND(ID_BUTTON40001,	&MFCMain::ToolBarButton1)
	ON_COMMAND(ID_GENERATETERRAIN, &MFCMain::MenuGenerateRandomTerrain)
	ON_COMMAND(ID_WIREFRAMEMODE, &MFCMain::MenuToggleWireframe)
	ON_COMMAND(ID_SPAWNTREE, &MFCMain::MenuSpawnTree)
	ON_COMMAND(ID_CREATE_TREE, &MFCMain::MenuSpawnTree)
	ON_COMMAND(ID_TRANSLATE, &MFCMain::MenuTranslate)
	ON_COMMAND(ID_ROTATE, &MFCMain::MenuRotate)
	ON_COMMAND(ID_SCALE, &MFCMain::MenuScale)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TOOL, &CMyFrame::OnUpdatePage)
END_MESSAGE_MAP()

BOOL MFCMain::InitInstance()
{
	//instanciate the mfc frame
	m_frame = new CMyFrame();
	m_pMainWnd = m_frame;

	m_frame->Create(	NULL,
					_T("World Of Flim-Flam Craft Editor"),
					WS_OVERLAPPEDWINDOW,
					CRect(0, 0, 800, 600),
					NULL,
					NULL,
					0,
					NULL
				);

	//get the rect from the MFC window so we can get its dimensions
//	m_toolHandle = Frame->GetSafeHwnd();						//handle of main window
	m_toolHandle = m_frame->m_DirXView.GetSafeHwnd();				//handle of directX child window
	m_frame->m_DirXView.GetWindowRect(&WindowRECT);
	m_width = WindowRECT.Width();
	m_height = WindowRECT.Height();
	
	m_frame->ShowWindow(SW_SHOW);
	m_frame->UpdateWindow();

	_settings.Create(IDD_DIALOG2);
	m_ToolSystem.onActionInitialise(m_toolHandle, 1920, 1080);

	return TRUE;
}

int MFCMain::Run()
{
	MSG msg;
	BOOL bGotMsg;

	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

	while (WM_QUIT != msg.message)
	{
		if (true)
		{
			bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);
		}
		else
		{
			bGotMsg = (GetMessage(&msg, NULL, 0U, 0U) != 0);
		}

		if (bGotMsg)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			m_ToolSystem.UpdateInput(&msg);
		}
		else
		{
			int ID = m_ToolSystem.getCurrentSelectionID();
			std::wstring statusString = L"Selected Object: " + std::to_wstring(ID);
			m_ToolSystem.Tick(&msg);

			//send current object ID to status bar in The main frame
			m_frame->m_wndStatusBar.SetPaneText(1, statusString.c_str(), 1);	
		}
	}

	return (int)msg.wParam;
}

void MFCMain::MenuFileQuit()
{
	//will post message to the message thread that will exit the application normally
	PostQuitMessage(0);
}

void MFCMain::MenuFileSaveTerrain()
{
	m_ToolSystem.onActionSaveTerrain();
}

void MFCMain::MenuSaveAll()
{
	m_ToolSystem.onActionSave();
	m_ToolSystem.onActionSaveTerrain();
}

void MFCMain::MenuEditSelect()
{
	//SelectDialogue m_ToolSelectDialogue(NULL, &m_ToolSystem.m_sceneGraph);		//create our dialoguebox //modal constructor
	//m_ToolSelectDialogue.DoModal();	// start it up modal

	//modeless dialogue must be declared in the class.   If we do local it will go out of scope instantly and destroy itself
	m_ToolSelectDialogue.Create(IDD_DIALOG1);	//Start up modeless
	m_ToolSelectDialogue.ShowWindow(SW_SHOW);	//show modeless
	m_ToolSelectDialogue.SetObjectData(&m_ToolSystem.m_sceneGraph, &m_ToolSystem.m_selectedObject);
}

void MFCMain::ToolBarButton1()
{	
	m_ToolSystem.onActionSave();
}

void MFCMain::MenuEditCopy()
{
	m_ToolSystem.onActionCopyItems();
}

void MFCMain::MenuEditPaste()
{
	m_ToolSystem.onActionPasteItems();
}

void MFCMain::MenuEditSettings()
{
	_settings.ShowWindow(SW_SHOW);
}

void MFCMain::MenuGenerateRandomTerrain()
{
	m_ToolSystem.onActionGenerateTerrain();
}

void MFCMain::MenuToggleWireframe()
{
	m_ToolSystem.onActionToggleWireframe();
}

void MFCMain::MenuSpawnTree()
{
	m_ToolSystem.onActionSpawnModel("database/data/Lowpoly_tree_sample.cmo", "database/data/placeholder.dds", DirectX::SimpleMath::Vector3(3.0f, 3.0f, 3.0f));
}

void MFCMain::MenuTranslate()
{
	m_ToolSystem.onActionChangeEditorState(Editor::State::TRANSLATE);
}

void MFCMain::MenuRotate()
{
	m_ToolSystem.onActionChangeEditorState(Editor::State::ROTATE);
}

void MFCMain::MenuScale()
{
	m_ToolSystem.onActionChangeEditorState(Editor::State::SCALE);
}

MFCMain::MFCMain()
{}

MFCMain::~MFCMain()
{}
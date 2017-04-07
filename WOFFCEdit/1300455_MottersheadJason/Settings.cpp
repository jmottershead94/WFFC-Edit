// Settings.cpp : implementation file
//

#include "../stdafx.h"
#include "Settings.h"
#include "afxdialogex.h"


// Settings dialog
IMPLEMENT_DYNAMIC(Settings, CDialogEx)

BEGIN_MESSAGE_MAP(Settings, CDialogEx)
	ON_COMMAND(IDC_CHECK3, &Settings::MenuInvertCamera)
END_MESSAGE_MAP()

Settings::Settings(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{}

Settings::~Settings()
{
}

void Settings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void Settings::MenuInvertCamera()
{
	Utils::SetInvertedCamera(!Utils::InvertCamera());
}


// Settings message handlers

// Settings.cpp : implementation file
//

#include "../stdafx.h"
#include "Settings.h"
#include "afxdialogex.h"


// Settings dialog
IMPLEMENT_DYNAMIC(Settings, CDialogEx)

BEGIN_MESSAGE_MAP(Settings, CDialogEx)
	ON_COMMAND(IDC_CHECK3, &Settings::MenuInvertCamera)
	ON_BN_CLICKED(IDOK, &Settings::OnBnClickedOk)
END_MESSAGE_MAP()

Settings::Settings(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{}

Settings::~Settings()
{
}

BOOL Settings::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_TS_X)->SetWindowTextW(L"1");
	GetDlgItem(IDC_TS_Y)->SetWindowTextW(L"1");
	GetDlgItem(IDC_TS_Z)->SetWindowTextW(L"1");

	GetDlgItem(IDC_RR_X)->SetWindowTextW(L"1");
	GetDlgItem(IDC_RR_Y)->SetWindowTextW(L"1");
	GetDlgItem(IDC_RR_Z)->SetWindowTextW(L"1");

	GetDlgItem(IDC_SR_X)->SetWindowTextW(L"0.25");
	GetDlgItem(IDC_SR_Y)->SetWindowTextW(L"0.25");
	GetDlgItem(IDC_SR_Z)->SetWindowTextW(L"0.25");

	return TRUE;
}

void Settings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void Settings::MenuInvertCamera()
{
	Utils::SetInvertedCamera(!Utils::InvertCamera());
}

void Settings::OnBnClickedOk()
{
	wchar_t 	numberraw[20];
	DirectX::SimpleMath::Vector3 translationSpeed, rotationRate, scaleRate;

	translationSpeed = Utils::TranslationSpeed();
	rotationRate = Utils::RotationRate();
	scaleRate = Utils::ScaleRate();

	// Retreive the numbers from the text boxes.
	GetDlgItemText(IDC_TS_X, numberraw, sizeof(numberraw));
	swscanf_s(numberraw, L"%f", &translationSpeed.x);
	GetDlgItemText(IDC_TS_Y, numberraw, sizeof(numberraw));
	swscanf_s(numberraw, L"%f", &translationSpeed.y);
	GetDlgItemText(IDC_TS_Y, numberraw, sizeof(numberraw));
	swscanf_s(numberraw, L"%f", &translationSpeed.z);

	GetDlgItemText(IDC_RR_X, numberraw, sizeof(numberraw));
	swscanf_s(numberraw, L"%f", &rotationRate.x);
	GetDlgItemText(IDC_RR_Y, numberraw, sizeof(numberraw));
	swscanf_s(numberraw, L"%f", &rotationRate.y);
	GetDlgItemText(IDC_RR_Y, numberraw, sizeof(numberraw));
	swscanf_s(numberraw, L"%f", &rotationRate.z);

	GetDlgItemText(IDC_SR_X, numberraw, sizeof(numberraw));
	swscanf_s(numberraw, L"%f", &scaleRate.x);
	GetDlgItemText(IDC_SR_Y, numberraw, sizeof(numberraw));
	swscanf_s(numberraw, L"%f", &scaleRate.y);
	GetDlgItemText(IDC_SR_Y, numberraw, sizeof(numberraw));
	swscanf_s(numberraw, L"%f", &scaleRate.z);

	// Make sure there are no negative values.
	translationSpeed = Maths::AbsVector(translationSpeed);
	rotationRate = Maths::AbsVector(rotationRate);
	scaleRate = Maths::AbsVector(scaleRate);

	Utils::SetTranslationSpeed(translationSpeed);
	Utils::SetRotationRate(rotationRate);
	Utils::SetScaleRate(scaleRate);

	ShowWindow(HIDE_WINDOW);
}
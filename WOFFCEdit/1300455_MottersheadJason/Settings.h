#pragma once

#include "../resource.h"
#include "Utilities/Utils.h"

// Settings dialog

class Settings : public CDialogEx
{
	DECLARE_DYNAMIC(Settings)

public:
	Settings(CWnd* pParent = NULL);   // standard constructor
	virtual ~Settings();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
	/**
	 * Allows the user to invert camera controls.
	 */
	afx_msg void MenuInvertCamera();

	DECLARE_MESSAGE_MAP()
};

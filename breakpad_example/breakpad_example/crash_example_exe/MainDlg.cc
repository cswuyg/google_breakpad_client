/**
dialog
cswuyg@gmail.com
2013.8.30
*/

#include "stdafx.h"
#include "MainDlg.h"


LRESULT CMainDlg::OnInitDialog( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	SetWindowText(L"A Crash Guard Example by cswuyg");
	CenterWindow();

	HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	SetIcon(hIconSmall, FALSE);

	return TRUE;
}

LRESULT CMainDlg::OnOK( WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	EndDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnCancel( WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	EndDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnCrash( WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	// crash
	char* p = NULL;
	*p = 0;
	return 0;
}

// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"
#include "NetAdapter.h"
	
#ifdef DWMBLUR	//win7毛玻璃开关
#include <dwmapi.h>
#pragma comment(lib,"dwmapi.lib")
#endif
	
CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;
}

CMainDlg::~CMainDlg()
{

}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	#ifdef DWMBLUR	//win7毛玻璃开关
	MARGINS mar = {5,5,30,5};
	DwmExtendFrameIntoClientArea ( m_hWnd, &mar );
	#endif

	SetMsgHandled(FALSE);
	return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;
	// 初始化刷新事件
	m_NetMatrix.SetEvent(this);
	// 初始化窗口
	assert(GetRoot());
	MyHelper::Instance()->InitWindow(GetRoot());
	// 初始化网格
	m_NetMatrix.Init();
	// 初始化 tileview
	SOUI::STileView* pTileView = FindChildByName2<SOUI::STileView>(L"tv_net");
	assert(pTileView);
	CNetAdapter* pAdapter = new CNetAdapter(m_NetMatrix.getNet());
	pTileView->SetAdapter(pAdapter);
	pAdapter->SetEvent(&m_NetMatrix);
	pAdapter->Release();
	return 0;
}

// 刷新网格
void CMainDlg::RefreshNet(std::vector<std::vector<Grid>> vecNet)
{
	SOUI::STileView* pTileView = FindChildByName2<SOUI::STileView>(L"tv_net");
	assert(pTileView);
	CNetAdapter* pAdapter = static_cast<CNetAdapter*>(pTileView->GetAdapter());
	if (pAdapter != nullptr) {
		pAdapter->UpdateNet(vecNet);
		pAdapter->notifyDataSetChanged();
	}
	// SMessageBox(NULL, L"此处需要刷新网格", L"提示", MB_OK);
}

void CMainDlg::OnClose()
{
	CSimpleWnd::DestroyWindow();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	if (!m_bLayoutInited) return;
	
	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if(!pBtnMax || !pBtnRestore) return;
	
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}


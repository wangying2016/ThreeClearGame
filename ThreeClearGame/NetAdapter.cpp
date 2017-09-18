#include "stdafx.h"
#include "NetAdapter.h"

CNetAdapter::CNetAdapter()
{

}

CNetAdapter::~CNetAdapter()
{

}

// 元素个数
int CNetAdapter::getCount()
{
	return NET_ROW_NUMBER * NET_COL_NUMBER;
}

// 设置界面样式
void CNetAdapter::getView(int position, SWindow * pItem,
	pugi::xml_node xmlTemplate)
{
	if (pItem->GetChildrenCount() == 0) {
		pItem->InitFromXml(xmlTemplate);
	}
	SButton* pButton = pItem->FindChildByName2<SButton>(L"btn_grid");
	assert(pItem);
	pItem->GetEventSet()->subscribeEvent(SOUI::EVT_CMD,
		Subscriber(&CNetAdapter::OnButtonClick, this));
}

// 按钮点击
bool CNetAdapter::OnButtonClick(EventArgs* pEvt)
{
	// SMessageBox(NULL, L"被点击了", L"提示", MB_OK);
	SWindow* pTemplate = sobj_cast<SWindow>(pEvt->sender);
	assert(pTemplate);
	SButton* pButton = pTemplate->FindChildByName2<SButton>(L"btn_grid");
	assert(pButton);
	pButton->SetCheck(TRUE);
	return true;
}
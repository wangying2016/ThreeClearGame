#include "stdafx.h"
#include "NetAdapter.h"

CNetAdapter::CNetAdapter(std::vector<std::vector<Grid>> vecNet)
{
	m_vecNet = vecNet;
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
	// 绑定按钮事件
	SButton* pButton = pItem->FindChildByName2<SButton>(L"btn_grid");
	assert(pItem);
	pItem->GetEventSet()->subscribeEvent(SOUI::EVT_CMD,
		Subscriber(&CNetAdapter::OnButtonClick, this));
	// 显示图像按钮
	std::pair<int, int> grid = covertPostion2Grid(position);
	switch (m_vecNet[grid.first][grid.second].status)
	{
	// 星
	case Grid_Star:
		pButton->SetAttribute(L"skin", SKIN_STAR);
	break;
	// 心
	case Grid_Heart:
		pButton->SetAttribute(L"skin", SKIN_HEART);
	break;
	// 剑
	case Grid_Sword:
		pButton->SetAttribute(L"skin", SKIN_SWORD);
	break;
	// 盾
	case Grid_SHIELD:
		pButton->SetAttribute(L"skin", SKIN_SHIELD);
	break;
	}
	pButton->RequestRelayout();
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

// 将 tileview 的 position 转化为 Grid 坐标
std::pair<int, int> CNetAdapter::covertPostion2Grid(int position)
{
	return std::make_pair<int, int>(position / NET_COL_NUMBER, position % NET_COL_NUMBER);
}
/*******************************************************************   
 *  文件名称: NetAdatper.h
 *  简要描述: 实现界面格子内容适配显示
 *   
 *  创建日期: 2017-9-18
 *  作　　者: 王莹
 *  说　　明: 
 *   
 *  修改日期: 
 *  作　　者: 
 *  说　　明: 
 ******************************************************************/  
#pragma once

class CNetAdapter : public SAdapterBase
{
public:
	CNetAdapter();
	virtual ~CNetAdapter();
	
	// 元素个数
	int getCount() override;

	// 设置界面样式
	void getView(int position, SWindow * pItem, 
		pugi::xml_node xmlTemplate) override;

	// 按钮点击
	bool OnButtonClick(EventArgs* pEvt);
};
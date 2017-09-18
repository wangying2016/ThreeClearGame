/*******************************************************************   
 *  文件名称: NetMatrix.h
 *  简要描述: 用来管理游戏中的网格信息的类
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
#include "ThreeClearHelper.h"

class NetMatrix
{
public:
	NetMatrix();
	virtual ~NetMatrix();

public:

	// 获取内部数据结构
	std::vector<std::vector<Grid>> getNet();

	// 初始化随机阵列
	// 1. 随机排列四种图像按钮
	// 2. 不能有 3 个及其以上个数相连
	void Init();

	// 尝试消除
	bool Change(Grid first, Grid second);

private:
	// 存储矩阵
	std::vector<std::vector<Grid>> m_vecNet;
};
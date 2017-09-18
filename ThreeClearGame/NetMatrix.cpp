#include "stdafx.h"
#include "NetMatrix.h"

NetMatrix::NetMatrix()
{
	for (int i = 0; i < NET_ROW_NUMBER; ++i) {
		std::vector<Grid> row;
		for (int j = 0; j < NET_COL_NUMBER; ++j) {
			Grid grid(i, j);
			row.push_back(grid);
		}
		m_vecNet.push_back(row);
	}
}

NetMatrix::~NetMatrix()
{
	m_vecNet.clear();
}
	
// 获取内部数据结构
std::vector<std::vector<Grid>> NetMatrix::getNet()
{
	return m_vecNet;
}

// 初始化随机阵列
void NetMatrix::Init()
{
	for (int i = 0; i < NET_ROW_NUMBER; ++i) {
		for (int j = 0; j < NET_COL_NUMBER; ++j) {
			int random = TreeClearHelper::Instance()->produceRadomNumber(4);
			switch (random)
			{
				case 0: m_vecNet[i][j].status = Grid_Star; break;
				case 1: m_vecNet[i][j].status = Grid_Heart; break;
				case 2: m_vecNet[i][j].status = Grid_Sword; break;
				case 3: m_vecNet[i][j].status = Grid_SHIELD; break;
			}
		}
	}
}

// 尝试消除
bool NetMatrix::Change(Grid first, Grid second)
{
	return true;
}
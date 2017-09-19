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
	RandomNet();
	while (!ValidNet()) RandomNet();
}

// 尝试消除
bool NetMatrix::Change(Grid first, Grid second)
{
	return true;
}

// 随机产生一个阵列
void NetMatrix::RandomNet()
{
	for (int i = 0; i < NET_ROW_NUMBER; ++i) {
		for (int j = 0; j < NET_COL_NUMBER; ++j) {
			int random = MyHelper::Instance()->Random(4);
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

// 是否合法阵列
bool NetMatrix::ValidNet()
{
	// 行检查是否有连续 3 个
	for (int i = 0; i < NET_ROW_NUMBER; ++i) {
		for (int j = 0; j < NET_COL_NUMBER - 2; ++j) {
			if (m_vecNet[i][j].status == m_vecNet[i][j + 1].status &&
				m_vecNet[i][j + 1].status == m_vecNet[i][j + 2].status) {
				return false;
			}
		}
	}
	// 列检查是否有连续 3 个
	for (int j = 0; j < NET_COL_NUMBER; ++j) {
		for (int i = 0; i < NET_ROW_NUMBER - 2; ++i) {
			if (m_vecNet[i][j].status == m_vecNet[i + 1][j].status &&
				m_vecNet[i + 1][j].status == m_vecNet[i + 2][j].status) {
				return false;
			}
		}
	}
	// 检查通过
	return true;
}
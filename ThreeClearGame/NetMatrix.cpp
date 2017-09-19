#include "stdafx.h"
#include "NetMatrix.h"
#include "MyHelper.h"

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
	RandomNet(m_vecNet);
	while (!ValidNet(m_vecNet)) RandomNet(m_vecNet);
}

// 尝试消除
bool NetMatrix::Change(PosPoint pre, PosPoint cur)
{
	auto vecNet = m_vecNet;
	std::swap(vecNet[pre.row][pre.col], vecNet[cur.row][cur.col]);
	if (!ValidNet(vecNet)) SMessageBox(NULL, L"成功消除", L"提示", MB_OK);
	else SMessageBox(NULL, L"消除失败", L"提示", MB_OK);
	return true;
}

// 随机产生一个阵列
void NetMatrix::RandomNet(std::vector<std::vector<Grid>>& vecNet)
{
	for (int i = 0; i < NET_ROW_NUMBER; ++i) {
		for (int j = 0; j < NET_COL_NUMBER; ++j) {
			int random = MyHelper::Instance()->Random(4);
			switch (random)
			{
			case 0: vecNet[i][j].status = Grid_Star; break;
			case 1: vecNet[i][j].status = Grid_Heart; break;
			case 2: vecNet[i][j].status = Grid_Sword; break;
			case 3: vecNet[i][j].status = Grid_SHIELD; break;
			}
		}
	}
}

// 是否合法阵列
bool NetMatrix::ValidNet(std::vector<std::vector<Grid>> vecNet)
{
	// 行检查是否有连续 3 个
	for (int i = 0; i < NET_ROW_NUMBER; ++i) {
		for (int j = 0; j < NET_COL_NUMBER - 2; ++j) {
			if (vecNet[i][j].status == vecNet[i][j + 1].status &&
				vecNet[i][j + 1].status == vecNet[i][j + 2].status) {
				return false;
			}
		}
	}
	// 列检查是否有连续 3 个
	for (int j = 0; j < NET_COL_NUMBER; ++j) {
		for (int i = 0; i < NET_ROW_NUMBER - 2; ++i) {
			if (vecNet[i][j].status == vecNet[i + 1][j].status &&
				vecNet[i + 1][j].status == vecNet[i + 2][j].status) {
				return false;
			}
		}
	}
	// 检查通过
	return true;
}
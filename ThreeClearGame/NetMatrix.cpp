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
	m_event = nullptr;
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
	// 交换这两个点
	auto vecNet = m_vecNet;
	std::swap(vecNet[pre.row][pre.col], vecNet[cur.row][cur.col]);
	// 检查是否能够消去
	if (!ValidNet(vecNet)) 
		MyHelper::Instance()->WriteLog(L"消除成功!");
	else {
		MyHelper::Instance()->WriteLog(L"消除失败!");
		return false;
	}
	// 消除成功，输出消除信息：两个点都需要进行查询
	std::vector<PosPoint> prePoints = GetCancelPoints(pre, vecNet);
	std::vector<PosPoint> curPoints = GetCancelPoints(cur, vecNet);
	SOUI::SStringW strPoint, strPointsMsg, strCancelMsg;
	for (auto it = prePoints.begin(); it != prePoints.end(); ++it)
		strPointsMsg += strPoint.Format(L"(%d, %d) ", it->row, it->col);
	for (auto it = curPoints.begin(); it != curPoints.end(); ++it)
		strPointsMsg += strPoint.Format(L"(%d, %d) ", it->row, it->col);
	strCancelMsg.Format(L"消除了以下点：%s", strPointsMsg);
	MyHelper::Instance()->WriteLog(strCancelMsg);
	// 设置删除的点为删除皮肤
	for (int i = 0; i < prePoints.size(); ++i) {
		vecNet[prePoints[i].row][prePoints[i].col].status = Grid_Delete;
	}
	for (int i = 0; i < curPoints.size(); ++i) {
		vecNet[curPoints[i].row][curPoints[i].col].status = Grid_Delete;
	}
	m_vecNet = vecNet;
	m_event->RefreshNet(m_vecNet);
	// TODO: 处理消除后的阵列下移，补充随机点
	// TODO: 如果补充后的阵列仍然有可以消除的点，则继续消除直到不能消除为止
	return true;
}

// 设置刷新事件指针
void NetMatrix::SetEvent(RefreshEvent* event)
{
	if (event != nullptr) m_event = event;
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
			case 3: vecNet[i][j].status = Grid_Shield; break;
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

// 计算消除点
std::vector<PosPoint> NetMatrix::GetCancelPoints(PosPoint point, std::vector<std::vector<Grid>> vecNet)
{
	// 由此起点开始发散查询
	std::vector<PosPoint> horizontalPoints, verticalPoints;
	GridStatus status = vecNet[point.row][point.col].status;
	// 向左
	for (int left = point.col - 1; left >= 0; --left) {
		if (vecNet[point.row][left].status == status)
			horizontalPoints.push_back(PosPoint(point.row, left));
		else break;
	}
	// 向右
	for (int right = point.col + 1; right < NET_COL_NUMBER; ++right) {
		if (vecNet[point.row][right].status == status)
			horizontalPoints.push_back(PosPoint(point.row, right));
		else break;
	}
	// 向上
	for (int up = point.row - 1; up >= 0; --up) {
		if (vecNet[up][point.col].status == status)
			verticalPoints.push_back(PosPoint(up, point.col));
		else break;
	}
	// 向下
	for (int down = point.row + 1; down < NET_ROW_NUMBER; ++down) {
		if (vecNet[down][point.col].status == status)
			verticalPoints.push_back(PosPoint(down, point.col));
		else break;
	}
	// 检查结果是否合理
	// 1. 水平或竖直方向上的个数小于等于 2，则该方向数值舍弃（之所以是 2，是因为
	// 基准点在最后加上）
	if (horizontalPoints.size() < 2) horizontalPoints.clear();
	if (verticalPoints.size() < 2) verticalPoints.clear();
	// 2. 将两个集合的点合并
	std::vector<PosPoint> results;
	for (auto h = horizontalPoints.begin(); h < horizontalPoints.end(); ++h)
			results.push_back(*h);
	for (auto v = verticalPoints.begin(); v < verticalPoints.end(); ++v)
			results.push_back(*v);
	if (horizontalPoints.size() >= 2 || verticalPoints.size() >= 2)
		results.push_back(point);
	return results;
}

// 显示消除消息
void NetMatrix::ShowCancelMsg()
{

}

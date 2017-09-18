#include <cstdlib>
#include <time.h>
#include "stdafx.h"
#include "ThreeClearHelper.h"

TreeClearHelper::TreeClearHelper()
{
	std::srand(time(0));
}

TreeClearHelper* TreeClearHelper::Instance()
{
	static std::shared_ptr<TreeClearHelper> spMgr;
	if (!spMgr.get()) {
		spMgr.reset(new TreeClearHelper());
	}
	return spMgr.get();
}

TreeClearHelper::~TreeClearHelper()
{

}

// 获取随机数
// modular  随机数发生器范围，0开始
// excepts  在随机数发生器范围内的不计入随机运算的数字
int TreeClearHelper::produceRadomNumber(int modular, std::vector<int> excepts)
{
	// 判断：excepts 是否占用了所有的 modular 的值
	if (modular <= excepts.size()) return -1;
	// 产生一个值
	int random = std::rand() % modular;
	// 判断该值是否被剔除不考虑，如果是的话，则再生成一个随机数，直到生成的随机数
	// 值不在被剔除值的范围中之后，才确定返回其值
	while (std::find(excepts.cbegin(), excepts.cend(), random) != excepts.cend()) {
		random = std::rand() % modular;
	}
	return random;
}
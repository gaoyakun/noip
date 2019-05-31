#include <vector>
#include <iostream>
#include <stdexcept>
#include "core/judge.h"

using std::vector;
using std::runtime_error;

/** 多路归并排序，将给定的k组从小到大排列的有序数列合并为一组有序数列 
 * 参数 numbers: 长度为k的数组，每个元素是一个长度为Sk的有序数组，数组内每个数字大小介于0到10000之间 
 * 输出: 一行，为合并后的有序数组，数字之间用一个空格键隔开
 * 数据规模：k<=1600, Sk<=1000
 */
static void solution (std::ostream &out, const vector<vector<int> > &numbers) {
	throw runtime_error("Not implemented");
}

DECLARE_PROBLEM(nwaymerge, solution);

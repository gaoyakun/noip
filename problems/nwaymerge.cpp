#include <vector>
#include <stdexcept>
#include <queue>

using std::vector;
using std::runtime_error;
using std::priority_queue;

struct Comp {
	bool operator () (int a, int b) const {
		return (a & 0xffff) > (b & 0xffff);
	}
};

/** 多路归并排序，将给定的k组从小到大排列的有序数列合并为一组有序数列 
 * 参数 numbers: 长度为k的数组，每个元素是一个长度为Sk的有序数组，数组内每个数字大小介于0到10000之间 
 * 参数 result: 空数组，请将合并结果存入这个数组 
 * 数据规模：k<=2000, Sk<=10000
 */
void solution (const vector<vector<int> > &numbers, vector<int> &result) {
	priority_queue<int, vector<int>, Comp> q;
	vector<int> p(numbers.size(), 0);
	for (int i = 0; i < p.size(); i++) {
		q.push ((i<<16)|numbers[i][p[i]]);
	}
	while (!q.empty()) {
		int n = q.top ();
		q.pop ();
		result.push_back(n & 0xffff);
		int idx = n >> 16;
		if (p[idx] < numbers[idx].size()-1) {
			p[idx]++;
			q.push ((idx<<16)|numbers[idx][p[idx]]);
		}
	}
}

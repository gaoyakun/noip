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

/** ��·�鲢���򣬽�������k���С�������е��������кϲ�Ϊһ���������� 
 * ���� numbers: ����Ϊk�����飬ÿ��Ԫ����һ������ΪSk���������飬������ÿ�����ִ�С����0��10000֮�� 
 * ���� result: �����飬�뽫�ϲ��������������� 
 * ���ݹ�ģ��k<=2000, Sk<=10000
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

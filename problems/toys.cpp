#include <vector>
#include <iostream>
#include <stdexcept>
#include "core/judge.h"

using std::vector;
using std::runtime_error;

/** 
 *��Jasio ��һ�������С�к�������ϲ��������ˣ�����n ����ͬ�����,���Ƕ��������˺ܸߵļ����ϣ�����Jasio �ò������ǡ�Ϊ�������ķ������㹻�Ŀռ䣬���κ�ʱ�̵ذ��϶������г���k����ߡ�
 *��Jasio�ڵذ�������ߡ�Jasio���������ڷ����������Ķ��ӣ���Jasio ����ذ��ϵ��������ʱ�������Լ�ȥ�ã���������������ڼ����ϣ���������������ȥ�ã���������ߵ�ʱ��˳��Ҳ�Ὣһ���ذ��ϵ���߷��ϼ���ʹ�õذ������㹻�Ŀռ䡣
 *���������������Լ��ĺ��ӣ��������ܹ�Ԥ�ϵ�Jasio����Щʲô��ߡ��������뾡����ʹ�Լ�ȥ����������ߵĴ����������٣�Ӧ����ô���Ű���߷Żؼ����ϵ�˳����?
 *  ���� n: ��߸���
 *  ���� k: ������������Ŀ
 *  ���� toys: Jasio�����������߱��
 *  ����� һ�����֣�Jasio����������Ҫ�ö��ٴ����
 *  
 *  ���ݹ�ģ��1 <= k <= n <= 100000, 1 <= toys.size() <= 500000
 */
static void solution (std::ostream &out, int n, int k, const vector<int> &toys) {
	throw runtime_error("Not implemented");
}

DECLARE_PROBLEM(toys, solution);

#include <vector>
#include <iostream>
#include <stdexcept>
#include "core/judge.h"

using std::vector;
using std::runtime_error;

/** 
 *　Jasio 是一个三岁的小男孩，他最喜欢玩玩具了，他有n 个不同的玩具,它们都被放在了很高的架子上，所以Jasio 拿不到它们。为了让他的房间有足够的空间，在任何时刻地板上都不会有超过k个玩具。
 *　Jasio在地板上玩玩具。Jasio的妈妈则在房间里陪他的儿子，当Jasio 想玩地板上的其他玩具时，他会自己去拿，如果他想玩的玩具在架子上，他的妈妈则会帮他去拿，当她拿玩具的时候，顺便也会将一个地板上的玩具放上架子使得地板上有足够的空间。
 *　他的妈妈很清楚自己的孩子，所以他能够预料到Jasio想玩些什么玩具。所以她想尽量的使自己去架子上拿玩具的次数尽量的少，应该怎么安排把玩具放回架子上的顺序呢?
 *  参数 n: 玩具个数
 *  参数 k: 地上玩具最大数目
 *  参数 toys: Jasio依次想玩的玩具编号
 *  输出： 一个数字，Jasio的妈妈最少要拿多少次玩具
 *  
 *  数据规模：1 <= k <= n <= 100000, 1 <= toys.size() <= 500000
 */
static void solution (std::ostream &out, int n, int k, const vector<int> &toys) {
	throw runtime_error("Not implemented");
}

DECLARE_PROBLEM(toys, solution);

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "test_common.h"

using std::cin;
using std::cout;
using std::endl;
using std::copy;
using std::flush;
using std::vector;

typedef vector<int>::iterator iter;
typedef vector<int>::const_iterator const_iter;

vector<int> nums[2];
size_t cur = 0;

size_t merge(size_t l, size_t r) {
	size_t tot = 0;
	if (l < r) {
		size_t mid = l + (r - l) / 2;
		tot += merge(l, mid);
		tot += merge(mid + 1, r);
		size_t i = l;
		size_t j = mid + 1;
		size_t k = l;
		while (i <= mid || j <= r) {
			if (j > r || (i <= mid && nums[0][i] <= nums[0][j])) {
				nums[1][k++] = nums[0][i++];
			} else {
				nums[1][k++] = nums[0][j++];
				tot += mid - i + 1;
			}
		}
		for (size_t i = l; i <= r; i++) {
			nums[0][i] = nums[1][i];
		}
	}
	return tot;
}

size_t algo_bruteforce() {
	size_t tot = 0;
	for (size_t i = 0; i < nums[0].size() - 1; i++) {
		for (size_t j = i + 1; j < nums[0].size(); j++) {
			if (nums[0][i] > nums[0][j]) {
				tot++;
			}
		}
	}
	return tot;
}

size_t algo_merge() {
	return merge(0, nums[0].size() - 1);
}


size_t(*algo[])() = {
	algo_bruteforce,
	algo_merge
};

const char* names[] = {
	"Brute force",
	"Merge sort"
};

double perf[] = {
	0,
	0
};

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Usage: test_reverse_couple ARRAY_SIZE TEST_COUNT" << endl;
		return 1;
	}
	const size_t n = atoi(argv[1]);
	const size_t times = atoi(argv[2]);
	int seed = (int)(rdtsc() % 1000);
	seed = 66;
	cout << "Random seed: " << seed << endl;
	randSeed(seed);

	nums[0].resize(n);
	nums[1].resize(n);
	vector<int> tmp(n);

	cout << "Testing ..." << flush;
	for (size_t k = 0; k < times; k++) {
		for (size_t i = 0; i < n; i++) {
			tmp[i] = randRange(-1000000, 1000000);
		}
		size_t val;
		for (size_t i = 0; i < sizeof(names) / sizeof(names[0]); i++) {
			Timing timing;
			copy(tmp.begin(), tmp.end(), nums[0].begin());

			timing.begin();
			size_t r = algo[i]();
			perf[i] += timing.end();

			if (i == 0) {
				val = r;
			}
			else if (r != val) {
				cout << "failed" << endl;
				return 1;
			}
		}
	}
	cout << "Ok" << endl;
	for (size_t k = 0; k < sizeof(names) / sizeof(names[0]); k++) {
		cout << "\t" << names[k] << "...";
		if (k == 0) {
			cout << "100%" << endl;
		}
		else {
			cout << (perf[k] / perf[0] * 1000) / 10 << "%" << endl;
		}
	}
	return 0;
}
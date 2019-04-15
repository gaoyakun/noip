## 树状数组（Binary Indexed Tree 二叉索引树）

&emsp;&emsp;树状数组类似于线段树，主要用于查询数组中任意区间的元素和。它的查询和修改的时间复杂度均为$O(\log N)$。它的核心规律为树状数组中第$i$个元素对应原数组中$[i-lowbit(i)+1,i]$这一区间的和。令A为原数组，C为对应的树状数组，则对应的公式为：

$$lowbit(n)=n\mathbin{\&}-n$$

$$C[n]=\sum_{k=n-lowbit(n)+1}^n A[k]$$

&emsp;&emsp;由公式可见，元素$C[i]$的前面一个不充叠的区间为$C[i-lowbit(i)]$，所以如果想要求原数组前$n$个元素的和，可以用以下的方式：

```c++
// 求树状数组C的前n个元素和（假设元素起始索引为1）：
int sum (int C[], int n) {
    int result = 0;
    while (n) {
        result += C[n];
        n -= n & -n;
    }
    return result;
}
```
&emsp;&emsp;基本的树状数组支持单点修改。
```c++
// 原数组的第n个元素增加d，total为总的元素个数
void add (int C[], int total, int n, int d) {
    while (n <= total) {
        C[n] += d;
        n += n & -n;
    }
}
```



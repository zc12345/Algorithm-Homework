#include <iostream>
using namespace std;
bool greedy(int d[],int n,int k){
	int s=0;
	int num=0;
	for(int i=0;i<k;i++){
		if(d[i]>n){
			cout<<"No Solution!"<<endl;
			return false;
		}else{
			s+=d[i];
			if(s>n){
				num++;
				s=d[i];
			}else continue;
		}
	}
	if(s>0)num++;
	cout<<num<<endl;
	return true;
}
int main()
{
	int n,k;
	int d[1000];
	cin>>n>>k;
	for(int i=0;i<k;i++){
		cin>>d[i];
	}
	bool b=greedy(d,n,k);
	system("pause");
	return 0;
}
/***********************************************
★问题描述： 一辆汽车加满油后可行驶n公里。旅途中有若干个加油站。设计一个有效算法，指出应在哪些加油站停靠加油，使沿途加油次数最少。
对于给定的n(n <= 5000)和k(k <= 1000)个加油站位置，编程计算最少加油次数。并证明算法能产生一个最优解。

★算法设计：对于给定的n和k个加油站位置，计算最少加油次数。

★数据输入： 由文件input.txt 给出输入数据。第1行有2个正整数n和k，表示汽车加满油后可行驶n公里，且旅途中有k个加油站。
接下来的1 行中，有k+1 个整数，表示第k个加油站与第k-1 个加油站之间的距离。第0 个加油站表示出发地，汽车已加满油。第k+1 个加油站表示目的地。

★结果输出: 将计算的最少加油次数输出到文件output.txt 。如果无法到达目的地，则输出”No Solution”。

输入文件示例
input.txt
7	7
1	2	3	4	5	1	6

输出文件示例
output.txt
4

************************************************/

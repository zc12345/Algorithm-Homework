#include<iostream>
using namespace std;

int set(int n){
	//if(n==1)return 1;
	//else if(n>=1)
	//{
		int m=1;
		for(int i=1;i<=n/2;i++)m+=set(i);
		return m;
	//}
	//else return -1;
}

int main(void){
	int k;
	cin>>k;
	cout<<set(k)<<endl;
	return 0;
} 

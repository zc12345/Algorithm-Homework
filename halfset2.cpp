#include<iostream>
using namespace std;

int list[1000]={0};

int set(int n){
	int m=1;
	for(int i=1;i<=n/2;i++){
		if(list[i]==0)
			m+=set(i);
		else
			m+=list[i];
		}
	return list[n]=m;
}
int main(void){
	int k;
	cin>>k;
	cout<<set(k)<<endl;
	return 0;
} 

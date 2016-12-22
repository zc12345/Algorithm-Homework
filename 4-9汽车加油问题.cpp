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

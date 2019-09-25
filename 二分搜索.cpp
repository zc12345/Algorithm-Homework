#include<iostream>
using namespace std;

template <class Type>
int BinarySearch1(Type a[], const Type& x, int n){
	int left=0;
	int right=n-1;
	while(left<=right){
		int middle=(left+right)/2;
		if(x==a[middle])return middle;
		if(x>a[middle])left=middle;
		else right=middle;
	}
	return -1;
}
template <class Type>
int BinarySearch2(Type a[], const Type& x, int n){
	int left=0;
	int right=n-1;
	while(left<right-1){
		int middle=(left+right)/2;
		if(x<a[middle])right=middle;
		else left=middle;
	}
	if(x==a[left])return left;
	else return -1;
}
template <class Type>
int BinarySearch3(Type a[], const Type& x, int n){
	int left=0;
	int right=n-1;
	while(left+1!=right-1){
		int middle=(left+right)/2;
		if(x>a[middle])left=middle;
		else right=middle;
	}
	if(x==a[left])return left;
	else return -1;
}
template <class Type>
int BinarySearch4(Type a[], const Type& x, int n){
	if(n>0&&x>=a[0]){
	int left=0;
	int right=n-1;
	while(left<right){
		int middle=(left+right)/2;
		if(x<a[middle])right=middle-1;
		else left=middle;
	}
	if(x==a[left])return left;
	}
	return -1;
}
template <class Type>
int BinarySearch5(Type a[], const Type& x, int n){
	if(n>0&&x>=a[0]){
	int left=0;
	int right=n-1;
	while(left<right){
		int middle=(left+right+1)/2;
		if(x<a[middle])right=middle-1;
		else left=middle;
	}
	if(x==a[left])return left;
	}
	return -1;
}
template <class Type>
int BinarySearch6(Type a[], const Type& x, int n){
	if(n>0&&x>=a[0]){
	int left=0;
	int right=n-1;
	while(left<right){
		int middle=(left+right+1)/2;
		if(x<a[middle])right=middle-1;
		else left=middle+1;
	}
	if(x==a[left])return left;
	}
	return -1;
}
template <class Type>
int BinarySearch7(Type a[], const Type& x, int n){
	if(n>0&&x>=a[0]){
	int left=0;
	int right=n-1;
	while(left<right){
		int middle=(left+right+1)/2;
		if(x<a[middle])right=middle;
		else left=middle;
	}
	if(x==a[left])return left;
	}
	return -1;
}
int main(){
	int n=10;	
	int a[10]={1,2,3,4,5,6,7,8,9,12};
	cout<<BinarySearch2(a,12,n);
	system("pause");
	return 0;
}

#include <iostream>    
#include <cmath>     
#include "RandomNumber.h"     
using namespace std;    
  
class Queen  
{  
    friend bool nQueen(int);  
private:  
    bool Place(int k);//���Իʺ�k���ڵ�x[k]�еĺϷ���  
    bool Backtrack(int t);//��n������Ļ��ݷ�  
    bool QueensLV(int stopVegas);//�������n���ʺ���˹ά��˹�㷨  
    int n,*x,*y;  
};  
  
bool Queen::Place(int k)  
{//���Իʺ�k���ڵ�x[k]�еĺϷ���  
    for(int j=1;j<k;j++)  
        if((abs(k-j)==abs(x[j]-x[k]))||(x[j]==x[k]))  
            return false;  
    return true;  
}  
  
bool Queen::Backtrack(int t)  
{//��n������Ļ��ݷ�  
    if(t>n){  
        for(int i=1;i<=n;i++)  
            y[i]=x[i];  
        return true;  
    }  
    else  
        for(int i=1;i<=n;i++)  
        {  
            x[t]=i;  
            if(Place(t)&&Backtrack(t+1))  
                return true;  
        }  
        return false;  
}  
  
bool Queen::QueensLV(int stopVegas)  
{//�������n���ʺ���˹ά��˹�㷨  
    RandomNumber rnd;  
    int k=1;//�����������  
    int count=1;  
    //1<=stopVegas<=n��ʾ����������õĻʺ���  
    while((k<=stopVegas)&&(count>0))  
    {  
        count=0;  
        for(int i=1;i<=n;i++)  
        {  
            x[k]=i;  
            if(Place(k))  
                y[count++]=i;  
        }  
        if(count>0)  
            x[k++]=y[rnd.Random(count)];//���λ��  
    }  
    return (count>0);//count>0��ʾ���óɹ�  
}  
  
bool nQueen(int n)  
{  
    //����ݷ����ϵĽ�n���������˹ά��˹�㷨  
    Queen X;  
    //��ʼ��X  
    X.n=n;  
    int *p=new int[n+1];  
    int *q=new int[n+1];  
    for(int i=0;i<=n;i++)  
    {  
        p[i]=0;  
        q[i]=0;  
    }  
    X.y=p;  
    X.x=q;  
    int stop=2;  
    if(n>15)  
        stop=n-15;  
    bool found=false;  
    while(!X.QueensLV(stop));  
    //�㷨�Ļ�����������  
    if(X.Backtrack(stop+1))  
    {  
        for(int i=1;i<=n;i++)  
            cout<<p[i]<<" ";  
        found=true;  
    }  
    cout<<endl;  
    delete []p;  
    delete []q;  
    return found;  
}  
  
int main()    
{
	int n;
	cin>>n;
    if(!nQueen(n))  
    {  
        cout<<"�������ɹ�����"<<endl;  
    }  
    system("pause");  
    return 0;  
}    
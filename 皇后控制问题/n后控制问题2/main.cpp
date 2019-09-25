#include <iostream>      
#include <ctime>   
#include <cmath>   
#include <cstdlib>   
using namespace std;
   
//2ά������   
template <class Type>   
void MArray(Type** &x, int rows, int cols)   
{   
        //������ָ��   
        x = new Type* [rows];   
        //Ϊÿ�з���ռ�   
        for(int j = 0; j < rows; j++)   
        {   
                x[j] = new Type[cols];   
        }   
}   
   
   
template <class Type>   
void DelArray(Type** &x, int rows)   
{   
        //�ͷ�Ϊÿ��������Ŀռ�   
        for(int j = 0; j < rows; j++)   
        {   
                delete[] x[j];   
        }   
        //ɾ����ָ��   
        delete[] x;   
        x = NULL;   
}   
   
const unsigned long maxshort=65536L;   
const unsigned long multiplier=1194211693L;   
const unsigned long adder=12345L;   
   
//�������   
class RandomNumber   
{   
public:   
    //���캯����ȱʡֵ0��ʾ��ϵͳ�Զ���������   
    RandomNumber(unsigned long s=0);   
    //����0:n-1֮����������   
    unsigned short Random(unsigned long n);   
    //����[0,1)֮������ʵ��   
    double fRandom(void);   
private:   
    //��ǰ����   
    unsigned long randSeed;   
};   
   
//��������   
RandomNumber::RandomNumber(unsigned long s)   
{   
    if(s==0)   
        randSeed=time(0); //��ϵͳʱ���������   
    else   
        randSeed=s;       //���û��ṩ����   
}   
   
//����0:n-1֮����������   
unsigned short RandomNumber::Random(unsigned long n)   
{   
    randSeed=multiplier*randSeed+adder;   
    return (unsigned short)((randSeed>>16)%n);   
}   
   
//����[0,1)֮������ʵ��   
double RandomNumber::fRandom(void)   
{   
    return Random(maxshort)/double(maxshort);   
}   
   
   
class Queen   
{   
    friend bool nQueen(int);   
    private:   
        bool Place(int k);//���Իʺ�k���ڵ�x[k]�еĺϷ���   
        bool ddBacktrack(int t);//��n������ĵ�����   
        int Placed(int k);//�����ѷ��ûʺ����   
        int QueensLV(int stopVegas);//�������n���ʺ����˹ά��˹�㷨   
        bool ctrl(int m);//���Իʺ��Ƿ��ѿ�������   
        int n,//�ʺ����   
            *x,*y,*ans,**r;   
        int max,shu;   
        RandomNumber rnd;//���������������������,���Ч������   
};   
   
bool Queen::Place(int k)   
{//���Իʺ�k���ڵ�x[k]�еĺϷ���   
    if(x[k]>0)   
        for(int j=1;j<k;j++)   
            if((x[j]>0)&&((abs(k-j)==abs(x[j]-x[k]))||x[j]==x[k]))   
                return false;   
    return true;   
}   
   
int Queen::Placed(int k)   
{//�����ѷ��ûʺ����   
    int num=0;   
    for(int j=1;j<=k;j++)   
        if(x[j]>0) num++;   
    return num;   
}   
   
bool Queen::ctrl(int m)   
{//���Իʺ��Ƿ��ѿ�������m*m   
    int i,j,p,q,count=0;   
    shu=0;   
    for(i=1;i<=m;i++)   
        for(j=1;j<=m;j++) r[i][j]=0;//��ʼ��0   
    for(i=1;i<=m;i++)   
    {   
        if(x[i]>0) //i���лʺ�ʱ   
        {   
            shu++;   
            for(j=1;j<=m;j++) {r[i][j]=1;r[j][x[i]]=1;}   
            for(p=i,q=x[i];p>=1&&q>=1;p--,q--) r[p][q]=1;   
            for(p=i,q=x[i];p<=m&&q>=1;p++,q--) r[p][q]=1;   
            for(p=i,q=x[i];p>=1&&q<=m;p--,q++) r[p][q]=1;   
            for(p=i,q=x[i];p<=m&&q<=m;p++,q++) r[p][q]=1;   
        }   
    }   
    for(i=1;i<=m;i++)   
        for(j=1;j<=m;j++) count+=r[i][j];   
    return(count==m*m);   
}   
   
   
bool Queen::ddBacktrack(int t)   
{//��������n������Ļ��ݷ�   
    x[t]=-1;   
    int k=t;   
    bool *jc =new bool [n+1];   
    for(int i=1;i<=n;i++)   
        jc[i]=true;            
    while(k>t-1)   
    {   
        x[k]+=1;//����ȡ0   
        while((x[k]<=n)&&!(Place(k))) x[k]+=1;   
        if(x[k]<=n)   
        {   
            if(k==n)   
            {//���һ����   
                if(ctrl(n)&&(shu<=max))   
                {   
                    ans[0]=shu;   
                    for(int i=1;i<=n;i++)   
                        ans[i]=x[i];                   
                    return true;   
                }   
            }   
            else   
            {   
                k++;   
                x[k]=-1;   
            }   
        }   
        else    
        {   
            k--;//����   
        }   
    }   
    return false;   
}   
   
int Queen::QueensLV(int stopVegas)   
{//�������n���ʺ����˹ά��˹�㷨   
//  RandomNumber rnd;//���������������������,���Ч������   
    int k=1;   
    int count;   
    shu=0;   
    while(k<=stopVegas)   
    {   
        count=0;   
        y[count++]=0;//���ſ���,��0���ǿ��е�   
        for(int i=1;i<=n;i++)   
        {   
            x[k]=i;   
            if(Place(k)) y[count++]=i;   
        }   
        if((x[k++]=y[rnd.Random(count)])>0) shu++;//����Ϊ0   
    }   
    return shu;   
}   
   
bool nQueen(int n)   
{//����ݷ����ϵĽ�n���������˹ά��˹�㷨   
    Queen X;   
    //��ʼ��   
    X.n=n;   
    int *a =new int [n+1];   
    int *b =new int [n+1];   
    int *cc =new int [n+1];   
    int **d;   
    MArray(d,n+1,n+1);   
    for(int i=0;i<=n;i++) a[i]=0;   
    X.x=a;   
    X.y=b;   
    X.r=d;   
    X.ans=cc;   
    X.max=n;   
    int stop=3;//stopΪ0���ǻ��ݷ�   
    int num=0;   
    if(stop>15) stop=n-15;   
    while(1)   
    {   
        num++;//�������   
        while(X.QueensLV(stop)==0);   
        //�㷨�Ļ�����������   
        if(X.ddBacktrack(stop+1))   
        {   
   
            if(X.shu<X.max) X.max=X.shu;   
   
       
        }   
        if(num>30)   
        {   
            cout<<cc[0]<<endl;   
            for(int i=1;i<=n;i++)   
                cout<<cc[i]<<' ';   
            cout<<endl;   
            delete[]a;   
            delete[]b;   
            delete[]cc;   
            DelArray(d,n+1);   
            return true;   
        }   
    }   
   
}   
   
int main()   
{   
    int n;   
    cin>>n;   
    bool b= nQueen(n);   
	system("pause");
	return 0;
}  
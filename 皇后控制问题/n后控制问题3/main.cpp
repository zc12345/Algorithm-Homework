#include   <iostream>   
#include   <cstdlib>   
#include   <ctime>  
using namespace std;
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
   
//2ά������   
template <class T>   
void Make2DArray(T** &x, int rows, int cols)   
{   
        //������ָ��   
        x = new T* [rows];   
        //Ϊÿ�з���ռ�   
        for(int j = 0; j < rows; j++)   
        {   
                x[j] = new T[cols];   
        }   
}   
   
   
template <class T>   
void Delete2DArray(T** &x, int rows)   
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
   
class Queen   
{   
    friend bool nQueen(int);   
    private:   
        bool Place(int k);//���Իʺ�k���ڵ�x[k]�еĺϷ���   
        bool Backtrack(int t);//��n������Ļ��ݷ�   
        bool ddBacktrack(int t);//������   
        int Placenum(int k);//��ʱ����,�����ѷ��ûʺ����   
        int QueensLV(int stopVegas);//�������n���ʺ����˹ά��˹�㷨   
        bool ctrl(int m);//���Իʺ��Ƿ��ѿ�������   
        int n,//�ʺ����   
            *x,*y,*a,**z;//x[k]��ʾ����k�лʺ����ڵ�x[k]��   
                         //y��������¼ÿ�лʺ����λ��   
                         //a��������¼���Ž�ʺ�λ��   
                         //z��������¼�ʺ���Ƶķ���   
        int cmin,c;//cmin��¼���Żʺ������cΪ��ǰ����   
        RandomNumber rnd;//���������������������,���Ч������   
};   
   
bool Queen::Place(int k)   
{//���Իʺ�k���ڵ�x[k]�еĺϷ���,x[k]��x[j]������0ʱ��Ƚ�   
    if(x[k]>0)   
        for(int j=1;j<k;j++)   
            if((x[j]>0)&&((abs(k-j)==abs(x[j]-x[k]))||x[j]==x[k]))   
                return false;   
    return true;   
}   
   
bool Queen::ctrl(int m)   
{//���Իʺ��Ƿ��ѿ�������m*m   
    int i,j,u,v,count=0;   
    for(i=1;i<=m;i++)   
        for(j=1;j<=m;j++) z[i][j]=0;//��ʼ��0   
    for(i=1;i<=m;i++)   
    {   
        if(x[i]>0) //i���лʺ�ʱ   
        {   
            for(j=1;j<=m;j++) {z[i][j]=1;z[j][x[i]]=1;}//i��,x[i]������Ԫ�ض�����   
            for(u=i,v=x[i];u>=1&&v>=1;u--,v--) z[u][v]=1;//(i,x[i])���϶Խ�������Ԫ�ض�����   
            for(u=i,v=x[i];u<=m&&v>=1;u++,v--) z[u][v]=1;//(i,x[i])���¶Խ�������Ԫ�ض�����   
            for(u=i,v=x[i];u>=1&&v<=m;u--,v++) z[u][v]=1;//(i,x[i])���϶Խ�������Ԫ�ض�����   
            for(u=i,v=x[i];u<=m&&v<=m;u++,v++) z[u][v]=1;//(i,x[i])���¶Խ�������Ԫ�ض�����   
        }   
    }   
    for(i=1;i<=m;i++)   
        for(j=1;j<=m;j++) count+=z[i][j];   
    return(count==m*m);   
}   
   
bool Queen::Backtrack(int t)   
{//��n������Ļ��ݷ�,�н����true   
    if(t>n)   
        {//���һ����   
//      for(int i=1;i<=n;i++)   
//          a[i]=x[i];   
//      return true;   
        if(ctrl(n)&&(c<=cmin))   
        {   
            a[0]=c;   
            for(int i=1;i<=n;i++)   
                a[i]=x[i];                 
            return true;   
        }   
        else return false;   
        }   
    else   
        for(int i=0;i<=n;i++)//����ȡ0   
        {   
            x[t]=i;   
            if(i>0) c++;   
            if((c<=cmin)&&Place(t)&&Backtrack(t+1)) return true;//��֦���õĻʺ�����������ֵ   
            if(i>0) c--;   
        }   
    return false;   
}   
   
bool Queen::ddBacktrack(int t)   
{//��������n������Ļ��ݷ�,��Ϊ������,��һ�������true   
    x[t]=-1;   
    int k=t;   
    bool *jc =new bool [n+1];   
    for(int i=1;i<=n;i++)   
        jc[i]=true;            
    while(k>t-1)   
    {   
        x[k]+=1;//����ȡ0   
        while((c<cmin)&&(x[k]<=n)&&!(Place(k))) x[k]+=1;   
        if(x[k]<=n)   
        {   
            if((x[k]>0)&&jc[k]) {c++;jc[k]=false;}   
            if(k==n)   
            {//���һ����   
//              for(int i=1;i<=n;i++)   
//                  a[i]=x[i];   
//              return true;   
                if(ctrl(n)&&(c<=cmin))   
                {   
                    a[0]=c;   
                    for(int i=1;i<=n;i++)   
                        a[i]=x[i];                 
                    return true;   
                }   
                //sum++;   
            }   
            else   
            {   
                k++;   
                x[k]=-1;   
            }   
        }   
        else    
        {   
            if(x[k]>0&&!jc[k]) {c--;jc[k]=true;}   
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
    c=0;   
    while(k<=stopVegas)   
    {   
        count=0;   
        y[count++]=0;//���ſ���,��0���ǿ��е�   
        for(int i=1;i<=n;i++)   
        {   
            x[k]=i;   
            if(Place(k)) y[count++]=i;   
        }   
        if((x[k++]=y[rnd.Random(count)])>0) c++;//����Ϊ0   
    }   
    return c;   
}   
   
bool nQueen(int n)   
{//����ݷ����ϵĽ�n������������˹ά��˹�㷨   
    Queen X;   
    //��ʼ��   
    X.n=n;   
    int *p =new int [n+1];   
    int *q =new int [n+1];   
    int *ans =new int [n+1];   
    int **r;   
    Make2DArray(r,n+1,n+1);   
    for(int i=0;i<=n;i++) p[i]=0;   
    X.x=p;   
    X.y=q;   
    X.z=r;   
    X.a=ans;   
    X.cmin=n;   
    int stop=3;//stopΪ0���ǻ��ݷ�   
    int num=0;   
    int stopnum=10;//�������stopnum�������ͬ�ʺ����������   
    if(stop>15) stop=n-15;   
    if(stop>12) stopnum=2;   
    while(true)   
    {   
        while(X.QueensLV(stop)==0);//�㷨��LV�������   
//      cout<<"c="<<X.c<<"   num="<<num<<endl;   
        if(X.Backtrack(stop+1))//�㷨�Ļ����������֣��ҽ��X. cmin   
        {   
            num++;//�������   
//          cout<<"c="<<X.c<<"   cmin="<<X.cmin<<"   num="<<num<<"   ans=";   
            if(X.c<X.cmin) {X.cmin=X.c;num=0;}//�ҵ�����,�������Ž�,�������¼�   
   
//          for(i=1;i<=n;i++)   
//              cout<<ans[i]<<' ';   
//          cout<<endl;   
   
               
        }   
        if(num>stopnum) //����stopnum�ζ�����ͬ����Ϊ������   
        {   
            cout<<ans[0]<<endl;   
            for(int i=1;i<=n;i++)   
                cout<<ans[i]<<' ';   
            cout<<endl;   
            delete[]p;//�ͷ�����ռ�   
            delete[]q;   
            delete[]ans;   
            Delete2DArray(r,n+1);   
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
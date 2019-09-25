#include <iostream>      
#include <ctime>   
#include <cmath>   
#include <cstdlib>   
using namespace std;
   
//2维数组类   
template <class Type>   
void MArray(Type** &x, int rows, int cols)   
{   
        //创建行指针   
        x = new Type* [rows];   
        //为每行分配空间   
        for(int j = 0; j < rows; j++)   
        {   
                x[j] = new Type[cols];   
        }   
}   
   
   
template <class Type>   
void DelArray(Type** &x, int rows)   
{   
        //释放为每行所分配的空间   
        for(int j = 0; j < rows; j++)   
        {   
                delete[] x[j];   
        }   
        //删除行指针   
        delete[] x;   
        x = NULL;   
}   
   
const unsigned long maxshort=65536L;   
const unsigned long multiplier=1194211693L;   
const unsigned long adder=12345L;   
   
//随机数类   
class RandomNumber   
{   
public:   
    //构造函数，缺省值0表示由系统自动产生种子   
    RandomNumber(unsigned long s=0);   
    //产生0:n-1之间的随机整数   
    unsigned short Random(unsigned long n);   
    //产生[0,1)之间的随机实数   
    double fRandom(void);   
private:   
    //当前种子   
    unsigned long randSeed;   
};   
   
//产生种子   
RandomNumber::RandomNumber(unsigned long s)   
{   
    if(s==0)   
        randSeed=time(0); //用系统时间产生种子   
    else   
        randSeed=s;       //由用户提供种子   
}   
   
//产生0:n-1之间的随机整数   
unsigned short RandomNumber::Random(unsigned long n)   
{   
    randSeed=multiplier*randSeed+adder;   
    return (unsigned short)((randSeed>>16)%n);   
}   
   
//产生[0,1)之间的随机实数   
double RandomNumber::fRandom(void)   
{   
    return Random(maxshort)/double(maxshort);   
}   
   
   
class Queen   
{   
    friend bool nQueen(int);   
    private:   
        bool Place(int k);//测试皇后k置于第x[k]列的合法性   
        bool ddBacktrack(int t);//解n后问题的迭代法   
        int Placed(int k);//计算已放置皇后个数   
        int QueensLV(int stopVegas);//随机放置n个皇后的拉斯维加斯算法   
        bool ctrl(int m);//测试皇后是否已控制棋盘   
        int n,//皇后个数   
            *x,*y,*ans,**r;   
        int max,shu;   
        RandomNumber rnd;//随机数产生器定义在类里,随机效果更好   
};   
   
bool Queen::Place(int k)   
{//测试皇后k置于第x[k]列的合法性   
    if(x[k]>0)   
        for(int j=1;j<k;j++)   
            if((x[j]>0)&&((abs(k-j)==abs(x[j]-x[k]))||x[j]==x[k]))   
                return false;   
    return true;   
}   
   
int Queen::Placed(int k)   
{//计算已放置皇后个数   
    int num=0;   
    for(int j=1;j<=k;j++)   
        if(x[j]>0) num++;   
    return num;   
}   
   
bool Queen::ctrl(int m)   
{//测试皇后是否已控制棋盘m*m   
    int i,j,p,q,count=0;   
    shu=0;   
    for(i=1;i<=m;i++)   
        for(j=1;j<=m;j++) r[i][j]=0;//初始置0   
    for(i=1;i<=m;i++)   
    {   
        if(x[i]>0) //i行有皇后时   
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
{//迭代法解n后问题的回溯法   
    x[t]=-1;   
    int k=t;   
    bool *jc =new bool [n+1];   
    for(int i=1;i<=n;i++)   
        jc[i]=true;            
    while(k>t-1)   
    {   
        x[k]+=1;//可以取0   
        while((x[k]<=n)&&!(Place(k))) x[k]+=1;   
        if(x[k]<=n)   
        {   
            if(k==n)   
            {//输出一个解   
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
            k--;//回溯   
        }   
    }   
    return false;   
}   
   
int Queen::QueensLV(int stopVegas)   
{//随机放置n个皇后的拉斯维加斯算法   
//  RandomNumber rnd;//随机数产生器定义在类里,随机效果更好   
    int k=1;   
    int count;   
    shu=0;   
    while(k<=stopVegas)   
    {   
        count=0;   
        y[count++]=0;//不放可行,即0都是可行的   
        for(int i=1;i<=n;i++)   
        {   
            x[k]=i;   
            if(Place(k)) y[count++]=i;   
        }   
        if((x[k++]=y[rnd.Random(count)])>0) shu++;//可以为0   
    }   
    return shu;   
}   
   
bool nQueen(int n)   
{//与回溯法相结合的解n后问题的拉斯维加斯算法   
    Queen X;   
    //初始化   
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
    int stop=3;//stop为0就是回溯法   
    int num=0;   
    if(stop>15) stop=n-15;   
    while(1)   
    {   
        num++;//计算次数   
        while(X.QueensLV(stop)==0);   
        //算法的回溯搜索部分   
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
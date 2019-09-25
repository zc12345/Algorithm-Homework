#include   <iostream>   
#include   <cstdlib>   
#include   <ctime>  
using namespace std;
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
   
//2维数组类   
template <class T>   
void Make2DArray(T** &x, int rows, int cols)   
{   
        //创建行指针   
        x = new T* [rows];   
        //为每行分配空间   
        for(int j = 0; j < rows; j++)   
        {   
                x[j] = new T[cols];   
        }   
}   
   
   
template <class T>   
void Delete2DArray(T** &x, int rows)   
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
   
class Queen   
{   
    friend bool nQueen(int);   
    private:   
        bool Place(int k);//测试皇后k置于第x[k]列的合法性   
        bool Backtrack(int t);//解n后问题的回溯法   
        bool ddBacktrack(int t);//迭代法   
        int Placenum(int k);//暂时不用,计算已放置皇后个数   
        int QueensLV(int stopVegas);//随机放置n个皇后的拉斯维加斯算法   
        bool ctrl(int m);//测试皇后是否已控制棋盘   
        int n,//皇后个数   
            *x,*y,*a,**z;//x[k]表示：第k行皇后置于第x[k]列   
                         //y是用来记录每行皇后可行位置   
                         //a是用来记录最优解皇后位置   
                         //z是用来记录皇后控制的方格   
        int cmin,c;//cmin记录最优皇后个数，c为当前个数   
        RandomNumber rnd;//随机数产生器定义在类里,随机效果更好   
};   
   
bool Queen::Place(int k)   
{//测试皇后k置于第x[k]列的合法性,x[k]和x[j]都大于0时候比较   
    if(x[k]>0)   
        for(int j=1;j<k;j++)   
            if((x[j]>0)&&((abs(k-j)==abs(x[j]-x[k]))||x[j]==x[k]))   
                return false;   
    return true;   
}   
   
bool Queen::ctrl(int m)   
{//测试皇后是否已控制棋盘m*m   
    int i,j,u,v,count=0;   
    for(i=1;i<=m;i++)   
        for(j=1;j<=m;j++) z[i][j]=0;//初始置0   
    for(i=1;i<=m;i++)   
    {   
        if(x[i]>0) //i行有皇后时   
        {   
            for(j=1;j<=m;j++) {z[i][j]=1;z[j][x[i]]=1;}//i行,x[i]列所有元素都控制   
            for(u=i,v=x[i];u>=1&&v>=1;u--,v--) z[u][v]=1;//(i,x[i])左上对角线所有元素都控制   
            for(u=i,v=x[i];u<=m&&v>=1;u++,v--) z[u][v]=1;//(i,x[i])左下对角线所有元素都控制   
            for(u=i,v=x[i];u>=1&&v<=m;u--,v++) z[u][v]=1;//(i,x[i])右上对角线所有元素都控制   
            for(u=i,v=x[i];u<=m&&v<=m;u++,v++) z[u][v]=1;//(i,x[i])右下对角线所有元素都控制   
        }   
    }   
    for(i=1;i<=m;i++)   
        for(j=1;j<=m;j++) count+=z[i][j];   
    return(count==m*m);   
}   
   
bool Queen::Backtrack(int t)   
{//解n后问题的回溯法,有解输出true   
    if(t>n)   
        {//输出一个解   
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
        for(int i=0;i<=n;i++)//可以取0   
        {   
            x[t]=i;   
            if(i>0) c++;   
            if((c<=cmin)&&Place(t)&&Backtrack(t+1)) return true;//剪枝已置的皇后数大于最优值   
            if(i>0) c--;   
        }   
    return false;   
}   
   
bool Queen::ddBacktrack(int t)   
{//迭代法解n后问题的回溯法,改为布尔型,有一个解输出true   
    x[t]=-1;   
    int k=t;   
    bool *jc =new bool [n+1];   
    for(int i=1;i<=n;i++)   
        jc[i]=true;            
    while(k>t-1)   
    {   
        x[k]+=1;//可以取0   
        while((c<cmin)&&(x[k]<=n)&&!(Place(k))) x[k]+=1;   
        if(x[k]<=n)   
        {   
            if((x[k]>0)&&jc[k]) {c++;jc[k]=false;}   
            if(k==n)   
            {//输出一个解   
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
    c=0;   
    while(k<=stopVegas)   
    {   
        count=0;   
        y[count++]=0;//不放可行,即0都是可行的   
        for(int i=1;i<=n;i++)   
        {   
            x[k]=i;   
            if(Place(k)) y[count++]=i;   
        }   
        if((x[k++]=y[rnd.Random(count)])>0) c++;//可以为0   
    }   
    return c;   
}   
   
bool nQueen(int n)   
{//与回溯法相结合的解n后控制问题的拉斯维加斯算法   
    Queen X;   
    //初始化   
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
    int stop=3;//stop为0就是回溯法   
    int num=0;   
    int stopnum=10;//如果连续stopnum次输出相同皇后数，就输出   
    if(stop>15) stop=n-15;   
    if(stop>12) stopnum=2;   
    while(true)   
    {   
        while(X.QueensLV(stop)==0);//算法的LV随机部分   
//      cout<<"c="<<X.c<<"   num="<<num<<endl;   
        if(X.Backtrack(stop+1))//算法的回溯搜索部分，且解≤X. cmin   
        {   
            num++;//计算次数   
//          cout<<"c="<<X.c<<"   cmin="<<X.cmin<<"   num="<<num<<"   ans=";   
            if(X.c<X.cmin) {X.cmin=X.c;num=0;}//找到更优,更新最优解,次数重新计   
   
//          for(i=1;i<=n;i++)   
//              cout<<ans[i]<<' ';   
//          cout<<endl;   
   
               
        }   
        if(num>stopnum) //连续stopnum次都是相同，认为最优啦   
        {   
            cout<<ans[0]<<endl;   
            for(int i=1;i<=n;i++)   
                cout<<ans[i]<<' ';   
            cout<<endl;   
            delete[]p;//释放数组空间   
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
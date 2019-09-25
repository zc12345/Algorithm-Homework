#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib> 
using namespace std;

const unsigned long maxshort=65536L; 
const unsigned long multiplier=1194211693L;
const unsigned long adder=12345L;
class RandomNumber
{
public:
    RandomNumber(void){};
    unsigned long randSeed;
    RandomNumber(unsigned long s)
    {
        if(s==0)
            randSeed=time(0);
        else
            randSeed=s;  
    }
    unsigned long Random(unsigned long n)
    {
        randSeed=multiplier*randSeed+adder;
        return (unsigned short)((randSeed>>16)%n);
    } 
    double fRandom(void)
    {
        return Random(maxshort)/double(maxshort);
    }
};
template <class T> 
void Make2DArray(T** &x, int rows, int cols)
{
    x = new T* [rows];
    for(int j = 0; j < rows; j++)
    {
        x[j] = new T[cols];
    }
} 
template <class T> 
void Delete2DArray(T** &x, int rows)
{ 
    for(int j = 0; j < rows; j++)
    {
        delete[] x[j];
    }    
    delete[] x;
    x = NULL;
}
class queen
{
    friend bool nqueen(int m);
     
    private:
        queen(void){};
        bool place(int k);
        bool backtrack(int t);
        int queenslv(int stopVegas);
        bool ctrl(int m);   
        int n,*x,*y,*a,**z;
                           
        int cmin,c;
        RandomNumber rnd;
};
bool queen::place(int k)
{
    if(x[k]>0)
        for(int j=1;j<k;j++)
            if((x[j]>0)&&((abs(k-j)==abs(x[j]-x[k]))||x[j]==x[k]))
                return false;
        return true; ;
}
bool queen::ctrl(int m)
{
    int i,j,u,v,count=0;
    for(i=1;i<=m;i++)
        for(j=1;j<=m;j++)
            z[i][j]=0;
    for(i=1;i<=m;i++)
    {
        if(x[i]>0)
        {
            for(j=1;j<=m;j++) {z[i][j]=1;z[j][x[i]]=1;}
            for(u=i,v=x[i];u>=1&&v>=1;u--,v--) z[u][v]=1;
            for(u=i,v=x[i];u<=m&&v>=1;u++,v--) z[u][v]=1;
            for(u=i,v=x[i];u>=1&&v<=m;u--,v++) z[u][v]=1;
            for(u=i,v=x[i];u<=m&&v<=m;u++,v++) z[u][v]=1;
        }
    }
    for(i=1;i<=m;i++)
        for(j=1;j<=m;j++)
            count+=z[i][j];
    return (count==m*m);
}
int queen::queenslv(int stopVegas) 
{
    int k=1;
    int count;
    c=0;
    while(k<=stopVegas)
    {
        count=0;
        y[count++]=0;
        for(int i=1;i<=n;i++)
        {
            x[k]=i;
            if(place(k)) y[count++]=i;
        }
        if((x[k++]=y[rnd.Random(count)])>0) c++;
    }
    return c;
}
bool queen::backtrack(int t)
{
    if(t>n)
    {
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
    {
        for(int i=0;i<=n;i++)
        {
            x[t]=i;
            if(i>0) c++;
            if((c<=cmin)&&place(t)&&backtrack(t+1))
                return true;
            if(i>0) c--;
        }
        return false;
    }
}
bool nqueen(int n)
{
    queen X;
    X.n=n;
    int *p=new int [n+1];
    int *q=new int [n+1];
    int *ans=new int [n+1];
    int **r;
    Make2DArray(r,n+1,n+1);       
    for(int i=0;i<n;i++) p[i]=0;   
    X.x=p;
    X.y=q;
    X.z=r;
    X.a=ans;
    X.cmin=n;   
    int stop=3;
    int num=0,stopnum=100;
    if(stop>15) stop=n-15;
    //if(stop>12) stopnum=2;
    while(true)
    {
        while(X.queenslv(stop)==0);
        if(X.backtrack(stop+1))
        {
            num++;
            if(X.c<X.cmin)
            {
                X.cmin=X.c;
                num=0;
            }
        }
        if(num>stopnum)
        {
            cout<<ans[0]<<endl;
            for(int i=1;i<n;i++)
                cout<<ans[i]<<" ";
            cout<<ans[n]<<endl;
            return true;
        }
    }
    delete []p;
    delete []q;
    delete []ans;
    Delete2DArray(r,n+1);
    return true;
}
int main()
{
    int n;
    cin>>n;
    bool b=nqueen(n);
	system("pause");
    return 0;
}
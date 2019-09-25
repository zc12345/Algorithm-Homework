#include <cstring>
#include <iostream>
using namespace std;

int dir[9][2]={{0,0},{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
int count1;
int dirs,best;
int board[20][20],bestw[20][20];
int m,n,k;
int sx,sy,ex,ey;
bool comp(int x,int y)
{
	if(x>0&&x<=n&&y>0&&y<=m&&board[x][y]==0)
	   return true;
	else return false;
}

void save()
{
	int i,j;
	for(i=1;i<=n;i++)
	   for(j=1;j<=m;j++)
	    bestw[i][j]=board[i][j];
}

void search(int dep,int x,int y,int di)
{
	if(dep==m*n-k&&x==ex&&y==ey&&dirs<=best)
	{
	   if(dirs<best) 
	   {
	    best=dirs;
	    count1=1;
	    save();
	   }
	   else count1++;
	   return;
	}
	if(dep==m*n-k||x==ex&&y==ey||dirs>best) return;
	else
	{
	   for(int i=1;i<=8;i++)
	    if(comp(x+dir[i][0],y+dir[i][1]))
	    {
	     board[x+dir[i][0]][y+dir[i][1]]=dep+1;
	     if(di!=i) dirs++;
	     search(dep+1,x+dir[i][0],y+dir[i][1],i);
	     if(di!=i) dirs--;
	     board[x+dir[i][0]][y+dir[i][1]]=0;
	    }
	}
}

int main()
{
	cin>>n>>m>>k;
	int i,j;
	int c,d;
	memset(board,0,sizeof(board));
	for(i=0;i<k;i++)
	{
	   cin>>c>>d;
	   board[c][d]=-1;
	}
	cin>>sx>>sy;
	cin>>ex>>ey;
	board[sx][sy]=1;
	best=m*n;
	dirs=-1;
	/***********************
	for(i=0;i<n;i++)
	{
	   for(j=0;j<m;j++)
	    cout<<board[i][j]<<" ";
	   cout<<endl;
	}
	***********************/
	search(1,sx,sy,0);
	cout<<best<<endl;
	cout<<count1<<endl;
	for(i=1;i<=n;i++)
	{
	   for(j=1;j<=m;j++)
	    cout<<bestw[i][j]<<" ";
	   cout<<endl;
	}
	system("pause");
	return 0;
}
/**********************************
������������ ����ŷ������Ҷ���Թ�������ŷ������Ҷ��һ��m��n���Թ��У���ͼ��ʾ��ÿһ�������ʾ�Թ��е�һ�����䡣
			��m��n����������һЩ�����Ƿ�յģ��������κ��˽��롣���Թ����κ�λ�þ�����8 ���������δ��յķ��䡣
			����ŷλ���Թ���(p��q)�����У��������ҳ�һ��ͨ������Ҷ���ڵ�(r��s)�����·��
			�ڵִ�����Ҷ֮ǰ���������߱�����δ��յķ����һ�Σ�����Ҫʹ��������Ҷ��ת�����Ϊ���١�
			ÿ�ı�һ��ǰ����������ת��һ�Ρ������һ���㷨��������ŷ�ҳ�����һ����·��

���㷨��ƣ� ���ڸ���������ŷ������Ҷ���Թ�����̼�������ŷͨ������Ҷ����������ת���·��

���������룺���ļ�input.txt�����������ݡ���һ����3��������n��m��k���ֱ��ʾ�Թ��������������ͷ�յķ�������
		   ��������k���У�ÿ��2������������ʾ����յķ������ڵ��кź��кš�����2�У�ÿ��Ҳ��2����������
		   �ֱ��ʾ����ŷ�����ķ���(p��q)������Ҷ�����ķ���(r��s)��

�������: �������������ŷͨ������Ҷ������ת��������ж�������ͬ������ת���·������ļ�output.txt��
		   �ļ��ĵ�һ��������ת��������ļ��ĵ�2   ���ǲ�ͬ������ת���·������������n��ÿ��m��������ʾ�Թ���һ������ת���·��
		   A[i][j]=k��ʾ��k�����﷽��(i,j)��A[i][j]=-1��ʾ����(i,j)�Ƿ�յġ��������ŷ�޷�ͨ������Ҷ�������No Solution!����

			�����ļ�ʾ��
			input.txt
			3 4 2
			1 2
			3 4
			1 1
			2 2

			����ļ�ʾ��
			output.txt
			6
			7
			1	-1	9	8	
			2	10	6	7	
			3	4	5	-1	

***********************************/
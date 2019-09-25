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
★问题描述： 罗密欧与朱丽叶的迷宫。罗密欧与朱丽叶身处一个m×n的迷宫中，如图所示。每一个方格表示迷宫中的一个房间。
			这m×n个房间中有一些房间是封闭的，不允许任何人进入。在迷宫中任何位置均可沿8 个方向进入未封闭的房间。
			罗密欧位于迷宫的(p，q)方格中，他必须找出一条通向朱丽叶所在的(r，s)方格的路。
			在抵达朱丽叶之前，他必须走遍所有未封闭的房间各一次，而且要使到达朱丽叶的转弯次数为最少。
			每改变一次前进方向算作转弯一次。请设计一个算法帮助罗密欧找出这样一条道路。

★算法设计： 对于给定的罗密欧与朱丽叶的迷宫，编程计算罗密欧通向朱丽叶的所有最少转弯道路。

★数据输入：由文件input.txt给出输入数据。第一行有3个正整数n，m，k，分别表示迷宫的行数，列数和封闭的房间数。
		   接下来的k行中，每行2个正整数，表示被封闭的房间所在的行号和列号。最后的2行，每行也有2个正整数，
		   分别表示罗密欧所处的方格(p，q)和朱丽叶所处的方格(r，s)。

★结果输出: 将计算出的罗密欧通向朱丽叶的最少转弯次数和有多少条不同的最少转弯道路输出到文件output.txt。
		   文件的第一行是最少转弯次数。文件的第2   行是不同的最少转弯道路数。接下来的n行每行m个数，表示迷宫的一条最少转弯道路。
		   A[i][j]=k表示第k步到达方格(i,j)；A[i][j]=-1表示方格(i,j)是封闭的。如果罗密欧无法通向朱丽叶则输出“No Solution!”。

			输入文件示例
			input.txt
			3 4 2
			1 2
			3 4
			1 1
			2 2

			输出文件示例
			output.txt
			6
			7
			1	-1	9	8	
			2	10	6	7	
			3	4	5	-1	

***********************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<iostream>
#define MAX 20               //边和顶点的最大数量
using namespace std;

//****************************无向图的建立
typedef struct Graph
{
	int vexnum;          //顶点数
	int arcnum;          //边的数量
	char vexs[MAX];      //顶点信息
	int arcs[MAX][MAX];  //边的信息
}Graph, * myGraph; 
//获取顶点的下标：
int getLocate(myGraph G,char v)
{
	int i;
	for (i = 0; i < G->vexnum; i++)
	{
		if (v == G->vexs[i])
			return i;
	}
	return -1;//没找到顶点
}
//图的创建：
void createGraph(myGraph & G)
{
	G = (Graph*)malloc(sizeof(Graph));
	int i, j, k;
	int vexnum, arcnum;
	char v1, v2;             //边的两个顶点
	printf("请输入顶点的数量：");
	cin >> G->vexnum;
	printf("请输入边的数量：");
	cin >> G->arcnum;
	printf("请依次将顶点数据输入进来\n");
	for (i=0;i<G->vexnum ;i++)
	{
		getchar();
		cin >> G->vexs[i];             //储存顶点信息
	}
	for (i = 0; i < G->vexnum; i++)
	{
		for (j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j] = 9999;        //初始化矩阵 
		}
	}
	scanf_s("请依次将边输入进来:\n");
	int n;
	for (i = 0; i < G->arcnum; i++)
	{
		//getchar( );
		cin >> v1 >> v2>>n;
		            //建立加权无向图
	}
	for (i = 0; i < G->arcnum; i++)
	{
		j = getLocate(G,v1);
		k= getLocate(G, v2);
		G->arcs[j][k] = n;
		G->arcs[k][j] = n;  
	}
}
struct  edge
{
	char head,tail;
	int lowcost;                  
}Edge[MAX];                  //存入每条边的首尾及其权值
void createEdge(myGraph  G)
{
	int k=0,i,j;
	for (i = 0; i < G->vexnum ; i++)
	{
		for (j = i; j < G->vexnum; j++)  //无向图只需要在上三角遍历即可
		{
			if (G->arcs [i][j]!=0&&G->arcs [i][j]!=9999)
			{
				Edge[k].head = G->vexs[i];
				Edge[k].tail = G->vexs[j];
				Edge[k].lowcost = G->arcs[i][j];
				k++;                 //最终k的值为G->arcnum/2
			}
		}
	}
}
void   sort(myGraph  G)
{
	createEdge(G);
	int i, j; char head, tail; int lowcost;
	for (i=1;i<G->arcnum /2;i++)
	{
		if (Edge[i].lowcost < Edge[i - 1].lowcost)
		{
			head = Edge[i].head;
			tail = Edge[i].tail;
			lowcost = Edge[i].lowcost;
			for (j = i - 1; lowcost < Edge[j].lowcost; j--)
			{
				Edge[j + 1].head = head;
				Edge[j + 1].tail = tail;
				Edge[j + 1].lowcost = lowcost;
			}

		}
	}
}
int main()
{
	myGraph G;
	int i,v1,v2,vs1,vs2;
	int Vexset[MAX];

	createGraph(G);
	sort(G);     //选出Edge中的一个最小边
	for (i = 0; i < G->vexnum; i++)  //初始化每个顶点为一个连通分量
			Vexset[i] = i;
	for (i = 0; i < G->arcnum / 2; i++)
	{
		v1 = getLocate(G,Edge[i].head);
		v2 = getLocate(G, Edge[i].tail);
		vs1 = Vexset[v1];
		vs2 = Vexset[v2];
		if (vs1 != vs2)    //说明两者不会构成回路，加到最小生成树
		{
			cout << Edge[i].head << "," << Edge[i].tail << endl;
			for (int j = 0; j < G->vexnum; j++)
				if (Vexset[j] == vs2)
					Vexset[j] = vs1;//将连通分量vs2的改为vs1
		}
	}
	return 0;
}
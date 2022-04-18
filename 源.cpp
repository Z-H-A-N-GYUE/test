#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<iostream>
#define MAX 20               //�ߺͶ�����������
using namespace std;

//****************************����ͼ�Ľ���
typedef struct Graph
{
	int vexnum;          //������
	int arcnum;          //�ߵ�����
	char vexs[MAX];      //������Ϣ
	int arcs[MAX][MAX];  //�ߵ���Ϣ
}Graph, * myGraph; 
//��ȡ������±꣺
int getLocate(myGraph G,char v)
{
	int i;
	for (i = 0; i < G->vexnum; i++)
	{
		if (v == G->vexs[i])
			return i;
	}
	return -1;//û�ҵ�����
}
//ͼ�Ĵ�����
void createGraph(myGraph & G)
{
	G = (Graph*)malloc(sizeof(Graph));
	int i, j, k;
	int vexnum, arcnum;
	char v1, v2;             //�ߵ���������
	printf("�����붥���������");
	cin >> G->vexnum;
	printf("������ߵ�������");
	cin >> G->arcnum;
	printf("�����ν����������������\n");
	for (i=0;i<G->vexnum ;i++)
	{
		getchar();
		cin >> G->vexs[i];             //���涥����Ϣ
	}
	for (i = 0; i < G->vexnum; i++)
	{
		for (j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j] = 9999;        //��ʼ������ 
		}
	}
	scanf_s("�����ν����������:\n");
	int n;
	for (i = 0; i < G->arcnum; i++)
	{
		//getchar( );
		cin >> v1 >> v2>>n;
		            //������Ȩ����ͼ
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
}Edge[MAX];                  //����ÿ���ߵ���β����Ȩֵ
void createEdge(myGraph  G)
{
	int k=0,i,j;
	for (i = 0; i < G->vexnum ; i++)
	{
		for (j = i; j < G->vexnum; j++)  //����ͼֻ��Ҫ�������Ǳ�������
		{
			if (G->arcs [i][j]!=0&&G->arcs [i][j]!=9999)
			{
				Edge[k].head = G->vexs[i];
				Edge[k].tail = G->vexs[j];
				Edge[k].lowcost = G->arcs[i][j];
				k++;                 //����k��ֵΪG->arcnum/2
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
	sort(G);     //ѡ��Edge�е�һ����С��
	for (i = 0; i < G->vexnum; i++)  //��ʼ��ÿ������Ϊһ����ͨ����
			Vexset[i] = i;
	for (i = 0; i < G->arcnum / 2; i++)
	{
		v1 = getLocate(G,Edge[i].head);
		v2 = getLocate(G, Edge[i].tail);
		vs1 = Vexset[v1];
		vs2 = Vexset[v2];
		if (vs1 != vs2)    //˵�����߲��ṹ�ɻ�·���ӵ���С������
		{
			cout << Edge[i].head << "," << Edge[i].tail << endl;
			for (int j = 0; j < G->vexnum; j++)
				if (Vexset[j] == vs2)
					Vexset[j] = vs1;//����ͨ����vs2�ĸ�Ϊvs1
		}
	}
	return 0;
}
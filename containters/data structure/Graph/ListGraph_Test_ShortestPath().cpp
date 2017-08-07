#include<iostream>
#include"ListGraph.hpp"
using namespace std;

int main(){
	const int infinite=1e6; 
	char v[]={'a','b','c','d','e'};
	ListGraph<char> og(sizeof(v)/sizeof(*v),v);//��������ͼ 
	og.add_edge(1,2,2);//a to b
	og.add_edge(1,3,3);//a to c
	og.add_edge(1,4,4);//a to d
	og.add_edge(1,5,5);//a to e
	og.add_edge(2,3,3);//b to c
	og.add_edge(2,4,4);//b to d
	og.add_edge(2,5,2);//b to e
	og.add_edge(3,4,4);//c to d
	og.add_edge(3,5,3);//c to e
	og.add_edge(4,5,3);//d to e
	int vertex = og.get_vertex();
	double dist[vertex+1];
	fill(dist,dist+vertex+1,infinite);
	
	og.ShortestPath(1,dist,infinite);//��a��������������·�� 
	for(int i=1;i<=vertex;++i){
		cout<<"a"<<" to "<<v[i-1]<<": "<<dist[i]<<endl;
	}
	
	return 0;
}

/*
��Ŀ���ݣ�
 ��5������(A,B,C,D,E),����ÿ�����е��������е�ֱ�������֪����������֮��
 ֻ��һ����·������ӳ���A������������е����·�����롣
 
��������
4�����ݣ� ��һ����A��(B,C,D,E)��ֱ����룬�ڶ�����B����C,D,E��
��ֱ����룬����������4����D��E��ֱ����롣

�������
A���е�(B,C,D,E)����̾��롣

��������
2 3 4 5  
3 4 2 
4 3   
3

�������
2 3 4 4

*/

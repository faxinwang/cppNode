#include<iostream>
#include"MatrixGraph.hpp"
using namespace std;

int main(){
	const int Infinity=1e6; 
	char v[]={'a','b','c','d','e'};
	MatrixGraph<char> og(sizeof(v)/sizeof(*v),v,Infinity);//��������ͼ 
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
	double dist[vertex];
	
	og.ShortestPath(1,dist);	//��a��������������·��
	for(int i=0;i<vertex;++i){
		cout<<"a"<<" to "<<v[i]<<": "<<dist[i]<<endl;
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

#ifndef MatrixGraph_hpp
#define MatrixGraph_hpp

#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<set>
#include"../DisJointSet/DisJointSet.hpp"

template<class T>
class MatrixGraph{
	private:
		//�߽��,��С�������㷨ʹ�õ�
		struct EdgeNode{
			int beg,end,weight;
			EdgeNode(int b,int e,int w):beg(b),end(e),weight(w){}
			bool operator<(const EdgeNode& edge)const{
				return weight<=edge.weight;
			}
		};
	private:
		int NumNode,NumEdge;
		const int NoEdge;
		std::vector<T> nodes;
		bool oriented;//true����ͼ,false����ͼ 
		std::vector<std::vector<int> > edge;
	public:
		MatrixGraph(int vSize,T* v,int NoEdgeFlag=-1,bool oriented=false);
		~MatrixGraph(){}
		void add_node(T nd);//���һ������
		bool add_edge(int u,int v,int w=1);//���һ����
		bool del_edge(int u,int v);//ɾ��һ������(�в�����,ֻ��ȥ���˸ö������еı�)
		bool exist_edge(int u,int v);//���Ƿ����
		int get_weight(int u,int v);//��ȡ��Ȩ
		void print_matrix();//��ӡ�ڽӾ���
		int in_degree(int u);//�󶥵�����
		int out_degree(int u);//�󶥵�ĳ���
		int degree(int u);//�󶥵�Ķ�
		bool is_oriented(){return oriented;}
		int get_vertex()const{return NumNode;};
		
		void DFS();//���������������
		void BFS();//���������������
		void TopoSort();//��������
		void ShortestPath(int u,double* dist);//��Դ���·��
		void ShortestPathForAll(std::vector<std::vector<int> >& a);//��Դ���·��
		int min_span_tree_kurskal();//��С������kurskal�㷨
		int min_span_tree_prim();//��С������prim�㷨
	private:
		void visit(int v);//���ʶ���
		void DFS(bool* visited,int v);//�����������
		void BFS(bool* visited,int v);//�����������
		int choose(bool* s,double* dist);//��Դ���·����������
};

//��ӡ���� 
template<class T>
void MatrixGraph<T>::print_matrix() {
	for(int i=0;i<NumNode;++i){
		for(int j=0;j<NumNode;++j)
			printf("%4d ",edge[i][j]);
		printf("\n");
	}
}
//�󶥵�u����� 
template<class T>
int MatrixGraph<T>::in_degree(int u){
	if(u<1 || u>NumNode) return -1;
	--u;
	int d=0;
	for(int i=0;i<NumNode;++i)
		if(edge[i][u] != NoEdge) ++d;
	return d-1;//a[i][i]==0 != NoEdge
}
//�󶥵�u�ĳ���
template<class T>
int MatrixGraph<T>::out_degree(int u){
	if(u<1 || u>NumNode) return -1;
	--u;
	int d=0;
	for(int j=0;j<NumNode;++j)
		if(edge[u][j]!=NoEdge) ++d;
	return d-1;//a[i][i]==0 != NoEdge
}
//�󶥵�u�Ķ�
template<class T>
int MatrixGraph<T>::degree(int u){
	int d = in_degree(u)+out_degree(u);
	return oriented?d:d/2; 
}

//���캯�� 
template<class T>
MatrixGraph<T>::MatrixGraph(int vSize,T* v,int NoEdgeFlag,bool oriented)
:NoEdge(NoEdgeFlag),NumNode(vSize),NumEdge(0),oriented(oriented){
	nodes.reserve(NumNode);
	for(int i=0;i<NumNode;++i)
		nodes.push_back(v[i]);
		
	edge.reserve(NumNode);
	for(int i=0;i<NumNode;++i){
		edge.push_back(std::vector<int>(NumNode));
		std::fill(edge[i].begin(),edge[i].end(),NoEdge);
		edge[i][i] = 0;
	}
}

//���һ���� 
template<class T>
bool MatrixGraph<T>::add_edge(int u,int v,int w){
	--u;--v;
	if(u<0 || u >= NumNode || v < 0 || v >= NumNode ){
		std::cout<<"Node not exist."<<std::endl;
		return false;//out of range
	} 
	if(edge[u][v]!=NoEdge){
		std::cout<<"edge("<<u<<','<<v<<") exist."<<std::endl;
		return false;//�ߴ��� 
	} 
	if(oriented){
		edge[u][v]=w;
	}else{
		edge[u][v]=edge[v][u]=w;
	}
	++NumEdge;
	return true;
}
//ɾ��һ���� 
template<class T>
bool MatrixGraph<T>::del_edge(int u,int v){
	--u;--v;
	if(u<0 || u >= NumNode || v < 0 || v >= NumNode ) return false;//out of range
	if(edge[u][v]==NoEdge) return false;//�߲����� 
	if(oriented){
		edge[u][v]=NoEdge;
	}else{
		edge[u][v]=edge[v][u]=NoEdge;
	}
	--NumEdge;
	return true;
}
//����(u,v)�Ƿ���� 
template<class T>
bool MatrixGraph<T>::exist_edge(int u,int v){
	if(u<0 || u >= NumNode || v < 0 || v >= NumNode ) return false;//out of range
	return edge[u][v]!=NoEdge? true:false;
}
//��ȡ��(u,v)��Ȩֵ 
template<class T>
int MatrixGraph<T>::get_weight(int u,int v){
	if(u<0 || u >= NumNode || v < 0 || v >= NumNode ) return false;//out of range
//	if(edge[u][v]==NoEdge) return 0;
	return edge[u][v];
}
//���һ������ 
template<class T>
void MatrixGraph<T>::add_node(T nd){
	nodes.push_back(nd);
	edge.push_back(std::vector<int>());
	for(int i=0;i<NumNode;++i)
		edge[i].push_back(NoEdge);
	++NumNode;
	for(int i=0;i<NumNode;++i)
		edge[NumNode-1].push_back(NoEdge);
}
//���ʽڵ�u������ 
template<class T>
void MatrixGraph<T>::visit(int u){
	std::cout<<nodes[u]<<' ';
}

//��������������� 
template<class T>
void MatrixGraph<T>::DFS(){
	bool visited[NumNode];
	std::fill(visited,visited+NumNode,false);
	
	for(int i=0;i<NumNode;++i)
		if(!visited[i]){
			DFS(visited,i);
			printf("\n");
		} 
}
//�����������
template<class T>
void MatrixGraph<T>::DFS(bool* visited,int v){
	visited[v]=true;
	visit(v);
	for(int j=0;j<NumNode;++j)
		if(!visited[j] && edge[v][j]!=NoEdge)  DFS(visited,j);
}

//��������������� 
template<class T> 
void MatrixGraph<T>::BFS(){
	 bool visited[NumNode];
	 std::fill(visited,visited+NumNode,false);
	 
	 for(int i=0;i<NumNode;++i)
	 	if(!visited[i]){
	 		BFS(visited,i);
	 		printf("\n");
	 	}
}
//����������� 
template<class T> 
void MatrixGraph<T>::BFS(bool* visited,int u){
	visited[u]=true;
	visit(u);
	std::queue<int> q;
	q.push(u);
	while(!q.empty()){
		u=q.front();
		q.pop();
		//for all vertices j adjacent to u
		for(int j=0;j<NumNode;++j)
			if(!visited[j] && edge[u][j]!=NoEdge){
				visited[j]=true;
				visit(j);
				q.push(j);
			}
	}
}

//�������� 
/*
�㷨˼��: 
1-����������������ȣ��������Ϊ0�Ķ�����ջ
2-ֻҪջ��Ϊ�գ����ظ����д���:
  a.��ջ����i��ջ����ӡ
  b.������i��ÿһ���ڽӵ�k����ȼ�1���������k����ȱ�Ϊ0���򽫶���k��ջ 
*/
template<class T>
void MatrixGraph<T>::TopoSort(){
	using namespace std; 
	if(oriented==false){
		cout<<"����ͼ��������������!"<<endl; 
		return;
	}	 
	stack<int> s;//Ҳ������queue 
	int count=0,cur;
	int indegree[NumNode];
	for(int i=0;i<NumNode;++i){
		indegree[i] = in_degree(i+1);//in_degree()�Ĳ�����ΧΪ[1,NumNode] 
		if(indegree[i] == 0) s.push(i);//�����Ϊ0�Ķ�����ջ 
	}
	while(!s.empty()){
		cur = s.top();
		s.pop();
		++count;
		cout<<nodes[cur]<<' ';
		//����cur������ÿһ��������ȼ�1 
		for(int i=0;i<NumNode;++i){
			if(edge[cur][i] != NoEdge)
				if(--indegree[i] == 0)
					s.push(i);//�����Ϊ0�Ķ�����ջ 
		}
	}
	if(count!=NumNode)
		cout<<"ͼ�д��ڻ�·"<<endl; 
}


/*
�������u��������������·��������dist�� 
���������� dist[i] ��u���ڵ� i ����̾��� 
infinity��һ���ȱ�Ȩ����ܶ��������������������Ȩ��ӵ�ʱ�򲻻ᷢ����� 
*/
template<class T>
int MatrixGraph<T>::choose(bool* s,double *dist){
	int min,i;
	//�ҵ�һ������s�еĶ��㸳��min 
	for(i=0;i<NumNode;++i)
		if(s[i]==false){
			min=i;
			break;
		}
	//��min����Ϊs[i]=false && dist[i] ��С��i 
	for(++i;i<NumNode;++i){
		if(s[i]==false && dist[min] > dist[i])
			min=i;
	}
	return min;
}

template<class T>
void MatrixGraph<T>::ShortestPath(int u,double* dist){
	--u;
	bool s[NumNode];
	for(int i=0;i<NumNode;++i){
		dist[i] = edge[u][i];
		s[i] = false;
	}
	s[u] = true;
	dist[u] = 0;
	
	for(int i=1;i<NumNode;++i){//determine n-1 paths from vertex u
		int v = choose(s,dist);	//choose returns a value v such that:
							//dist[v]=minimum dist[i] where s[i]=false
		s[v] = true;
		//���²���s�еĵ㵽u����̾���
		for(int w=0;w<NumNode; ++w)
			if(!s[w] && dist[v]+edge[v][w] < dist[w])
				dist[w] = dist[v] + edge[v][w];
	}
}

//������������������̾���
//��Դ���·��
template<class T>
void MatrixGraph<T>::ShortestPathForAll(std::vector<std::vector<int> >& a){
	//a[i][j] is the length of the shortest path betweent i and j
	a.reserve(NumNode);
	for(int i=0;i<NumNode;++i)
		a.push_back(std::vector<int>(edge[i].begin(),edge[i].end()));
		
//	printf("copy finished!\n");
	
	for(int k=0;k<NumNode;++k)
		for(int i=0;i<NumNode;++i)
			for(int j=0;j<NumNode;++j)
				if(a[i][k] + a[k][j] < a[i][j])
					a[i][j] = a[i][k] + a[k][j];
}

/*kurskal����³˹�������㷨����С������*/
/*
���Խ�kurskal�㷨��ʽ��������Ϊ����G=(V,E)��һ����Ȩ������ͨͼ��F=(v,e)������
�����е�����������ʼ״̬�£�F �ı߼�Ϊ�գ�v=V. ͼ��n���������n�ζ�����������
�������ɭ�ְ�����n��ֻ��n�ø���������û�бߡ�Ȼ����E��ѡ��һ��Ȩֵ��С�ıߣ�
��������E��ɾ���������F�м��������߲��������·���������ߵ�������������ɭ����
��ͬ������������뵽F�У����������������͹鲢����һ�������ظ��������̣�ֱ��
ѡ����n-1���ߣ���ʱF��ֻʣ��һ�����������������С��������
*/
template<class T>
int MatrixGraph<T>::min_span_tree_kurskal(){
	using namespace std;
	int min_span=0,used_edge=NumNode-1;
	set<EdgeNode> edgeSet;
	//�����б߷���edgeSet
	for(int i=0;i<NumNode;++i)
		for(int j=0;j<NumNode;++j)
			if(edge[i][j] != NoEdge && i!=j)
				edgeSet.insert(EdgeNode(i,j,edge[i][j]));
	DisJointSet djs(NumNode);//�������ཻ��,NumNode��Ԫ��
	//��ʼ�����߽�㣬�����ҳ�NumNode-1����
	typename set<EdgeNode>::iterator pos=edgeSet.begin();
	cout<<"��С������ʹ�õ��ı�:"<<endl;
	while(used_edge){
		int u = djs.Find(pos->beg);
		int v = djs.Find(pos->end);
		if(u!=v){//u��v����ͬһ�����У��������(u,v)�����γɻ�·
			--used_edge;
			djs.Union(u,v);//�ϲ�u��v���ڵ���
			min_span += pos->weight;
			cout<<"( "<<nodes[pos->beg]
				<<" ,"<<nodes[pos->end]
				<<" ,"<<pos->weight
				<<" )"<<endl;
		}
		++pos;
	}
	return min_span;
}

/*
��С������:prim()�㷨
*/
template<class T>
int MatrixGraph<T>::min_span_tree_prim(){
	using namespace std;
	int min_span=0;
	set<int> nodeSet;       //����������еĽ��
	set<EdgeNode> edgeSet;//������б߽��
	//�����б߽�����edgeSet������
	for(int i=0;i<NumNode;++i)
		for(int j=0;j<NumNode;++j)
			if(edge[i][j]!=NoEdge && i!=j)
				edgeSet.insert(EdgeNode(i,j,edge[i][j]));
				
	typename set<EdgeNode>::iterator pos=edgeSet.begin();
	nodeSet.insert(pos->beg);//�������ѡ��һ����������������㼯��
	
	//��edgeSet��ѡ���Ȩ��С��������һ�����㲻���������еı�
	//�������������еĶ�����뵽��������
	//ֱ�����еĶ��㶼����������Ϊֹ
	cout<<"��С�������õ��ı�:"<<endl;
	while(nodeSet.size()<NumNode){
        int u,v;
		for(pos=edgeSet.begin();pos!=edgeSet.end();++pos){
			u = pos->beg;
			v = pos->end;
			//���һ�������������У���һ���㲻����������
	        if(nodeSet.find(u)!=nodeSet.end() && nodeSet.find(v)==nodeSet.end()){
	        	nodeSet.insert(v);
	        	min_span += pos->weight;
	        	cout<<"( "<<nodes[pos->beg]
					<<" ,"<<nodes[pos->end]
					<<" ,"<<pos->weight
					<<" )"<<endl;
				break;
				//ע������� break ����©������Ϊÿ�μ���һ����������������ı���
				//���������ҷ���������Ȩֵ��С�ı�
	        }
		}
	}
	return min_span;
}


#endif

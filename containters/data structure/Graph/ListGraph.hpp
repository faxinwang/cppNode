#ifndef ListGraph_hpp
#define ListGraph_hpp

#include<iostream>
#include<deque>
#include<list>
#include<queue>
#include<stack>
#include<set>
#include"../DisJointSet/DisJointSet.hpp"

/*ͼ:�����ӱ�ʵ��*/
template<class T>
class ListGraph{
	private:
		struct EdgeNode{
			int beg;
			int end;
			double weight;
			EdgeNode(int s,int e,int w):beg(s),end(e),weight(w){}
			//�������ʹ��weight<=e.weight������weight==e.weightʱ��e���ᱻ
			//���뵽�����(��Ϊ����ʹ��!(a<b) && !(b<a)���ж����) 
			bool operator<(const EdgeNode& e)const{return weight<=e.weight;}
			bool operator==(const EdgeNode& e)const{
				return (beg==e.beg && end==e.end && weight==e.weight);
			}
		};
		std::deque<std::list<EdgeNode>* > array;
		std::deque<T> nodes;
		int NumNode;
		bool oriented;
	public:
		ListGraph(int size,T* v,bool orient=false);
		~ListGraph();
		void add_node(T nd);//��ӽ�� 
		void add_edge(int u,int v,double w=0);//��ӱ� 
		void del_edge(int u,int v);//ɾ���� 
		bool exist_edge(int u,int v);//��(u,v)�Ƿ���� 
		double get_weight(int u,int v);//��ȡ��(u,v)��Ȩ 
		int in_degree(int u);//���u����� 
		int out_degree(int u);//���u�ĳ��� 
		int degree(int u);//���u�Ķ� 
		bool is_oriented()const{return oriented;}//�Ƿ�Ϊ����ͼ 
		int get_vertex(){return NumNode;}//��ȡ������� 
		
		void DFS();//����������� 
		void BFS();//����������� 
		double min_span_tree_kurskal();//��С������ kurskal�㷨 
		double min_span_tree_prim();//��С������prim�㷨
		void TopoSort();//�������� 
		//�����v������n-1���ڵ����̾���浽dist��
		void ShortestPath(int v,double *dist,double infinite);
		
	private:
		void visit(int u);//���ʽ������ 
		void DFS(bool *visited,int u);
		void BFS(bool* visited,int u);
		void find_indegree_for_all(int* indegree);//�������н�����ȴ������� 
		int choose(bool *s,double *dist);//ShortestPath()�ĸ������� 
		double dist_vw(int u,int w,double infinite);//ShortestPath()�������� 
};

/* ���캯�� */
//size-���еĽ���� v-���н������, orient-false����true���� 
template<class T>
ListGraph<T>::ListGraph(int size,T* v,bool orient)
:NumNode(size),oriented(orient){
	//�ճ���һ��λ��
	nodes.push_back(T());
	for(int i=0;i<size;++i){
		nodes.push_back(v[i]);
	}
	//�����size+1��Ԫ��,�ճ���һ��λ��
	for(int i=0;i<=size;++i){
		array.push_back(new std::list<EdgeNode>);
	}
}
/*��������*/ 
template<class T>
ListGraph<T>::~ListGraph(){
	for(int i=0;i<=NumNode;++i)
		delete array[i];
}
/*��ӽ��*/
template<class T>
void ListGraph<T>::add_node(T nd){
	++NumNode;
	nodes.push_back(nd);
	array.push_back(new std::list<EdgeNode>);
}
/*��(u,v)�Ƿ����*/ 
template<class T>
bool ListGraph<T>::exist_edge(int u,int v){
	if(u<1 || u>NumNode || v<1 || v>NumNode ){
		std::cout<<"Node not exist."<<std::endl;
		return false;
	}
	//�ڵ�u��������Ѱ����vΪ�յ�ı߽ڵ� 
	typename std::list<EdgeNode>::iterator pos;
	for(pos=array[u]->begin();pos!=array[u]->end();++pos){
		if(v == pos->end) return true;
	}
	return false;
}
/*��ӱ�(u,v,w)*/
template<class T>
void ListGraph<T>::add_edge(int u,int v,double w){
	if(u<1 || u>NumNode || v<1 || v>NumNode ){
		std::cout<<"Node not exist."<<std::endl;
		return;
	}
	//����ߴ��ڣ����ظ���� 
	if(exist_edge(u,v)){
		std::cout<<"Edge("<<u<<','<<v<<") exist."<<std::endl;
		return;
	}
	
	if(oriented){//����ͼ��ֻ����ӱ�edge(u,v,w) 
		array[u]->push_back(EdgeNode(u,v,w));
	}else{//����ͼ,��Ҫ��ӷ����������(u,v,w)��(v,u,w) 
		array[u]->push_back(EdgeNode(u,v,w));
		array[v]->push_back(EdgeNode(v,u,w));
	}
}
/*ɾ����(u,v,w)*/
template<class T>
void ListGraph<T>::del_edge(int u,int v){
	if(u<1 || u>NumNode || v<1 || v>NumNode ){
		std::cout<<"Node not exist."<<std::endl;
		return;
	}
	typename std::list<EdgeNode>::iterator pos;
	//����ͼ��ֻ��ɾ���� u �� v �ı� 
	if(oriented){
		for(pos=array[u]->begin();pos!=array[u]->end();++pos){
			if(v == pos->end)
				array[u]->erase(pos);
		}
	//����ͼ����Ҫɾ�������߽ڵ� 
	}else{
		//ɾ�� u �е��� v Ϊ�յ�ı� 
		for(pos=array[u]->begin();pos!=array[u]->end();++pos){
			if(v == pos->end){
				array[u]->erase(pos);
				break;
			}
		}
		//ɾ�� v �е��� u Ϊ�յ�ı�
		for(pos=array[v]->begin();pos!=array[v]->end();++pos){
			if(u == pos->end){
				array[v]->erase(pos);
				break;
			}
		}
	}
}
/*��ȡ��(u,v)��Ȩ���߲������򷵻�0*/
template<class T>
double ListGraph<T>::get_weight(int u,int v){
	typename std::list<EdgeNode>::iterator pos;
	for(pos=array[u]->begin();pos!=array[u]->end();++pos){
		if(v == pos->end)
			return pos->weight;
	}
	return 0;
}
/*���u����� */ 
template<class T>
int ListGraph<T>::in_degree(int u){
	if(u<1 || u>NumNode){
		std::cout<<"Node not exist."<<std::endl;
		return -1;
	}
	
	//�����б߽����Ѱ����uΪ�յ�ı� 
	int d=0;
	for(int i=1;i<=NumNode;++i){
		typename std::list<EdgeNode>::iterator pos;
		for(pos=array[i]->begin(); pos!=array[i]->end();++pos){
			if(pos->end == u) ++d;
		}
	}
	return d;
}
/*���ĳ���*/ 
template<class T>
int ListGraph<T>::out_degree(int u){
	if(u<1 || u>NumNode ){
		std::cout<<"Node not exist."<<std::endl;
		return -1;
	}
	
	return array[u]->size();
}
/*���Ķ�=���+����*/ 
template<class T>
int ListGraph<T>::degree(int u){
	int d = in_degree(u) + out_degree(u);
	//���������ͼ������������ظ� 
	return oriented? d:d/2;
}
/*���ʽ��u������*/
template<class T>
void ListGraph<T>::visit(int u){
	if(u<1 || u>NumNode) return;
	std::cout<<nodes[u]<<' ';
}

/*���������������*/
template<class T>
void ListGraph<T>::DFS(){
	bool visited[NumNode+1];
	std::fill(visited,visited+NumNode+1,false);
	
	for(int u=1;u<=NumNode;++u){
		if(!visited[u]){
			DFS(visited,u);
			printf("\n");
		}
	}
}
/*�����������*/
template<class T>
void ListGraph<T>::DFS(bool *visited,int u){
	visited[u]=true;
	visit(u);
	typename std::list<EdgeNode>::iterator pos;
	for(pos=array[u]->begin(); pos!=array[u]->end(); ++pos){
		if(!visited[pos->end])
			DFS(visited,pos->end);
	}
}

/*���������������*/
template<class T>
void ListGraph<T>::BFS(){
	bool visited[NumNode+1];
	std::fill(visited,visited+NumNode+1,false);
	
	for(int u=1;u<=NumNode;++u){
		if(!visited[u]){
			BFS(visited,u);
			printf("\n");
		}
	}
}
/*�����������*/
template<class T>
void ListGraph<T>::BFS(bool* visited,int u){
	visited[u]=true;
	visit(u);
	std::queue<int> q;
	q.push(u);
	while(!q.empty()){
		u=q.front();
		q.pop();
		//for all u's adjacent vertex
		typename std::list<EdgeNode>::iterator pos;
		for(pos=array[u]->begin(); pos!=array[u]->end(); ++pos){
			if(!visited[pos->end]){
				visited[pos->end]=true;
				visit(pos->end);
				q.push(pos->end);
			}
		}
	}
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
double ListGraph<T>::min_span_tree_kurskal(){
	using namespace std;
	int used_edge=NumNode-1;//�ܹ���Ҫn-1����(nΪ������) 
	double min_span=0; 
	set<EdgeNode> edgeSet;
	//�����б߽ڵ����set������
	for(int i=1;i<=NumNode;++i){
		typename list<EdgeNode>::iterator pos;
		for(pos=array[i]->begin(); pos!=array[i]->end(); ++pos){
			edgeSet.insert(EdgeNode(pos->beg,pos->end,pos->weight));
		}
	}
//	cout<<"edgeSet.size():"<<edgeSet.size()<<endl;
	DisJointSet djs(NumNode+1);//�����СӦΪNumNode+1,��Ϊelem[NumNode]�ᱻʹ�� 
	typename set<EdgeNode>::iterator pos=edgeSet.begin();
	cout<<"��С������ʹ�õ��ı�:"<<endl;
	while(used_edge){
		int u=djs.Find(pos->beg);
		int v=djs.Find(pos->end);
		if(u!=v){//�����(u,v)�����γɻ�· 
			djs.Union(u,v);
			min_span += pos->weight;
			--used_edge;
			cout<<"( "<<nodes[pos->beg]
					 <<" , "<<nodes[pos->end]
					 <<" , "<<pos->weight
					 <<" )"<<endl; 
		}
		++pos;
	}
	return min_span;
}

/*prim������ķ���㷨����С������*/
/*
prim�㷨���ܱ�kurskal���ܲ�����������kurskal(����ʱ��)��

*/
template<class T>
double ListGraph<T>::min_span_tree_prim(){
	using namespace std;
	double min_span=0;
	set<int> nodeSet;//���������������еĽڵ� 
	set<EdgeNode> edgeSet;
	//�����б߽ڵ����edgeset������
	for(int i=1;i<=NumNode;++i){
		typename list<EdgeNode>::iterator pos;
		for(pos=array[i]->begin(); pos!=array[i]->end(); ++pos){
			edgeSet.insert(EdgeNode(pos->beg,pos->end,pos->weight));
		}
	}
//	cout<<"edgeSet.size():"<<edgeSet.size()<<endl;

	typename set<EdgeNode>::iterator pos = edgeSet.begin();
	//�Ƚ�����һ��������뵽�������㼯�� 
	nodeSet.insert(pos->beg);
	//һֱ������������n���ڵ� 
	while(nodeSet.size()<NumNode){
		int u,v;
		//ÿ�μ���һ�����㵽�������к󣬶�Ҫ��ͷ��ʼ�����еı���Ѱ��Ȩֵ��С
		//����ֻ������һ���������������еıߣ����������������е���һ��������뵽�������� 
		for(pos = edgeSet.begin(); pos != edgeSet.end(); ++pos){
			u = pos->beg;
			v = pos->end;
			//���u����С�������У�����v������С�������У���v���뵽��С�������� 
			if(nodeSet.find(u)!=nodeSet.end()&& nodeSet.find(v)==nodeSet.end()){
				nodeSet.insert(v);//��v���뵽�������� 
				min_span += pos->weight;
				cout<<"( "<<nodes[u]
					<<" , "<<nodes[v]
					<<" , "<<pos->weight
					<<" )"<<endl;
					break;
			//ע������� break ����©������Ϊÿ�μ���һ����������������ı���
			//���������ҷ���������Ȩֵ��С�ı� 
			}
		}
	}
	return min_span;
}

//�������� 
/*
�㷨˼��: 
1-����������������ȣ��������Ϊ0�Ķ�����ջ
2-ֻҪջ��Ϊ�գ����ظ����д���:
  a.��ջ����i��ջ����ӡ
  b.������i��ÿһ���ڽӵ�k����ȼ�1���������k����ȱ�Ϊ0���򽫶���k��ջ 
*/
//�������ж������� 
template<class T>
void ListGraph<T>::find_indegree_for_all(int *indegree){
	using namespace  std;
	typename list<EdgeNode>::iterator pos;
	for(int i=1;i<=NumNode;++i)
		for(pos=array[i]->begin(); pos!=array[i]->end(); ++pos)
			++indegree[pos->end]; 
} 
template<class T>
void ListGraph<T>::TopoSort(){
	using namespace std;
	if(oriented==false){
		cout<<"����ͼ��������������!"<<endl;
		return ;
	}
	stack<int> s;
	int indegree[NumNode+1];
	//indegree�������ȫ����ʼ��Ϊ0 
	for(int i=1;i<=NumNode;++i) indegree[i]=0;
	int cur,count=0;
	//indegree[i]�����i����������
	find_indegree_for_all(indegree);
	for(int i=1;i<=NumNode;++i){
		if(indegree[i]==0)
			s.push(i);//�����Ϊ0�Ľ����ջ 
	}
	typename list<EdgeNode>::iterator pos;
	while(!s.empty()){
		cur = s.top();
		s.pop();
		++count;
		cout<<nodes[cur]<<' ';//����ջ�Ľ����� 
		//��������cur�����Ľ�����ȼ�1 
		for(pos=array[cur]->begin(); pos!=array[cur]->end(); ++pos){
			if(--indegree[pos->end] == 0)
				s.push(pos->end);//����ȱ�Ϊ0�Ľ����ջ 
		}
	}
	if(count!=NumNode){
		cout<<"ͼ�д��ڻ�·!"<<endl; 
	}
}

/*
ShortestPath()�ĸ������� 
Ѱ�Ҳ���s�е���dist[u]��С��u������ 
sΪ�Ѿ���ȷ�����������u����̾���ĵ�ļ��� 
*/ 

template<class T>
int ListGraph<T>::choose(bool* s,double *dist){
	int min=0,i;
	//�ҵ�һ������s�еĶ��㸳��min 
	for(i=1;i<=NumNode;++i)
		if(s[i]==false){
			min=i;
			break;
		}
	//��min����Ϊs[i]=false && dist[i]��С ��i 
	for(++i;i<=NumNode;++i){
		if(s[i]==false && dist[min] > dist[i])
			min=i;
	}
	return min;
}
//ȡ�ö���uw֮��ľ���,���uw֮��û�бߣ��򷵻ز���infinite 
template<class T>
double ListGraph<T>::dist_vw(int v,int w,double infinite){
	typename std::list<EdgeNode>::iterator pos;
	for(pos=array[v]->begin(); pos!=array[v]->end(); ++pos)
		if(pos->end == w)
			return pos->weight;
	return infinite;
}
/*
����infinite��ʾһ�������б�Ȩ����ܶ��������Ҫ��֤�����Ȩ���ʱ��
������� 
*/
template<class T>
void ListGraph<T>::ShortestPath(int u,double *dist,double infinite){
	//dist[j] (1<= j < n) is set to the length of the shortest path from v to j	
	using namespace std;
	bool s[NumNode+1];
	//��s��Ԫ�ض���ʼ��Ϊfalse 
	fill(s,s+NumNode+1,false);
	//��ʼ��dist��Ԫ��Ϊ�������u֮��ı�Ȩ 
	typename list<EdgeNode>::iterator pos;
	for(pos=array[u]->begin();pos!=array[u]->end();++pos)
		dist[pos->end] = pos->weight;
	//��u����s�� 
	s[u] = true;
	dist[u] = 0;
	
	for(int i=1; i < NumNode ; ++i){//determine n-1 paths from vertex v
		int v=choose(s,dist);	//min_dist returns a value v such that:
								//dist[v] = minimum dist[i] where s[i]=false
		s[v] = true;
		//upate the dist between u and w where s[w] = false
		for(int w=1;w<=NumNode; ++w){
			double distvw = dist_vw(v,w,infinite);
			if(!s[w] && dist[v]+ distvw < dist[w])
				dist[w]=dist[v]+ distvw; 
		}
	}
}



#endif 

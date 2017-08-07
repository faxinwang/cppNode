#ifndef BinTree_h
#define BinTree_h

#include<iostream>
#include<cstring>
#include<queue>
#include<stack>

/*
	n �� �ڵ�����ɵĶ���������ĿΪ c(2n,n)/(n+1)
	n �� Ԫ��ͨ����ͬ�Ľ���ջ˳����Եõ���������ҲΪ�������
	n+1 ��������˵ķ�����Ҳ��������� 
	��������:http://blog.csdn.net/jinhongdu/article/details/8065003 
*/ 


int max(int a,int b){
	return a>b?a:b;
}

template<class T>
class BinTree{
	private: 
		struct Node{
			T data;
			Node *left,*right;
			Node(const T& d,Node *l=0,Node* r=0)
			:data(d),left(l),right(r){}
		}*root;
		int n0,n1,n2;	//Ҷ��㣬1�Ƚڵ㣬2�Ƚ������� 
		T noFlag,tmpdata;//��ָ����ţ�����ʱʹ�õ���ʱ�������������������ʱ���� 
	private:
		int depth(Node* r);	//��������� 
		int size(Node* r);//��ڵ����� 
		void count(Node* r);//������Ƚ������� 
		void dlr(Node* r);//������� 
		void ldr(Node* r);//������� 
		void lrd(Node* r);//������� 
		void clear(Node* r);//��ս�� 
		void visit(Node* r);//����һ���ڵ� 
		Node* create();//������
		Node* recover(T* dlr,T* ldr,int len);//�����������ָ��� 
		Node* copy(Node* r);//���ڿ������캯������һ���� 
		bool Equal(const Node* a,const Node* b);//������ 
	public:
		BinTree(T flag):root(0),noFlag(flag){}
		BinTree():root(0){}
		BinTree(const BinTree<T> &t);//�������캯�� 
		~BinTree();
		void createTree();//create()�������� 
		void createTree(const T t);//�������� 
		void createTree(const T* a,int n);//��˳�����齨��
		void createTree(T* dlr,T* ldr,int len);//recover(Node*)�������� 
		void DLR(){dlr(root); }//dlr(Node*)�������� 
		void LDR(){ldr(root); }//ldr(Node*)�������� 
		void LRD(){lrd(root); }//lrd(Node*)��������
		void NoRecInorder();//����������� 
		void levelOrder();//������� 
		int depth(){return depth(root);}//depth()�������� 
		int size();//size(Node* r)�������� 
		void countNodes();//count(Node*)�������� 
		int getN0(){return n0;}//��ȡҶ������� 
		int getN1(){return n1;}//��ȡ1�Ƚ������ 
		int getN2(){return n2;}//��ȡ2�Ƚ������ 
		bool operator==(const BinTree& t);//������ 
		void rotate();//rotate(Node* rt)�������� 
		void rotate(Node* rt);//������ת 
		
	public:
		typedef T* elem_ptr;
		Node* begin(){return root;}
		Node* end(){return 0;}
		class InorderIterator{
			public:
				InorderIterator():curNode(0){}
				Node* operator++();
				Node* operator++(int);//postfix
				void operator=(Node* r){curNode=r;}
				T operator*(){return curNode->data;}
				bool operator!=(const Node* r){return curNode!=r;}
				
			private:
				Node* next();
			private:
				std::stack<Node*> s;
				Node* curNode; 
		};
		
		
};
template<class T>
BinTree<T>::~BinTree(){
	clear(root);
}
template<class T>
void BinTree<T>::clear(Node* r){
	if(r){
		clear(r->left);
		clear(r->right);
		
		delete r;
		r=0;
	}
}
template<class T>
inline void BinTree<T>::visit(Node* r){
	std::cout<< r->data << ' ';
}
template<class T>
int BinTree<T>::depth(Node* r){
	if(r==0) return 0;
	else return max(depth(r->left),depth(r->right))+1;
}
template<class T>
int BinTree<T>::size(){
	return size(root);
}
template<class T>
int BinTree<T>::size(Node* r){
	if(r==0) return 0;
	return 1+size(r->left)+size(r->right);
}



template<class T>
void BinTree<T>::dlr(Node* r){
	if(r){
		visit(r);
		dlr(r->left);
		dlr(r->right);
	}
}

template<class T>
void BinTree<T>::ldr(Node* r){
	if(r){
		ldr(r->left);
		visit(r);
		ldr(r->right);
	}
}
template<class T>
void BinTree<T>::lrd(Node* r){
	if(r){
		lrd(r->left);
		lrd(r->right);
		visit(r);
	}
}

template<class T>
void BinTree<T>::count(Node *r){
	if(r->left && r->right){
	//	cout<<"++n2"<<endl;
		++n2;
		count(r->left);
		count(r->right);
	}else if(r->left){
	//	cout<<"++n1 left"<<endl;
		++n1;
		count(r->left);
	}else if(r->right){
	//	cout<<"++n1 right"<<endl;
		++n1;
		count(r->right);
	}else{
	//	cout<<"++n0"<<endl;
		++n0;
	}
}
template<class T>
void BinTree<T>::countNodes(){
	n0=n1=n2=0;
	count(root);
}

//���������н���
template<class T>
void BinTree<T>::createTree(){
	root=create();
}
template<class T>
typename BinTree<T>::Node* BinTree<T>::create(){
	std::cin>>tmpdata;
	if(tmpdata==noFlag) return 0;
		Node* t=new Node(tmpdata);
	t->left=create();
	t->right=create();
	return t;
}

//������ 
template<class T>
void BinTree<T>::createTree(const T* a,int n){
	std::queue<Node*> q;
	Node* tmp;
	root = new Node(a[0]);
	q.push(root);
	for(int i=0;i<n && !q.empty();){
		tmp=q.front();
		q.pop();
		
		//�����ǰ���ĸ��ڵ�Ϊ�գ���ô��ǰ���Ҳ�ǿսڵ㣬�����Ҹ����ǿյĽ�� 
		if( a[++i] == noFlag )
			while(a[(i-1)/2]==noFlag && i<n) ++i;
		if(a[i] != noFlag && i<n )//i<n
			q.push(tmp->left=new Node(a[i]));
			
		//�����ǰ���ĸ��ڵ�Ϊ�գ���ô��ǰ���Ҳ�ǿսڵ㣬�����Ҹ����ǿյĽ�� 
		if( a[++i] == noFlag )
			while(a[(i-1)/2]==noFlag && i<n) ++i;
		if(a[i] != noFlag && i<n )//i<n 
			q.push(tmp->right=new Node(a[i]));
	}
}

//�����������ָ�һ�Ŷ�����
template<class T> 
void BinTree<T>::createTree(T* dlr,T* ldr,int len){
	root=recover(dlr,ldr,len);
}
template<class T>
typename BinTree<T>::Node* BinTree<T>::recover(T* dlr,T* ldr,int len){
	
	if(len<=0) return 0;
	Node* rt = new Node(dlr[0]);
	T *p,*q;
	int i;
	for(i=0;ldr[i]!=dlr[0]&& i<len;++i);
	p=dlr+1;	//ȷ������������������ָ�� 
	q=ldr;		//ȷ������������������ָ�� 
	rt->left=recover(p,q,i);//�ݹ鹹��������
	
	p=dlr+i+1; 	//ȷ������������������ָ��
	q=ldr+i+1;	//ȷ������������������ָ��
	rt->right=recover(p,q,len-i-1);//�ݹ鹹��������
	return rt;
}

//�������� 
template<class T>
void BinTree<T>::createTree(T flag){
	using namespace std;
	queue<Node*> que;
	Node* tmp;
	T x,ldata,rdata;
	//������������flag���п� 
	std::cout<<"������ڵ�:";
	std::cin>>x;
	root=new Node(x);
	que.push(root);
	while(!que.empty()){
		tmp=que.front();
		que.pop();
		std::cout<<"\n����"<<tmp->data<<"����������("<<flag<<"��ʾ�սڵ�):"; 
		std::cin>>ldata>>rdata;
		if(ldata!=flag)
			que.push(tmp->left=new Node(ldata));
		if(rdata!=flag)
			que.push(tmp->right=new Node(rdata));
	}
	std::cout<<"create completed!"<<std::endl;
}

//copy constructor
template<class T>
BinTree<T>::BinTree(const BinTree<T>& t){
	noFlag=t.noFlag;
	root=copy(t.root);
}
template<class T>
typename BinTree<T>::Node* BinTree<T>::copy(Node* oldTree){
	if(oldTree==0)return 0;
	return new Node(oldTree->data,
					copy(oldTree->left),
					copy(oldTree->right));
} 

// test equalence
template<class T>
bool BinTree<T>::operator==(const BinTree<T>& t){
	return Equal(root,t.root);
}
template<class T>
bool BinTree<T>::Equal(const Node* a,const Node* b){
	if(!a && !b) return true;				//both a and b are 0
	return ( a && b							//both a adn b are non-zero
			&& (a->data == b->data)			//data is the same
			&& Equal(a->left,b->left)		//left subtree equal
			&& Equal(a->right,b->right));	//right subtree equal
}
//�������Ĳ������ 
template<class T>
void BinTree<T>::levelOrder(){
	std::queue<Node*> q;
	Node* curNode=root;
	while(curNode){
		visit(curNode);
		if(curNode->left) q.push(curNode->left);
		if(curNode->right) q.push(curNode->right);
		if(q.empty()) return ;
		curNode=q.front();
		q.pop();
	}
}

//����������� 
template<class T> 
void BinTree<T>::NoRecInorder(){
	//Norecursive inorder traversal using a stack
	std::stack<Node*> s;
	Node* curNode=root;
	while(1){
		while(curNode){
			s.push(curNode);
			curNode=curNode->left;
		}
		if(s.empty())return;
		curNode = s.top();
		s.pop();
		visit(curNode);
		curNode=curNode->right;
	}
}

//������ת�������� 
template<class T> 
void BinTree<T>::rotate(){
	rotate(root);
}
//������ת���� 
template<class T>
void BinTree<T>::rotate(Node* rt){
	if(rt){
		rotate(rt->left);//������ת������ 
		rotate(rt->right);//������ת������
		
		Node* tmp=rt->left;
		rt->left = rt->right;
		rt->right = tmp;
	}
}

//���������������Next()����
template<class T> 
typename BinTree<T>::Node* BinTree<T>::InorderIterator::next(){
	while(curNode){
		s.push(curNode);
		curNode=curNode->left;
	}
	if(s.empty()) return 0;
	curNode=s.top();
	s.pop();
	Node* tmp = curNode; 
	curNode=curNode->right;
	return tmp;
}

template<class T>
typename BinTree<T>::Node* BinTree<T>::InorderIterator::operator++(){
	curNode = next();
	return curNode;
}
template<class T>
typename BinTree<T>::Node* BinTree<T>::InorderIterator::operator++(int){
	Node* tmp=curNode;
	curNode = next();
	return tmp;
}


#endif




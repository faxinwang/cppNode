/*
���������Ҳ��Ϊ��������������������һ�ſ�����������һ��ͬʱ������������������
1 ����������Ϊ�գ����������е�����Ԫ�صļ�ֵ���ȸ��ڵ�ļ�ֵС
2 ����������Ϊ�գ����������е�����Ԫ�صļ�ֵ���ȸ��ڵ�ļ�ֵ��
3 ������������Ҷ����һ�����������
�����������Ҫ����insert,find,delete����
��Щ�������������µ�ʱ�临�Ӷ��� O(logN)
�������£�����������˻�Ϊһ�����Ա�ʱ�临�Ӷ���O(n)
*/


#ifndef BSTree_H
#define BSTree_H

#include<iostream>

template<class T>
class BSTree{
	private:
		struct Node{
			T data;
			Node *left,*right;
			Node(const T& dat=T(),Node* l=0,Node* r=0):
				data(dat),left(l),right(r){}
		}*root,*parent;
	private:
		void insert(Node* &rt,const T& x);
		void remove(Node* rt,const T& x);
		bool find(Node* rt,const T& x)const;
		void clear(Node* &rt);
		void visit(Node* r);//���ʽڵ� 
		void LDR(Node*);//�������
		T getTop();//��ȡ���ڵ������ 
	public:
		BSTree():root(0){}
		~BSTree(){clear();}
		bool find(const T& x)const;
		void insert(const T& x);
		void remove(const T& x);
		void clear();
		bool empty(){return root==0;}
		void LDR(){LDR(root);};
		void operator=(const BSTree<T>& t);
		
		void ThreeWayJoin(const BSTree<T>& small,T mid,const BSTree<T>& big);
		void TwoWayJoin(BSTree<T>& small,BSTree<T>& big);
		void Split(T mid,BSTree<T>& small,BSTree<T>& big);
		
};

template<class T>
void BSTree<T>::operator=(const BSTree<T>& t){
	parent=root=t.root;
}
//��·�ϲ� 
template<class T>
void BSTree<T>::ThreeWayJoin(const BSTree<T>& small,T mid,const BSTree<T>& big){
	clear();
	root=new Node(mid,small.root,big.root);
}
template<class T>
T BSTree<T>::getTop(){
	if(empty()){
		throw "Int getTop : root==0 error!";
	}else{
		return root->data;
	}
}
//��·�ϲ� 
template<class T>
void BSTree<T>::TwoWayJoin(BSTree<T>& small,BSTree<T>& big){
	clear();
	T mid = big.getTop();
	big.remove(mid);
	root = new Node(mid,small.root,big.root);
}
template<class T>
void BSTree<T>::Split(T mid,BSTree<T>& small,BSTree<T>& big){
	//split the binary search tree with respect to key k
	if(!root){
		small.root=big.root=0;
		return;
	}
	//create header nodes for small and big
	Node *sHead=new Node(),
		 *s=sHead,
		 *bHead=new Node(),
		 *b=bHead,
		 *curNode=root;
		 	
	while(curNode){
		if(curNode->data >=mid ){	//add to big
			b->left = curNode;
			b=curNode;
			curNode=curNode->left;
		}else{	//add to small
			s->right=curNode;
			s=curNode;
			curNode=curNode->right;
		}
	}
		
	s->right = b->left = 0;
	
	small.root = sHead->right;
	delete sHead;
	big.root = bHead->left;
	delete bHead;
	
	return ;
}


template<class T>
void BSTree<T>::clear(){
	clear(root);
}

template<class T>
void BSTree<T>::visit(Node* r){
	std::cout<< r->data <<' '; 
}

template<class T>
void BSTree<T>::clear(Node* &rt){
	if(rt->left != 0)
		clear(rt->left);
	if(rt->right != 0)
		clear(rt->right);
	delete rt;
	rt=0;
}

template<class T>
void BSTree<T>::LDR(Node* r){
	if(r){
		LDR(r->left);
		visit(r);
		LDR(r->right);
	}
}

template<class T>
bool BSTree<T>::find(const T& x)const{
	return find(root,x);
}
template<class T>
bool BSTree<T>::find(Node *rt,const T& x)const{
	Node* curNode=root;
	while(curNode){
		if(x < curNode->data)
			curNode=curNode->left;
		else if(x > curNode->data)
			curNode=curNode->right;
		else return true;
	}
	return false;
}

template<class T>
void BSTree<T>::insert(const T& x){
	insert(root,x);
}
template<class T>
void BSTree<T>::insert(Node* &rt,const T& x){
	if(rt==0)
		rt=new Node(x);
	else if(x < rt->data)
		insert(rt->left,x);
	else if(x > rt->data)
		insert(rt->right,x);
}

template<class T>
void BSTree<T>::remove(const T& x){
	remove(root,x);
}
/*
//ɾ���ڵ�ĵݹ��㷨 
template<class T>
void BSTree<T>::remove(Node* rt,const T& x){
	if(rt==0) return ;
	if(rt->data != x)
		parent=rt;
	if(x < rt->data)//Ŀ������������ 
		remove(rt->left,x);
	else if(x > rt->data)//Ŀ������������ 
		remove(rt->right,x);
	else if(rt->left && rt->right){//��ɾ���Ľڵ����������� 
		Node* tmp=rt->right;//��Ŀ�����������Ѱ������ 
		while(tmp->left) tmp=tmp->left;
		rt->data=tmp->data;
		remove(rt->right,tmp->data);//ɾ������ 
	}else if(rt->left){//��ɾ���Ľڵ�ֻ��һ������� 
		if(parent->left==rt)
			parent->left=rt->left;
		if(parent->right==rt)
			parent->right=rt->left;
		delete rt;
	}else if(rt->right){//��ɾ���Ľڵ�ֻ��һ���Ҷ��� 
		if(parent->left==rt)
			parent->left=rt->right;
		if(parent->right==rt)
			parent->right=rt->right;
		delete rt;
	}else{//��ɾ���Ľڵ���Ҷ�ڵ㣬ֱ��ɾ�� 
		if(parent->left==rt)
			parent->left=0;
		else
			parent->right=0; 
		delete rt;
	}
}
*/

//ɾ���ڵ�ķǵݹ��㷨 
template<class T>
void BSTree<T>::remove(Node* curNode,const T& x){
	Node* p=curNode;
	 
	//����ɾ�ڵ㲻�ǵ�һ���ڵ㣬pָ��ɾ���ڵ����һ���ڵ� 
	while(curNode && curNode->data != x){
		p=curNode;
		curNode=(x < curNode->data)?curNode->left:curNode->right;
	}
	if(curNode==0) return;//��ɾ��Ԫ�ز����� 
	if(curNode->left && curNode->right){		//��ɾ�ڵ����������� 
		Node* tmp=curNode->right;
		while(tmp->left){//�������� 
			p=tmp;
			tmp=tmp->left;
		}	
		curNode->data=tmp->data;
		if(tmp->right){//������������������һ�ڵ�ָ�������� 
			p->left=tmp->right;
			delete tmp;//ɾ������ 
		}else{//������Ҷ�ڵ㣬ֱ��ɾ�� 
			p->left=0;
			delete tmp;
		}
	}else if(curNode->left){//��ɾ�ڵ�ֻ�������� 
		if(p->left==curNode)
			p->left=curNode->left;
		else
			p->right=curNode->left;
		delete curNode; 
	}else if(curNode->right){//��ɾ�ڵ�ֻ�������� 
		if(p->left==curNode)
			p->left=curNode->right;
		else
			p->right=curNode->right;
		delete curNode;
	}else{//��ɾ�ڵ���Ҷ�ڵ� 
		if(p->left==curNode)
			p->left=0;
		else
			p->right=0;
		delete curNode;
	} 
}





#endif 

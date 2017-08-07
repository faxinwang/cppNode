#ifndef DisJointSet_h
#define DisJointSet_h

class DisJointSet{
	private:
		int size;
		int *parent;
	public:
		DisJointSet(int n);
		~DisJointSet(){delete []parent;}
		bool Union(int root1,int root2);
		int Find(int x);
};

DisJointSet::DisJointSet(int n):size(n){
	parent = new int[size];
	for(int i=0;i<size;++i)
		parent[i]=-1;
}

int DisJointSet::Find(int x){
	if(parent[x]<0) return x;
	return parent[x]=Find(parent[x]);
	/*
	//�ǵݹ�汾
	for(int p=x; parent[p]>=0; p=parent[p]);
	while(i!=p){
		int s=parent[i];
		parent[i]=p;
		i=s;
	}
	return p;
	*/
}


bool DisJointSet::Union(int root1,int root2){
	if(root1 == root2) return false;
	if(parent[root1]<parent[root2]){//root1�Ľڵ����϶�,��root1��Ϊ���ڵ� 
		parent[root1]+=parent[root2];//����root1�еĽڵ��� 
		parent[root2]=root1;
	}else{
		parent[root2]+=parent[root1];
		parent[root1]=root2;
	}
	return true;
}


#endif 

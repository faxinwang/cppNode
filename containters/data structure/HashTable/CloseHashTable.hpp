#ifndef openHashTable_h
#define openHashTable_h 

#include<iostream>

template<class T>
class CloseHashTable{
	private:
		struct Node{
			T data;
			int state;//0--empty  1--active  2--deleted
			Node(){state=0;}
		};
		Node* array;
		int size;
		int deleted;
	private:
		void rehash();
		int (*key)(const T& x);
		static int defaultKey(const int &k){return k;}
		int lagerPrime(int n);
	public:
		CloseHashTable(int sz=101,int (*f)(const T& x) = defaultKey );
		~CloseHashTable(){delete[] array;}
		bool find(const T& x)const;
		bool insert(const T& x);
		bool remove(const T& x);
};

//��size��ֵ��Ϊ�ȸ���������ĵ�һ�������ǱȽϺõ����� 
template<class T>
CloseHashTable<T>::CloseHashTable(int sz,int (*f)(const T& x) ){
	size = lagerPrime(sz);
// 	size = sz;
	std::cout<<"size: "<<size<<std::endl;
	key = f;
	deleted = 0;
	array = new Node[size];
}

template<class T>
void CloseHashTable<T>::rehash(){
	std::cout<<"rehashing..."<<std::endl;
	Node *old=array;
	array = new Node[size];
	for(int i=0;i<size;++i){
		if(old[i].state==1)
			insert(old[i].data);
	}
	delete[] old;
	std::cout<<"rehash done!"<<std::endl;
}

template<class T>
bool CloseHashTable<T>::find(const T& x)const{
	int initPos,pos;
	initPos = pos = key(x) % size;
	do{
		if(array[pos].state==0) return false;
		if(array[pos].state==1 && array[pos].data==x) return true;
		pos=(pos+1)%size;
	}while(pos!=initPos);
	return false;//����û�и�Ԫ�� 
}

template<class T>
bool CloseHashTable<T>::insert(const T& x){
	int initPos,pos;
	initPos = pos = key(x) % size;
	if(array[pos].state ==1 ){
		std::cout<<"key crash: "<<x<<",key = "<<pos<<std::endl;
	}
	do{
		if(array[pos].state != 1){
			array[pos].data = x;
			array[pos].state = 1;
			return true;
		}
		if(array[pos].state == 1 && array[pos].data==x)
			return false;//��Ԫ���Ѿ����� 
		pos=(pos+1)%size;
	}while(pos!=initPos);
	return false;//û��λ�ÿɲ��� 
}

template<class T>
bool CloseHashTable<T>::remove(const T& x){
	int initPos,pos;
	initPos = pos = key(x) % size ;
	do{
		if(array[pos].state==0) return false;//����û�и�Ԫ��
		if(array[pos].state==1 && array[pos].data==x) {
			array[pos].state=2;
			if(++deleted == size/3)
				rehash();//��ɾԪ�شﵽ1/3����,����ɢ��; 
			return true;
		}
		pos = ( pos + 1 ) % size;
	}while(pos!=initPos);
	return false;//����û�и�Ԫ�� 
}

template<class T>
int CloseHashTable<T>::lagerPrime(int n){
	int i,j;
	for(i=n+1;;++i){
		for(j=2; i % j ; ++j);
		if( j == i) return i;
	}
}


#endif

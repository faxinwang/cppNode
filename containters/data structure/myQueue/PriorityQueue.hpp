#ifndef PriorityQueue_h
#define PriorityQueue_h

template<class T>
class PriorityQueue{
	private:
		int currSize;
		int capacity;
		T* elem;
	private:
		void doubleSpace();
		void buildHeap();
		void percolateDown(int hole);//������͸ 
	public:
		PriorityQueue(int cap=100):capacity(cap),currSize(0){
			elem=new T[capacity];
		}
		PriorityQueue(const T* dat,int size);
		~PriorityQueue(){delete []elem;}
		
		bool empty(){return !currSize;}
		void enQueue(const T& x);
		T deQueue();
		T getHead()const{return elem[1];}
};

template<class T>
void PriorityQueue<T>::enQueue(const T& x){
	if(currSize==capacity) doubleSpace();
	//���Ϲ���
	int hole=++currSize;
	for(;hole>1 && x < elem[hole/2];hole/=2){
		elem[hole]=elem[hole/2];
	}
	elem[hole]=x;
}
template<class T>
T PriorityQueue<T>::deQueue(){
	T data=elem[1];//elem[1]Ϊ��һ��Ԫ�أ�elem[0]δʹ�� 
	elem[1]=elem[currSize--];
	percolateDown(1);//����Ϊ�սڵ��λ��
	return data; 
}
template<class T>
void PriorityQueue<T>::percolateDown(int hole){
	int child;
	T tmp=elem[hole];
	for(;hole*2<=currSize;hole=child){
		child=hole*2;
		if(child+1 <= currSize && elem[child] > elem[child+1])
			++child;//ʹchildָ���ӽڵ��н�С��һ��
		if(elem[child]<tmp)
			elem[hole]=elem[child];
		else
			break;
	}
	elem[hole]=tmp;
}
template<class T>
void PriorityQueue<T>::buildHeap(){
	//�ӵ�һ����Ҷ�ڵ㿪ʼ����Ԫ�أ������ѵ������� 
	for(int i=currSize/2;i>0;--i){
		percolateDown(i);
	}
}
template<class T>
PriorityQueue<T>::PriorityQueue(const T* dat,int size):capacity(size*2),currSize(size){
	elem=new T[capacity];
	for(int i=0;i<size;++i)
		elem[i]=dat[i];
	buildHeap();
}
template<class T>
void PriorityQueue<T> ::doubleSpace(){
	capacity*=2;
	T* tmp=new T[capacity];
	for(int i=0;i<currSize;++i)
		tmp[i]=elem[i];
	delete elem;
	elem=tmp;
}
#endif

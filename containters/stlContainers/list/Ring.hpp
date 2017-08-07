#ifndef Ring_h
#define Ring_h

#include<iterator>
#include<list>



template<class T>
class Ring:public std::list<T>{
	std::list<T> lst;
	public:
		//declaration necessary so the following 'friend' statment
		//sees this 'iterator' instead of std::iterator
		class iterator;
		friend class iterator; 
		class iterator:public std::iterator<std::bidirectional_iterator_tag,T,ptrdiff_t>
		{
				typedef typename std::list<T>::iterator It;
				It it;
				std::list<T> *ring;
			public:
				iterator(){}
				iterator(std::list<T> &lst,It it):ring(&lst),it(it){}
				bool operator==(const iterator& x)const{
					return it==x.it;
				}
				bool operator!=(const iterator& x)const{
					return !(*this==x);
				}
				typename std::list<T>::reference operator*()const{
					return *it;
				}
				iterator& operator++(){
					++it;
					if(it==ring->end())
						it=ring->begin();
					return *this;
				}
				//postfix
				iterator& operator++(int){
					iterator tmp=*this;
					++*this;
					return tmp;
				}
				iterator& operator--(){
					if(it==ring->begin())
						it=ring->end();
					--it;
					return *this;
				}
				//postfix
				iterator& operator--(int){
					iterator tmp=*this;
					--*this;
					return tmp;
				}
				iterator insert(const T& x){
					return iterator(*ring,ring->insert(it,x));
				}
				iterator erase(){
					return iterator(*ring,ring->erase(it));
				}
		};
		void push_back(const T& x){ lst.push_back(x); }
		iterator begin(){ return iterator(lst,lst.begin()); }
		int size(){ return lst.size(); }
};
/*
	���Կ���������������붼����Ե��������еġ����Ring iterator����֪��
	���ѭ������ʵ�̵㣬�������������һ��ָ����Ϊ��"˫��"Ring��������ã�
	�Ӷ�֪��ʲôʱ��ô�һ��������һ�ˡ�
	��Ҫע����ǣ�ΪRing���õ½ӿ��൱���ޣ��ر��ǣ�����û��end()��������Ϊ
	һ���������������ѭ����״̬�������ζ�Ų������κ���Ҫ��end()Ϊ�������κ�
	STL�㷨��ʹ��Ring�� 
*/

#endif

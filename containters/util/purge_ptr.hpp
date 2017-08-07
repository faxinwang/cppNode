//Delete pointers in an STL sequence container.
#ifndef Purge_ptr_hpp
#define Perge_prt_hpp

#include<algorithm>

template<class Seq>
void purge_ptr(Seq& c){
	//�˴�typename�Ǳ���ģ���ΪSeq��һ��ģ���������iteraotr��Ƕ����Seq�е�
	//ĳ�ֶ���,��Ҫ��typename�ؼ��������߱�������������һ������ 
	typename Seq::iterator it;
	for(it=c.begin();it!=c.end();++it){
		delete *it;
		*it=0;
	}
}

//Iteraotr version
template<class Iter>
void purge_ptr(Iter beg,Iter end){
	for(;beg!=end;++beg){
		delete *beg;
		*beg=0;
	}
}


#endif

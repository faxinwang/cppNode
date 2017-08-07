#ifndef isPrime_h
#define isPrime_h

#include<cmath>
#include<cstdlib>
#include<ctime>
/*
	�����������ж������Ķ��� 
	1.���p������������0<x<p����ô pow(x,p-1) % p == 1 �����.
	2.���p������������0<x<p����ô pow(x,2) % p == 1 �������Ψһ����
		�ĸ��� x=1 �� x=p-1. 
	��� p û��ͨ������������������һ����֤��P�������������x�����ѡ��ģ�
	��Ȼ��1/4�ĸ��ʻ��󽫺�����Ϊ������������ܶԲ�ͬ��x�������β��ԣ��������ѡ��
	5 �� x ,��ʧ��ĸ��ʽ�Ϊpow(0.25,5)���Ѿ����Ժ��ԡ� 
*/

template<class Num>
class  primeChecker{
	private:
		const int Trials;
	private:
		bool check(int x,int i,Num p);
	public:
		primeChecker(int trial=5):Trials(trial){}
		bool isPrime(Num p);
};

//�ж�p�Ƿ����������������� 
template<class Num>
bool primeChecker<Num>::check(int a,int i,Num p){
	if(i==0) return 1;
	int x =check(a,i/2,p);
	if(x==0) return 0;
	
	int y=(x*x)%p;
	if(y==1 && x!=1 && x!=p-1) return 0;
	if(i%2) y=(a*y)%p;
	return y;
}

template<class Num>
bool primeChecker<Num>::isPrime(Num n){
	srand(time(0));
	for(int i=0;i<Trials;++i)
		if(check(rand()%(n-1)+1,n-1,n)!=1)
			return false;
	return true;//��ζ�����,���ȷ��nΪ���� 
}


#endif 

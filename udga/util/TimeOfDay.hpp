#ifndef TimeOfDay_H
#define TimeOfDay_H

#include<iostream>
#include<iomanip>

template<int base>//����Ϊbase���� 
class Number{
	int n;//��ŵ�ǰ��ֵ 
	public:
		Number(int i=0):n(i){}// i����С��base 
		int advance(int k);//��ǰֵ����k����λ 
		int getValue(){return n;}
};
template<int base>
int Number<base>::advance(int k){
	int s=0;
	n+=k;
	while(n>=base){
		n -= base;
		++s;
	}
	
	return s;
}

class TimeOfDay{
		Number<24> hours;//Сʱ��0-23�� 
		Number<60> minutes;
		Number<60> seconds;
		Number<1000> milliseconds;//���루0 - 999�� 
	public:
		TimeOfDay(int h=0,int m=0,int s=0,int mi=0):hours(h),
			minutes(m),seconds(s),milliseconds(mi){}
		void advanceMillis(int k){
			advanceSecond(milliseconds.advance(k));
		}
		void advanceSecond(int k){
			advanceMinute(seconds.advance(k));
		}
		void advanceMinute(int k){
			advanceHour(minutes.advance(k));
		}
		void advanceHour(int k){
			hours.advance(k);
		}
		//��"ʱ:��:��.����" �ĸ�ʽ��ʾʱ�� 
		void show(){ 
			using namespace std;
			char ch=cout.fill('0');//��ȡ��ǰ����ַ� 
			cout<<setw(2)<<hours.getValue()<<":"
				<<setw(2)<<minutes.getValue()<<":"
				<<setw(2)<<seconds.getValue()<<"."
				<<setw(3)<<milliseconds.getValue()<<endl;
			cout.fill(ch);//��ԭ����ַ� 
		}
};
#endif

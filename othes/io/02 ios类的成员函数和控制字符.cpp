#include<iostream>
using namespace std;

/*

enum{
	skipws	//���������еĿհף���������
	left	//��������
	right 	//�Ҷ������
	internal//�ڷ���λ�ͻ�ָʾ���������ַ����������
	dec		//ʮ�������
	oct		//�˽������
	hex		//ʮ���������
	showbase//��ʾ��ָʾ��,������������
	showpoint//��ʾС����,�������
	showpos	 //������ǰ��ʾ'+' �ţ��������
	scientific //�ÿ�ѧ��������ʾ������,�������
	fixed	//�ö�����ʽ��ʾ������
	unitbuf	//���������������ˢ�������
	stdio	//�����������ˢ��stdout stderr��������� 
};		

����״̬��־:setf(ios::״̬��ʶ1|ios::״̬��ʶ2|...); 
���״̬��ʶ��:unsetf(ios::״̬��־); 
*/

int main2(){
	cout<<"cout.width()="<<cout.width()<<endl;
	cout<<"cout.fill()="<<cout.fill()<<endl;
	cout<<"cout.precision()="<<cout.precision()<<endl;
	cout<<123<<"	"<<123.456<<endl;
	cout<<"----------------------------------\n"; 
	cout.width(10);
	cout.precision(3);
	cout.fill('*');
	cout<<123<<"	"<<123.4567<<endl;
	cout<<"width()="<<cout.width()<<endl;
	cout<<"precision()="<<cout.precision()<<endl;
	cout<<"---------------------------------------\n";
	cout.width(10);
	cout.fill('#');
	cout<<123<<"	"<<123.456789<<endl;
	cout.setf(ios::right|ios::showpos);
	cout<<123<<"	"<<123.456789<<endl;
	
	return 0;
}



#include <iostream>
using namespace std;
/*
	int get() �����г�ȡ�����ַ�������
 	istream& get(char*,int,char) �����г�ȡ�ַ�ֱ����ֹ��(Ĭ��Ϊ'\n')���ȡ�ַ����ﵽ�ڶ�������ָ���ĸ�����
	�ﵽ�ļ�β������洢�ڵ�һ������ָ�����ַ������
	istream& get(char&) �����г�ȡ�����ַ����������ñ����С� 
	istream& get(streambuf&, char)������ȡ���ַ�����streambuf����ֱ����ֹ�����ļ�β�� 
	istream& getline(char*,int,char) �����г�ȡ�ַ�����ֹ��(Ĭ��Ϊ'\n'),���ȡ�ַ����ﵽ�������������ļ�β��
	���������ֹ����������г�ȡ��ֹ������ֻ�ǽ��������� 
*/
int main1(int argc, char *argv[]) {
	char str1[80],str2[80],ch;
	cout<<"plesse input a char: ";
	cout<<cin.get()<<endl;
	cout<<"please input a char: ";
	cin.get(ch);
	
	cout<<ch<<endl;
	
	cout<<"please input s string: ";
	for(int i=0;i<80;i++){
		cin.get(str1[i]);
		if(str1[i]=='\n'){
			str1[i]=0;
			break;
		}
	}
	cout<<str1<<endl;
	cout<<"please input a string: ";
	cin.get(str2,80);
	cout<<str2<<endl;
	cout<<"please input a string"<<endl; 
	cin.getline(str1,80);
	cin.getline(str2,80);
	cout<<"str1: "<<str1<<endl;
	cout<<"str2: "<<str2<<endl;
	
	return 0;
}

#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<ctype.h>
#include<iomanip>
using namespace std;
/*
	��1��
	������ļ��ж���һƬ���ģ�ͳ������26��Ӣ����ĸ���ֵô�����
	�ֱ������ִ�Сд�� �����ִ�Сд�����
	---����������Ϊ26������upper��lower�ֱ�ͳ�ƴ�Сд����ĸ������
	�����ִ�Сд�Ľ��Ϊupper+lower. 
*/

const int line = 5;
int main(){
	vector<int> upper(26,0),lower(26,0),temp(26,0);
	ofstream ofile;
	ofile.open("test.txt");
	char str[80];
	for(int i=1;i<=line;i++){
		cout<<"�����"<<i<<"��:" ;
		cin.getline(str,80);
		ofile<<str;
	}
	ofile.close();
	
	ifstream ifile("test.txt");
	char c;
	while((c=ifile.get())!=EOF) {
		if(islower(c)) lower[c-'a']++;
		if(isupper(c)) upper[c-'A']++;
	}
	ifile.close();
	
	for(char ch='A';ch<='Z';ch++) cout<<"  "<<ch; cout<<endl;
	for(int i=0;i<26;i++) cout<<setw(3)<<upper[i]; cout<<endl;
	puts("");
	
	for(char ch='a';ch<='z';ch++) cout<<"  "<<ch; cout<<endl;
	for(int i=0;i<26;i++) cout<<setw(3)<<lower[i]; cout<<endl;
	puts("");

	for(char ch='A';ch<='Z';ch++) cout<<ch<<char(ch+32)<<" "; cout<<endl;
	for(int i=0;i<26;i++) cout<<setw(3)<<lower[i]+upper[i]; cout<<endl;
	puts("**************** 1 *****************************************");
	
	return 0;
}

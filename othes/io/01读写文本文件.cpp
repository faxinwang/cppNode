#include<fstream>
#include<iostream>
using namespace std;

int main1(){
	ofstream fout("test.txt");
	if(!fout){
		cout<<"���ļ�ʧ�ܣ�\n"; 
		return 1;
	}
	fout<<"helloworld!"<<endl; 
	fout<<10<<endl;
	fout<<hex<<10<<endl;
	fout.close();
	
	int i;
	char ch,str[20];
	ifstream fin("test.txt");
	if(!fin){
		cout<<"���ļ�ʧ��!"<<endl; 
		return 1;
	}
	fin>>str>>i>>ch;
	cout<<str<<endl
		<<i<<endl
		<<ch<<endl;
	fin.close();
	return 0;
}

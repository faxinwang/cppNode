#include<iostream>
#include<string>
using namespace std;

/* ͨ������newString=replace_all(str,substr,newsubstr) �õ�str�е�substrȫ����
newsubstr�滻���´���ԭstr�����ı�*/

string replace_all(string str,string substr,string newsubstr){
	string newStr(str);
	int n=substr.length();
	int pos=0;
	while((pos=newStr.find(substr,pos))!=string::npos)
		newStr.replace(pos,n,newsubstr);
	return newStr;
}



int main(){
	string str("I love you,but you love him!");
	cout<<replace_all(str,"love","LOVE")<<endl;
	
	
	return 0;
}

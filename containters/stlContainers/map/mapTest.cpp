#pragma warning(disable:123)
#include<iostream>
#include<map>
#include<string>
#include<iomanip>

/*	
	<algorighm>ͷ�ļ����й���set����ѧ����
	include()	���һ�����򼯺�����һ�����򼯺ϵ��Ӽ�������true
	set_union()	�����������򼯺ϵĲ���
	set_intersection()�����������򼯺ϵĽ���
	set_difference() �����������򼯺ϵĲ 

*/

using namespace std;
void readitem(map<string, int>&m);
int main(){
	map<string,int> mp;
	readitem(mp);
	int total=0;
	map<string,int>::iterator it;
	cout<<"ͳ�ƽ��:"<<endl;
	for(it=mp.begin();it!=mp.end();it++){
		total+=(*it).second;
		cout<<setw(12)<<(*it).first<<"\t"<<it->second<<endl;
	}
	cout<<"----------------total:"<<total<<endl;
	mp.erase(mp.begin());
	total=0;
	cout<<"after mp.erase(mp.begin()):\n";
	for(it=mp.begin();it!=mp.end();it++){
		total+=(*it).second;
		cout<<setw(12)<<(*it).first<<"\t"<<it->second<<endl;
	}
	cout<<"----------------total:"<<total<<endl;
	
	return 0;
}

void readitem(map<string,int>&mp){
	string word;
	int val;
	cout<<"�������ݣ�\n�ľ���		����\n";
	while(cin>>word){
		cin>>val;
		mp[word]+=val;
	}
}

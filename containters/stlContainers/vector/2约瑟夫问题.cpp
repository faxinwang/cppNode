#include<iostream>
#include<vector>
using namespace std;
/*
��n���ˣ���Ŵ�1��n��Χ��һȦ���ӵ�s���˿�ʼ��1����,����m���˳��֣����Ŵ���һ���˿�ʼ����,ֱ�������˶�����
���е��˵���ų�Ϊһ��josephu���� 

*/

template<typename T>
void myjosephu(int s,int m,vector<T> &v1,vector<T> &v2)
{
	vector<T>::iterator it1=v1.begin(),it2=v2.begin();
	for(int i=1;i<s;i++)
		if(it1==v1.end()) it1=v1.begin();
	while(!v1.empty()){
		for(int i=1;i<m;i++)		//ģ�ⱨ�� 
			if(++it1==v1.end())
				it1=v1.begin();
		v2.insert(it2++,*it1);
		v1.erase(it1);
		//��������Ϊ���һ��������һ�����������ǵ�һ���� 
		if(it1==v1.end()) it1=v1.begin();
	}
}


int main(){
	vector<int> L,M;
	int n,s,m,val;
	cout<<"����������:"<<endl; cin>>n;
	L.reserve(n);
	M.reserve(n);
	cout<<"����"<<n<<"��Ԫ�أ��ÿո����"<<endl;
	for(int i=0;i<n;i++){
		cin>>val;
		L.push_back(val);
	} 
	cout<<"���뱨������ʼλ�úͱ���ֵs,m:"<<endl; cin>>s>>m;
	myjosephu(s,m,L,M);
	cout<<"\n����˳��\n";
	for(vector<int>::iterator it=M.begin();it!= M.end();it++)
		cout<<*it<<" ";
	
	
	return 0;
}



#include<iostream>
#include<vector>
using namespace std;

/*
����n�������������Ƿֱ����ѡ����һ������������Ϊģ��������������Щ�������з���
����ģ(modulus)Ϊ5,������:35,27,18,33,100,130,214
����������Ľ����:
����0:35 100 130
����1:
����2:27
����3:18 33
����4:214
������������
����v������Ϊn,�洢�������n������
����vv:����Ϊ modulus,����һ����ά����,Ԫ��vv[j]�洢����v��v[i]% modulus����
j������v[i].
����remainder()������v��ÿ��Ԫ��v[i]����modulus,����������ֵ����v[i]��������
vv����ӦԪ���� 
*/

void remainder(vector<int>& v,int modulus,vector<vector<int> >& vv){
	for(vector<int>::const_iterator it=v.begin();it!=v.end();it++){
		int index=(*it)%modulus;
		vv[index].push_back(*it);	//��*it��ӵ�����vv[index]�� 
	}
}

int main(){
 	int modulus,n;
 	cout<<"����ģmodulus:";cin>>modulus;
 	vector<vector<int> > vv(modulus);
 	
 	cout<<"����Ҫ�������������:"; cin>>n;
 	vector<int> v(n);
 	
 	cout<<"������"<<n<<"������:"<<endl;
 	for(int i=0;i<n;i++)
 		cin>>v[i];
 	
 	remainder(v,modulus,vv);
 	
 	for(int i=0;i<modulus;i++){
 		cout<<"����"<<i<<": ";
 		if(vv[i].empty())
 			cout<<endl;
 		else{
 			for(vector<int>::const_iterator it=vv[i].begin();it!=vv[i].end();it++)
 				cout<<*it<<" ";
 			cout<<endl;
 		}
 	}
 	
	
	return 0;
}

#include<iostream>
using namespace std;

/*
	ostream &operator<<(ostream &out,ClassName obj)
	{
		�������� 
		return out;
	}
	istream &operator(istram &in,ClassName& obj)//ע��ڶ��������������������ͣ�������� 
	{
		��������
		return in; 
	}
	����������������������������ĳ�Ա����,һ��Ӧ���䶨��Ϊ���
	��Ԫ����,���⣬��һ������������ostream istream�����ã���Ȼ��������ݲ��ᱻ�͵�Ŀ�괦 
*/
class Student{
	private :
		char name[20];
		char numID[10];
		int score[3];
	public:
		friend ostream& operator<<(ostream &out,Student st);
		friend istream& operator>>(istream &in,Student& st);
}; 
ostream& operator<<(ostream &out,Student st){
	out<<endl<<"ѧ����Ϣ����:"<<endl 
		<<"����:"<<st.name<<endl
		<<"ѧ��:"<<st.numID<<endl
		<<"���ųɼ�:"<<st.score[0]<<" "<<st.score[1]<<" "<<st.score[2]
		<<endl;
		
		return out;
}
istream& operator>>(istream &in,Student& st){
	cout<<"������ѧ����Ϣ:"<<endl;
	cout<<"����:"; in>>st.name;
	cout<<"ѧ��:"; in>>st.numID;
	cout<<"���ųɼ�:"; in>>st.score[0]>>st.score[1]>>st.score[2]; 
	return in;
}
int main4(){
	Student std;
	cin>>std;
	cout<<std; 
	
	return 0;
}

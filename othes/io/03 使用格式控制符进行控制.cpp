#include<iostream>
#include<iomanip>
using namespace std;

/*
Ԥ�����ʽ���Ʒ���Ϊ�������Ͳ����������֣�����������ͷ�ļ�iomanip�У�������������iostream�� 

dec		//ʮ����,���ú�һֱ�����ã�ֱ�����޸�Ϊֹ 
hex 	//ʮ������
oct		//�˽���
ws		//����������ʱ������ͷ�Ŀհ׷�
endl	//����һ�����з���ˢ�������
ends	//����һ�����ַ�,�Խ���һ���ַ���,���������
flush	//������ˢ�������
setbase(int n)//���û���λ(0 8 10 16)Ĭ��Ϊ0(ʮ����)
resetiosflags(long n)//�ر��в���ָ���ĸ�ʽ,������������
setiosflags(long n)//�����в���ָ���ĸ�ʽ��������������
setfill(int c)	//��������ַ�,Ĭ��Ϊ�ո�������������
setprecision(int n)	//����С��λ,Ĭ��Ϊ6Ϊ��������������,������������� 
setw(int n)	//�������������������,ֻ�������һ����������� 
*/

//�Զ����ʽ���Ʒ�,
ostream &myout(ostream out){
	cout.setf(ios::right);
	cout<<setw(10)<<dec<<setfill('#');
	return out;	//���뷵�ز����еĶ��� ,�Ҳ���������һ��ostream���� 
}

int main3(){
	cout<<myout<<123<<endl;
	cout<<123<<setiosflags(ios::scientific)<<setw(15)<<123.456789<<endl;
	cout<<123<<"ʮ������:"<<setw(10)<<hex<<123<<endl;
	cout<<123<<"�˽���:"<<setw(10)<<oct<<123<<endl;
	cout<<123<<"ʮ����:"<<setw(10)<<dec<<123<<endl;
	cout<<resetiosflags(ios::scientific)<<setprecision(4)<<123.456789<<endl;
	cout<<setiosflags(ios::right)<<setfill('#')<<setw(10)<<12345<<endl;
	
	return 0;
}
 


�ɽ�stirng������һ���������䲿�ֲ�������:
(��pos,pos1,pos2, n,n1,n2, ���޷��������� str,str1,str2,��string���Ͷ���,
	istr,ostr�ֱ���istream,ostream����,ch,delim���ַ�,charArray���ַ�����)
1.���캯��:
	string s				����һ���մ�s 
	string s(charArray)		���ַ������ʼ�� 
	string s(charArray,n)	���ַ������ǰn���ַ���ʼ�� 
	string s(str)			�������캯�� 
2.�������:
	getline(istr,s,delim)	��istr�ж�ȡ�ַ�����s,�����ﵽn,�������ļ�β,������delim��ʾ���ַ�ʱ����
	getline(istr,s)			��istr����ȡ�ַ�����s,�������з�����,����ȡ���з���������s��
	istr>>s					��istr����ȡ�ַ�,�����հ�ʱ����,����istr
	ostr<<s					��s����ostr�У�����ostr
3.������
	s=val					��ֵ 
	s+=val					��ӵ�s���� 
	s[pos]					�±���� 
	s+t						����s��t���ӵĽ��,t�����Ǵ����ַ����飬�ַ� 
	<,<=,>,>=,==,!= 		�Ƚ�
4.���
	s.append(str)			��str�����s֮�� 
	s.append(str,pos,n)		��str�д�pos��ʼ��n���ַ���ӵ�s֮�� 
	s.append(charArray)		���ַ�������ӵ�s֮��
5.��ֵ
	s.assign(str)			��str��s��ֵ 
	s.assign(str,pos,n)		��str�д�pos��ʼ��n���ַ���s��ֵ 
	s.assign(charArray) 	���ַ������s��ֵ
6.�󳤶�
	s.size()				��������������ͳ��c����һ'\0'��β���ַ����ĳ��� 
	s.length()
7.�Ƚ�
	s.compare(str) 			����sС�ڣ����ڻ����str,���ظ�����0 ������ 
	s.compare(charArray)	ͬ�� 
	s.compare(pos,n,str)	s�д�pos��n���ַ�ͬstr�Ƚ�
8.����
	s.insert(pos,str)			��pos������str 
	s.insert(pos1,str,pos2,n)	��str�д�pos2��ʼ��n���ַ��������pos1�� 
	s.insert(pos,charArray,n) 	��charArrayǰn���ַ�����pos��
9.�滻
	s.replace(pos1,n1,str)			��str�滻s�д�pos1��ʼ��n���ַ� 
	s.replace(pos1,n1,str,pos2,n2)	��str�д�pos2��ʼ��n2���ַ��滻s�д�pos1��ʼ��n1���ַ� 
	s.replace(pos1,n1,charArray,n2)	��charArray��ǰn���ַ��滻s�д�pos1��ʼ��n1���ַ� 
	s.replace(pos1,n1,n2,ch)		��n2���ַ�ch�滻s�д�pos1��ʼ��n1���ַ�
10.ȡ�Ӵ�
	s.substr(pos,n)			����s�д�pos��ʼ��n���ַ�,posĬ��ֵΪ0,nĬ��ֵΪs�ĳ���
11.�п�
	s.empty() 
12.����
	s.find(str,pos)			��s�д�pos����ʼ����str,�����ҳɹ�����str�״γ��ֵ�λ��,posĬ��ֵΪ0 
	s.find(charArray,pos) 	ͬ�� 
	s.rfind(str,pos)		��s��ǰ(pos+str.size())�в���str,�����ҳɹ��������һ�γ��ֵ�λ��,���򷵻�-1��
	
size_type s.find_first_of(const string& str) const
size_type s.find_first_of(const string& str,size_type idx)const
size_type s.find_first_not_of(const string& str)const
size_type s.find_first_not_of(const string& str,size_type idx)const

size_type s.find_first_of(const char* cstr) const
size_type s.find_first_of(const char* cstr,size_type idx)const
size_type s.find_first_not_of(const char* cstr)const
size_type s.find_first_not_of(const char* cstr,size_type idx)const

size_type s.find_first_of(const char* cstr,size_type idx,size_type str_len)const
size_type s.find_first_not_of(const char* cstr,size_type idx,size_type str_len)const

size_type s.find_first_of(char c) const
size_type s.find_first_of(char c,size_type idx)const
size_type s.find_first_not_of(char c)const
size_type s.find_first_not_of(char c,size_type idx)const
//all those functions have corresponding function : find_last_
	
string��׼��������������string��ת��ΪC�����ַ���:
	s.c_str()	���洢��s�е��ַ�����Ϊ�ַ����鷵��,�����'\0' ��Ϊ������ 
	s.data()	���洢��s�е��ַ�����Ϊ�ַ����鷵��,����ӽ����� '\0' 
	s.copy(charArray,n,pos)	��s�д�pos��ʼ��n���ַ��滻charArray��ǰn���ַ� ,pos��Ĭ��ֵΪ0,���������滻���ַ����� 

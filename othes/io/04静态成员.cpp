#include<iostream>
using std::cout;
using std::cin;
using std::endl;
class Point{
	int x,y;
	int id;
	public:
		static int n;
		Point(int x=0,int y=0){
			this->x=x;
			this->y=y;
			n++;
			id=n;
		}
		Point(Point &p){
			x=p.x;
			y=p.y;
			n++;
			id=n;
		}
		int getId(){
			return id;
		}
	//��̬��Ա�������Է��ʾ�̬��Ա���� 
	static int getN(){
		return n;
	}
	
};
//��̬��Ա�����������������ʼ�� 
int Point::n=0;

int main4(){
	Point p1(1,1);
	Point p2(2,2);
	Point p3(p2);
	
	cout<<"p1.id="<<p1.getId()<<endl; 
	cout<<"p2.id="<<p2.getId()<<endl;
	cout<<"p3.id="<<p3.getId()<<endl; 
	
	cout<<Point::n<<endl;
	
	return 0;
}

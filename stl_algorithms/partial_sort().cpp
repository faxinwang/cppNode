#include"algostuff.hpp"
using namespace std;

/*
	void
	partial_sort(RandomAccessIter beg, RandomAccessIter sortEnd,
				 RandomAccessIter end)
	void
	partial_sort(RandomAccessIter beg, RandomAccessIter sortEnd,
				 RandomAccessIter end, BinaryPredicate op)
	
*/


int main(){
	deque<int> coll;
	INSERT_ELEMENTS(coll,3,7);
	INSERT_ELEMENTS(coll,2,6);
	INSERT_ELEMENTS(coll,1,5);
	PRINT_ELEMENTS(coll);
	
	//sort until the first five elements are sorted
	partial_sort(coll.begin(),
				 coll.begin()+5,
				 coll.end());
	PRINT_ELEMENTS(coll);
	
	//sort inversely until the first five elements are sorted
	partial_sort(coll.begin(),
				 coll.begin()+5,
				 coll.end(),
				 greater<int>());
	PRINT_ELEMENTS(coll);
	
	//sort all elements
	partial_sort(coll.begin(),
				 coll.end(),
				 coll.end());
	PRINT_ELEMENTS(coll);
	
	return 0;
}

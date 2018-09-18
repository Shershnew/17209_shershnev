#include <iostream>
#include "flat_map.h"

int main(){
	Fmap::Flat_map fm, fm2;
	Fmap::Value v1(1),v2(2),v3(3),v4(4),v5(5);
	fm.insert("a1",v1);
	fm.insert("a3",v3);
	fm.insert("a2",v2);
	fm.insert("a5",v5);
	fm.insert("a4",v4);
	try{
		fm.print();
		std::cout << fm["a5"].age << std::endl;
		fm2 = fm;

	}
	catch(const char * str){
		std::cout << str << std::endl;
	}
	return 0;
}
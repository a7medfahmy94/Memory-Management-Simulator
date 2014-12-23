#include <iostream>
#include "Memory.h"
using namespace std;



int main(){
	Memory m;
	cout << (m.addPartition(50)) << endl;
	cout << (m.addPartition(70)) << endl;
	cout << (m.addPartition(120)) << endl;
	cout << (m.addPartition(270)) << endl;
	cout << (m.addPartition(220)) << endl;

	cout << "============\n";

	cout << (m.allocate(1,20)) << endl;
	cout << (m.allocate(2,20)) << endl;
	cout << (m.allocate(3,20)) << endl;

	cout << "============\n";

	m.print();

	cout << "============\n";
	m.defragmentation();
	cout << "============\n";

	m.print();

}

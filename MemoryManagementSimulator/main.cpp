#include <iostream>
#include "Memory.h"
using namespace std;



int main(){

	/*
	 *10 20 20 10
	 *5  7  15
	 *try to take another 30 but fails due to fragmentation
	 *calling defragmentation solves it
	 */
	Memory m;
	cout << (m.addPartition(10)) << endl;
	cout << (m.addPartition(20)) << endl;
	cout << (m.addPartition(20)) << endl;
	cout << (m.addPartition(10)) << endl;

	cout << "============\n";

	cout << (m.allocate(1,5)) << endl;
	cout << (m.allocate(1,7)) << endl;
	cout << (m.allocate(1,15)) << endl;
	cout << (m.allocate(1,30)) << endl;

	cout << "============\n";
	m.defragmentation();
	cout << (m.allocate(1,30)) << endl;

	cout << "============\n";
	m.print();

}
